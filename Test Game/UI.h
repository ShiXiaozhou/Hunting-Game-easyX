#pragma once
#ifndef UI_H
#define UI_H
#define WIDTH 800
#define HEIGHT 600
#define GAME_WIDTH 650
#define GAME_HEIGHT 450

#define ANIMAL_HEIGHT 120
#define ANIMAL_WIDTH 120
#define LINE_ONE 130
#define LINE_TWO 290

#define BULLET_GAP 163
#define BULLET_HEIGHT 130

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct animal{
	double x;
	double y;
	double v;
	int typeNumber;
	struct animal *next;
}ANIMAL;

typedef struct question{
	double x;
	double y;
	int first;
	int second;
	char sign;
	bool choice;
	struct question *next;
	ANIMAL animal;
}QUESTION;

typedef struct bullet{
	double x;
	double y;
	int value;
	struct bullet *next;
}BULLET;

typedef struct game {
	int score = 0;
	int indexOfBackground;
	char username[20];
	MOUSEMSG mouse;
	IMAGE animals[10];
	IMAGE background[4];
	IMAGE button[20];
	IMAGE bul[10];
	QUESTION *question;
	BULLET *bullet;
}GAME;

typedef struct {
	IMAGE bp0, bp2, bp3, bp4, bp5;
	IMAGE bp6, bp7, bp8, bp9, bp10;
}BACKPLACE;

void setBackground(GAME &game);
int displayBackground(GAME game);
GAME *displayWindow(GAME &game);
void displayButton(GAME game);
void initButton(GAME &game);
void displayBullet();
void displayScore(GAME game);
#endif