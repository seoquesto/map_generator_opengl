#include "MakeNoise.h"
#include <vector>
#include "MyNoise.h"
#include <iostream>



//KONSTRUKOR DOMYSLNY
MakeNoise::MakeNoise()
{
}


//DESTRUKTOR
MakeNoise::~MakeNoise()
{
	if (mn != 0)
		delete mn;
}

//ZWARCA ZAAKTUALIZOWANY VEKTOR WSPOLZEDNYCH DLA OSI Y
std::vector<float> MakeNoise::UpdateNoise(const float &width_, const float &height_, const float &distanceBetweenPoint, const float &scale_, float octaves, float persistance, float lacunarity, float offset[]) {
	std::vector<float> nois;
	if (mn == 0) return nois;
	float s_ = scale_;

	if (s_ <= 0.01f) s_ = 0.01f;


	for (float x = -width_ / 2; x <width_ / 2; x += distanceBetweenPoint) {
		for (float y = -height_ / 2; y < height_ / 2; y += distanceBetweenPoint) {


			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0;

			for (int i = 0; i<octaves; i++) {
				float tempY = y / scale_* frequency+offset[1];
				float tempX = x / scale_ * frequency+offset[0];
				float n_ = mn->noise(tempX * 10, tempY * 10, 1.0f);

				noiseHeight += n_*amplitude;
				amplitude += persistance;
				frequency += lacunarity;
			}

			nois.push_back(noiseHeight);
		}
	}

	return nois;
}



//GENERUJE NOWY VEKTOR DLA OSI WSPOLZEDNYCH Y
std::vector<float> MakeNoise::GenerateNoise(const float &width_, const float &height_, const float &distanceBetweenPoint, const float &scale_, bool random, float octaves, float persistance, float lacunarity, float offset[]) {
	std::vector<float> nois;
	float s_ = scale_;
	if (mn != 0) delete mn;
	
	if(random) mn = new MyNoise(true);
	else mn = new MyNoise();

	if (s_ <= 0.01f) s_ = 0.01f;

	
	for (float x = -width_ / 2; x <width_ / 2; x += distanceBetweenPoint) {
		for (float y = -height_ / 2; y < height_ / 2; y += distanceBetweenPoint) {
			

			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0;
			
			for(int i =0;i<octaves;i++){
				float tempY = y/ scale_* frequency+offset[1];
				float tempX = x / scale_ * frequency+offset[2];
				float n_ = mn->noise(tempX*10, tempY*10,1.0f);

				noiseHeight += n_*amplitude;
				amplitude += persistance;
				frequency += lacunarity;
			}

			nois.push_back(noiseHeight);
		}
	}

	return nois;

}