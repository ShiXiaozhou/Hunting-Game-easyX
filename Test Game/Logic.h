#pragma once
#ifndef LOGIC_H
#define LOGIC_H

QUESTION *createQuestion(int numberOfQuestion, BULLET *bullet);
void initAnimal(int indexOfQuestion, float velocity, QUESTION *pointer);
BULLET *initBullet();
void moveAnimal(QUESTION *head);
void checkBorder(QUESTION *question);
int checkButton(int mouseX, int mouseY);
int checkBullet(int mouseX, int mouseY, BULLET *head);
int checkQuestion(int mouseX, int mouseY, QUESTION *head);
int computeResult(QUESTION *question, int questionNum);
void gameOver(QUESTION *question, BULLET *bullet, BKGD *pointer);
void deleteAll(QUESTION *question);
#endif