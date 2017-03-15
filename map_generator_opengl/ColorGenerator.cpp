#include "ColorGenerator.h"
#include <vector>
#include <iostream>



//KONSTRUKTOR DOMYSLNY
ColorGenerator::ColorGenerator()
{
	InitColors();
}


//DESTRKTOR
ColorGenerator::~ColorGenerator()
{
}

//konstrutor kopjujacy
ColorGenerator::ColorGenerator(const ColorGenerator& c_) {
	this->_mapHeight = c_._mapHeight;
	this->_mapWidth = c_._mapWidth;
	this->_distanceBetweenPoint = c_._distanceBetweenPoint;
	this->_widthPoints = c_._widthPoints;
	this->_heightPoints = c_._heightPoints;
	this->_noise = c_._noise;
	for (int i = 0; i < 6; i++) {
		this->_color[i] = c_._color[i];
	}
}

//przeciazony operator =
ColorGenerator& ColorGenerator::operator=(const ColorGenerator& c_) {
	this->_mapHeight = c_._mapHeight;
	this->_mapWidth = c_._mapWidth;
	this->_distanceBetweenPoint = c_._distanceBetweenPoint;
	this->_widthPoints = c_._widthPoints;
	this->_heightPoints = c_._heightPoints;
	this->_noise = c_._noise;
	for (int i = 0; i < 6; i++) {
		this->_color[i] = c_._color[i];
	}
	return *this;
}


//FUNKCJA USTAWIAJACA WARTOSCI
void ColorGenerator::SetValues(const float& mh_, const float& mw_, const float& dbw_, std::vector<float> n_) {
	_mapHeight = mh_;
	_mapWidth = mw_;
	_distanceBetweenPoint = dbw_;
	_noise = n_;
	_widthPoints = GetTotalWidthPoints();
	_heightPoints = GetTotalHeightPoints();
	InitColors();
}


//FUNKCJA ZWRACAJACA VEKTOR KOLORW
std::vector<__Color> ColorGenerator::GetColorVector() {
	std::vector<__Color> temp;
	float noiseHeight = 0.0f;
	int tempX = 0;
	int tempY = 0;
	InitColors();
	
	for (float x = -_mapWidth / 2; x < _mapWidth / 2; x += _distanceBetweenPoint) {
		tempY = 0;
		for (float z = -_mapHeight / 2; z < _mapHeight / 2; z += _distanceBetweenPoint) {
			noiseHeight = _noise[(_widthPoints*tempX) + tempY];
				for(int i =0; i < 6;i++){
					if (noiseHeight <= _color[i]._height) {
						temp.push_back(_color[i]);
						break;
					}
					
				}
				tempY++;
		}
		tempX++;
	}
	return temp;
}


//ZLICZA ILOSC PUNTKOW W OSI Z
unsigned int ColorGenerator::GetTotalHeightPoints()
{
	int temp = 0;
	for (float i = -_mapHeight / 2; i < _mapHeight / 2; i += _distanceBetweenPoint) {
		temp++;
	}
	return temp;
}

//ZLICZA ILOSC PUNTKOW W OSI X
unsigned int ColorGenerator::GetTotalWidthPoints()
{
	int temp = 0;
	for (float i = -_mapWidth / 2; i < _mapWidth / 2; i += _distanceBetweenPoint) {
		temp++;
	}
	return temp;
}


//INICIALIZACJA KOLOROW
void ColorGenerator::InitColors(){
	_color[0]._height = 1.8f;
	_color[0]._values[0] = 0;
	_color[0]._values[1] = 102;
	_color[0]._values[2] = 204;

	_color[1]._height = 1.9f;
	_color[1]._values[0] = 255;
	_color[1]._values[1] = 255;
	_color[1]._values[2] = 102;

	_color[2]._height = 2.2f;
	_color[2]._values[0] = 76;
	_color[2]._values[1] = 153;
	_color[2]._values[2] = 0;

	_color[3]._height = 2.3f;
	_color[3]._values[0] = 128;
	_color[3]._values[1] = 89;
	_color[3]._values[2] = 59;

	_color[4]._height = 2.5f;
	_color[4]._values[0] = 102;
	_color[4]._values[1] = 70;
	_color[4]._values[2] = 46;

	_color[5]._height = 6.0f;
	_color[5]._values[0] = 243;
	_color[5]._values[1] = 243;
	_color[5]._values[2] = 243;
}