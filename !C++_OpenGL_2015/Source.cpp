#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
#include <vector>
#include <time.h>
#include <SFML\Audio\Music.hpp>
using namespace sf;
float const PI = 3.1415;
#endif
#include <iostream>
#include <string>

#include "Wall.h"
#include "Character.h"
#include "Source.h"
#include "bonus.h"


int displX = 1920, displY = 1080;
float angleX, angleY;
float sensitivity = 15;
float stageSize = 1500.f;

GLuint GetTexture(sf::String name) {
	sf::Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;
	image.flipVertically();
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	return texture;
}

int main() {
	srand(time(0));
	std::vector<std::string> maplines;
	generateWalls(maplines);

	bool bonusAvalible = true;
	int bPosX = rand() % (int)(stageSize*2);
	int bPosZ = rand() % (int)(stageSize * 2);

	float ftime = 0.3;
	Font font;
	font.loadFromFile("assets/CyrilicOld.TTF");
	int fsize = 30;
	float df = 1.1;
	Text timeLeft("", font, fsize);
	timeLeft.setStyle(sf::Text::Bold);

	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 2;


	RenderWindow window(VideoMode(displX, displY), "Escape from Labyrinth", sf::Style::Resize, window_settings);
	ShowCursor(FALSE);
	Texture t; t.loadFromFile("assets/background.jpg");
	Sprite background(t);

	GLuint texture;
	texture = GetTexture("assets/myside.jpg");
	GLuint texture1;
	texture1 = GetTexture("assets/1.jpg");

	glutSettings();

	Character pl(1500, 2000, 1500);
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
		std::vector<Wall> walls;

		rotateCam(window);

		ftimeChanger(ftime, clock, fsize, df);
		//if (ftime < 0) 
		//	break;
		timeLeft.setString(std::to_string(ftime * 10));
		timeLeft.setCharacterSize(fsize);

		window.pushGLStates();
		window.draw(background);
		window.draw(timeLeft);
		window.popGLStates();
		glutLookAt(pl);
		generateInnerWalls(walls, texture, maplines);
		generateOuterWalls(walls, texture);
		if (bonusAvalible) 			{
		Bonus b(stageSize / 8, texture1, bPosX, bPosZ);
		if (sqrt((pl.xPos - b.xPos)*(pl.xPos - b.xPos) + (pl.zPos - b.zPos)*(pl.zPos - b.zPos)) < pl.w * 10) {
			pl.takeBonus(b.type, ftime);
			std::cout << "You take " << b.type << " bonus" << std::endl;
			bonusAvalible = false;
		}
		}
		window.pushGLStates();
		window.draw(timeLeft);
		window.popGLStates();
		if (Keyboard::isKeyPressed(Keyboard::Tilde)) {
			std::string code;
			std::cin >> code;
			if (code == "hesoyam") {
				ftime += 3;
			}
			else if (code == "whosyourdaddy") {
				pl.godMode();
			}
		}
	

		pl.keyboard(angleX, angleY);
		pl.update(time, walls);
		window.display();
	}
	glDeleteTextures(1, &texture);glDeleteTextures(1, &texture1);
	return 0;
}
void ftimeChanger(float &ftime, sf::Clock &clock, int &fsize, float &df) {
	ftime -= clock.getElapsedTime().asSeconds();
	if (ftime * 10 < 10) {
		if (fsize < 28)
			df = 1.05;
		if (fsize > 38)
			df = 0.98;
		fsize *= df;
	}
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
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 5000.f);
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
void generateInnerWalls(std::vector<Wall> &walls, const GLuint &texture, std::vector<std::string> &str) {
	for (int j = 0; j < str.size(); j++) {
		int k = 0;
		for (int i = 1; i <= str[j].size(); i++) {
			if (str[j][i - 1] == ' ')
				continue;
			if (str[j][i - 1] == '|') {
				walls.push_back(Wall(stageSize / 5, texture, Horizontal, stageSize / 10 * (j * 2 + 1), stageSize / 10 * (i - k - 1) * 2));
				k++;
			}
			if (str[j][i - 1] == '_')
				if (j == 19)
					continue;
				else
					walls.push_back(Wall(stageSize / 5, texture, Vertikal, stageSize / 10 * (2 + 2 * j), stageSize / 10 * ((i - k) * 2 - 1)));
		}
	}
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
void generateWalls(std::vector<std::string>& map) {
	srand(time(0));
	int j = 0;
	int size = 10;
	std::string tempstr;
	for (int i = 0; i < size; i++)
		tempstr += ' ';
	int id[15]{ NULL };
	do {
		for (int i = 1; i <= 15; i++) {
			if (id[i-1] == NULL)
				for (int q = i; q <= 15; q++)
					if (isFree(id, q)) {
						id[i-1] = q;
						break;
					}		
		}
		int i = 1;
		int walls = 0;
		do{
			if (id[i-1] == id[i]) 				{
				tempstr.insert(tempstr.begin() + i+walls, '|');
				walls++;
			}
			else 				{
				if (rand() % 2) {
					tempstr.insert(tempstr.begin() + i+walls, '|');
					walls++;
				}
				else
					id[i] = id[i-1];
			}
			i++;
		} while (i < size);

		int before = 0;
		for (int i = 0; i < tempstr.size(); i++) {
			if (tempstr[i] == ' ' || tempstr[i] == '_')
				before++;
		}
		i = 0;
		walls = 0;
		do {
			if (tempstr[i+walls] == '|') 	{
				walls++;
				continue;
			}
			bool isHole = false;
			int temp = id[i];
			do {
				if (tempstr[i + walls] == '|') 	{
					walls++;
				}
				if (rand() % 2)
					tempstr[i + walls] = '_';
				else
					isHole = true;
				i++;
			} while (id[i] == temp && (i + walls) < tempstr.size());
			if (!isHole)
				tempstr[i - 1 + walls] = ' ';
		} while (i+walls < tempstr.size());

		int after = 0;
		for (int i = 0; i < tempstr.size(); i++) {
			if (tempstr[i] == ' ' || tempstr[i] == '_')
				after++;
		}
		map.push_back(tempstr);
		for (int i = 0; i < tempstr.size(); i++) {
			if (tempstr[i] == '|') {
				tempstr.erase(tempstr.begin() + i);
				i--;
			}
			if (tempstr[i] == '_') {
				tempstr[i] = ' ';
				id[i] = NULL;
			}
		}
		j++;
	} while (j < 9);
	return;
}
bool isFree(int id[15], int num) {
	for (int i = 0; i < 15; i++)
		if (id[i] == num)
			return false;
	return true;
}