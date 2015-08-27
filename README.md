#Matgclib
Matlab bindings for [gclib](http://www.galilmc.com/downloads/api) to send commands to Galil motion controllers using MATLAB.

## Configuration
Open `move.m` and `rotate.m` and set the ip address of the motor controller and the mechanical specifications of the encoders

## Compiling for 64-bit MATLAB
1. Download Cygwin and add the 64bit MinGW compiler and make utility
2. Open `Makefile` and set the MATLAB root directory and compiler (if required)
3. Type `make`

## Usage
Move the contents of the `bin` directory anywhere on the MATLAB path and use `move(axis, speed, displacement, 'block')` and `rotate(degrees_per_second, degrees, 'block')`.