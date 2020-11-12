#include "../JuceLibraryCode/JuceHeader.h"
#include "DecibelKnobLookAndFeel.h"

DecibelKnobLookAndFeel::DecibelKnobLookAndFeel()
{

};

void DecibelKnobLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto radius = jmin(width / 2, height / 2) - 4.0f; //radius of circle
	auto centreX = x + width * 0.5f; 
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto centerAngle = rotaryStartAngle + .5 * (rotaryEndAngle - rotaryStartAngle);

	// fill
	//g.setColour(Colours::black);
	g.setGradientFill(ColourGradient(Colours::darkslategrey, centreX, centreY, Colours::black, rx, ry, true));
	g.fillEllipse(rx, ry, rw, rw);

	// outline
	g.setColour(Colours::aqua);
	g.drawEllipse(rx, ry, rw, rw, 3.0f);
	//g.setGradientFill(ColourGradient(Colours::darkslategrey, rx, ry, Colours::azure, rx+10.0f, ry+10.0f, false));
	//g.drawEllipse(rx, ry, rw, rw, 3.0f);

	g.setColour(Colours::black);
	g.drawEllipse(rx-3.0f, ry-3.0f, rw + 6.0f, rw + 6.0f, 3.0f);

	//code defining the pointer
	Path p;
	auto pointerLength = radius * 0.33f;
	auto pointerThickness = 2.0f;
	p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
	p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

	// pointer coloring
	g.setColour(Colours::antiquewhite);
	g.fillPath(p);

	//defining the adjusting arc on the slider
	Path s;
	//s.addPieSegment(centreX, ry, radius, radius, 0, angle, 2*radius);
	//s.quadraticTo(x + radius, y, x + radius, y + 2 * radius);
	float radiansMod = std::fmod(angle, 2 * MathConstants<float>::pi);
	//auto leftSliderAngle = std::fmin(radiansMod, MathConstants<float>::pi);
	if (slider.getName() == "AngledKnob")
	{
		//s.addArc(rx, ry, 2 * radius, 2 * radius, MathConstants<float>::pi, std::fmin(angle, centerAngle), true);
		//s.addArc(rx, ry, 2 * radius, 2 * radius, std::fmax(angle, centerAngle), 3 * MathConstants<float>::pi, true);
		s.addArc(rx, ry, 2 * radius, 2 * radius, rotaryEndAngle, angle + 2* MathConstants<float>::pi, true);
	}
	else if (slider.getName() == "SymKnob")
	{
		s.addArc(rx, ry, 2 * radius, 2 * radius, MathConstants<float>::pi, std::fmin(angle, centerAngle), true);
		s.addArc(rx, ry, 2 * radius, 2 * radius, std::fmax(angle, centerAngle), 3 * MathConstants<float>::pi, true);
	}
	else
	{
		s.addArc(rx, ry, 2 * radius, 2 * radius, MathConstants<float>::pi, std::fmin(angle, centerAngle), true);
		s.addArc(rx, ry, 2 * radius, 2 * radius, std::fmax(angle, centerAngle), 3 * MathConstants<float>::pi, true);
	}
	//s.addArc(rx, ry, 2 * radius, 2 * radius, std::fmax(0, angle), MathConstants<float>::pi, true);
	g.setColour(Colours::purple);
	g.strokePath(s, PathStrokeType(3.0f));

	
};
