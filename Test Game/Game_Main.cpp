//
//	Game_Main.cpp
//	Test Game
//
//	Created by 师小洲 on 2019/3/16.
//	Copyright © 2019 师小洲. All rights reserved. 
//
#include "Main.h"
#pragma comment(lib, "Winmm.lib")

int main() {
	BKGD background;
	IMAGE button[15];
	BULLET *bullet;
	BULLET *head = NULL;
	QUESTION *question = NULL, *qhead = NULL, *pointer = NULL;
	USER user;
//	IMAGE mouseImage, mouseImage_r;
	IMAGE help, modeChoose, ranking;
	IMAGE animal[10], animal_r[10];
	MOUSEMSG Mouse;
	clock_t start, finish;
	clock_t startGame, finishGame;
	double duration, gameDuration;

	srand((unsigned)time(NULL));
	setBackground(&background);
//	loadimage(&mouseImage, "image/mouse.jpg");
//	loadimage(&mouseImage, "image/mouse_r.jpg");
	loadimage(&help, "image/helpPage.jpg");
	loadimage(&modeChoose, "image/mode.jpg");
	imageLoading(animal, animal_r);
	int change = 0;
	int mode = 1;
	double timeLeft = 0;

	mciSendString("open audio/game_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);

	while (1) {
		initgraph(WIDTH, HEIGHT);	//can showconsole if necessary
		int end = 0;
		int fail = 0;
		int deleteAnimal = 0;
		BeginBatchDraw();
		bullet = initBullet();
		head = bullet;
		initButton(button);
		int helpPage = 0;
		
		//The Welcome Page
		while (change == 0) {
			background.indexOfBackground = 0;
			displayBackground(&background);
			displayButton(button, &background);
			if (helpPage == 1) {
				putimage(0, 0, &help);
			}
			if (MouseHit()) {
				Mouse = GetMouseMsg();
			//	putimage(Mouse.x, Mouse.y, &mouseImage, SRCINVERT);
			//	putimage(Mouse.x, Mouse.y, &mouseImage_r, NOTSRCERASE);
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 300 && Mouse.y <= 340) {
						//area of start
						//如果上次有缓存, 判断是否要用上次的游戏记录
						change = 1;
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 380 && Mouse.y <= 420) {
						//area of help
						helpPage = 1;
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 460 && Mouse.y <= 500) {
					//  area of exit
					//	gameOver(question, bullet, &background);
						return 0;
					}
					else if (Mouse.x >= 760 && Mouse.x < 800 && Mouse.y >= 0 && Mouse.y <= 40) {
						helpPage = 0;
					}
				}
				else if (Mouse.uMsg == WM_MOUSEMOVE) {
					if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 300 && Mouse.y <= 340) {
						//change start button
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 380 && Mouse.y <= 420) {
						//change help button
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 460 && Mouse.y <= 500) {
						//change exit button
					}
					else {
						//displayButton();
					}
				}
			}
			FlushBatchDraw();
		}
		change = 0;
		int modeLoop = 0;
		while (modeLoop == 0) {
			putimage(0, 0, &modeChoose);
			FlushBatchDraw();
			char chooseMode;
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 350 && Mouse.x <= 450 && Mouse.y >= 195 && Mouse.y <= 245) {
						question = createQuestion(10, bullet);
						initAnimal(10, 1, question);
						timeLeft = 60;
					}
					else if (Mouse.x >= 320 && Mouse.x <= 483 && Mouse.y >= 275 && Mouse.y <= 325) {
						question = createQuestion(10, bullet);
						initAnimal(10, 2, question);
						timeLeft = 45;
					}
					else if (Mouse.x >= 300 && Mouse.x <= 500 && Mouse.y >= 355 && Mouse.y <= 405) {
						question = createQuestion(10, bullet);
						initAnimal(10, 4, question);
						timeLeft = 30;
					}
					modeLoop = 1;
				}
			}
		}
		
		background.indexOfBackground = 1;
		displayBackground(&background);
		user.score = 0;
		FlushBatchDraw();

		displayBullet(bullet);
		displayWindow(&user);
		displayScore(&user);

		int indexOfLoop = 0;
		int innerLoop = 0;
		char s[10];
		int fps = 0;
		int setBullet = 0;
		int time = 0;

		int answer = 0;
		int result = 0;
		int computeNum = 0;
		start = clock();

	//  main game loop
		startGame = clock();
		while (end == 0) {
			int chooseNum = 0; //time of choose question
			int buttonType = -1;
			int questionNum = -1;
			
			indexOfLoop++;
			time++;
			sprintf_s(s, "fps: %d", fps);
			if (indexOfLoop % 7 == 0) {
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				if (duration > 1) {
					start = clock();
					fps = innerLoop;
					innerLoop = 0;
				}
				putimage(0, 0, &background.background[3]);
				if (deleteAnimal == 0) {
					displayAnimal(question, animal, animal_r);
					displayQuestion(question);
					moveAnimal(question);
					checkBorder(question);
				}
				displayButton(button, &background);
				displayUsername(&user);
				outtextxy(700, 10, s);
				innerLoop++;
			}
			//Time bar
			finishGame = clock();
			gameDuration = (finishGame - startGame) / CLOCKS_PER_SEC;
			drawTime(timeLeft - gameDuration);

			if (timeLeft - gameDuration < 0) {
				fail++;
				end++;
			}
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				int mouseX = Mouse.x;
				int mouseY = Mouse.y;
			//	solidcircle(mouseX, mouseY, 5);
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (setBullet != 0 && mouseX >= 0 && mouseX <= GAME_WIDTH &&
						mouseY >= LINE_ONE && mouseY <= LINE_TWO + ANIMAL_HEIGHT) {
						mciSendString("stop shotmusic", NULL, 0, NULL);
						mciSendString("close shotmusic", NULL, 0, NULL);
						mciSendString("open audio/shot.mp3 alias shotmusic", NULL, 0, NULL);
						mciSendString("play shotmusic", NULL, 0, NULL);
						displayBullet(bullet);
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
									free(qhead);
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
									question = pointer;
								}
							}
							else {
								user.score -= 10;
								displayScore(&user);
							}
							answer = 0;
							result = 0;
						}
						setBullet = 0;
						computeNum++;
					}
					else if (mouseX >= GAME_WIDTH && mouseX <= WIDTH && mouseY >= 0 && mouseY <= GAME_HEIGHT) {
						//judge button
						buttonType = checkButton(mouseX, mouseY);
						if (buttonType == 1) {
							//do PAUSE;
							system("pause");
							end = 2;
							//putimage continue button
							
						}
						else if (buttonType == 2) {
						//  do Clear
							deleteAll(question);
							deleteAnimal = 1;
							MessageBox(GetHWnd(), "是否回到结束页面", "提示", MB_YESNO);
						}
						else if (buttonType == 3) {
							//whether save the game data?
							return 0;
						}
					}
					else if (mouseX >= 0 && mouseX <= GAME_WIDTH && mouseY >= GAME_HEIGHT && mouseY <= HEIGHT) {
						//judge bullet
						mciSendString("stop clickmusic", NULL, 0, NULL);
						mciSendString("close clickmusic", NULL, 0, NULL);
						mciSendString("open audio/click.mp3 alias clickmusic", NULL, 0, NULL);
						mciSendString("play clickmusic", NULL, 0, NULL);
						displayBullet(bullet);
						int bulletType = checkBullet(mouseX, mouseY, bullet);

						if (bulletType != -1) {
							for (int indexOfLoop = 0; indexOfLoop < bulletType; indexOfLoop++) {
								bullet = bullet->next;
							}
							answer = bullet->value;
							//change the bullet number color
							sprintf_s(s, "%d", bullet->value);
							setfillcolor(RED);
							solidcircle(bullet->x + BULLET_GAP / 2, bullet->y + BULLET_HEIGHT / 2, 20);
							RECT r = { bullet->x, bullet->y, bullet->x + BULLET_GAP, bullet->y + BULLET_HEIGHT };
							drawtext(_T(s), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

							setBullet++;
							bullet = head;
						}
					}
				}
			}
			if (_kbhit()) {
				int index = _getch();
				if (index >= 49 && index <= 52) {
					displayBullet(bullet);
					for (int i = 0; i < index - 49; i++) {
						bullet = bullet->next;
					}
					answer = bullet->value;
					sprintf_s(s, "%d", bullet->value);
					setfillcolor(RED);
					solidcircle(bullet->x + BULLET_GAP / 2, bullet->y + BULLET_HEIGHT / 2, 20);
					RECT r = { bullet->x, bullet->y, bullet->x + BULLET_GAP, bullet->y + BULLET_HEIGHT };
					drawtext(_T(s), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					bullet = head;
					setBullet++;
				}
			}
			if (user.score >= 100) {
				end = end + 2;
			}
			if (computeNum > 10 && user.score < 100) {
				fail++;
				end++;
			}
			FlushBatchDraw();
		}
		writeRecordFile(&user);

		IMAGE gameOver;
		loadimage(&gameOver, "image/gameOver.jpg");
		int recordPage = 0;
	//	End Page
		while (end == 2 || fail == 1) {
			//int scorePage = 0;
			//while (scorePage == 0) {
			//	//putimage 你的得分 && 是否保存游戏记录？
			//	//if(yes)->writeRecord   if(no)->do not write ,then cut the loop
			//}
			if (end == 2) {
				background.indexOfBackground = 2;
				displayBackground(&background);
			} 
			if (fail == 1) {
				putimage(0, 0, &gameOver);
			}
			MOUSEMSG Mouse;
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				switch (Mouse.uMsg) {
				case WM_LBUTTONDOWN:
					if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 270 && Mouse.y <= 310) {
						//area of restart
						end = 0;
						fail = 0;
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 360 && Mouse.y <= 400) {
						//area of ranking
						recordPage = 1;
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 450 && Mouse.y <= 490) {
					//	gameOver(question, bullet, &background);
						return 0;
					}
					else if (Mouse.x >= 760 && Mouse.x < 800 && Mouse.y >= 0 && Mouse.y <= 40) {
						recordPage = 0;
					}
				}
			}
			if (recordPage == 1) {
				loadimage(&ranking, "image/RankingPage.jpg");
				putimage(0, 0, &ranking);
				//display the elements in the ranking page
				drawRecordFile();
			}
			FlushBatchDraw();
		}
	}
	EndBatchDraw();
	_getch();
	closegraph();
	return 0;
}



