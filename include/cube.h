#pragma once
#include <iostream>
#include <random>
#include <string>

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_real_distribution<> distr(-5, 5); // define the range


class Cube
{
public:

    float cubeX;
    float cubeY;
    float cubeZ;
    float cubeSizeX;
    float cubeSizeY;
    float cubeSizeZ;  

};



