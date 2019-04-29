#pragma once
#ifndef LOGIC_H
#define LOGIC_H

QUESTION *createQuestion(int numberOfQuestion, BULLET *bullet);
void initAnimal(int indexOfQuestion, int velocity, QUESTION *pointer);
BULLET *initBullet();
void moveAnimal(QUESTION *head);
void checkBorder(QUESTION *question);
int checkButton(int mouseX, int mouseY);
int checkBullet(int mouseX, int mouseY, BULLET *head);
int checkQuestion(int mouseX, int mouseY, QUESTION *head);
int computeResult(QUESTION *question, int questionNum);
void deleteAll(QUESTION *question);
QUESTION *copyList(QUESTION *question);
//void gameOver(QUESTION *question, BULLET *bullet, BKGD *pointer);
#endif