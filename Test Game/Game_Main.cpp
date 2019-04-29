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
	IMAGE help, modeChoose, ranking;
	IMAGE animal[10], animal_r[10];
	MOUSEMSG Mouse;
	clock_t start, finish;
	clock_t startGame, finishGame;
	IMAGE startBtn, helpBtn, exitBtn, recover;
	IMAGE startBtn_r, helpBtn_r, exitBtn_r, back;
	double duration, gameDuration;

	srand((unsigned)time(NULL));
	setBackground(&background);
	loadimage(&help, "image/helpPage.jpg");
	loadimage(&modeChoose, "image/mode.jpg");
	imageLoading(animal, animal_r);
	int change = 0;
	int mode = 1;
	double timeLeft = 0;
	//loadimage(&startBtn, "image/CTA_2.jpg");
	//loadimage(&helpBtn, "image/CTA_3.jpg");
	//loadimage(&exitBtn, "image/CTA_4.jpg");
	loadimage(&startBtn_r, "image/START1.jpg");
	loadimage(&helpBtn_r, "image/Help1.jpg");
	loadimage(&exitBtn_r, "image/EXIT1.jpg");
	loadimage(&back, "image/START2.jpg");
	loadimage(&recover, "image/recovery.jpg");

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
		question = createQuestion(10, bullet);
		int helpPage = 0;
		int modeLoop = 0;
		
		//The Welcome Page
		while (change == 0) {
			background.indexOfBackground = 0;
			displayBackground(&background);
		//	displayButton(button, &background);
			if (helpPage == 1) {
				putimage(0, 0, &help);
			}
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 300 && Mouse.y <= 340) {
						putimage(315, 300, &back, SRCAND);
						putimage(315, 300, &startBtn_r, SRCINVERT);
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 380 && Mouse.y <= 420) {
						putimage(315, 380, &back, SRCAND);
						putimage(315, 380, &helpBtn_r, SRCINVERT);
					}
					else if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 460 && Mouse.y <= 500) {
						putimage(315, 460, &back, SRCAND);
						putimage(315, 460, &exitBtn_r, SRCINVERT);
					}
				}
				if (Mouse.uMsg == WM_LBUTTONUP) {
					if (Mouse.x >= 325 && Mouse.x <= 475 && Mouse.y >= 300 && Mouse.y <= 340) {
						//area of start
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
				
				FlushBatchDraw();
				
			}
			
		}
		change = 0;
		
		while (modeLoop == 0) {
			putimage(0, 0, &modeChoose);
			FlushBatchDraw();
			if (MouseHit()) {
				Mouse = GetMouseMsg();
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 350 && Mouse.x <= 450 && Mouse.y >= 195 && Mouse.y <= 245) {
						initAnimal(10, 1, question);
						timeLeft = 60;
					}
					else if (Mouse.x >= 320 && Mouse.x <= 483 && Mouse.y >= 275 && Mouse.y <= 325) {
						initAnimal(10, 2, question);
						timeLeft = 45;
					}
					else if (Mouse.x >= 300 && Mouse.x <= 500 && Mouse.y >= 355 && Mouse.y <= 405) {
						initAnimal(10, 4, question);
						timeLeft = 30;
					}
					modeLoop = 1;
				}
			}
		}
		/*MessageBox(GetHWnd(), "是否继续游戏？", "提示", MB_YESNO);
		timeLeft = readData(&user, bullet, question);*/
		
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
		int deleteNum = 0;
		int pause = 0;
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
					pointer = copyList(question);
				}
				displayButton(button, &background);
				if (deleteAnimal == 1) {
					putimage(666, 260, &recover);
				}
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
									pointer = copyList(question);
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
							pause = 1;
							
						}
						else if (buttonType == 2) {
						//  do Clear
							if (deleteNum == 1) {
								question = pointer;
								deleteNum = 0;
								deleteAnimal = 0;
							}
							else {
								deleteAll(question);
								deleteAnimal = 1;
								deleteNum++;
							}
							
						}
						else if (buttonType == 3) {
							//whether save the game data?
							MessageBox(GetHWnd(), "是否保存游戏数据？", "提示", MB_YESNO);
							writeData(&user, timeLeft - gameDuration, bullet, question);
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
		loadimage(&ranking, "image/RankingPage.jpg");
		int recordPage = 0;
	//	End Page
		while (end == 2 || fail == 1) {
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
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
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
				putimage(0, 0, &ranking);
				drawRecordFile(&user		);
			}
			FlushBatchDraw();
		}
	}
	EndBatchDraw();
	_getch();
	closegraph();
	return 0;
}



