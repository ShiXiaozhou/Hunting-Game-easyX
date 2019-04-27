#include "UI.h"
#include "Logic.h"
#include "Data.h"

int writeRecordFile(USER *user) {
	FILE *fp;
	fopen_s(&fp, "Data/gameRecord.dat", "a");
	if (fp == NULL) {
		return FAIL;
	}
	fprintf(fp, "%s %d", user->username, user->score);
	fclose(fp);

	return SUCCESS;
}

int drawRecordFile() {
	USER *tmp[11] = {0};
	USER *temp = (USER *)malloc(sizeof(USER));
	FILE *fp;
	int i = 0;
	fopen_s(&fp, "Data/gameRecord.dat", "rb");
	if (fp == NULL) {
		return FAIL;
	}
	while (i <= 10 && fscanf_s(fp, "%s %d", tmp[i]->username, &tmp[i]->score) != EOF) {
		i++;
	}
	for (int j = 0; j < i - 1; j++) {
		int minIndex = j;
		for (int k = j + 1; k < i; k++) {
			if (tmp[minIndex]->score > tmp[k]->score) {
				minIndex = k;
			}
		}
		if (j != minIndex) {
			temp->score = tmp[minIndex]->score;
			tmp[minIndex]->score = tmp[j]->score;
			tmp[j]->score = temp->score;
		}
	}
	i = 0;
	while (i <= 10 && fscanf_s(fp, "%s %d", tmp[i]->username, &tmp[i]->score) != EOF) {
	//	sprintf_s(secondNum, "%d ", head->second);
	//	strcat_s(firstNum, 10, sign);
		printf("%3d%15s%10d\n", i + 1, tmp[i]->username, tmp[i]->score);
		i++;
	}

	
	fclose(fp);

	return SUCCESS;
}

