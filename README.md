# akibatech01
Source Code written in 'Akihabara Technical Report Vol.1'

# Description
It is sample for 'P3 SMD' LED Matrix.
GPIO in ESP32 displays numeric character on the matrix using HUB75 interface.
It is configured for 128x32 LED Matrix.
If your LED Matrix is 64x32, use 2 cascadable　Matrices.

# Dependency
ESP-WROOM-32(ESP32)
ESP-IDF v3.1

# Setup
Copy esp-idf\examples\peripherals\gpio to msys32\home\(your home directory)\gpio
Replace main\gpio_example_main.c
Execute 'make menuconfig' to assign virtual COM port to write program
Execute 'make flash' to compile, link and program into ESP32

# Usage
Power on ESP32

# Licence
This software is released under the MIT License, see LICENSE.

# Authors
cn_hibari at circle 'Akibayome'
akibayome@khh.biglobe.ne.jp

# Note
'Akihabara Technical Report Vol.1'　is a coterie magazine by circle 'Akibayome'.
