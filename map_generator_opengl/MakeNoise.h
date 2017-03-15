#pragma once
#include <vector>
#include "MyNoise.h"
class MakeNoise
{
private:
	//wskaznik na klasie liczaca wartoisc w osi y
	MyNoise* mn;
public:

	//konstruktor
	MakeNoise();

	//destruktor
	~MakeNoise();

	//funkcja zwracajaca vektor wspolzednych osi y
	std::vector<float> GenerateNoise(const float &width_, const float &height_, const float &distanceBetweenPoint, const float &scale_, bool random, float octaves, float persistance, float lacunarity, float offset[]);
	
	//funkcja aktualizujaca vektor osi y
	std::vector<float> UpdateNoise(const float &width_, const float &height_, const float &distanceBetweenPoint, const float &scale_, float octaves, float persistance, float lacunarity,float offset[]);
};

