//
//	Game_Main.cpp
//	Test Game
//	
//	Created by 师小洲 on 2019/3/16.
//	Copyright © 2019 师小洲. All rights reserved. 
//
#include "Main.h"

int main() {
	BKGD background;
	IMAGE button[15];
	BULLET *bullet;
	BULLET *head = NULL;
	QUESTION *question, *qhead = NULL, *pointer = NULL;
	USER user;
	IMAGE mouseImage;
	IMAGE animal[10], animal_r[10];
	MOUSEMSG Mouse;
	clock_t start, finish;
	double duration;

	srand((unsigned)time(NULL));
	setBackground(&background);
	loadimage(&mouseImage, "image/mouse.jpg");
	imageLoading(animal, animal_r);
	int change = 0;
	int end = 0;

	while (1) {

		initgraph(WIDTH, HEIGHT);
		BeginBatchDraw();
		bullet = initBullet();
		head = bullet;
		initButton(button);

		//The Welcome Page
		while (change == 0) {
			background.indexOfBackground = 0;
			displayBackground(&background);
			displayButton(button, &background, &user);
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 300 && Mouse.y <= 340) {
						//area of start
						change = 1;
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 380 && Mouse.y <= 420) {
						//area of help
						IMAGE help;
						loadimage(&help, "image/helpPage.jpg");
						putimage(0, 0, &help);
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 460 && Mouse.y <= 500) {
						//area of exit
					//	gameOver(question, bullet, &background);
						return 0;
					}
					break;
				}
			}
			FlushBatchDraw();
		}
		change = 0;

		question = createQuestion(10, bullet);
		initAnimal(10, 2, question);
		
		background.indexOfBackground = 1;
		displayBackground(&background);
		user.score = 0;

		displayBullet();
		displayBulletNumber(bullet);
		displayWindow(&user);
		displayScore(&user);

		int indexOfLoop = 0;
		int innerLoop = 0;
		char s[10];
		int fps = 0;
		start = clock();
		int setBullet = 0;

		int answer = 0;
		int result = 0;

	//  main game loop
		while (end == 0) {
			indexOfLoop++;
			sprintf_s(s, "fps: %d", fps);
			
			int chooseNum = 0; //time of choose question
			int buttonType = -1;
			int questionNum = -1;

			if (indexOfLoop % 7 == 0) {
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				if (duration > 1) {
					start = clock();
					fps = innerLoop;
					innerLoop = 0;
				}
				putimage(0, 0, &background.background[3]);
				displayAnimal(question, animal, animal_r);
				displayQuestion(question);
				moveAnimal(question);
				checkBorder(question);
				displayButton(button, &background, &user);
				outtextxy(700, 10, s);
				innerLoop++;
			}

			if (MouseHit()) {
				Mouse = GetMouseMsg();
				int mouseX = Mouse.x;
				int mouseY = Mouse.y;
			//	solidcircle(mouseX, mouseY, 5);
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (setBullet == 1 && mouseX >= 0 && mouseX <= GAME_WIDTH &&
						mouseY >= LINE_ONE && mouseY <= LINE_TWO + ANIMAL_HEIGHT) {
						questionNum = checkQuestion(mouseX, mouseY, question);
						if (questionNum != -1) {
							result = computeResult(question, questionNum);
							//compare the answer with the result
							qhead = question;
							pointer = question;
							if (answer == result) {
								user.score += 10;
								displayScore(&user);
								//free the question from the linked list
								if (questionNum == 0) {
									question = question->next;
									free(question);
								}
								else {
									for (int i = 0; i < questionNum; i++) {
										question = question->next;
									}
									for (int index = 0; index < questionNum - 1; index++) {
										qhead = qhead->next;
									}
									qhead->next = question->next;
									free(question);
									//update the position
								}
								question = pointer;
							}
							else {
								user.score -= 10;
								displayScore(&user);
							}
							answer = 0;
							result = 0;
						}
						setBullet = 0;
					}
					else if (mouseX >= GAME_WIDTH && mouseX <= WIDTH && mouseY >= 0 && mouseY <= GAME_HEIGHT) {
						//judge button
						buttonType = checkButton(mouseX, mouseY);

						if (buttonType == 1) {
							//do PAUSE;
							system("pause");
							//putimage continue button
						}
						else if (buttonType == 2) {
							//do Clear
							deleteAll(question);
						}
						else if (buttonType == 3) {
							//	gameOver(question, bullet, &background);
							return 0;
						}
					}
					else if (mouseX >= 0 && mouseX <= GAME_WIDTH && mouseY >= GAME_HEIGHT && mouseY <= HEIGHT) {
						//judge bullet
						int bulletType = checkBullet(mouseX, mouseY, bullet);
						if (bulletType != -1) {
							for (int indexOfLoop = 0; indexOfLoop < bulletType; indexOfLoop++) {
								bullet = bullet->next;
							}
							answer = bullet->value;
							setBullet++;
							bullet = head;
						}
					}
				}
			}
			if (user.score >= 100) {
				end++;
			}
			FlushBatchDraw();
		}

	//	End Page
		while (end == 1) {
			background.indexOfBackground = 2;
			displayBackground(&background);
			displayButton(button, &background, &user);
			MOUSEMSG Mouse;
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				switch (Mouse.uMsg) {
				case WM_LBUTTONDOWN:
					if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 270 && Mouse.x <= 310) {
						//area of restart
						//how to restart?
						break;
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 360 && Mouse.y <= 400) {
						//area of ranking
						IMAGE ranking;
						loadimage(&ranking, "image/rankingPage.jpg");
						putimage(0, 0, &ranking);
						//display the elements in the ranking page
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 450 && Mouse.y <= 490) {
						//	gameOver(question, bullet, &background);
						return 0;
					}
					//	case WM_MOUSEMOVE:
							//button style
				}
			}
			FlushBatchDraw();
		}
		end = 0;
	}
	EndBatchDraw();
	_getch();
	closegraph();
	return 0;
}



