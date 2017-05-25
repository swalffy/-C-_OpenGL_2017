#include "Character.h"

Character::Character(float _x, float _y, float _z) {
	xPos = _x; yPos = _y; zPos = _z;
	dx = 0; dy = 0; dz = 0;
	w = 15; h = 40; speed = 40;
	onGround = false;
	god = true;
}
Character::Character(float _x, float _z) {
	xPos = _x; yPos = 300; zPos = _z;
	dx = 0; dy = 0; dz = 0;
	w = 15; h = 40; speed = 40;
	onGround = false;
}
void Character::update(float time, std::vector<Wall> walls) {
	if (this->god) {
		if (yPos < 1500) {
			dy += 1.5*time;
		}
		if (yPos = 1500)
			dy = 0;
		xPos += dx*time;
		yPos += dy*time;
		zPos += dz*time;
		dx = dz = 0;
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			godMode();
		}
	}
	else {
		if (!onGround)
			dy -= 1.5*time;
		xPos += dx*time;
		collision(dx, 0, 0, walls);
		yPos += dy*time;
		collision(0, dy, 0, walls);
		zPos += dz*time;
		collision(0, 0, dz, walls);
		dx = dz = 0;
	}
}
bool Character::commonSectionCircle(Wall wall) {
	float x1, x2, y1, y2;
	if (wall.orient == Horizontal) {
		x1 = wall.xPos - wall.size / 2;
		x2 = wall.xPos + wall.size / 2;
		y1 = y2 = wall.zPos;
	}
	else {
		y1 = wall.zPos - wall.size / 2;
		y2 = wall.zPos + wall.size / 2;
		x1 = x2 = wall.xPos;
	}
	x1 -= this->xPos;
	y1 -= this->zPos;
	x2 -= this->xPos;
	y2 -= this->zPos;

	double dx = x2 - x1;
	double dy = y2 - y1;
	double a = dx*dx + dy*dy;
	double b = 2.*(x1*dx + y1*dy);
	double c = x1*x1 + y1*y1 - this->w*this->w * 6;
	if (-b < 0)
		return (c < 0);
	if (-b < (2.*a))
		return ((4.*a*c - b*b) < 0);
	return (a + b + c < 0);
}
void Character::keyboard(float angleX, float angleY) {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dx = -sin(angleX / 180 * PI) * speed;
		dz = -cos(angleX / 180 * PI) * speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		dx = sin(angleX / 180 * PI) * speed;
		dz = cos(angleX / 180 * PI) * speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dx = sin((angleX + 90) / 180 * PI) * speed;
		dz = cos((angleX + 90) / 180 * PI) * speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dx = sin((angleX - 90) / 180 * PI) * speed;
		dz = cos((angleX - 90) / 180 * PI) * speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
		if (onGround) {
			onGround = false;
			dy = 20;
		}
	}
void Character::collision(float dx, float dy, float dz, std::vector<Wall> walls) {
	if (yPos <= h * 3 + 10 && dy < 0) {
		onGround = true;
		dy = 0;
		yPos = h * 3 + 10;
	}
	if (isColided(walls)) {
		if (dx > 0)	xPos -= w*1.25;
		if (dx < 0)  xPos += w*1.25;
		dx = 0;
		if (dz > 0)  zPos -= w*1.25;
		if (dz < 0)  zPos += w*1.25;
		dz = 0;
	}
}
bool Character::isColided(std::vector<Wall>walls) {
	for (int i = 0; i < walls.size(); i++)
		if (commonSectionCircle(walls[i])) {
			return true;
		}
	return false;
}
void Character::godMode() 	{
	this->god = !this->god;
}
void Character::takeBonus(bonus type, float& curtime) 	{
	switch (type) {
	case addtime:
		curtime += 1;
		break;
	case fly:
		godMode();
		break;
	case win:
		//win level
		break;
	}
}