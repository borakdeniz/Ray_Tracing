#pragma once

namespace Random
{
	//Gets current seed
	int GetSeed();

	//Sets current seed
	void SetSeed(const int& iSeed);

	//Gets maximum allowed integers
	int RandMax();

	//Random integer number generator
	int RandInt();
	int RandRange(const int& iMin, const int& iMax);

	//Random float number generator from 0.0f to 1.0f
	float RandFloat();

	//Random float number generator from interval [x0, 1x]
	float RandRange(const float& fX0, const float& fX1);

}