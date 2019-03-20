#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "UI.h"

void setBackground(GAME &game) {
	GAME *pointer;
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
	return 0;
}

GAME *displayWindow(GAME &game) {
	GAME *pointer = &game;
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
