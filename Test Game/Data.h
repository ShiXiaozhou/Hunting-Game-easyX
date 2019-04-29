#pragma once
#ifndef DATA_H
#define DATA_H
int drawRecordFile(USER *user);
int writeRecordFile(USER *user);
int writeData(USER *user, double time, BULLET *bhead, QUESTION *qhead);
double readUser(USER *user);
int readBullet(BULLET *bullet);
int readQuestion(QUESTION *question);
double readData(USER *user, BULLET *bhead, QUESTION *qhead);
#endif