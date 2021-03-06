# MoDetect

This application will take audio input base-band from any digital RF transmission and automatically detect the transmission mode. Content of the signal is not demodulated or interpreted, only the signal mode, such as CW, PSK31, RTTY, JT-65, etc. will be detected. This will be accomplished by decomposing the audio signal into its FFT signature over time. Then a basic Markov-chain analysis will compare the transition matrix' signature with the typical one for each mode until a match is found. Once frequency deltas & durations are generated (at random for now), a right-stochastic transition matrix shows a normalised count of occurrences of states going from the row-value to the column-value in the sample. A colour-based graph visualises this same information using coloured dots whose value ranges can be calibrated in real time using a slider. 

## Status
The source code is currently implemented using the Qt platform.  I'm currently still working on the Digital Signal Processing portion and it will be uploaded in late April 2018. Meanwhile, the user interface and signal-generation simulator compile and work well as a demo of the concept.

## Next Steps
Generating actual data from digital signal processing (DSP) by performing a fast Fourier transform (FFT) analysis to retrieve frequency information over a real-time audio sample. Then, I will incorporate the actual mechanism that will store transition matrices for each signal type and allow a comparison for signal ID. 

## Environment
I've compiled this using Qt Creator 4.5.1 (Based on Qt 5.10.1) and compiling using MSVC 2015, 64-bits on x86. Even though I haven't yet put much effort on portability at this early stage of the implementation, your comments on any portability issues you encounter are most welcome.

## Language Features, Classes, Techniques

- C++
- Qt Widgets
- Qt Signal/Slot communications
- Qt Widget promotion
- Unconventional User Interface
- Use of STL containers such as std::vector<>, std::map<>
- Use of Placement New memory allocation (rarely used) to allocate a contiguous block of memory for the matrix.
- Real-time programming and example of using the std::chrono STL templates.
- Digital Signal Processing (DSP)


# Installation
 Simply compile all the code in Qt Creator using all files in the same directory.

# License
All the source code in this Repository is original and its licensing is modeled after the MIT License (https://opensource.org/licenses/MIT) 

Copyright 2018 Roger M. Delisle

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
