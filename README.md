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

Connection between LED Matrix and ESP32 GPIO should be the following.　　
R1 IO18　　
G1 IO21　　
B1 IO23　　
R2 IO26  
G2 IO25  
B2 IO17  
CLK IO27  
A IO14  
B IO16  
C IO4  
D IO13  
LAT IO32  
OE(negative) IO33  

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

# References
It uses 'Shinonome font'　http://openlab.ring.gr.jp/efont/shinonome/

# Note
'Akihabara Technical Report Vol.1'　is a coterie magazine by circle 'Akibayome'. https://techbookfest.org/event/tbf05/circle/27750004
