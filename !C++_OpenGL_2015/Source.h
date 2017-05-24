#pragma once

void rotateCam(sf::RenderWindow &window);

void generateOuterWalls(std::vector<Wall> &walls, const GLuint &texture);

void generateInnerWalls(std::vector<Wall> &walls, const GLuint &texture, std::vector<std::string>&);

void generateWalls(std::vector<std::string>& );

void glutSettings();

void glutLookAt(Character &pl);
