#include "Character.h"

Character::Character(float _x, float _y, float _z) {
	xPos = _x; yPos = _y; zPos = _z;
	dx = 0; dy = 0; dz = 0;
	w = 15; h = 40; speed = 40;
	onGround = false;
}

void Character::update(float time) {
	if (!onGround)
		dy -= 1.5*time;
	//onGround = 0;
	xPos += dx*time;
	collision(dx, 0, 0);
	yPos += dy*time;
	collision(0, dy, 0);
	zPos += dz*time;
	collision(0, 0, dz);
	dx = dz = 0;
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
void Character::collision(float dx, float dy, float dz) {
	if (yPos <= h * 3 + 10 && dy < 0) {
		onGround = true;
		dy = 0;
		yPos = h * 3 + 10;
	}
//	if (isColided)
//	if (dx > 0)  xPos -= w;
//	if (dx < 0)  xPos += w;
//	if (dz > 0)  zPos -= w;
//	if (dz < 0)  zPos += w;
}