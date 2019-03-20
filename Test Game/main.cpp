#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "UI.h"

int main() {
	GAME game;
	
	initgraph(WIDTH, HEIGHT); // highlight error
	setBackground(game);
	game.indexOfBackground = 2;
	displayBackground(game);
	displayWindow(game);
	
	_getch();
	closegraph();
	return 0;
}

