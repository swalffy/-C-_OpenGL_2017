#ifndef globalVariables
#define globalVariables
int displX = 1920, displY = 1080;
float angleX, angleY;
float sensitivity = 15;
float stageSize = 1500.f;
#endif 

#ifndef globalVariables
#define globalVariables
int displX = 1920, displY = 1080;
float angleX, angleY;
float sensitivity = 15;
float stageSize = 1500.f;
#endif 
#include "Source.h"
#include "Wall.h"
#include "Character.h"
#include "bonus.h"
int main() {
	bool fullscreen = false;
	while (true) {
		switch (mainMenuFunc()) {
		case 0:
			return 0;
			break;
		case 1:
			if (gameFunct(fullscreen) == 0)
				msgFunc(false);
			else
				msgFunc(true);
			
			break;
		case 2:
			if (optionsFunc())
				fullscreen = !fullscreen;
			break;
		}
	}
	
}
