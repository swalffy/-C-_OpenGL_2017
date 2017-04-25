#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib,"glu32.lib")
#include <gl/glut.h>
using namespace sf;

int displX = 1920, displY = 1080;
float angleX, angleY;
float x = 0, y = 0, z = 0;
float sensitivity = 2.0;
float const PI = 3.1415;
float size = 20.f;

GLuint GetTexture(sf::String name) {
	sf::Image image;
	image.loadFromFile(name);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return texture;
}

class Stage {
protected:
	float size;
	GLuint texture;
public:
	Stage() {

	}
	Stage(float _size, GLuint _texture) {
		size = _size;
		texture = _texture;
		glTranslatef(x*size + size, y, z*size + size);
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
		glTranslatef(-x*size - size , y, -z*size - size);
	}
};
class Wall : public Stage {
	enum Direction {
		Hor = true,
		Ver = false
	};
	float weight;
	float height;
	Wall(float _size, GLuint _texture, Direction dir) {
		weight = 1 * _size;
		height = 1.5 * _size;
		texture = _texture;
		if (dir) {
			glTranslatef(x*size + size, y, z*size + size);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0, 0); glVertex3f(-weight, -height, -size);
			glTexCoord2f(1, 0); glVertex3f(weight, -height, -size);
			glTexCoord2f(1, 1); glVertex3f(weight, height, -size);
			glTexCoord2f(0, 1); glVertex3f(-weight, height, -size);

			glTexCoord2f(0, 0); glVertex3f(weight, -height, size);
			glTexCoord2f(1, 0); glVertex3f(-weight, -height, size);
			glTexCoord2f(1, 1); glVertex3f(-weight, height, size);
			glTexCoord2f(0, 1); glVertex3f(weight, height, size);

			glTexCoord2f(0, 0); glVertex3f(-weight, -height, size);
			glTexCoord2f(1, 0); glVertex3f(-weight, -height, -size);
			glTexCoord2f(1, 1); glVertex3f(-weight, height, -size);
			glTexCoord2f(0, 1); glVertex3f(-weight, height, size);

			glTexCoord2f(0, 0); glVertex3f(weight, -height, -size);
			glTexCoord2f(1, 0); glVertex3f(weight, -height, size);
			glTexCoord2f(1, 1); glVertex3f(weight, height, size);
			glTexCoord2f(0, 1); glVertex3f(weight, height, -size);

			glTexCoord2f(0, 0); glVertex3f(-weight, -height, size);
			glTexCoord2f(1, 0); glVertex3f(weight, -height, size);
			glTexCoord2f(1, 1); glVertex3f(weight, -height, -size);
			glTexCoord2f(0, 1); glVertex3f(-weight, -height, -size);

			glTexCoord2f(0, 0); glVertex3f(-weight, height, -size);
			glTexCoord2f(1, 0); glVertex3f(weight, height, -size);
			glTexCoord2f(1, 1); glVertex3f(weight, height, size);
			glTexCoord2f(0, 1); glVertex3f(-weight, height, size);

			glEnd();
			glTranslatef(-x*size - size, y, -z*size - size);
		}
		else if (!dir) {

		}
	}
};

class Character {
public:
	float x, y, z;
	float dx, dy, dz;
	float w, h, d; 
	float speed;
	
	Character(float _x, float _y, float _z) {
		x = _x; y = _y; z = _z;
		dx = 0; dy = 0; dz = 0;
		w = 5; h = 20; d = 5; speed = 40;
	}

	void update(float time) {
		x += dx*time;
		y += dy*time;
		z += dz*time;
		dx = dz = 0;
	}

	void keyboard() {
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
	}

};

int main() {
	RenderWindow window(VideoMode(displX, displY), "Escape from Labyrinth");
	ShowCursor(FALSE);
	Texture t;
	t.loadFromFile("assets/background.jpg");
	Sprite background(t);

	GLuint texture = 0;
	texture = GetTexture("assets/myside.jpg");

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 3000.f);
	glEnable(GL_TEXTURE_2D);

	Character pl(300, 500, 300);
	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time /= 50;
		if (time>3) 
			time = 3;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		pl.keyboard();
		pl.update(time);

		//----[Rotate camera]-----------
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
		//-------------------------------
		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pl.x, pl.y + pl.h / 2, pl.z,
			pl.x - sin(angleX / 180 * PI),
			pl.y + pl.h / 2 + (tan(angleY / 180 * PI)),
			pl.z - cos(angleX / 180 * PI),
			0, 1, 0);

		Stage a(1500.f, texture);
		Wall b(1500.f,texture,Hor);
		window.display();
	}
	glDeleteTextures(1, &texture);
	return 0;
}