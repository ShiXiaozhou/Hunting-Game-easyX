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
	//初始化变量
	USER user;
	BKGD background;
	IMAGE button[15];
	MOUSEMSG Mouse;
	BULLET *bullet, *head = NULL;
	IMAGE help, modeChoose, ranking, gameOver;	//用于储存各界面背景图片
	IMAGE animal[10], animal_r[10];	//用于储存动物图片
	clock_t start, finish;	//用于计算帧数
	clock_t startGame, finishGame;	//用于显示游戏时间
	IMAGE recoverBtn, continueBtn;
	IMAGE startBtn_r, helpBtn_r, exitBtn_r, back;
	QUESTION *question = NULL, *qhead = NULL, *pointer = NULL;
	double duration, gameDuration, timeLeft;
	srand((unsigned)time(NULL));
	initgraph(WIDTH, HEIGHT);

	//加载图片
	setBackground(&background);
	imageLoading(animal, animal_r);
	loadimage(&help, "image/helpPage.jpg");
	loadimage(&modeChoose, "image/mode.jpg");
	loadimage(&startBtn_r, "image/START1.jpg");
	loadimage(&helpBtn_r, "image/Help1.jpg");
	loadimage(&exitBtn_r, "image/EXIT1.jpg");
	loadimage(&back, "image/START2.jpg");
	loadimage(&recoverBtn, "image/recovery.jpg");
	loadimage(&continueBtn, "image/CONTINUE_BUTTON.jpg");
	loadimage(&gameOver, "image/gameOver.jpg");
	loadimage(&ranking, "image/RankingPage.jpg");
	//播放背景音乐
	mciSendString("open audio/game_music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);

	while (1) {
		//初始化变量
		char s[10];
		int end = 0;
		int fail = 0;
		int deleteAnimal = 0;
		int helpPage = 0;
		int modeLoop = 0;
		int change = 0;
		int indexOfLoop = 0;
		int innerLoop = 0;
		int fps = 0;
		int setBullet = 0;
		int answer = 0;
		int result = 0;
		int computeNum = 0;
		int deleteNum = 0;
		int pause = 0;
		int pauseNum = 0;
		int recordPage = 0;
		int questionNum = 0;
		int windowOption = 0;
		int startShift = 0, shiftNum = 0;
		double shift = 0, shiftSum = 0;

		initButton(button);
		bullet = initBullet();
		head = bullet;
		questionNum = readQuestionNum(&user);
		question = createQuestion(questionNum, bullet);
		initAnimal(questionNum, 1, question);
		BeginBatchDraw();

		//开始界面的循环
		while (change == 0) {
			background.indexOfBackground = 0;
			displayBackground(&background);
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
						return 0;
					}
					else if (Mouse.x >= 760 && Mouse.x < 800 && Mouse.y >= 0 && Mouse.y <= 40) {
						helpPage = 0;
					}
				}
				FlushBatchDraw();
			}
		}
		//读取游戏状态
		if (MessageBox(GetHWnd(), "是否继续上次游戏进度？", "提示", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK) {
			timeLeft = readData(&user, bullet, question);
			modeLoop = 1;
			windowOption++;
		}
		//游戏模式选择
		while (modeLoop == 0) {
			putimage(0, 0, &modeChoose);
			FlushBatchDraw();
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

		start = clock();
		startGame = clock();
		background.indexOfBackground = 1;
		displayBackground(&background);
		FlushBatchDraw();

		displayBullet(bullet);
		if (windowOption == 0) {
			displayWindow(&user);
			user.score = 0;
		}
		displayScore(&user);
		//游戏主流程函数
		while (end == 0) {
			int chooseNum = 0;	//作答题目的次数
			int buttonType = -1;
			int questionIndex = -1;
			sprintf_s(s, "fps: %d", fps);
			indexOfLoop++;
			//控制刷新频率
			if (indexOfLoop % 7 == 0) {
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				putimage(0, 0, &background.background[3]);
				if (duration > 1) {
					start = clock();
					fps = innerLoop;
					innerLoop = 0;
				}
				if (deleteAnimal == 0) {
					displayAnimal(question, animal, animal_r);
					displayQuestion(question);
					if (pause == 0) {
						moveAnimal(question);
					}
					checkBorder(question);
					pointer = copyList(question);
				}
				displayButton(button, &background);
				if (deleteAnimal == 1) {
					//恢复删除按钮
					putimage(666, 260, &recoverBtn);
				}
				if (pause == 1) {
					//继续按钮
					putimage(666, 160, &continueBtn);
				}
				displayUsername(&user);
				outtextxy(700, 10, s);
				innerLoop++;
			}
			//显示时间条
			if (pause == 0) {
				if (shiftNum != 0) {
					shiftSum += clock();
					shiftNum = 0;
				}
				finishGame = clock();
				gameDuration = (finishGame - startGame - shiftSum + shift) / CLOCKS_PER_SEC;
			}
			else if (startShift == 0) {
				shift += clock();
				startShift = 1;
				shiftNum = 1;
			}
			drawTime(timeLeft - gameDuration);

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
						questionIndex = checkQuestion(mouseX, mouseY, question);
						if (questionIndex != -1) {
							result = computeResult(question, questionIndex);
							//比较子弹的答案与数学题答案
							qhead = question;
							pointer = question;
							if (answer == result) {
								user.score += 10;
								displayScore(&user);
								//删除作答正确的数学题
								if (questionIndex == 0) {
									question = question->next;
									free(qhead);
								}
								else {
									for (int i = 0; i < questionIndex; i++) {
										question = question->next;
									}
									for (int index = 0; index < questionIndex - 1; index++) {
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
						user.questionLeft = 10 - computeNum;
					}
					else if (mouseX >= GAME_WIDTH && mouseX <= WIDTH && mouseY >= 0 && mouseY <= GAME_HEIGHT) {
						//判断按钮
						buttonType = checkButton(mouseX, mouseY);
						if (buttonType == 1) {
							//暂停
							if (pauseNum == 1) {
								pause = 0;
								pauseNum = 0;
							}
							else {
								pause = 1;
								pauseNum++;
								startShift = 0;
							}
						}
						else if (buttonType == 2) {
							//删除全部数学题
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
							//退出游戏前可选是否存档
							if (MessageBox(GetHWnd(), "是否保存此次游戏数据？", "提示", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDOK) {
								writeData(&user, timeLeft - gameDuration, bullet, question);
							}
							return 0;
						}
					}
					else if (mouseX >= 0 && mouseX <= GAME_WIDTH && mouseY >= GAME_HEIGHT && mouseY <= HEIGHT) {
						//点击音效
						mciSendString("stop clickmusic", NULL, 0, NULL);
						mciSendString("close clickmusic", NULL, 0, NULL);
						mciSendString("open audio/click.mp3 alias clickmusic", NULL, 0, NULL);
						mciSendString("play clickmusic", NULL, 0, NULL);
						//判断子弹
						displayBullet(bullet);
						int bulletType = checkBullet(mouseX, mouseY, bullet);
						if (bulletType != -1) {
							for (int indexOfLoop = 0; indexOfLoop < bulletType; indexOfLoop++) {
								bullet = bullet->next;
							}
							answer = bullet->value;
							//选中后改变子弹颜色
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
			//判断游戏状态
			if (timeLeft - gameDuration < 0) {
				fail++;
				end++;
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

		//游戏结束页面
		while (end == 2 || fail == 1) {
			if (end == 2) {
				background.indexOfBackground = 2;
				displayBackground(&background);
			}
			if (fail == 1) {
				putimage(0, 0, &gameOver);
			}

			if (MouseHit()) {
				Mouse = GetMouseMsg();
				if (Mouse.uMsg == WM_LBUTTONDOWN) {
					if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 270 && Mouse.y <= 310) {
						//重新开始按钮
						end = 0;
						fail = 0;
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 360 && Mouse.y <= 400) {
						//排行榜按钮
						recordPage = 1;
					}
					else if (Mouse.x >= 310 && Mouse.x <= 490 && Mouse.y >= 450 && Mouse.y <= 490) {
						//游戏结束按钮
						return 0;
					}
					else if (Mouse.x >= 760 && Mouse.x < 800 && Mouse.y >= 0 && Mouse.y <= 40) {
						//关闭排行榜按钮
						recordPage = 0;
					}
				}
			}
			if (recordPage == 1) {
				putimage(0, 0, &ranking);
				drawRecordFile(&user);
			}
			FlushBatchDraw();
		}
	}

	EndBatchDraw();
	_getch();
	closegraph();
	return 0;
}



