#pragma once
#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>
using namespace sf;
float const PI = 3.1415;
#endif

enum bonus {
	addtime = 0,
	fly = 1,
	win = 2
};
class Bonus {
private:
	GLuint texture;
public:
	bonus type;
	float size;
	float xPos, zPos;
	Bonus ();
	Bonus(float, float, float,bonus);
};