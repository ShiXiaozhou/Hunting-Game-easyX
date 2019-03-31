#include "UI.h"

void setBackground(GAME &game) {
	GAME *pointer;
	pointer = (GAME *)malloc(sizeof(GAME));
	pointer = &game;
	IMAGE bk1;
	IMAGE bk2;
	IMAGE bk3;
	loadimage(&bk1, "image/StartBackground.jpg");
	loadimage(&bk2, "image/GameBackground.jpg");
	loadimage(&bk3, "image/EndBackground.jpg");
	pointer->background[1] = bk1;
	pointer->background[2] = bk2;
	pointer->background[3] = bk3;
}

int displayBackground(GAME game) {
	if (game.indexOfBackground == 1) {
		putimage(0, 0, &game.background[1]);
	}
	else if (game.indexOfBackground == 2) {
		putimage(0, 0, &game.background[2]);
	}
	else if (game.indexOfBackground == 3) {
		putimage(0, 0, &game.background[3]);
	}
	else {
		return -1;
	}
	//显示按钮区背景
	//需要改背景
	setfillcolor(RGB(120, 120, 120));
	solidrectangle(650, 0, 800, 450);

	return 0;
}

GAME *displayWindow(GAME &game) {
	GAME *pointer = &game;
	pointer = (GAME *)malloc(sizeof(GAME));
	LOGFONT f;
	InputBox(pointer->username, 20, "请输入用户名：");
	setbkmode(TRANSPARENT);
	gettextstyle(&f);
	f.lfHeight = 22;
	_tcscpy_s(f.lfFaceName, _T("微软黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(670, 54, "User Name: ");
	outtextxy(670, 80, pointer->username);
	return pointer;
}
/*显示按钮区，将按钮图片存入数组待取用*/
void initButton(GAME &game) {
	GAME *pointer = &game;

	//载入按钮并存入数组
	IMAGE startButton;
	IMAGE helpButton;

	IMAGE pauseButton;
	IMAGE deleteButton;
	IMAGE exitButton;
	IMAGE continueButton;
	IMAGE createButton;

	IMAGE restartButton;
	IMAGE rankingButton;
	loadimage(&startButton, "image/startButton.jpg");
	loadimage(&helpButton, "image/helpButton.jpg");

	loadimage(&pauseButton, "image/PAUSE_BUTTON.jpg");
	loadimage(&continueButton, "image/CONTINUE_BUTTON.jpg");
	loadimage(&deleteButton, "image/DELETE_BUTTON.jpg");
	loadimage(&exitButton, "image/EXIT_BUTTON.jpg");
	loadimage(&createButton, "image/CREATE_BUTTON.jpg");

	loadimage(&restartButton, "image/restartButton.jpg");
	loadimage(&rankingButton, "image/rankingButton.jpg");

	pointer->button[0] = rankingButton;
	pointer->button[1] = startButton;
	pointer->button[2] = helpButton;
	pointer->button[3] = pauseButton;
	pointer->button[4] = continueButton;
	pointer->button[5] = deleteButton;
	pointer->button[6] = createButton;
	pointer->button[7] = exitButton;
	pointer->button[8] = restartButton;
	
}

void displayButton(GAME game) {
	GAME *pointer;
	pointer = &game;
	IMAGE startButton;
	IMAGE helpButton;

	IMAGE pauseButton = pointer->button[3];
	IMAGE deleteButton = pointer->button[5];
	IMAGE exitButton = pointer->button[7];
	IMAGE continueButton;
	IMAGE createButton;

	IMAGE restartButton;
	IMAGE rankingButton;
	if (game.indexOfBackground == 1) {
		//putimage at according place
	}
	else if (game.indexOfBackground == 2) {
		putimage(666, 161, &pauseButton);
		putimage(666, 261, &deleteButton);
		putimage(666, 361, &exitButton);
	}
	else if (game.indexOfBackground == 3) {
		//putimage at according place
	}
}
//显示子弹区
void displayBullet() {
	IMAGE BULLET_R;
	IMAGE BULLET;

	loadimage(&BULLET_R, "image/BULLET.jpg");
	loadimage(&BULLET, "image/BULLET!.jpg");

	//显示分割线
	setcolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(0, 450, WIDTH, HEIGHT);

	for (int index = 0; index < 4; index++) {
		putimage(12 + index * BULLET_GAP, 470, &BULLET_R, SRCAND);
		putimage(12 + index * BULLET_GAP, 470, &BULLET, SRCINVERT);
	}
}

//显示得分区
void displayScore(GAME game) {
	//显示得分栏
	IMAGE board;
	loadimage(&board, "image/BOARD.jpg");
	putimage(658, 456, &board);

	//显示得分(坐标待计算)
	LOGFONT f;
	setbkmode(TRANSPARENT);
	gettextstyle(&f);
	f.lfHeight = 22;
	_tcscpy_s(f.lfFaceName, _T("微软黑体"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	settextstyle(&f);
	settextcolor(BLACK);
	outtextxy(670, 480, game.score);
}
//IMAGE generateAnimal(QUESTION *question, int IndexOfAnimal, BACKPLACE *img) {
//	QUESTION *p = question;
//	int indexOfAnimal;
//	IMAGE panda, pig, frog, goat, tiger, hippo, monkey, lion, dog, cat;
//	IMAGE panda_r, pig_r, frog_r, goat_r, tiger_r, hippo_r, monkey_r, lion_r, dog_r, cat_r;
//
//	loadimage(&panda, "image/panda.jpg");
//	/*loadimage(&pig, "image/pig.jpg");
//	loadimage(&frog, "image/frog.jpg");
//	loadimage(&goat, "image/goat.jpg");
//	loadimage(&tiger, "image/tiger.jpg");
//	loadimage(&hippo, "image/hippo.jpg");
//	loadimage(&monkey, "image/monkey.jpg");
//	loadimage(&lion, "image/lion.jpg");
//	loadimage(&dog, "image/dog.jpg");
//	loadimage(&cat, "image/cat.jpg");
//
//	loadimage(&panda_r, "image/panda_r.jpg");
//	loadimage(&pig_r, "image/pig_r.jpg");
//	loadimage(&frog_r, "image/frog_r.jpg");
//	loadimage(&goat_r, "image/goat_r.jpg");
//	loadimage(&tiger_r, "image/tiger_r.jpg");
//	loadimage(&hippo_r, "image/hippo_r.jpg");
//	loadimage(&monkey_r, "image/monkey_r.jpg");
//	loadimage(&lion_r, "image/lion_r.jpg");
//	loadimage(&dog_r, "image/dog_r.jpg");
//	loadimage(&cat_r, "image/cat_r.jpg");*/
//
//	switch (indexOfAnimal) {
//	case 0:
//		while (1) {
//			BeginBatchDraw();
//			clearrectangle(p->animal.x, p->animal.y, p->animal.x + ANIMAL_WIDTH, p->animal.y + ANIMAL_HEIGHT);
//			putimage(p->animal.x, p->animal.y, &img->bp0);
//			putimage(p->animal.x, p->animal.y, &panda_r, SRCAND);
//			putimage(p->animal.x, p->animal.y, &panda, SRCINVERT);
//			EndBatchDraw();
//			Sleep(12);
//		}
//		break;
//	default:
//		while (1) {
//			BeginBatchDraw();
//			clearrectangle(p->animal.x, p->animal.y, p->animal.x + ANIMAL_WIDTH, p->animal.y + ANIMAL_HEIGHT);
//			putimage(p->animal.x, p->animal.y, &img->bp0);
//			putimage(p->animal.x, p->animal.y, &panda_r, SRCAND);
//			putimage(p->animal.x, p->animal.y, &panda, SRCINVERT);
//			EndBatchDraw();
//			Sleep(12);
//		}
//	}
//}
////为显示动物提供遮罩
//BACKPLACE provideBackplace(QUESTION *head) {
//	QUESTION *p;
//	p = head;
//	IMAGE bk2;
//	BACKPLACE *image;
//	loadimage(&bk2, "image/GameBackground.jpg");
//	switch (p->animal.typeNumber) {
//	case 0:
//		getimage(&image->bp0, p->animal.x, p->animal.y, p->animal.x + ANIMAL_WIDTH, p->animal.y + ANIMAL_HEIGHT);
//	default:
//		getimage(&image->bp0, p->animal.x, p->animal.y, p->animal.x + ANIMAL_WIDTH, p->animal.y + ANIMAL_HEIGHT);
//		return *image;
//	}
//}