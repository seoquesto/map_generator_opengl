#pragma once
#ifndef MYNOISE_H
#define MYNOISE_H

#include <vector>
/*
* KLASA ZROBIONA W OPARCIU O STRONE http://mrl.nyu.edu/~perlin/noise/ 
*
*/

class MyNoise {

public:
	//inicializacja domyœlna
	MyNoise();
	//konstruktor sluzacy do randomowego wypelnienia vektora
	MyNoise(bool);
	//konstruktor kopjujacy
	MyNoise(const MyNoise&);
	//przeciazony operator = 
	MyNoise& operator=(const MyNoise&);
	//funkcja ktora zwroci nowa wartosc y
	double noise(double x, double y, double z);

protected:
	//vektor ktory przykowuje randomowe liczby
	std::vector<int> p;

private:
	//FUNKCJE POMOCNICZE 
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};

#endif
