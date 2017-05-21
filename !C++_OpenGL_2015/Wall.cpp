#include "Wall.h"


	Wall::Wall() {}
	Wall::Wall(float size, GLuint _texture,orientation orient,float offX, float offZ) {
		this->size = size;
		texture = _texture;
		xPos =  offX;
		zPos = offZ; 
		this->orient = orient;
		glTranslatef(offX, 0, offZ);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		switch (orient) {
		case Horizontal:
			glTexCoord2f(0, 0); glVertex3f(-size / 2, -500, -2);
			glTexCoord2f(1, 0); glVertex3f(size / 2, -500, -2);
			glTexCoord2f(1, 1); glVertex3f(size / 2, 500, -2);
			glTexCoord2f(0, 1); glVertex3f(-size / 2, 500, -2);

			glTexCoord2f(0, 0); glVertex3f(size / 2, -500, 2);
			glTexCoord2f(1, 0); glVertex3f(-size / 2, -500, 2);
			glTexCoord2f(1, 1); glVertex3f(-size / 2, 500, 2);
			glTexCoord2f(0, 1); glVertex3f(size / 2, 500, 2);

			glTexCoord2f(0, 0); glVertex3f(-size / 2, -500, 2);
			glTexCoord2f(1, 0); glVertex3f(-size / 2, -500, -2);
			glTexCoord2f(1, 1); glVertex3f(-size / 2, 500, -2);
			glTexCoord2f(0, 1); glVertex3f(-size / 2, 500, 2);

			glTexCoord2f(0, 0); glVertex3f(size / 2, -500, -2);
			glTexCoord2f(1, 0); glVertex3f(size / 2, -500, 2);
			glTexCoord2f(1, 1); glVertex3f(size / 2, 500, 2);
			glTexCoord2f(0, 1); glVertex3f(size / 2, 500, -2);

			glTexCoord2f(0, 0); glVertex3f(-size / 2, -500, 2);
			glTexCoord2f(1, 0); glVertex3f(size / 2, -500, 2);
			glTexCoord2f(1, 1); glVertex3f(size / 2, -500, -2);
			glTexCoord2f(0, 1); glVertex3f(-size / 2, -500, -2);

			glTexCoord2f(0, 0); glVertex3f(-size / 2, 500, -2);
			glTexCoord2f(1, 0); glVertex3f(size / 2, 500, -2);
			glTexCoord2f(1, 1); glVertex3f(size / 2, 500, 2);
			glTexCoord2f(0, 1); glVertex3f(-size / 2, 500, 2);
			break;
		case Vertikal:
			glTexCoord2f(0, 0); glVertex3f(-2, -500, -size / 2);
			glTexCoord2f(1, 0); glVertex3f(2, -500, -size / 2);
			glTexCoord2f(1, 1); glVertex3f(2, 500, -size / 2);
			glTexCoord2f(0, 1); glVertex3f(-2, 500, -size / 2);

			glTexCoord2f(0, 0); glVertex3f(2, -500, size / 2);
			glTexCoord2f(1, 0); glVertex3f(-2, -500, size / 2);
			glTexCoord2f(1, 1); glVertex3f(-2, 500, size / 2);
			glTexCoord2f(0, 1); glVertex3f(2, 500, size / 2);

			glTexCoord2f(0, 0); glVertex3f(-2, -500, size / 2);
			glTexCoord2f(1, 0); glVertex3f(-2, -500, -size / 2);
			glTexCoord2f(1, 1); glVertex3f(-2, 500, -size / 2);
			glTexCoord2f(0, 1); glVertex3f(-2, 500, size / 2);

			glTexCoord2f(0, 0); glVertex3f(2, -500, -size / 2);
			glTexCoord2f(1, 0); glVertex3f(2, -500, size / 2);
			glTexCoord2f(1, 1); glVertex3f(2, 500, size / 2);
			glTexCoord2f(0, 1); glVertex3f(2, 500, -size / 2);

			glTexCoord2f(0, 0); glVertex3f(-2, -500, size / 2);
			glTexCoord2f(1, 0); glVertex3f(2, -500, size / 2);
			glTexCoord2f(1, 1); glVertex3f(2, -500, -size / 2);
			glTexCoord2f(0, 1); glVertex3f(-2, -500, -size / 2);

			
			glTexCoord2f(0, 0); glVertex3f(-2, 500, -size / 2);
			glTexCoord2f(1, 0); glVertex3f(2, 500, -size / 2);
			glTexCoord2f(1, 1); glVertex3f(2, 500, size / 2);
			glTexCoord2f(0, 1); glVertex3f(-2, 500, size / 2);
			break;
		}
		glEnd();
		glTranslatef(-offX, 0, -offZ);
	}
	