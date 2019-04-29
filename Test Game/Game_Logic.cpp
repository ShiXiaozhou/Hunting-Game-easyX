#include "UI.h"
#include "Logic.h"

BULLET *initBullet() {
	BULLET *p;
	BULLET *head = NULL, *tail = NULL;
	int value[20];
	int repeatOrNot = 0;
	int repeat = 0;
	for (int i = 0; i < 4; i++) {
		p = (BULLET*)malloc(sizeof(*p));
		p->y = 460;
		p->x = BULLET_GAP * i;
		while (repeat == 0) {
			value[i] = rand() % 21;
			for (int index = 0; index < i; index++) {
				if (value[i] == value[index]) {
					repeatOrNot++;
				}
			}
			if (repeatOrNot == 0) {
				p->value = value[i];
				repeat++;
			}
		}
		repeat = 0;

		p->next = NULL;
		if (head == NULL) {
			head = p;
			tail = p;
		}
		else {
			tail->next = p;
			tail = p;
		}
	}
	return head;
}

QUESTION *createQuestion(int numberOfQuestion, BULLET *bul) {
	BULLET *bullet = bul;
	QUESTION *pointer, *head = NULL, *tail = NULL;
	int indexOfSign;
	int first, second;
	char sign; 
	for (int i = 0; i < numberOfQuestion; i++) {
		pointer = (QUESTION *)malloc(sizeof(QUESTION));
		indexOfSign = rand() % 4;
		switch (indexOfSign) {
		case 0: {
			sign = '+';
			int a = 0;
			while (a < 1) {
				int bulletIndex = rand() % 4;
				for (int index = 0; index < bulletIndex; index++) {
					bullet = bullet->next;
				}
				first = rand() % 20;
				if (first <= bullet->value) {
					second = bullet->value - first;
					pointer->first = first;
					pointer->second = second;
					pointer->sign = sign;
					a++;
				}
				bullet = bul;
			}
			break;
		}
		case 1: {
			sign = '-';
			int b = 0;
			while (b < 1) {
				int bulletIndex = rand() % 4;
				for (int index = 0; index < bulletIndex; index++) {
					bullet = bullet->next;
				}
				first = rand() % 20;
				if (first >= bullet->value) {
					second = first - bullet->value;
					pointer->first = first;
					pointer->second = second;
					pointer->sign = sign;
					b++;
				}
				bullet = bul;
			}
			break;
		}
		case 2: {
			sign = '*';
			int a = 0;
			while (a < 1) {
				int bulletIndex = rand() % 4;
				for (int index = 0; index < bulletIndex; index++) {
					bullet = bullet->next;
				}
				first = rand() % 20;
				if (first != 0 && bullet->value % first == 0) {
					second = bullet->value / first;
					pointer->first = first;
					pointer->second = second;
					pointer->sign = sign;
					a++;
				}
				bullet = bul;
			}
			break;
		}
		case 3: {
			sign = '/';
			int d = 0;
			while (d < 1) {
				int bulletIndex = rand() % 4;
				for (int index = 0; index < bulletIndex; index++) {
					bullet = bullet->next;
				}
				first = rand() % 21;
				if (bullet->value != 0 && first != 0 && first % bullet->value == 0) {
					second = first / bullet->value;
					pointer->first = first;
					pointer->second = second;
					pointer->sign = sign;
					d++;
				}
				bullet = bul;
			}
			break;
			}
		}
		pointer->next = NULL;
		if (head == NULL) {
			head = pointer;
			tail = pointer;
		}
		else {
			tail->next = pointer;
			tail = pointer;
		}
	
	}
	return head;
}

void moveAnimal(QUESTION *head) {
	QUESTION *pointer = head;
	while (pointer != NULL) {
		pointer->animal->x -= pointer->animal->v;
		pointer = pointer->next;
	}
}

int checkButton(int mouseX, int mouseY) {
	if (mouseX >= 666 && mouseX < 786 && mouseY >= 160 && mouseY < 200) {
		// PAUSE
		return 1;
	}
	else if (mouseX >= 666 && mouseX < 786 && mouseY >= 260 && mouseY < 300) {
		//DELETE
		return 2;
	}
	else if (mouseX >= 666 && mouseX < 786 && mouseY >= 360 && mouseY < 400) {
		//EXIT
		return 3;
	}
	else return 0;
}

int checkBullet(int mouseX, int mouseY, BULLET *head) {
	BULLET *p = head;
	int indexOfLoop = 0;
	while (p != NULL) {
		if (mouseX >= p->x && mouseX <= p->x + BULLET_GAP && mouseY >= p->y && mouseY <= p->y + BULLET_HEIGHT) {
			return indexOfLoop;
		}
		else {
			p = p->next;
		}
		indexOfLoop++;
	}
	return -1;
}

void gameOver(QUESTION *head, BULLET *header, BKGD *pointer) {
	QUESTION *question = NULL;
	BULLET *bullet = NULL;
	while (head != NULL) {
		free(head->animal);
		head = head->next;
	}
	while (head != NULL) {		
		question = head->next;
		free(head);
		head = question;
	}
	while (header != NULL) {
		bullet = header->next;
		free(header);
		header = bullet;
	}

	free(pointer);
}

void deleteAll(QUESTION *head) {
	QUESTION *question = NULL;
	while (head) {
		question = head->next;
		free(head);
		head = question;
	}
}

int checkQuestion(int mouseX, int mouseY, QUESTION *head) {
	QUESTION *p = head;
	int num = 0;
	while (p != NULL) {
		if (p->animal->x <= mouseX && p->animal->x + ANIMAL_WIDTH >= mouseX 
			&& p->animal->y <= mouseY && p->animal->y + ANIMAL_HEIGHT >= mouseY) {
			return num;
		}
		else {
			num++;
			p = p->next;
		}
	}
	return -1;
}

int computeResult(QUESTION *question, int questionNum) {
	QUESTION *pointer = question;
	
	for (int i = 0; i < questionNum; i++) {
		pointer = pointer->next;
	}
	//compute result
	switch (pointer->sign) {
	case 43:
		return pointer->first + pointer->second;
		break;
	case 45:
		return pointer->first - pointer->second;
		break;
	case 42:
		return pointer->first *pointer->second;
		break;
	case 47:
		return pointer->first / pointer->second;
		break;
	}
	return SUCCESS;
}

void checkBorder(QUESTION *question) {
	QUESTION *pointer = question;
	while (pointer != NULL) {
		if (pointer->animal->x <= -ANIMAL_WIDTH) {
			pointer->animal->x = GAME_WIDTH;
		} 
		pointer = pointer->next;
	}
	pointer = question;

}

void initAnimal(int indexOfQuestion, int velocity, QUESTION *head) {
	QUESTION *pointer = head;
	for (int index = 0; index < indexOfQuestion; index++) {
		pointer->animal = (ANIMAL *)malloc(sizeof(ANIMAL));
		if (index < 5) {
			pointer->animal->x = GAME_WIDTH + ANIMAL_WIDTH * index;
			pointer->animal->y = LINE_ONE;
		}
		else {
			pointer->animal->x = GAME_WIDTH + ANIMAL_WIDTH * (index - 5);
			pointer->animal->y = LINE_TWO;
		}
		pointer->animal->v = velocity;
		pointer->animal->typeNumber = rand() % 10;

		pointer = pointer->next;
	}
	
}
// score page
//int finialScore(USER *user) {
//	//循环
//	//putimage page image
//	//word style
//	outtextxy(10, 10, user->score);
//	//of yes -> writeRecordFile
//	//if no -> not write
//}
