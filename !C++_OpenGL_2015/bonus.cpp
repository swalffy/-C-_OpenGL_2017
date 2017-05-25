#include "bonus.h"
Bonus::Bonus() {}
Bonus::Bonus(float size, float offX, float offZ, bonus type) {
	std::string name;
	if (type == win) {
		this->type = win;
		name = "assets/endlevel.jpg";
	}
	else if (type == addtime) {
		this->type = addtime;
		name = "assets/time.jpg";
	}
	else if (type == fly) {
		this->type = fly;
		name = "assets/godmode.jpg";
	}
	sf::Image image;
	image.loadFromFile(name);
	image.flipVertically();
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	this->size = size;
	float height = 300;
	this->texture = texture;
	xPos = offX;
	zPos = offZ;
	glTranslatef(offX, height / 2, offZ);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, -size / 2);
	glTexCoord2f(1, 0); glVertex3f(size / 2, -height, -size / 2);
	glTexCoord2f(1, 1); glVertex3f(size / 2, height, -size / 2);
	glTexCoord2f(0, 1); glVertex3f(-size / 2, height, -size / 2);

	glTexCoord2f(0, 0); glVertex3f(size / 2, -height, size / 2);
	glTexCoord2f(1, 0); glVertex3f(-size / 2, -height, size / 2);
	glTexCoord2f(1, 1); glVertex3f(-size / 2, height, size / 2);
	glTexCoord2f(0, 1); glVertex3f(size / 2, height, size / 2);

	glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, size / 2);
	glTexCoord2f(1, 0); glVertex3f(-size / 2, -height, -size / 2);
	glTexCoord2f(1, 1); glVertex3f(-size / 2, height, -size / 2);
	glTexCoord2f(0, 1); glVertex3f(-size / 2, height, size / 2);

	glTexCoord2f(0, 0); glVertex3f(size / 2, -height, -size / 2);
	glTexCoord2f(1, 0); glVertex3f(size / 2, -height, size / 2);
	glTexCoord2f(1, 1); glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(0, 1); glVertex3f(size / 2, height, -size / 2);

	glTexCoord2f(0, 0); glVertex3f(-size / 2, -height, size / 2);
	glTexCoord2f(1, 0); glVertex3f(size / 2, -height, size / 2);
	glTexCoord2f(1, 1); glVertex3f(size / 2, -height, -size / 2);
	glTexCoord2f(0, 1); glVertex3f(-size / 2, -height, -size / 2);


	glTexCoord2f(0, 0); glVertex3f(-size / 2, height, -size / 2);
	glTexCoord2f(1, 0); glVertex3f(size / 2, height, -size / 2);
	glTexCoord2f(1, 1); glVertex3f(size / 2, height, size / 2);
	glTexCoord2f(0, 1); glVertex3f(-size / 2, height, size / 2);

	glEnd();
	glTranslatef(-offX, -height / 2, -offZ);
}
