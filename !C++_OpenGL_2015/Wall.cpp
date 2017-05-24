#include "Wall.h"

Wall::Wall() {}
Wall::Wall(float size, GLuint _texture, orientation orient, float offX, float offZ) {
	this->size = size;
	float height = 500;
	texture = _texture;
	xPos = offX;
	zPos = offZ;
	this->orient = orient;
	glTranslatef(offX, height/2, offZ);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	switch (orient) {
	case Horizontal:
		glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, -2);
		glTexCoord2f(1, 0); glVertex3f(size / 2, -height, -2);
		glTexCoord2f(1, 1); glVertex3f(size / 2, height, -2);
		glTexCoord2f(0, 1); glVertex3f(-size / 2, height, -2);

		glTexCoord2f(0, 0); glVertex3f(size / 2, -height, 2);
		glTexCoord2f(1, 0); glVertex3f(-size / 2, -height, 2);
		glTexCoord2f(1, 1); glVertex3f(-size / 2, height, 2);
		glTexCoord2f(0, 1); glVertex3f(size / 2, height, 2);

		glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, 2);
		glTexCoord2f(1, 0); glVertex3f(-size / 2, -height, -2);
		glTexCoord2f(1, 1); glVertex3f(-size / 2, height, -2);
		glTexCoord2f(0, 1); glVertex3f(-size / 2, height, 2);

		glTexCoord2f(0, 0); glVertex3f(size / 2, -height, -2);
		glTexCoord2f(1, 0); glVertex3f(size / 2, -height, 2);
		glTexCoord2f(1, 1); glVertex3f(size / 2, height, 2);
		glTexCoord2f(0, 1); glVertex3f(size / 2, height, -2);

		glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, 2);
		glTexCoord2f(1, 0); glVertex3f(size / 2, -height, 2);
		glTexCoord2f(1, 1); glVertex3f(size / 2, -height, -2);
		glTexCoord2f(0, 1); glVertex3f(-size / 2, -height, -2);

		glTexCoord2f(0, 0); glVertex3f(-size / 2, height, -2);
		glTexCoord2f(1, 0); glVertex3f(size / 2, height, -2);
		glTexCoord2f(1, 1); glVertex3f(size / 2, height, 2);
		glTexCoord2f(0, 1); glVertex3f(-size / 2, height, 2);
		break;
	case Vertikal:
		glTexCoord2f(0, 0); glVertex3f(-2, -height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(2, -height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(2, height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-2, height, -size / 2);

		glTexCoord2f(0, 0); glVertex3f(2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(-2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(-2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(2, height, size / 2);

		glTexCoord2f(0, 0); glVertex3f(-2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(-2, -height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(-2, height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-2, height, size / 2);

		glTexCoord2f(0, 0); glVertex3f(2, -height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(2, height, -size / 2);

		glTexCoord2f(0, 0); glVertex3f(-2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(2, -height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-2, -height, -size / 2);


		glTexCoord2f(0, 0); glVertex3f(-2, height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(2, height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(-2, height, size / 2);
		break;
	}
	glEnd();
	glTranslatef(-offX, -height/2, -offZ);
}
Stage::Stage() {}
Stage::Stage(float _size, GLuint _texture) {
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