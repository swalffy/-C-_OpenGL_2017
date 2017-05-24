#ifndef libs
#define libs
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
#include <vector>
#include <time.h>
using namespace sf;
float const PI = 3.1415;
#endif
#include <iostream>
#include <string>

#include "Wall.h"
#include "Character.h"
#include "Source.h"


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




	/*mapline = " | | | | | | | ";





	maplines.push_back(mapline);*/
	/*mapline = " |  |__ | | ";
	maplines.push_back(mapline);*/
	/*mapline = " | __| |_| _  ";
	maplines.push_back(mapline);
	mapline = "_ |  | __|    ";
	maplines.push_back(mapline);
	mapline = "___|_____    ";
	maplines.push_back(mapline);*/
	sf::ContextSettings window_settings;
	window_settings.depthBits = 24; 
	window_settings.stencilBits = 8; 
	window_settings.antialiasingLevel = 2; 


	RenderWindow window(VideoMode(displX, displY), "Escape from Labyrinth", sf::Style::Resize,window_settings);
	ShowCursor(FALSE);
	Texture t; t.loadFromFile("assets/background.jpg");
	Sprite background(t);

	GLuint texture;
	texture = GetTexture("assets/myside.jpg");
	GLuint texture1;
	texture1 = GetTexture("assets/1.jpg");

	glutSettings();

	Character pl(1500, 1500, 1500);
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

		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		glutLookAt(pl);
		generateOuterWalls(walls, texture);
		generateInnerWalls(walls, texture1, maplines);

		pl.keyboard(angleX, angleY);
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
void generateInnerWalls(std::vector<Wall> &walls, const GLuint &texture,std::vector<std::string> &str) {
	// c - элементы строки
	// e - сроки
	for (int j = 0; j < str.size(); j++) 		{
		int k = 0;
		for (int i = 1; i <= str[j].size(); i++) {
			if (str[j][i - 1] == ' ')
				continue;
			if (str[j][i - 1] == '|') {
				walls.push_back(Wall(stageSize / 5, texture, Horizontal, stageSize / 10 * (j*2 + 1), stageSize / 10 * (i-k-1)*2));
				k++;
			}
			if (str[j][i - 1] == '_')
				if (j == 19)
					continue;
				else
					walls.push_back(Wall(stageSize / 5, texture, Vertikal, stageSize / 10 * (2 + 2 * j), stageSize / 10 * ((i-k) * 2 - 1)));
		}
	}


	//a = Array(c);
	//b = Array(c);
	//var k = Array(c),
	//	
	//// Цикл по строкам
	//for (cr_l = 0; cr_l < e; cr_l++) {
	//	// Проверка принадлежности ячейки в строке к какому-либо множеству        
	//	for (i = 0; i < c; i++)
	//		0 == cr_l && (a[i] = 0), d.clearRect(13 * i + 3, 13 * cr_l + 3, 10, 10), k[i] = 0, 1 == b[i] && (b[i] = a[i] = 0), 0 == a[i] && (a[i] = q++);

	//	// Создание случайным образом стенок справа и снизу
	//	for (i = 0; i < c; i++) {
	//		k[i] = Math.floor(2 * Math.random()), b[i] = Math.floor(2 * Math.random());

	//		if ((0 == k[i] || cr_l == e - 1) && i != c - 1 && a[i + 1] != a[i]) {
	//			var l = a[i + 1];
	//			for (j = 0; j < c; j++) a[j] == l && (a[j] = a[i]);
	//			d.clearRect(13 * i + 3, 13 * cr_l + 3, 15, 10)
	//		}
	//		cr_l != e - 1 && 0 == b[i] && d.clearRect(13 * i + 3, 13 * cr_l + 3, 10, 15)
	//	}

	//	// Проверка на замкнутые области.
	//	for (i = 0; i < c; i++) {
	//		var p = l = 0;
	//		for (j = 0; j < c; j++) a[i] == a[j] && 0 == b[j] ? p++ : l++;
	//		0 == p && (b[i] = 0, d.clearRect(13 * i + 3, 13 * cr_l + 3, 10, 15))
	//	}
	//}

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
void generateWalls(std::vector<std::string>& map) 	{
	srand(time(0));

		std::string tempstr;
		for (int i = 0; i < 40; i++)
			tempstr+= ' ';
		tempstr[25] = '\0';
		int id[40];
		for (int i = 0; i < 30; i++) {
			id[i] = i;
		}
		int wallCount = 1;
		for (int i = 0; i < 9; i++) {
			if (id[i] != id[i + 1])
				if (!(rand() % 2)) {
					tempstr[i + wallCount] = '|';
					wallCount++;
				}
				else
					id[i + 1] = id[i];
			else {
				tempstr[i + wallCount] = '|';
				wallCount++;
			}
		}
		wallCount = 0;
		for (int i = 0; i < 10; i++) {
			bool isHole = false;
			if (tempstr[i] == '|')
				continue;
			int k = id[i - wallCount];
			while (id[i - wallCount] == k) {
				if (!(rand() % 2)) {
					tempstr[i] = '_';
				}
				else {
					tempstr[i] = ' ';
					isHole = true;
				}
				i++;
			}
			if (!isHole)
				tempstr[i - 1] = ' ';
			wallCount++;
		}
		std::cout << tempstr << std::endl;

		map.push_back(tempstr);
}