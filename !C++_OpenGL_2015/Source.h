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
#include "Wall.h"
#include "Character.h"
extern int displX, displY;
extern float angleX, angleY, sensitivity, stageSize ;
GLuint GetTexture(sf::String);

void msgFunc(bool);
int mainMenuFunc();

int optionsFunc();

int gameFunct(bool);

void rotateCam(sf::RenderWindow &);

void generateOuterWalls(std::vector<Wall> &walls, const GLuint &);

void generateInnerWalls(std::vector<Wall> &walls, const GLuint &, std::vector<std::string>&);

void generateWalls(std::vector<std::string>& );

void glutSettings();

void glutLookAt(Character &pl);

void ftimeChanger(float &ftime, sf::Clock &, int &, float &);

bool isFree(int id[15], int);

void createSkyBox(GLuint skybox[6], int );

void getAllTextures(GLuint &texture, GLuint  skybox[6]);