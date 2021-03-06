
#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
WaveletizerAudioProcessorEditor::WaveletizerAudioProcessorEditor (WaveletizerAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    setSize (475, 650);
	setLookAndFeel(&decibelKnobLookAndFeel);

	//body knob
	addAndMakeVisible(coarseKnob = new Slider());
	coarseKnob->setRange(-20.0f, 20.0f, 0.1f);
	coarseKnob->setValue(0);
	coarseKnob->setPopupMenuEnabled(false);
	coarseKnob->setSliderStyle(Slider::Rotary);
	coarseKnob->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	coarseKnob->setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
	coarseKnob->setTextValueSuffix(" dB");
	coarseKnob->setBounds(25, 50, 200, 200);
	coarseKnob->addListener(this);
	coarseKnobAttachment.reset(new SliderAttachment(valueTreeState, "coarse", *coarseKnob));
	addAndMakeVisible(bodyLabel = new Label());
	bodyLabel->setBounds(125, 25, 150, 50);
	bodyLabel->setText("Body Gain", dontSendNotification);

	//detail knob
	addAndMakeVisible(detailKnob = new Slider());
	detailKnob->setRange(-20.0f, 20.0f, 0.1f);
	detailKnob->setValue(0);
	detailKnob->setPopupMenuEnabled(false);
	detailKnob->setSliderStyle(Slider::Rotary);
	detailKnob->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	detailKnob->setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
	detailKnob->setTextValueSuffix(" dB");
	detailKnob->setBounds(25, 250, 200, 200);
	detailKnob->addListener(this);
	detailKnobAttachment.reset(new SliderAttachment(valueTreeState, "detail", *detailKnob));
	addAndMakeVisible(detailLabel = new Label());
	detailLabel->setBounds(125, 225, 150, 50);
	detailLabel->setText("Detail Gain", dontSendNotification);

	//input gain knob
	addAndMakeVisible(inputGainKnob = new Slider());
	inputGainKnob->setRange(-20.0f, 20.0f, 0.1f);
	inputGainKnob->setValue(0);
	inputGainKnob->setPopupMenuEnabled(false);
	inputGainKnob->setSliderStyle(Slider::Rotary);
	inputGainKnob->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	inputGainKnob->setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
	inputGainKnob->setTextValueSuffix(" dB");
	inputGainKnob->setBounds(25, 450,200, 200);
	inputGainKnob->addListener(this);
	inputGainKnobAttachment.reset(new SliderAttachment(valueTreeState, "inputGain", *inputGainKnob));
	addAndMakeVisible(inputGainLabel = new Label());
	inputGainLabel->setBounds(125, 425, 150, 50);
	inputGainLabel->setText("Input Gain", dontSendNotification);

	//output gain knob

	addAndMakeVisible(outputGainKnob = new Slider());
	outputGainKnob->setRange(-20.0f, 20.0f, 0.1f);
	outputGainKnob->setValue(0);
	outputGainKnob->setPopupMenuEnabled(false);
	outputGainKnob->setSliderStyle(Slider::Rotary);
	outputGainKnob->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	outputGainKnob->setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
	outputGainKnob->setTextValueSuffix(" dB");
	outputGainKnob->setBounds(250, 250, 200, 200);
	outputGainKnob->addListener(this);
	outputGainKnobAttachment.reset(new SliderAttachment(valueTreeState, "outputGain", *outputGainKnob));
	addAndMakeVisible(outputGainLabel = new Label());
	outputGainLabel->setBounds(350, 225, 150, 50);
	outputGainLabel->setText("Output Gain", dontSendNotification);


	//mix knob
	addAndMakeVisible(mixKnob = new Slider());
	mixKnob->setRange(0.0f, 100.0f, 0.1f);
	mixKnob->setValue(0);
	mixKnob->setPopupMenuEnabled(false);
	mixKnob->setSliderStyle(Slider::Rotary);
	mixKnob->setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
	mixKnob->setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
	mixKnob->setNumDecimalPlacesToDisplay(1);
	//mixKnob->setTextValueSuffix("Mix");
	mixKnob->setBounds(250, 450, 200, 200);
	mixKnob->addListener(this);
	mixKnob->setComponentID("mixKnob");
	mixKnobAttachment.reset(new SliderAttachment(valueTreeState, "mix", *mixKnob));
	addAndMakeVisible(mixLabel = new Label());
	mixLabel->setBounds(350, 425, 150, 50);
	mixLabel->setText("Mix", dontSendNotification);
	
	//wavelet combo box 
	addAndMakeVisible(waveletComboBox = new ComboBox());
	fillComboBox(waveletComboBox);
	waveletComboBox->setBounds(250, 60, 150, 30);
	waveletComboBox->addListener(this);
	waveletComboBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, "waveletFilter", *waveletComboBox));
	addAndMakeVisible(waveletComboBoxLabel = new Label());
	waveletComboBoxLabel->setBounds(250, 20, 100, 50);
	waveletComboBoxLabel->setText("Filter", dontSendNotification);

	//level combo box
	addAndMakeVisible(levelComboBox = new ComboBox());
	levelComboBox->setBounds(250, 130, 50, 30);
	levelComboBox->addListener(this);
	const StringArray levelChoices = { "1", "2", "3", "4" };
	for (int i = 0; i < levelChoices.size(); ++i)
	{
		levelComboBox->addItem(levelChoices[i], i+1);
	}
	levelComboBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, "level", *levelComboBox));
	addAndMakeVisible(levelComboBoxLabel = new Label());
	levelComboBoxLabel->setBounds(250, 90, 100, 50);
	levelComboBoxLabel->setText("Level", dontSendNotification);

	//soft clipper combo box
	addAndMakeVisible(softClipperComboBox = new ComboBox());
	softClipperComboBox->setBounds(250, 200, 150, 30);
	softClipperComboBox->addListener(this);
	const StringArray softClipperChoices = { "None", "Hyperbolic Tangent", "Algebraic", "Arc Tangent", "Fast Clipper" };
	for (int i = 0; i < softClipperChoices.size(); ++i)
	{
		softClipperComboBox->addItem(softClipperChoices[i], i+1);
	}
	softClipperComboBoxAttachment.reset(new ComboBoxAttachment(valueTreeState, "softClipper", *softClipperComboBox));
	addAndMakeVisible(softClipperComboBoxLabel = new Label());
	softClipperComboBoxLabel->setBounds(250, 160, 100, 50);
	softClipperComboBoxLabel->setText("Soft Clipper", dontSendNotification);
}

WaveletizerAudioProcessorEditor::~WaveletizerAudioProcessorEditor()
{
	setLookAndFeel(nullptr);
}

void WaveletizerAudioProcessorEditor::fillComboBox(ComboBox * comboBox)
{
	comboBox->addSectionHeading("Length 2");
	comboBox->addItem("Haard", 1);
	comboBox->addSeparator();
	comboBox->addSectionHeading("Length 4");
	comboBox->addItem("Doe Bah Shee 4", 2);
	comboBox->addItem("Nail Bat", 3);
	comboBox->addItem("Gaussian", 4);
	comboBox->addSeparator();
	comboBox->addSectionHeading("Length 6");
	comboBox->addItem("Doe Bah Shee 6", 5);
	comboBox->addItem("Coif", 6);
	comboBox->addItem("Sym", 7);
	comboBox->addSeparator();
	comboBox->addSectionHeading("Length 8");
	comboBox->addItem("Bior1", 8);
	comboBox->addItem("Bior2", 9);
	comboBox->addItem("Bior3", 10);
}

//==============================================================================
void WaveletizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void WaveletizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void WaveletizerAudioProcessorEditor::sliderValueChanged(Slider * slider)
{
}

void WaveletizerAudioProcessorEditor::comboBoxChanged(ComboBox * comboBox)
{

}
