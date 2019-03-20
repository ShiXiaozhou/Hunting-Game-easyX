#pragma once
#ifndef UI_H
#define UI_H
#define WIDTH 800
#define HEIGHT 600
#define GAME_WIDTH 650
#define GAME_HEIGHT 450

#define BULLET_GAP 163
#define BULLET_HEIGHT 130

typedef struct game {
	int score = 0;
	char username[20];
	MOUSEMSG mouse;
	IMAGE animals[10];
	IMAGE background[4];
	IMAGE button[10];
	IMAGE bullet[10];
	int indexOfBackground;
	//	QUESTION *question;
}GAME;

void setBackground(GAME &game);
int displayBackground(GAME game);
GAME *displayWindow(GAME &game);
#endif