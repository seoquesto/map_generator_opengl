#pragma once
#include <vector>
#include "MakeNoise.h"
#include "ColorGenerator.h"
#include "__Color.h"

enum BuilderWith {
	points = 0,
	lines = 1,
	triangles = 2
};
class WorldGenerator
{
protected:
	float _mapWidth;				//szerokosc mapy
	float _mapHeight;				//wielkosc mapy
	float _distanceBetweenPoint;	//dystans miedzy punktami na mapie
	float _noiseReduceScale;		//skala mapy
	float _octaves; 
	float _persistance;
	float _lacunarity;				//wielkosc zoomu
	unsigned int _widthPoints;		//ilosc puntkow w osi x
	unsigned int _heightPoints;		//ilosc punktow w osi z
	bool _random;					//czy randomowe generowanie mapy
	float offset[2];				//offset
	std::vector<float> noiseResult;	//wartosc mapy w osi y
	std::vector<__Color> colorsMap;	//kolory mapy dla wspolzednych y
	int hexTypeOfBuild;			    //sposob wyswietlania mapy
	void CheckValues();				//sprawdzanie parametrow
	
	MakeNoise makeNoise;
	ColorGenerator colorGenerator;

															 
public:
	//konstruktor domyslny
	WorldGenerator();  

	//konstruktor inicializujacy
	WorldGenerator(const float& mw_, 
					const float& mh_,
					const float& dbp_, 
					const float& nrs_, 
					const bool& r_, 
					BuilderWith bw, 
					const float& o_, 
					const float& p_, 
					const float& l_);

	//destruktor
	~WorldGenerator();

	//funkcja generujaca mape
	void GenerateWorld();

	//funkcja ustawiajaca parametry
	void SetParameters(const float& mw_, const float& mh_, const float& dbp_, const float& nrs_, const bool& r_, BuilderWith bw, const float& o_, const float& p_, const float& l_);
	
	//funkcja zwracajaca ilosc punktow w osi x
	unsigned int GetTotalWidthPoints();
	
	//funkcja zwracajaca ilosc punktow w osi z
	unsigned int GetTotalHeightPoints();

	 //jezeli true to uruchamia randomowy generator mapy
	 void RandomMapGenerator(bool);

	 //generowanie nowej mapy
	 void GenerateNewMap();

	 //ustawienie trybu wyswietlania mapy
	 void MapBuilderWith(BuilderWith);

	 //aktualizacja mapy
	 void UpdateMap();

	 //funkcje ustawiajace parametry
	 void SetDistanceBetweenPoint(float);
	 void SetReduceNoiseScale(float);
	 void SetOctaves(float);
	 void SetPersistance(float);
	 void SetLacunarity(float);	  ;
	 void SetOffset(float o_[2]);
};


