/*
  ==============================================================================

    WaveletizerComponents.cpp
    Created: 27 Mar 2020 2:23:55pm
    Author:  Nate

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

class SymKnob : public Slider
{
	SymKnob(float min, float max, float step, float defaultValue, int width, int height, String suffix = String())
	{
		setRange(min, max, step);
		setValue(defaultValue);
		setSliderStyle(Slider::Rotary);
		setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
		setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
		setTextValueSuffix(suffix);
		setSize(width, height);
		setName("SymKnob");
	}
};

class AngledKnob : public Slider
{
	AngledKnob(float min, float max, float step, float defaultValue, int width, int height, String suffix=String())
	{
		setRange(min, max, step);
		setValue(defaultValue);
		setSliderStyle(Slider::Rotary);
		setRotaryParameters(MathConstants<float>::pi * 1.3f, MathConstants<float>::pi * 2.7f, true);
		setTextBoxStyle(Slider::TextBoxRight, false, 70, 20);
		setTextValueSuffix(suffix);
		setSize(width, height);
		setName("AngledKnob");
	}
};

class HertzSlider : public Slider
{
	HertzSlider(float defaultValue, int width, int height, String suffix = String())
	{
		setRange(20.0f, 20000.0f, 1.0f);
		setValue(defaultValue);
		setSliderStyle(Slider::LinearVertical);
		setTextValueSuffix(suffix);
		setSize(width, height);
		setName("HertzSlider");
		setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
	}
};

class FilterComponent : public Component
{

};