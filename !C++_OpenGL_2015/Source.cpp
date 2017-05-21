#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
#include <vector>
using namespace sf;
float const PI = 3.1415;
#endif
#include "Wall.h"
#include "Character.h"
#include <iostream>
#include "Source.h"


int displX = 1920, displY = 1080;
float angleX, angleY;
float x = 0, y = 0, z = 0;
float sensitivity = 15;
float stageSize = 1500.f;

GLuint GetTexture(sf::String name) {
	sf::Image image;
	image.loadFromFile(name);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}

int main() {
	RenderWindow window(VideoMode(displX, displY), "Escape from Labyrinth");
	ShowCursor(FALSE);
	Texture t;
	t.loadFromFile("assets/background.jpg");
	Sprite background(t);
	GLuint texture;
	texture = GetTexture("assets/myside.jpg");

	glutSettings();

	Character pl(150, 150);
	Clock clock;
	//Main cycle is here
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time /= 50;
		if (time > 3)
			time = 3;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		pl.keyboard(angleX, angleY);
		std::vector<Wall> walls;

		rotateCam(window);

		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		glutLookAt(pl);

		generateOuterWalls(walls, texture);
		pl.update(time, walls);
		window.display();
	}
	glDeleteTextures(1, &texture);
	return 0;
}

void glutLookAt(Character &pl) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pl.xPos, pl.yPos + pl.h / 2, pl.zPos,
		pl.xPos - sin(angleX / 180 * PI),
		pl.yPos + pl.h / 2 + (tan(angleY / 180 * PI)),
		pl.zPos - cos(angleX / 180 * PI),
		0, 1, 0);
}

void glutSettings() {
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 30000.f);
	glEnable(GL_TEXTURE_2D);
}

void generateOuterWalls(std::vector<Wall> &walls, const GLuint &texture) {

	walls.push_back(Wall(stageSize * 2, texture, Vertikal, 0, stageSize));
	walls.push_back(Wall(stageSize * 2, texture, Horizontal, stageSize, 0));
	walls.push_back(Wall(stageSize * 2, texture, Horizontal, stageSize, stageSize * 2));
	walls.push_back(Wall(stageSize * 2, texture, Vertikal, stageSize * 2, stageSize));
	glTranslatef(stageSize, 0, stageSize);
	Stage a(stageSize, texture);
	glTranslatef(-stageSize, 0, -stageSize);
}

void rotateCam(sf::RenderWindow &window) {
	POINT mouseXY;
	GetCursorPos(&mouseXY);
	int xt = window.getPosition().x + displX / 2;
	int yt = window.getPosition().y + displY / 2;

	angleX += (xt - mouseXY.x) / sensitivity;
	angleY += (yt - mouseXY.y) / sensitivity;

	if (angleY > 80)
		angleY = 80;
	if (angleY < -80)
		angleY = -80;
	SetCursorPos(xt, yt);
}
