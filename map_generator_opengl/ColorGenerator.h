#pragma once
#include <vector>
#include "__Color.h"

class ColorGenerator
{
protected:
	float _mapHeight;				//wielkosc z mapy
	float _mapWidth;				//wielkosc x mapy
	float _distanceBetweenPoint;	//dystans miedzy punktami
	int _widthPoints;				//ilosc punktow w osi x
	int _heightPoints;				//ilosc punktow w osi y
	std:: vector<float> _noise;		//wartosc wzgledem ktorego beda tworzone kolor
	__Color _color[6];				//6 kolorow
public:
	//konstuktor
	ColorGenerator();	

	//destrukor
	~ColorGenerator();

	//konstruktor kopjujacy
	ColorGenerator(const ColorGenerator&);

	//przeciazony operator = 
	ColorGenerator& operator=(const ColorGenerator&);

	//funkcja do wporwadzania wartosc
	void SetValues(const float& mh_, const float& mw_, const float& dbw_, std::vector<float> n_);

	//zwraca vektor kolorow
	std::vector<__Color> GetColorVector();

	//zlicza ilosc puntkow w osi z
	unsigned int GetTotalHeightPoints(); 

	//zlicza ilosc punktow w osi y
	unsigned int GetTotalWidthPoints();
	void InitColors();
};

