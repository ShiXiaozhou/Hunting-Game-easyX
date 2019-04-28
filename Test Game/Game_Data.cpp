#include "UI.h"
#include "Logic.h"
#include "Data.h"

int writeRecordFile(USER *user) {
	FILE *fp;
	USER userData[10];
	fopen_s(&fp, "Data/gameRecord.dat", "r");
	if (fp == NULL) {
		return FAIL;
	}
	//read the top ten of the recordfile and compare current score with them
	for (int i = 0; i < 10; i++) {
		fscanf_s(fp, "%s %d\n", userData[i].username, sizeof(userData[i].username), &userData[i].score);
	}
	for (int i = 0; i < 10; i++) {
		int max = userData[i].score;
		for (int j = i + 1; j < 10; j++) {
			if (max < userData[j].score) {
				int temp = max;
				max = userData[j].score;
				userData[j].score = temp;
			}
		}
		userData[i].score = max;
	}
	
	for (int i = 0; i < 10; i++) {
		if (userData[i].score < user->score) {
			for (int j = 8; j >= i; j--) {
				userData[j + 1].score = userData[j].score;
			}
			userData[i].score = user->score;
			strcpy_s(userData[i].username, user->username);
			break;
		}
	}
	fclose(fp);

	fopen_s(&fp, "Data/gameRecord.dat", "w");
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%s %d\n", userData[i].username, userData[i].score);
	}
	fclose(fp);
	return SUCCESS;
}

int drawRecordFile() {
	FILE *fp;
	USER userData[10];
	errno_t err;
	err = fopen_s(&fp, "Data/gameRecord.dat", "r");
	if (fp == NULL) {
		return FAIL;
	}
	for (int i = 0; i < 10; i++) {
		fscanf_s(fp, "%s %d\n", userData[i].username, sizeof(userData[i].username), &userData[i].score);
	}
	//print in the ranking page
	LOGFONT f;
	setbkmode(TRANSPARENT);
	gettextstyle(&f);
	f.lfHeight = 32;
	_tcscpy_s(f.lfFaceName, _T("Comic Sans MS"));
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);
	settextcolor(WHITE);
	for (int i = 0; i < 10; i++) {
		outtextxy(255, 170 + 35 * i, userData[i].username);
		char str[12];
		sprintf_s(str, "%d", userData[i].score);
		outtextxy(460, 170 + 35 * i, str);
	}
	
	fclose(fp);

	return SUCCESS;
}
// 用户名，得分，时间，子弹链表，动物链表
int writeData(USER *user, double time, BULLET *bhead, QUESTION *qhead) {
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data/gameData.dat", "w");
	if (fp == NULL) {
		return FAIL;
	}

	fprintf(fp, "%s %d %lf ", user->username, user->score, time);
	for (int i = 0; i < 4; i++) {
		fprintf(fp, "%d %d %d ", bhead->x, bhead->y, bhead->value);
		bhead = bhead->next;
	}
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%d %c %d ", qhead->first, qhead->sign, qhead->second);
		fprintf(fp, "%d %d %d %d", qhead->animal->typeNumber, qhead->animal->v, qhead->animal->x, qhead->animal->y);
		qhead = qhead->next;
	}
	fclose(fp);

	return SUCCESS;
}

int readUser(USER *user) {
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data/gameData.dat", "r");
	
	fscanf_s(fp, "%s %d ", user->username, sizeof(user->username), &user->score);
	fclose(fp);
	return SUCCESS;
}

double readTime(double time) {
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data/gameData.dat", "r");

	fscanf_s(fp, "%lf ", &time);
	fclose(fp);

	return time;
}

int readBullet(BULLET *bullet) {
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data/gameData.dat", "r");

	for (int i = 0; i < 4; i++) {
		fscanf_s(fp, "%d %d %d ", &bullet->x, &bullet->y, &bullet->value);
		bullet = bullet->next;
	}
	fclose(fp);

	return SUCCESS;
}

int readQuestion(QUESTION *question) {
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data/gameData.dat", "r");

	for (int i = 0; i < 10; i++) {
		fscanf_s(fp, "%d %c %d ", &question->first, &question->sign, 1, &question->second);
		fscanf_s(fp, "%d %d %d %d", &question->animal->typeNumber, &question->animal->v, &question->animal->x, &question->animal->y);
		question = question->next;
	}
	fclose(fp);

	return SUCCESS;
}

double readData(USER *user, double time, BULLET *bhead, QUESTION *qhead) {
	double timeLeft;
	readUser(user);
	timeLeft = readTime(time);
	readBullet(bhead);
	readQuestion(qhead);

	return timeLeft;
}