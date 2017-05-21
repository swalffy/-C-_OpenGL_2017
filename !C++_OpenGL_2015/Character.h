#pragma once
#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
using namespace sf;
float const PI = 3.1415;
float size = 20.f;
#endif
class Character {
public:
	float xPos, yPos, zPos;
	float dx, dy, dz;
	float w, h;
	float speed;
	bool onGround;

	Character(float _x, float _y, float _z);

	void update(float time);

	void keyboard(float, float);

	void collision(float, float, float);
};