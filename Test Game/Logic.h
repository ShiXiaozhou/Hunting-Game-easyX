#pragma once
#include <time.h>
#ifndef LOGIC_H
#define LOGIC_H

QUESTION *createQuestion(int numberOfQuestion, BULLET *bullet);
ANIMAL *initAnimal(int order, int indexOfLine, int velocity);
void displayQuestion(QUESTION *head);
int checkBorder(QUESTION *head);
BULLET *initBullet(BULLET &bullet);
void displayButtonNumber(BULLET *bullet);

//int checkButton(int mouseX, int mouseY);
//BULLET checkBullet(int mouseX, int mouseY, BULLET *head);
#endif