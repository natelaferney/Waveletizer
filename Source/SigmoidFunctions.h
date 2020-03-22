/*
  ==============================================================================

    SidgmoidFunctions.h
    Created: 4 Oct 2019 1:20:40pm
    Author:  nate

  ==============================================================================
*/

#pragma once
#include<cmath>
using namespace std;
static const float pi = 3.141592653589793;

namespace SigmoidFunctions 
{
    inline float logistic(float x)
    {
        return 1/(1 + exp(-1*x));
    };
    
    inline float hyperbolicTangent(float x)
    {
        return tanh(x);
    };
    
    inline float algebraic(float x)
    {
        return x / (sqrt(1 + pow(x, 2)));
    };
    
    inline float leslieClipper(float x)
    {
        return (x - .5)/x;
    };
    
    inline float arcTangent(float x)
    {
        return (2.0f / pi) * atan(pi * x / 2.0f);
    };

	inline float fastClip(float x)
	{
		return x / (1 + abs(x));
	};
};

