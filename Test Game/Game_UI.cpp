#include "UI.h"

int setBackground(BKGD *pointer) {
	IMAGE bk0, bk1, bk2, bkk;

	loadimage(&bk0, "image/StartBackground.jpg");
	loadimage(&bk1, "image/GameBackground.jpg");
	loadimage(&bk2, "image/EndBackground.jpg");
	loadimage(&bkk, "image/GameBack.jpg");
	pointer->background[0] = bk0;
	pointer->background[1] = bk1;
	pointer->background[2] = bk2;
	pointer->background[3] = bkk;
	return SUCCESS;
}

int displayBackground(BKGD *bk) {
	IMAGE slogan;
	if (bk->indexOfBackground == 0) {
		LOGFONT f;
		setbkmode(TRANSPARENT);
		gettextstyle(&f);
		f.lfHeight = 88;
		_tcscpy_s(f.lfFaceName, _T("Comic Sans MS"));
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = FW_BOLD;
		settextstyle(&f);
		settextcolor(WHITE);
		putimage(0, 0, &bk->background[0]);
		outtextxy(190, 155, "Hunting Game");
	}
	else if (bk->indexOfBackground == 1) {
		putimage(0, 0, &bk->background[1]);
	}
	else if (bk->indexOfBackground == 2) {
		putimage(0, 0, &bk->background[2]);
		
	}
	else {
		return FAIL;
	}
	return SUCCESS;
}

int displayWindow(USER *head) {
	USER *pointer = head;
	InputBox(pointer->username, 20, "Please enter your username:");

	return SUCCESS;
}

int initButton(IMAGE *button) {
	//开始界面
	IMAGE startButton;
	IMAGE helpButton;
	//游戏界面
	IMAGE pauseButton;
	IMAGE deleteButton;
	IMAGE exitButton;
	IMAGE continueButton;
	IMAGE createButton;
	//结束界面
	IMAGE restartButton;
	IMAGE rankingButton;
	IMAGE exitButtonTwo;
	IMAGE exitButtonThree;
	//将按钮图片存入数组
	loadimage(&startButton, "image/StartButton.jpg");
	loadimage(&helpButton, "image/HelpButton.jpg");
	loadimage(&pauseButton, "image/PAUSE_BUTTON.jpg");
	loadimage(&deleteButton, "image/DELETE_BUTTON.jpg");
	loadimage(&exitButton, "image/EXIT_BUTTON.jpg");
	loadimage(&continueButton, "image/CONTINUE_BUTTON.jpg");
	loadimage(&createButton, "image/CREATE_BUTTON.jpg");
	loadimage(&restartButton, "image/Restart.jpg");
	loadimage(&rankingButton, "image/Ranking.jpg");
	loadimage(&exitButtonTwo, "image/ExitButton.jpg");
	loadimage(&exitButtonThree, "image/Exit.jpg");
	
	*button = startButton;
	*(button + 1) = helpButton;
	*(button + 2) = pauseButton;
	*(button + 3) = deleteButton;
	*(button + 4) = exitButton;
	*(button + 5) = continueButton;
	*(button + 6) = createButton;
	*(button + 7) = restartButton;
	*(button + 8) = rankingButton;
	*(button + 9) = exitButtonTwo;
	*(button + 10) = exitButtonThree;

	return SUCCESS;
}

int displayUsername(USER *head) {
	USER *user = (USER*)malloc(sizeof(USER));
	user = head;
	LOGFONT f;
	setbkmode(TRANSPARENT);
	gettextstyle(&f);
	f.lfHeight = 24;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(675, 54, "Username：");
	outtextxy(675, 80, user->username);
	return SUCCESS;
}

int displayButton(IMAGE *button, BKGD *bk) {
	IMAGE startButton = button[0];
	IMAGE helpButton = button[1];
	IMAGE pauseButton = button[2];
	IMAGE deleteButton = button[3];
	IMAGE exitButton = button[4];
	IMAGE continueButton = button[5];
	IMAGE createButton = button[6];
	IMAGE restartButton = button[7];
	IMAGE rankingButton = button[8];
	IMAGE exitButtonTwo = button[9];
	IMAGE exitButtonThree = button[10];

	if (bk->indexOfBackground == 0) {
		putimage(325, 300, &startButton);
		putimage(325, 380, &helpButton);
		putimage(325, 460, &exitButtonTwo);
	}
	else if (bk->indexOfBackground == 1) {
		//Display Buttton Background
		setfillcolor(RGB(120, 120, 120));
		solidrectangle(650, 0, 800, 448);
		putimage(666, 160, &pauseButton);
		putimage(666, 260, &deleteButton);
		putimage(666, 360, &exitButton);
	}
	else if (bk->indexOfBackground == 2) {
		putimage(310, 270, &restartButton);
		putimage(310, 360, &rankingButton);
		putimage(310, 450, &exitButtonThree);
	}
	else {
		return FAIL;
	}
	return SUCCESS;
}

int displayScore(USER *user) {
	//display board
	IMAGE board;
	USER *pointer = (USER*)malloc(sizeof(*pointer));
	pointer = user;
	loadimage(&board, "image/BOARD.jpg");
	putimage(656, 456, &board);
	FlushBatchDraw();
	//display score
	LOGFONT f;
	setbkmode(TRANSPARENT);
	gettextstyle(&f);
	f.lfHeight = 48;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	settextstyle(&f);
	settextcolor(BLACK);
	char score[10];
	sprintf_s(score, "%d", pointer->score);
	outtextxy(700, (HEIGHT - GAME_HEIGHT) / 2 + GAME_HEIGHT - 10, score);

	return SUCCESS;
}

int displayQuestion(QUESTION *question) {
	QUESTION *head = question;
	char firstNum[20], sign[4], secondNum[4];
	while (head != NULL) {
		sprintf_s(firstNum, "%d ", head->first);
		sprintf_s(sign, "%c ", head->sign);
		sprintf_s(secondNum, "%d ", head->second);
		strcat_s(firstNum, 10, sign);
		strcat_s(firstNum, 10, secondNum);
		LOGFONT f;
		setbkmode(TRANSPARENT);
		gettextstyle(&f);
		f.lfHeight = 26;
		_tcscpy_s(f.lfFaceName, _T("Consolas"));
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = FW_BOLD;
		settextstyle(&f);
		settextcolor(BLACK);
		RECT rectangle = { head->animal->x, head->animal->y, head->animal->x + ANIMAL_WIDTH - 30, head->animal->y + ANIMAL_HEIGHT };
		drawtext(_T(firstNum), &rectangle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		head = head->next;
	}
	return SUCCESS;
}

int displayBullet(BULLET *head) {
	IMAGE BULLET_R;
	IMAGE BULLET;
	//显示分割线
	setcolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	rectangle(0, 450, WIDTH, HEIGHT);
	//显示子弹
	loadimage(&BULLET_R, "image/BULLET.jpg");
	loadimage(&BULLET, "image/BULLET_r.jpg");
	for (int index = 0; index < 4; index++) {
		putimage(12 + index * BULLET_GAP, 470, &BULLET_R, SRCAND);
		putimage(12 + index * BULLET_GAP, 470, &BULLET, SRCINVERT);
	}
	//显示子弹数字
	setfillcolor(BLUE);
	setlinecolor(BLUE);
	char s[5];
	while (head != NULL) {
		sprintf_s(s, "%d", head->value);
		setfillcolor(BLUE);
		solidcircle(head->x + BULLET_GAP / 2, head->y + BULLET_HEIGHT / 2, 20);
		LOGFONT f;
		setbkmode(TRANSPARENT);
		gettextstyle(&f);
		f.lfHeight = 22;
		_tcscpy_s(f.lfFaceName, _T("Consolas"));
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = FW_NORMAL;
		settextstyle(&f);
		settextcolor(BLACK);
		RECT r = { head->x, head->y, head->x + BULLET_GAP, head->y + BULLET_HEIGHT };
		drawtext(_T(s), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		head = head->next;
	}
	return SUCCESS;
}

void imageLoading(IMAGE *animal, IMAGE *animal_r) {
	IMAGE panda, pig, frog, giraffe, tiger, hippo, monkey, lion, dog, cat;
	IMAGE panda_r, pig_r, frog_r, giraffe_r, tiger_r, hippo_r, monkey_r, lion_r, dog_r, cat_r;
	//载入动物图
	loadimage(&panda, "image/sheep.jpg");
	loadimage(&pig, "image/pig.jpg");
	loadimage(&frog, "image/frog.jpg");
	loadimage(&giraffe, "image/giraffe.jpg");
	loadimage(&tiger, "image/tiger.jpg");
	loadimage(&hippo, "image/hippo.jpg");
	loadimage(&monkey, "image/monkey.jpg");
	loadimage(&lion, "image/lion.jpg");
	loadimage(&dog, "image/dog.jpg");
	loadimage(&cat, "image/cat.jpg");
	//载入掩码图
	loadimage(&panda_r, "image/sheep_r.jpg");
	loadimage(&pig_r, "image/pig_r.jpg");
	loadimage(&frog_r, "image/frog_r.jpg");
	loadimage(&giraffe_r, "image/giraffe_r.jpg");
	loadimage(&tiger_r, "image/tiger_r.jpg");
	loadimage(&hippo_r, "image/hippo_r.jpg");
	loadimage(&monkey_r, "image/monkey_r.jpg");
	loadimage(&lion_r, "image/lion_r.jpg");
	loadimage(&dog_r, "image/dog_r.jpg");
	loadimage(&cat_r, "image/cat_r.jpg");
	
	*animal = panda;
	*(animal + 1) = pig;
	*(animal + 2) = frog;
	*(animal + 3) = giraffe;
	*(animal + 4) = tiger;
	*(animal + 5) = hippo;
	*(animal + 6) = monkey;
	*(animal + 7) = lion;
	*(animal + 8) = dog;
	*(animal + 9) = cat;

	*animal_r = panda_r;
	*(animal_r + 1) = pig_r;
	*(animal_r + 2) = frog_r;
	*(animal_r + 3) = giraffe_r;
	*(animal_r + 4) = tiger_r;
	*(animal_r + 5) = hippo_r;
	*(animal_r + 6) = monkey_r;
	*(animal_r + 7) = lion_r;
	*(animal_r + 8) = dog_r;
	*(animal_r + 9) = cat_r;
}

void displayAnimal(QUESTION *head, IMAGE *animal, IMAGE *animal_r) {
	QUESTION *p = head;

	while (p != NULL) {
		switch (p->animal->typeNumber) {
		case 0:
			putimage(p->animal->x - 7, p->animal->y, animal_r, NOTSRCERASE);
			putimage(p->animal->x - 7, p->animal->y, animal, SRCINVERT);
			break;
		case 1:
			putimage(p->animal->x, p->animal->y, animal_r + 1, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 1, SRCINVERT);
			break;
		case 2:
			putimage(p->animal->x, p->animal->y, animal_r + 2, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 2, SRCINVERT);
			break;
		case 3:
			putimage(p->animal->x, p->animal->y, animal_r + 3, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 3, SRCINVERT);
			break;
		case 4:
			putimage(p->animal->x, p->animal->y, animal_r + 4, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 4, SRCINVERT);
			break;
		case 5:
			putimage(p->animal->x, p->animal->y, animal_r + 5, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 5, SRCINVERT);
			break;
		case 6:
			putimage(p->animal->x, p->animal->y, animal_r + 6, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 6, SRCINVERT);
			break;
		case 7:
			putimage(p->animal->x, p->animal->y, animal_r + 7, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 7, SRCINVERT);
			break;
		case 8:
			putimage(p->animal->x, p->animal->y, animal_r + 8, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 8, SRCINVERT);
			break;
		case 9:
			putimage(p->animal->x, p->animal->y, animal_r + 9, SRCAND);
			putimage(p->animal->x, p->animal->y, animal + 9, SRCINVERT);
			break;
		}
		p = p->next;
	}
}

void drawTime(double sec) {
	char str[30];
	settextcolor(RGB(255, 255, 255));
	settextstyle(20, 0, _T("Consolas"));
	sprintf_s(str, "Remaining Time：%2.lf s", sec);
	outtextxy(15, 20, str);
}