#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../JuceLibraryCode/JuceHeader.h"
extern "C" {
#include "KissFFT/kiss_fft.h"
}
extern "C" {
#include "KissFFT/tools/kiss_fftr.h"
}
#include <complex>

static const int MINIMUM_BUFFER_SIZE = 32;
static const float BUFFER_OFFSET_FACTOR = 1.5;
static const StringArray waveletFilterCollection = { "Haard", "Doe Bah Shee 4", "Nail Bat", "Gaussian", "Doe Bah Shee 6",
"Coif", "Sym", "Bior1", "Bior2", "Bior3"};

static const StringArray levelChoices = { "1", "2", "3", "4" };
//==============================================================================
WaveletizerAudioProcessor::WaveletizerAudioProcessor() :
	parameters(*this, nullptr, Identifier("Waveletizer"),
		{
			std::make_unique<AudioParameterFloat>
			("coarse", "Coarse", NormalisableRange<float>(-20.0f, 20.0f, 0.1f), 0.0f),
			std::make_unique<AudioParameterFloat>
			("detail", "Detail", NormalisableRange<float>(-20.0f, 20.0f, 0.1f), 0.0f),
			std::make_unique<AudioParameterFloat>
			("outputGain", "Output Gain", NormalisableRange<float>(-20.0f, 20.0f, 0.1f), 0.0f),
			std::make_unique<AudioParameterFloat>
			("mix", "Mix", NormalisableRange<float>(0.0f, 100.0f, 0.1f), 100.0f),
			std::make_unique<AudioParameterInt>
			("level", "Level", 1, 4, 1),
			std::make_unique<AudioParameterChoice>
			("waveletFilter", "Wavelet Filter", waveletFilterCollection, 0)
	}),
#ifndef JucePlugin_PreferredChannelConfigurations
	AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	coarse = parameters.getRawParameterValue("coarse");
	detail = parameters.getRawParameterValue("detail");
	mixParameter = parameters.getRawParameterValue("mix");
	outputGain = parameters.getRawParameterValue("outputGain");
	level = parameters.getRawParameterValue("level");
	waveletFilterFloat = parameters.getRawParameterValue("waveletFilter");
	cfgFFT = NULL;
	cfgIFFT = NULL;
}

WaveletizerAudioProcessor::~WaveletizerAudioProcessor()
{
	kiss_fftr_free(cfgFFT);
	kiss_fftr_free(cfgIFFT);
	cfgFFT = NULL;
	cfgIFFT = NULL;
}

//==============================================================================
const String WaveletizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaveletizerAudioProcessor::acceptsMidi() const
{
    return false;
}

bool WaveletizerAudioProcessor::producesMidi() const
{
    return false;
}

bool WaveletizerAudioProcessor::isMidiEffect() const
{
    return false;
}

double WaveletizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaveletizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaveletizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaveletizerAudioProcessor::setCurrentProgram (int index)
{
}

const String WaveletizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaveletizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WaveletizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	int N = (int)((BUFFER_OFFSET_FACTOR * samplesPerBlock) + .5);
	if (N <= MINIMUM_BUFFER_SIZE) N = MINIMUM_BUFFER_SIZE;
	if (N % 2 == 1) N += 1;
	int K = N / 2 + 1;
	dwtResult.reserveBuffer(N);
	realBufferFFT.resize(N, 0.0f);
	complexBufferFFT.resize(K);
	if (K % 2 == 0) dwtResult.result.resize(K, 0.0f);
	else dwtResult.result.resize(K + 1, 0.0f);
	cfgFFT = kiss_fftr_alloc(N, 0, NULL, NULL);
	cfgIFFT = kiss_fftr_alloc(N, 1, NULL, NULL);
	oldSamplesPerBlock = N;
	const int currentWaveletChoiceIndex = (int)*waveletFilterFloat;
	const std::string currentWaveletChoice = waveletFilterCollection[currentWaveletChoiceIndex].toStdString();
	if (currentWaveletChoice != dwtResult.getCurrentFilter()) dwtResult.updateFilter(currentWaveletChoice);
}

void WaveletizerAudioProcessor::releaseResources()
{
	if (cfgFFT != NULL)
	{
		free(cfgFFT);
		cfgFFT = NULL;
	}
	if (cfgIFFT != NULL)
	{
		free(cfgIFFT);
		cfgIFFT = NULL;
	}

	std::fill(realBufferFFT.begin(), realBufferFFT.end(), 0.0f);
	for (auto e : complexBufferFFT)
	{
		e.r = 0.0f;
		e.i = 0.0f;
	}
	std::fill(dwtResult.result.begin(), dwtResult.result.end(), 0.0f);
}

bool WaveletizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;
	else return true;
}

void WaveletizerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
	int bufferSize = buffer.getNumSamples();
	int N = oldSamplesPerBlock;
	int K = N / 2 + 1;
	std::complex<float> temp;
	const int currentWaveletChoiceIndex = (int)*waveletFilterFloat;
	const std::string currentWaveletChoice = waveletFilterCollection[currentWaveletChoiceIndex].toStdString();
	const int waveletLevel = (int)*level;
	const float coarseGain = Decibels::decibelsToGain(*coarse);
	const float detailGain = Decibels::decibelsToGain(*detail);
	const float outputGainDb = Decibels::decibelsToGain(*outputGain);
	const float mixValue = *mixParameter / 100;
	float newSampleValue;

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
	
	std::fill(realBufferFFT.begin(), realBufferFFT.end(), 0.0f);


	//hopefully this switch always goes to default
	bool needsReallocation = (N < bufferSize);
	switch (needsReallocation)
	{
	case true:
		N = (int)((BUFFER_OFFSET_FACTOR * bufferSize) + .5);
		if (N <= MINIMUM_BUFFER_SIZE) N = MINIMUM_BUFFER_SIZE;
		if (N % 2 == 1) N += 1;
		K = N / 2 + 1;
		dwtResult.reserveBuffer(N);
		realBufferFFT.resize(N, 0.0f);
		complexBufferFFT.resize(K);
		if (K % 2 == 0) dwtResult.result.resize(K, 0.0f);
		else dwtResult.result.resize(K + 1, 0.0f);
		free(cfgFFT);
		free(cfgIFFT);
		cfgFFT = kiss_fftr_alloc(N, 0, NULL, NULL);
		cfgIFFT = kiss_fftr_alloc(N, 1, NULL, NULL);
		oldSamplesPerBlock = N;
		break;
	default:
		break;
	}

	//update the filters if needed
	bool updateFilter = (currentWaveletChoice != dwtResult.getCurrentFilter());
	switch (updateFilter)
	{
	case true:
		dwtResult.updateFilter(currentWaveletChoice);
		break;
	default:
		break;
	}

	//process each channel
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		for (int i=0; i < bufferSize; ++i) realBufferFFT[i] = buffer.getSample(channel, i);
		kiss_fftr(cfgFFT, &realBufferFFT[0], &complexBufferFFT[0]);
		for (int i = 0; i < K; ++i) dwtResult.result[i] = std::sqrt(std::pow(std::abs(complexBufferFFT[i].r), 2) + std::pow(std::abs(complexBufferFFT[i].i), 2));
		bool isKEven = ((K % 2) == 0);
		switch (isKEven)
		{
		case false:
			dwtResult.result[K] = 0.0f;
			break;
		default:
			break;
		}
		dwtResult.dwt(waveletLevel);
		dwtResult.applyGain(coarseGain, detailGain, waveletLevel);
		dwtResult.idwt(waveletLevel);
		for (int i = 0; i < K; ++i)
		{
            temp = std::polar((dwtResult.result[i] < 0) ? 0.0f : dwtResult.result[i], atan2(complexBufferFFT[i].i, complexBufferFFT[i].r));
			complexBufferFFT[i].r = std::real(temp) / N;
			complexBufferFFT[i].i = std::imag(temp) / N;
		}
		
		kiss_fftri(cfgIFFT, &complexBufferFFT[0], &realBufferFFT[0]);
		//apply output gain
		std::transform(realBufferFFT.begin(), realBufferFFT.end(), realBufferFFT.begin(), [outputGainDb](auto& c) {return c * outputGainDb; });
		for (int i = 0; i < bufferSize; ++i)
		{
			newSampleValue = (mixValue * realBufferFFT[i]) + ((1.0 - mixValue) * buffer.getSample(channel, i));
			buffer.setSample(channel, i, newSampleValue);
		}
    }
}

//==============================================================================
bool WaveletizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WaveletizerAudioProcessor::createEditor()
{
    return new WaveletizerAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void WaveletizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	XmlElement * xml = new XmlElement("Waveletizer");
	xml->setAttribute(Identifier("coarseParameter"), (double)parameters.getParameter("coarse")->convertTo0to1(*coarse));
	xml->setAttribute(Identifier("detailParameter"), (double)parameters.getParameter("detail")->convertTo0to1(*detail));
	xml->setAttribute(Identifier("mixParameter"), (double)parameters.getParameter("mix")->convertTo0to1(*mixParameter));
	xml->setAttribute(Identifier("outputGainParameter"), (double)parameters.getParameter("outputGain")->convertTo0to1(*outputGain));
	xml->setAttribute(Identifier("waveletFilterType"), (double)parameters.getParameter("waveletFilter")->convertTo0to1(*waveletFilterFloat));
	xml->setAttribute(Identifier("levelType"), (double)parameters.getParameter("level")->convertTo0to1(*level));
	copyXmlToBinary(*xml, destData);
	delete xml;
}

void WaveletizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState != nullptr)
	{
		const float coarseValue = (float)xmlState->getDoubleAttribute("coarseParameter", 0.0f);
		const float detailValue = (float)xmlState->getDoubleAttribute("detailParameter", 0.0f);
		const float mixValue = (float)xmlState->getDoubleAttribute("mixParameter", 1.0f);
		const float outputGainValue = (float)xmlState->getDoubleAttribute("outputGainParameter", 0.0f);
		const float waveletTypeValue = (float)xmlState->getDoubleAttribute("waveletFilterType", 0.0f);
		const float levelValue = (float)xmlState->getDoubleAttribute("levelType", 0.0f);
	
		parameters.getParameter("coarse")->beginChangeGesture();
		parameters.getParameter("detail")->beginChangeGesture();
		parameters.getParameter("mix")->beginChangeGesture();
		parameters.getParameter("outputGain")->beginChangeGesture();
		parameters.getParameter("waveletFilter")->beginChangeGesture();
		parameters.getParameter("level")->beginChangeGesture();

		parameters.getParameter("coarse")->setValueNotifyingHost(coarseValue);
		parameters.getParameter("detail")->setValueNotifyingHost(detailValue);
		parameters.getParameter("mix")->setValueNotifyingHost(mixValue);
		parameters.getParameter("outputGain")->setValueNotifyingHost(outputGainValue);
		parameters.getParameter("waveletFilter")->setValueNotifyingHost(waveletTypeValue);
		parameters.getParameter("level")->setValueNotifyingHost(levelValue);

		parameters.getParameter("coarse")->endChangeGesture();
		parameters.getParameter("detail")->endChangeGesture();
		parameters.getParameter("mix")->endChangeGesture();
		parameters.getParameter("outputGain")->endChangeGesture();
		parameters.getParameter("waveletFilter")->endChangeGesture();
		parameters.getParameter("level")->endChangeGesture();
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaveletizerAudioProcessor();
}
