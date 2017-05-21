#pragma once
#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
using namespace sf;
float const PI = 3.1415;
#endif
enum orientation {
	Horizontal = 0,
	Vertikal = 1
};
class Wall {
private:
	GLuint texture;
public:
	float size;
	float xPos, zPos;
	orientation orient;
	Wall();
	Wall(float, GLuint,orientation, float, float);
};