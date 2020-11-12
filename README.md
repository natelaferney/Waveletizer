This repository contains the source code for the plugin I built which I've codenamed the Waveletizer.
This is a VST3 64-bit plugin and is compatible with both Windows and iOS 10 and was built using the JUCE framework.

This plugin works by applying a Wavelet Transform to the audio signal's spectrum magnitude. The plugin provides a Body
and Detail Gain Control to apply gain to the Coarse and Detail bands of the Wavelet Transformed signal. The plugin provides
10 different Wavelet Filters varying in lengths from 2 to 8 which include classics such as the Haar and Daubechies filters.
There is also a level control to provide multiple levels of Wavelet decomposition. All the Detail coefficients from all
the levels of decomposition are placed in a single band though the code is capable of manipulating the detail coefficients
at a single band only. The signal is then passed through a soft clipper module with 5 different curve shapes. 
An output gain and dry/wet control are also provided at the end of the chain for more control of the signal.

The code relies on the [KissFFT library](https://github.com/mborgerding/kissfft)

This software is licensed under GPL Version 3