#pragma once
#ifndef DATA_H
#define DATA_H
int drawRecordFile(USER *user);
int writeRecordFile(USER *user);
int writeData(USER *user, double time, BULLET *bhead, QUESTION *qhead);
double readData(USER *user, BULLET *bhead, QUESTION *qhead);
int readQuestionNum(USER *user);
#endif