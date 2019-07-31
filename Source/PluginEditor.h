#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "DecibelKnobLookAndFeel.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

class WaveletizerAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, public ComboBox::Listener
{
public:
    WaveletizerAudioProcessorEditor(WaveletizerAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~WaveletizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider * slider) override;
	void comboBoxChanged(ComboBox * comboBox) override;
	
private:
	void fillComboBox(ComboBox * comboBox);
    WaveletizerAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	ScopedPointer<Slider> coarseKnob;
	ScopedPointer<SliderAttachment> coarseKnobAttachment;
	ScopedPointer<Slider> detailKnob;
	ScopedPointer<SliderAttachment> detailKnobAttachment;
	ScopedPointer<Slider> mixKnob;
	ScopedPointer<SliderAttachment> mixKnobAttachment;
	ScopedPointer<Slider> outputGainKnob;
	ScopedPointer<SliderAttachment> outputGainKnobAttachment;
	ScopedPointer<ComboBox> waveletComboBox;
	ScopedPointer<ComboBoxAttachment> waveletComboBoxAttachment;
	ScopedPointer<ComboBox> levelComboBox;
	ScopedPointer<ComboBoxAttachment> levelComboBoxAttachment;
	ScopedPointer<Label> bodyLabel;
	ScopedPointer<Label> detailLabel;
	ScopedPointer<Label> mixLabel;
	ScopedPointer<Label> outputGainLabel;
	ScopedPointer<Label> waveletComboBoxLabel;
	ScopedPointer<Label> levelComboBoxLabel;
	DecibelKnobLookAndFeel decibelKnobLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveletizerAudioProcessorEditor)
};
