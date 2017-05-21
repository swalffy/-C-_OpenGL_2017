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
#include "Character.h"
#include "Wall.h"

#include <iostream>
#include "Source.h"

bool commonSectionCircle(Character pl, Wall wall) {
	float x1, x2, y1, y2;
	if (wall.orient == Horizontal) {
		x1 = wall.xPos - wall.size/2;
		x2 = wall.xPos + wall.size/2;
		y1 = y2 = wall.zPos;
	}
	else {
		y1 = wall.zPos - wall.size / 2;
		y2 = wall.zPos + wall.size / 2;
		x1 = x2 = wall.xPos;
	}
	x1 -= pl.xPos;
	y1 -= pl.zPos;
	x2 -= pl.xPos;
	y2 -= pl.zPos;

	double dx = x2 - x1;
	double dy = y2 - y1;
	double a = dx*dx + dy*dy;
	double b = 2.*(x1*dx + y1*dy);
	double c = x1*x1 + y1*y1 - pl.w*pl.w*6;
	if (-b < 0)
		return (c < 0);
	if (-b < (2.*a))
		return ((4.*a*c - b*b) < 0);
	return (a + b + c < 0);
}
bool isColided(Character pl, std::vector<Wall>walls) {
	for (int i = 0; i < walls.size(); i++)
		if (commonSectionCircle(pl, walls[i])) {
				return true;
		}
			
	return false;

}

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
class Stage {
protected:
	float size;
	GLuint texture;
public:
	Stage() {}
	Stage(float _size, GLuint _texture) {
		size = _size;
		texture = _texture;
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0); glVertex3f(-size, -2, -size);
		glTexCoord2f(1, 0); glVertex3f(size, -2, -size);
		glTexCoord2f(1, 1); glVertex3f(size, 2, -size);
		glTexCoord2f(0, 1); glVertex3f(-size, 2, -size);

		glTexCoord2f(0, 0); glVertex3f(size, -2, size);
		glTexCoord2f(1, 0); glVertex3f(-size, -2, size);
		glTexCoord2f(1, 1); glVertex3f(-size, 2, size);
		glTexCoord2f(0, 1); glVertex3f(size, 2, size);

		glTexCoord2f(0, 0); glVertex3f(-size, -2, size);
		glTexCoord2f(1, 0); glVertex3f(-size, -2, -size);
		glTexCoord2f(1, 1); glVertex3f(-size, 2, -size);
		glTexCoord2f(0, 1); glVertex3f(-size, 2, size);

		glTexCoord2f(0, 0); glVertex3f(size, -2, -size);
		glTexCoord2f(1, 0); glVertex3f(size, -2, size);
		glTexCoord2f(1, 1); glVertex3f(size, 2, size);
		glTexCoord2f(0, 1); glVertex3f(size, 2, -size);

		glTexCoord2f(0, 0); glVertex3f(-size, -2, size);
		glTexCoord2f(1, 0); glVertex3f(size, -2, size);
		glTexCoord2f(1, 1); glVertex3f(size, -2, -size);
		glTexCoord2f(0, 1); glVertex3f(-size, -2, -size);

		glTexCoord2f(0, 0); glVertex3f(-size, 2, -size);
		glTexCoord2f(1, 0); glVertex3f(size, 2, -size);
		glTexCoord2f(1, 1); glVertex3f(size, 2, size);
		glTexCoord2f(0, 1); glVertex3f(-size, 2, size);

		glEnd();
	}
};
int main() {
	RenderWindow window(VideoMode(displX, displY), "Escape from Labyrinth");
	ShowCursor(FALSE);
	Texture t;
	t.loadFromFile("assets/background.jpg");
	Sprite background(t);

	GLuint texture;
	texture = GetTexture("assets/myside.jpg");

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 30000.f);
	glEnable(GL_TEXTURE_2D);

	Character pl(150, 300, 150);
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
		pl.keyboard(angleX,angleY);
		pl.update(time);

		rotateCam(window);

		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pl.xPos, pl.yPos + pl.h / 2, pl.zPos,
			pl.xPos - sin(angleX / 180 * PI),
			pl.yPos + pl.h / 2 + (tan(angleY / 180 * PI)),
			pl.zPos - cos(angleX / 180 * PI),
			0, 1, 0);
		
		std::vector<Wall> walls;
		generateOuterWalls(walls, texture);
		if (isColided(pl, walls)) 			{
			pl.collision(pl.dx,pl.dy,pl.dz);
		}
		
		std::cout << pl.xPos << " " << pl.zPos << " | " <<  isColided(pl,walls) << std::endl;
		window.display();
	}
	glDeleteTextures(1, &texture);
	return 0;
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
