#pragma once
#ifndef DATA_H
#define DATA_H
int drawRecordFile();
int writeRecordFile(USER *user);
int writeData(USER *user, double time, BULLET *bhead, QUESTION *qhead);
int readUser(USER *user);
double readTime(double time);
int readBullet(BULLET *bullet);
int readQuestion(QUESTION *question);
double readData(USER *user, double time, BULLET *bhead, QUESTION *qhead);
#endif