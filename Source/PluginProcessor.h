#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
extern "C" {
#include "KissFFT/kiss_fft.h"
}
extern "C" {
#include "KissFFT/tools/kiss_fftr.h"
}
#include "DWTResult.h"
//==============================================================================
/**
*/
class WaveletizerAudioProcessor  : public AudioProcessor
{
public:
    WaveletizerAudioProcessor();
    ~WaveletizerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
	AudioProcessorValueTreeState parameters;
	std::vector<kiss_fft_scalar> realBufferFFT;
	std::vector<kiss_fft_cpx> complexBufferFFT;
	DWTResult dwtResult;
	float * coarse;
	float * detail;
	float * mixParameter;
	float * outputGain;
	float * level;
	float * waveletFilterFloat;
	int oldSamplesPerBlock{ 0 };
	kiss_fftr_cfg cfgFFT;
	kiss_fftr_cfg cfgIFFT;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveletizerAudioProcessor)
};