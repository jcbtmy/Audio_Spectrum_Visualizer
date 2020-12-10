# Audio Spectrum Visualizer
OpenGL and FFTW Audio Spectrum Visualizer
written in C++. This program takes in an audio file and computes the Discrete Fourier Transform against the sample rate and outputs the frequencies to a colored sphere. The frequencies are distributed across the stacks of the sphere. The max frequency of the each bin where bin=frequencies/stacks is the value by which each stack is scaled.

## Usage

### make 
	cmake .
	make

### run 
	./Graphics <audio file>

## Library Dependencies
	* libav
	* libao
	* fftw
	* OpenGL
	* glfw
