#include "Source.h"
#include "Wall.h"
#include "Character.h"
#include "bonus.h"

void ftimeChanger(float &ftime, sf::Clock &clock, int &fsize, float &df) {
	ftime -= clock.getElapsedTime().asSeconds()*10;
	if (ftime * 10 < 10) {
		if (fsize < 28)
			df = 1.05;
		if (fsize > 38)
			df = 0.98;
		fsize *= df;
	}
}
void glutLookAt(Character &pl) {
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pl.xPos, pl.yPos + pl.h / 2, pl.zPos,
		pl.xPos - sin(angleX / 180 * PI),
		pl.yPos + pl.h / 2 + (tan(angleY / 180 * PI)),
		pl.zPos - cos(angleX / 180 * PI),
		0, 1, 0);
}
void glutSettings() {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 8000.f);
	glEnable(GL_TEXTURE_2D);
}
void generateOuterWalls(std::vector<Wall> &walls, const GLuint &texture) {

	walls.push_back(Wall(stageSize * 2, texture, Vertikal, 0, stageSize));
	walls.push_back(Wall(stageSize * 2, texture, Horizontal, stageSize, 0));
	walls.push_back(Wall(stageSize * 2, texture, Horizontal, stageSize, stageSize * 2));
	walls.push_back(Wall(stageSize * 2, texture, Vertikal, stageSize * 2, stageSize));
	glTranslatef(stageSize, 0, stageSize);
	Stage a(stageSize, texture);
	glTranslatef(-stageSize, 0, -stageSize);
}
void generateInnerWalls(std::vector<Wall> &walls, const GLuint &texture, std::vector<std::string> &str) {
	for (int j = 0; j < str.size(); j++) {
		int k = 0;
		for (int i = 1; i <= str[j].size(); i++) {
			if (str[j][i - 1] == ' ')
				continue;
			if (str[j][i - 1] == '|') {
				walls.push_back(Wall(stageSize / 5, texture, Horizontal, stageSize / 10 * (j * 2 + 1), stageSize / 10 * (i - k - 1) * 2));
				k++;
			}
			if (str[j][i - 1] == '_')
				if (j == 19)
					continue;
				else
					walls.push_back(Wall(stageSize / 5, texture, Vertikal, stageSize / 10 * (2 + 2 * j), stageSize / 10 * ((i - k) * 2 - 1)));
		}
	}
}
void rotateCam(sf::RenderWindow &window) {
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
}
void generateWalls(std::vector<std::string>& map) {
	srand(time(0));
	int j = 0;
	int size = 10;
	std::string tempstr;
	for (int i = 0; i < size; i++)
		tempstr += ' ';
	int id[15]{ NULL };
	do {
		for (int i = 1; i <= 15; i++) {
			if (id[i-1] == NULL)
				for (int q = i; q <= 15; q++)
					if (isFree(id, q)) {
						id[i-1] = q;
						break;
					}		
		}
		int i = 1;
		int walls = 0;
		do{
			if (id[i-1] == id[i]) 				{
				tempstr.insert(tempstr.begin() + i+walls, '|');
				walls++;
			}
			else 				{
				if (rand() % 2) {
					tempstr.insert(tempstr.begin() + i+walls, '|');
					walls++;
				}
				else
					id[i] = id[i-1];
			}
			i++;
		} while (i < size);

		i = 0;
		walls = 0;
		do {
			if (tempstr[i+walls] == '|') 	{
				walls++;
				continue;
			}
			bool isHole = false;
			int temp = id[i];
			do {
				if (tempstr[i + walls] == '|') 	{
					walls++;
				}
				if (rand() % 2)
					tempstr[i + walls] = '_';
				else
					isHole = true;
				i++;
			} while (id[i] == temp && (i + walls) < tempstr.size());
			if (!isHole)
				tempstr[i - 1 + walls] = ' ';
		} while (i+walls < tempstr.size());

		map.push_back(tempstr);
		for (int i = 0; i < tempstr.size(); i++) {
			if (tempstr[i] == '|') {
				tempstr.erase(tempstr.begin() + i);
				i--;
			}
			if (tempstr[i] == '_') {
				tempstr[i] = ' ';
				id[i] = NULL;
			}
		}
		j++;
	} while (j < 10);
	return;
}
bool isFree(int id[15], int num) {
	for (int i = 0; i < 15; i++)
		if (id[i] == num)
			return false;
	return true;
}
void createSkyBox(GLuint skybox[6], int size) {
	glBindTexture(GL_TEXTURE_2D, skybox[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);   glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0);   glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1);   glVertex3f(size, size, -size);
	glTexCoord2f(0, 1);   glVertex3f(-size, size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skybox[5]);
	glBegin(GL_QUADS);	
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();
}
GLuint GetTexture(sf::String name) {
	sf::Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;
	image.flipVertically();
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	return texture;
}
void getAllTextures(GLuint &texture, GLuint  skybox[6]) {
	texture = GetTexture("assets/myside.jpg");
	skybox[0] = GetTexture("assets/skybox/3.jpg");
	skybox[1] = GetTexture("assets/skybox/5.jpg");
	skybox[2] = GetTexture("assets/skybox/2.jpg");
	skybox[3] = GetTexture("assets/skybox/4.jpg");
	skybox[4] = GetTexture("assets/skybox/6.jpg");
	skybox[5] = GetTexture("assets/skybox/1.jpg");
}
int gameFunct(bool fullscreen) 	{
	srand(time(0));
	std::vector<std::string> maplines;
	generateWalls(maplines);

	bool bonusAvalible = true;
	int bPosX = rand() % (int)(stageSize * 2);
	int bPosZ = rand() % (int)(stageSize * 2);
	bonus bType;
	if (rand() % 2)
		bType = addtime;
	else
		bType = fly;
	int ePosX = 2800;
	int ePosZ = 2800;

	float ftime = 3;
	Font font;
	font.loadFromFile("assets/CyrilicOld.TTF");
	int fsize = 30;
	float df = 1.1;
	Text timeLeft("", font, fsize);
	timeLeft.setStyle(sf::Text::Bold);

	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 2;
		RenderWindow window(VideoMode(displX, displY), "Game|Escape from Labyrinth",  (fullscreen? sf::Style::Fullscreen: sf::Style::Resize), window_settings);
	ShowCursor(FALSE);

	GLuint texture, skybox[6];
	getAllTextures(texture, skybox);

	glutSettings();

	Character pl(150, 300, 150);
	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time /= 50;
		if (time > 3)
			time = 3;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		std::vector<Wall> walls;

		rotateCam(window);

		ftimeChanger(ftime, clock, fsize, df);
		if (ftime < 0)
			return 0;
		timeLeft.setString(std::to_string(ftime * 10));
		timeLeft.setCharacterSize(fsize);

		glutLookAt(pl);
		generateInnerWalls(walls, texture, maplines);
		generateOuterWalls(walls, texture);
		createSkyBox(skybox, 4000);
		Bonus e(stageSize / 8, ePosX, ePosZ, win);
		if (bonusAvalible) {
			Bonus b(stageSize / 8, bPosX, bPosZ, bType);
			if (sqrt((pl.xPos - b.xPos)*(pl.xPos - b.xPos) + (pl.zPos - b.zPos)*(pl.zPos - b.zPos)) < pl.w * 10) {
				pl.takeBonus(b.type, ftime);
				bonusAvalible = false;
			}
		}
		if (sqrt((pl.xPos - e.xPos)*(pl.xPos - e.xPos) + (pl.zPos - e.zPos)*(pl.zPos - e.zPos)) < pl.w * 10)
			if (pl.takeBonus(e.type, ftime))
				return 1;

		window.pushGLStates();
		window.draw(timeLeft);
		window.popGLStates();
		if (Keyboard::isKeyPressed(Keyboard::Tilde)) {
			std::string code;
			std::cin >> code;
			if (code == "hesoyam") {
				ftime += 3;
			}
			else if (code == "whosyourdaddy") {
				pl.godMode();
			}
		}

		pl.keyboard(angleX, angleY);
		pl.update(time, walls);
		window.display();
	}
	glDeleteTextures(1, &texture);
	return 0;
}
int mainMenuFunc() {
	Texture background, newGame, options, exit;
	background.loadFromFile("assets/menu.jpg");
	newGame.loadFromFile("assets/btn.png");
	options.loadFromFile("assets/btn.png");
	exit.loadFromFile("assets/btn.png");
	Sprite menuBack(background), menuNew(newGame), menuOptions(options), menuExit(exit);
	menuNew.setPosition(885, 440);
	menuOptions.setPosition(885, 520);
	menuExit.setPosition(885, 600);

	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 2;
	glutSettings();
	RenderWindow window(VideoMode(1360, 768), "MainMenu|Escape from Labyrinth", sf::Style::Resize || sf::Style::Close, window_settings);
	while (window.isOpen()) {
		ShowCursor(TRUE);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
		}
		int menuNum = 0;
		if (IntRect(885, 440, 400, 70).contains(Mouse::getPosition(window)))
			menuNum = 1;
		if (IntRect(885, 520, 400, 70).contains(Mouse::getPosition(window)))
			menuNum = 2;
		if (IntRect(885, 600, 400, 70).contains(Mouse::getPosition(window)))
			menuNum = 3;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1)
				return 1;
			if (menuNum == 2)
				return 2;
			if (menuNum == 3)
				return 0;
		}
		window.draw(menuBack);
		window.draw(menuNew);
		window.draw(menuOptions);
		window.draw(menuExit);
		window.display();
	}
}
int optionsFunc() {
	Texture background;
	background.loadFromFile("assets/options.jpg");
	Sprite menuBack(background);
	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 2;
	glutSettings();
	RenderWindow window(VideoMode(1360, 768), "Options|Escape from Labyrinth", sf::Style::Resize || sf::Style::Close, window_settings);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
			return 1;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
			return 0;
		window.draw(menuBack);
		window.display();
	}
}
void msgFunc(bool result) {
	Texture background;
	if (result)
		background.loadFromFile("assets/complite.jpg");
	else
		background.loadFromFile("assets/die.jpg");
	Sprite menuBack(background);
	float ftime = 20;
	Clock clock;
	sf::ContextSettings window_settings;
	window_settings.depthBits = 24;
	window_settings.stencilBits = 8;
	window_settings.antialiasingLevel = 2;
	glutSettings();
	RenderWindow window(VideoMode(1360, 768), "Options|Escape from Labyrinth", sf::Style::Resize || sf::Style::Close, window_settings);
	while (window.isOpen()) {
		ftime -= clock.getElapsedTime().asSeconds();
		window.draw(menuBack);
		window.display();
		if (ftime < 0)
			return;
	}
}