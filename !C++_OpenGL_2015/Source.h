#pragma once

void rotateCam(sf::RenderWindow &window);

void generateOuterWalls(std::vector<Wall> &walls, const GLuint &texture);

void glutSettings();

void glutLookAt(Character &pl);
