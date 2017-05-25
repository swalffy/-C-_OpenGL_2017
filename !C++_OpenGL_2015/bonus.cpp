#include "bonus.h"
Bonus::Bonus() {}
Bonus::Bonus(float size, GLuint _texture, float offX, float offZ) {
	this->size = size;
	float height = 300;
	texture = _texture;
	xPos = offX;
	zPos = offZ;
	if (rand() % 3 == 0)
		this->type = addtime;
	else if (rand() % 3 == 1)
		this->type = fly;
	else
		this->type = win;
	
	glTranslatef(offX, height / 2, offZ);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-size/2, -height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(size/2, -height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(size/2, height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-size/2, height, -size / 2);

		glTexCoord2f(0, 0); glVertex3f(size/2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(-size/2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(-size/2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(size/2, height, size / 2);

		glTexCoord2f(0, 0); glVertex3f(-size/2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(-size/2, -height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(-size/2, height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-size/2, height, size / 2);

		glTexCoord2f(0, 0); glVertex3f(size/2, -height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(size/2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(size/2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(size/2, height, -size / 2);

		glTexCoord2f(0, 0); glVertex3f(-size/2, -height, size / 2);
		glTexCoord2f(1, 0); glVertex3f(size/2, -height, size / 2);
		glTexCoord2f(1, 1); glVertex3f(size/2, -height, -size / 2);
		glTexCoord2f(0, 1); glVertex3f(-size/2, -height, -size / 2);


		glTexCoord2f(0, 0); glVertex3f(-size/2, height, -size / 2);
		glTexCoord2f(1, 0); glVertex3f(size/2, height, -size / 2);
		glTexCoord2f(1, 1); glVertex3f(size/2, height, size / 2);
		glTexCoord2f(0, 1); glVertex3f(-size/2, height, size / 2);

	glEnd();
	glTranslatef(-offX, -height / 2, -offZ);
}