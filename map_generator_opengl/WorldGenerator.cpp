#include "WorldGenerator.h"
#include <windows.h>
#include <vector>

#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/freeglut.h>
#include <iostream>

#include "MakeNoise.h"

//KONSTRUKTOR DOMYSLNY
WorldGenerator::WorldGenerator():
	_mapWidth(5.0f),
	_mapHeight(5.0f),
	_distanceBetweenPoint(0.01f),
	_noiseReduceScale(20.0f), 
	_widthPoints(0)
	,_heightPoints(0),
	hexTypeOfBuild(0x0004),
	_octaves(4.0f),
	_persistance(0.01f),
	_lacunarity(0.7f)
{
	offset[0] = offset[1]=0.0f;
	_widthPoints = GetTotalWidthPoints();
	_heightPoints = GetTotalHeightPoints();
	GenerateNewMap();
	colorGenerator.SetValues(_mapHeight, _mapWidth, _distanceBetweenPoint, noiseResult);
	colorsMap = colorGenerator.GetColorVector();
}

//KONSTRUKTOR INICIALIZUJACY
WorldGenerator::WorldGenerator(const float& mw_, const float& mh_, const float& dbp_, const float& nrs_, const bool& r_, BuilderWith bw, const float& o_, const float& p_, const float& l_)
	:_mapWidth(mw_), 
	_mapHeight(mh_), 
	_distanceBetweenPoint(dbp_),
	_noiseReduceScale(nrs_),
	_random(r_),
	_widthPoints(0), 
	_heightPoints(0),
	_octaves(o_),
	_persistance(p_),
	_lacunarity(l_)
{				

	offset[0] = offset[1] = 0.0f;
	MapBuilderWith(bw);
	_widthPoints = GetTotalWidthPoints();
	_heightPoints = GetTotalHeightPoints();
	GenerateNewMap();  
}	
						
//DESTRUKTOR
WorldGenerator::~WorldGenerator()
{
}

//GENEROWANIE NOWEJ MAPY
void WorldGenerator::GenerateNewMap() {
	_widthPoints = GetTotalWidthPoints();
	_heightPoints = GetTotalHeightPoints();
	std::cout << "persis: " << _persistance << std::endl;
	noiseResult = makeNoise.GenerateNoise(_mapWidth, _mapHeight, _distanceBetweenPoint, _noiseReduceScale, _random, _octaves, _persistance, _lacunarity,offset);
	colorGenerator.SetValues(_mapHeight, _mapWidth, _distanceBetweenPoint, noiseResult);
	colorsMap = colorGenerator.GetColorVector();
}

//AKTUALIZACJA MAPY
void WorldGenerator::UpdateMap() {
	noiseResult=makeNoise.UpdateNoise(_mapWidth, _mapHeight, _distanceBetweenPoint, _noiseReduceScale, _octaves, _persistance, _lacunarity,offset);
	colorGenerator.SetValues(_mapHeight, _mapWidth, _distanceBetweenPoint, noiseResult);
	colorsMap = colorGenerator.GetColorVector();
	GenerateWorld();
}																											


//SPOSOB LACZENIA PUNKTOW / WYSIWETLANIA MAPY 
void WorldGenerator::MapBuilderWith(BuilderWith bw_) {
	switch (bw_)
	{
	case points:
		hexTypeOfBuild = 0x0000;
		break;
	case lines:
		hexTypeOfBuild = 0x0001;
		break;
	case triangles:
		hexTypeOfBuild = 0x0004;
		break;
	default:  
		hexTypeOfBuild = 0x0001;
		break;
	}
}


//FUNKCJA GENERUJE MAPE
void WorldGenerator::GenerateWorld() {
	CheckValues();
	unsigned int tempX, tempY, kk;
	tempX = 0; tempY = 0; kk = 0; 
	
	glBegin(hexTypeOfBuild);
	for (float x = -_mapWidth / 2; x < _mapWidth / 2; x += _distanceBetweenPoint) {
		tempY = 0;
		if (tempX == _heightPoints - 2) break;
		for (float z = -_mapHeight / 2; z < _mapHeight / 2; z += _distanceBetweenPoint) {  			
			glColor3f((float)colorsMap[(_widthPoints*tempX) + tempY]._values[0] / 255, (float)colorsMap[(_widthPoints*tempX) + tempY]._values[1] / 255, (float)colorsMap[(_widthPoints*tempX) + tempY]._values[2] / 255);
			glVertex3d(x, noiseResult[(_widthPoints*tempX) + tempY], z);
			glVertex3d(x + _distanceBetweenPoint, noiseResult[(_widthPoints*(tempX + 1)) + tempY], z);	  			
			glVertex3d(x + _distanceBetweenPoint, noiseResult[(_widthPoints*(tempX + 1)) + (tempY + 1)], z + _distanceBetweenPoint);
			glVertex3d(x, noiseResult[(_widthPoints*tempX) + (tempY + 1)], z + _distanceBetweenPoint);						
			glVertex3d(x + _distanceBetweenPoint, noiseResult[(_widthPoints*(tempX + 1)) + (tempY + 1)], z + _distanceBetweenPoint);  
			glVertex3d(x, noiseResult[(_widthPoints*tempX) + tempY], z);  
			kk++;
			tempY++;
		}
		tempX++;
	}
	glEnd();	
}


//USTAWIENIE PARAMETROW GENEROWANEJ MAPY
void WorldGenerator::SetParameters(const float& mw_, const float& mh_, const float& dbp_, const float& nrs_, const bool& r_, BuilderWith bw, const float& o_, const float& p_, const float& l_) {
	_mapWidth=mw_; 
	_mapHeight = mh_; 
	_distanceBetweenPoint = dbp_;
	_noiseReduceScale = nrs_;
	_random = r_;
	_octaves = o_;
	_persistance = p_;
	_lacunarity = l_;
	MapBuilderWith(bw);
	_widthPoints = GetTotalWidthPoints();
	_heightPoints = GetTotalHeightPoints();
	GenerateNewMap();	 
	colorGenerator.SetValues(_mapHeight, _mapWidth, _distanceBetweenPoint, noiseResult);
	colorsMap = colorGenerator.GetColorVector();
	UpdateMap();
}


//ILOSC PUNKTOW W OSI Z
unsigned int WorldGenerator::GetTotalHeightPoints()
{
	int temp = 0;
	for (float i = -_mapHeight / 2; i < _mapHeight / 2; i += _distanceBetweenPoint) {
		temp++;
	}
	return temp;
}

//ILOSC PUNKTOW W OSI X
unsigned int WorldGenerator::GetTotalWidthPoints()
{
	int temp = 0;
	for (float i = -_mapWidth / 2; i < _mapWidth / 2; i += _distanceBetweenPoint) {
		temp++;
	}
	return temp;
}

//URUCHOMIENIE RANDOMOWEGO GENEROWANIA MAPY
void WorldGenerator::RandomMapGenerator(bool b_) {
	_random = b_;
	UpdateMap();
}

//USAWIENIE DISTANSU MIEDZY PUNKTAMI
void WorldGenerator::SetDistanceBetweenPoint(float f_) {
	if (f_ <= 0.0f) return;
	_distanceBetweenPoint = f_;
	UpdateMap();
}

//USTAWIENIE SKALI GENEROWANEJ MAPY
void WorldGenerator::SetReduceNoiseScale(float f_) {
	if (_noiseReduceScale <= 0.0f) return;
	_noiseReduceScale = f_;
	UpdateMap();
}

//FUNKCJA SPRAWDZAJACA POPRAWNOSC PARAMETROW
void WorldGenerator::CheckValues() {
	this->_mapWidth <= 0.001 ? 0.001f : this->_mapWidth;
	this->_mapHeight <= 0.001 ? 0.001f : this->_mapHeight;
	this->_distanceBetweenPoint <= 0.0f ? 0.00001f : this->_distanceBetweenPoint;
	this->_noiseReduceScale <= 0.0f ? 0.001f : this->_noiseReduceScale;
	if (this->_persistance <= -1.0f) this->_persistance = -1.0f;
	if (this->_octaves <= 0.0f) this->_octaves = 0.001f;
	if (this->_lacunarity <= 0.0f) this->_lacunarity = 0.001f;
	if (_widthPoints <= 0) return;
	if (_heightPoints <= 0) return;
	if( noiseResult.size()<=0) return;
}

//
void WorldGenerator::SetOctaves(float f_) {
	if (this->_octaves <= 0.0f) this->_octaves = 0.001f;
	_octaves = f_;	
	UpdateMap();
	
}
void WorldGenerator::SetPersistance(float f_) {
	if (this->_persistance <= -1.0f) this->_persistance = -1.0f;
	_persistance = f_;
	UpdateMap();	 
}

//USTAWIENIE "ZOOM'u"
void WorldGenerator::SetLacunarity(float f_) {
	if (this->_lacunarity <= 0.0f) this->_lacunarity = 0.001f;
	_lacunarity = f_;
	UpdateMap();

}

//OFFSET
void WorldGenerator::SetOffset(float o_[2]) {
	offset[0] = o_[0];
	offset[1] = o_[1];		 
	UpdateMap();
}


