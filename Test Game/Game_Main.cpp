#include "run.h"

int main() {
	GAME game;
	IMAGE mouse;
	BULLET *bullet;
	bullet = (BULLET *)malloc(sizeof(BULLET));
	BULLET bul;
	int mouseX = game.mouse.x, mouseY = game.mouse.y;

	initgraph(WIDTH, HEIGHT);
	loadimage(&mouse, "image/mouse.jpg");

    initButton(game);
	setBackground(game);
	game.indexOfBackground = 2;
	displayBackground(game);
	displayButton(game);
	displayBullet();
	displayScore(game);
	displayWindow(game);

	/*initAnimal(1, 1, 1);
	bullet = initBullet(bul);
	createQuestion(10, bullet);
	displayQuestion(game.question);
	displayButtonNumber(bullet);*/

	while (1) {
		
		if (MouseHit()) {
			game.mouse = GetMouseMsg();
			switch (game.mouse.uMsg) {
			case WM_LBUTTONDOWN:
				if (mouseX >= 0 && mouseX <= GAME_WIDTH && mouseY >= 0 && mouseY <= GAME_HEIGHT) {
					//warning tone
				}
				else if (mouseX >= GAME_WIDTH && mouseX <= WIDTH && mouseY >= 0 && mouseY <= GAME_HEIGHT) {
					//judge button
					int buttonType = 0 ;/*= checkButton(mouseX, mouseY)*/
					if (buttonType == 1) {
						// do PAUSE 
						/*
						the pause button replaced by continue button
						animal and question stop
						time stop
						*/
					}
					else if (buttonType == 2) {
						//do Clear
						/*
						delete all the animals and questions 
						change the delete button to create
						*/
					}
					else if (buttonType == 3) {
						//do EXIT
					}
				}
				else if (mouseX >= GAME_WIDTH && mouseX <= WIDTH && mouseY >= GAME_HEIGHT && mouseY <= HEIGHT) {
					//judge bullet
				}
				else {
					return -1;
				}
			case WM_MOUSEMOVE:
				putimage(mouseX, mouseY, &mouse);
			default:
				continue;
			}
		}
	}

	_getch();
	closegraph();
	return 0;
}

