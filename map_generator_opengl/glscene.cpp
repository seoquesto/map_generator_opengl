#include <windows.h>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/freeglut.h>
#include "MakeNoise.h"

#include <vector>
#include <iostream>
#include "glscene.h"
#include "MyNoise.h"
#include "WorldGenerator.h"

GLint glScene::winx_ = 0;
GLint glScene::winy_ = 0;

GLint texture1;

//--------MOJE ZMIENNE----------------
MakeNoise makeNoise_;
WorldGenerator worldGenerator;

//ZMIENNE KTORYCH NAJLEPIEJ NIE RUSZAC//
const float mapXSize = 5.0f,				//5.0
			mapZSize = 5.0f,				//5.0 Najlepiej jezeli bedzie taka sama wartosc jak mapXSize ostatecznie +-distanceBetweenPoint
			octaves = 4.0f;					//stala
//---//

//ZMIENNA OPCJONALNA DO POPRAWY EFEKTU
float		distanceBetweenPoint = 0.04;	// Im mniej tym wieksza gladkosc ale tez wiecej mocy obliczeniowej jest potrzebne
											// zalecany przedzial to [1.0; 0.005] wszystko zalezy od mocy komputera. default: 0.05
											//proponuje zrobic test na samym pocz¹tku. Uruchomic aplikacje i przytrzymywac klawisz F8 jezeli
											//przejscie bedzie plynne tzn. efekt fali bez przycinek to mozna zmniejszyc wartosc zmiennej. Jezeli
											//nie ma efektu fali (podczas przytrzymywania klawisza F8 nic sie nie dzieje) nalezy nieznacznie 
											//zwiekszyc wartosc np. distanceBetweenPoint+0.01f
//---//


//MOZLIWOSC ZMIANY PRZY POMOCY KLAWIATURY
float		
			//F11 oraz F12
			noiseScale = 25.0f,				//Wygladzenie mapy im wiecej tym gladsza mapa

			//F6 I F7 os OX
			//F8 I F9 os OZ
			offset[2],						//offset przy ustawieniu odpowiedniej wartosci "distanceBetweenPoint" i blizej 1.0f tym lepiej
											//tym bardziej lagodne lub nawet plynny przejscie mozemy uzyskac, i mniejsza wartosc distanceBetweenPont
											//tym wiecej mocy obliczeniowej bedzie potrzeba a tym samym przejsce bedzie "klatkowalo"

			//LEWY SHIFT I PRAWY SHIFT
			persistance = -0.3f,			//OSTROSC

			//LEWY CTRL I PRAWY CTRL
			lacunarity = 0.7f;				//ZOOM
		


//--------------------------------------

glScene::glScene()
:
	repaintRequest_(GL_FALSE)
{
	rot_[0] = rot_[1] = rot_[2] = 0.0f;
}

glScene::~glScene()
{
}

void glScene::Resize()
{
   Resize(winx_, winy_);
}

void glScene::Resize(int _w, int _h)
{
	winx_ = _w;
	winy_ = _h;

	if(_h == 0)
   		_h = 1;
	if(_w == 0)
   		_w = 1;

	//ustawienie viewportu
	glViewport(0, 0, _w, _h);

	//macierze projekcji
	glMatrixMode(GL_PROJECTION);
	//ustaw aktualna macierz na I
	glLoadIdentity();

	//ustaw uklad wspolrzednych
	glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -4.0f, 4.0f);

	//macierze modelowania
	glMatrixMode(GL_MODELVIEW);
	//ustaw aktualna macierz na I
	glLoadIdentity();
}

void glScene::SetupRC()
{
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   MapInit();
   glEnable(GL_DEPTH_TEST);
}
void glScene::MapInit() {
	worldGenerator.SetParameters(mapXSize, mapZSize, distanceBetweenPoint, noiseScale, true, BuilderWith::lines, octaves, persistance,lacunarity);
	offset[0] = offset[1]=0.0f;
}

void glScene::CleanRC()
{
}

void glScene::RenderScene()
{

	repaintRequest_ = GL_FALSE;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	glTranslated(0.0f, -2.0f, 0.0f);
	
			glRotatef(rot_[0]*5, 1.0, 0.0, 0.0);
			glRotatef(rot_[1]*5, 0.0, 1.0, 0.0);
			glRotatef(rot_[2]*5, 0.0, 0.0, 1.0);

			worldGenerator.GenerateWorld();
					
		glPopMatrix();	 
	glFlush();
}


void glScene::KeyboardFunction(char _key, int, int)
{
	std::cout << _key;
	if(_key == 32)
	{
	}
	repaintRequest_ = GL_TRUE;
}


void glScene::KeyboardFunction(int _key, int, int)
{
	std::cout << _key;
	if(_key == GLUT_KEY_RIGHT)
		rot_[1] +=0.5;
	else if(_key == GLUT_KEY_LEFT)
		rot_[1] -= 0.5;
	else if(_key == GLUT_KEY_UP)
		rot_[0] += 0.5;
	else if(_key == GLUT_KEY_DOWN)
		rot_[0] -= 0.5;
	else if(_key == GLUT_KEY_PAGE_UP)
		rot_[2] += 0.5;
	else if(_key == GLUT_KEY_PAGE_DOWN)
		rot_[2] -= 0.5;
	else if (_key == GLUT_KEY_F1) {	 	
		worldGenerator.MapBuilderWith(BuilderWith::points);
		std::cout << "\nF1: Points!";
	}
	else if (_key == GLUT_KEY_F2){
		worldGenerator.MapBuilderWith(BuilderWith::lines);
		std::cout << "\nF2: Lines!";
	}
	else if (_key == GLUT_KEY_F3){
		worldGenerator.MapBuilderWith(BuilderWith::triangles);	
		std::cout << "\nF3: Triangles!";
	}
	else if (_key == GLUT_KEY_F4) {
	}
	else if (_key == GLUT_KEY_F5) {
		worldGenerator.GenerateNewMap();
		std::cout << "\nF5 Generate new map!";
	}


	if (_key == 54) {
		offset[0] -= 0.004f;
		worldGenerator.SetOffset(offset);
		std::cout << "\nUpdate offsetX: " << offset[0];
	}
    if (_key == 52) {
		offset[0] += 0.004f;
		worldGenerator.SetOffset(offset);
		std::cout << "\nUpdate offsetX: " << offset[0];
	}

	if (_key == 56) {
		offset[1] -= 0.004f;
		worldGenerator.SetOffset(offset);
		std::cout << "\nUpdate offsetY: " << offset[1];
	}
    if (_key == 50) {
		offset[1] += 0.004f;
		worldGenerator.SetOffset(offset);
		std::cout << "\nUpdate offsetY: " << offset[1];
	}

	if (_key == 45) {  
		if (noiseScale <= 4.0) return;
		noiseScale -= 0.12f;
		worldGenerator.SetReduceNoiseScale(noiseScale);
		std::cout << "\nF12 Scale: " << noiseScale;
	}
	if (_key == 43) {
		noiseScale += 0.12f;
		worldGenerator.SetReduceNoiseScale(noiseScale);
		std::cout << "\nF11 Scale: " << noiseScale;
	}

	 if (_key == 44) {
		if (persistance <= -.4)return;
		persistance -=0.01f;
		worldGenerator.SetPersistance(persistance);
		std::cout << "\nPersistance: " << persistance;
	}
	else if (_key == 48) { 
		if (persistance >= 0.35)  return; 
		persistance += 0.01f;
		worldGenerator.SetPersistance(persistance);
		std::cout << "\nPersistance: " << persistance;
	}

	if(rot_[0] > 360) rot_[0] = 360 - rot_[0];
	if(rot_[1] > 360) rot_[1] = 360 - rot_[1];
	if(rot_[2] > 360) rot_[2] = 360 - rot_[2];

	repaintRequest_ = GL_TRUE;
}

void glScene::MouseMove(int, int)
{
}
void glScene::MouseLBDown(int, int)
{
}
void glScene::MouseLBUp(int, int)
{
}


void glScene::Timer()
{
	repaintRequest_ = GL_TRUE;
}

bool glScene::WantTimer()
{
	return false;
}

int glScene::GetTimer()
{
	return 0;
}
