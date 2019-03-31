#include "UI.h"
#include "Logic.h"

/* 完成动物块&数学题的创建，存入链表，输出，循环移动*/

/* 根据子弹的答案，创建合适的数学题，存入链表 */
QUESTION *createQuestion(int numberOfQuestion, BULLET *bullet) {
	BULLET *initBullet(); // declare function 
	bullet = initBullet();
	QUESTION *pointer, *head = NULL;
	int indexOfSign; // choose sign at random
	int index = 0;
	int first, second;
	char sign; 
	pointer = (QUESTION *)malloc(sizeof(QUESTION));
	while (index < numberOfQuestion) {
		srand((unsigned)time(NULL));
		indexOfSign = rand() % 4;
		pointer = (QUESTION *)malloc(sizeof(QUESTION));
		if (head == NULL) {
			head = pointer;
		}
		switch (indexOfSign) {
		case 0:
			sign = '+';
			first = rand() % 20;
			if (first <= bullet->value) {
				second = bullet->value - first;
				pointer->first = first;
				pointer->second = second;
				pointer->sign = sign;
				pointer = pointer->next;
			}
			break;
		case 1:
			sign = '-';	first = rand() % 20;
			if (first >= bullet->value) {
				second = first - bullet->value;
				pointer->first = first;
				pointer->second = second;
				pointer->sign = sign;
				pointer = pointer->next;
			}
			break;
		case 2:
			sign = '*';first = rand() % 20;
			if (bullet->value % first == 0) {
				second = bullet->value / first;
				pointer->first = first;
				pointer->second = second;
				pointer->sign = sign;
				pointer = pointer->next;
			}
			break;
		case 3:
			sign = '/';first = rand() % 21;
			if (first % bullet->value == 0) {
				second = first / bullet->value;
				pointer->first = first;
				pointer->second = second;
				pointer->sign = sign;
				pointer = pointer->next;
			}
			break;
		default:
			sign = '/';first = rand() % 21;
			if (first % bullet->value == 0) {
				second = first / bullet->value;
				pointer->first = first;
				pointer->second = second;
				pointer->sign = sign;
				pointer = pointer->next;
			}
			break;
		}
		index++;
	}
	pointer->next = NULL;
	return head;
}
//initial (x,y), velocity and typeNumber of animal
ANIMAL *initAnimal(int order, int indexOfLine, int velocity) {
	ANIMAL *pointer = NULL;
//	pointer = (ANIMAL *)malloc(sizeof(ANIMAL));
	pointer->x = ANIMAL_WIDTH * order;
	if (indexOfLine == 1) {
		pointer->y = LINE_ONE;
	}
	else if (indexOfLine == 2) {
		pointer->y = LINE_TWO;
	}
	pointer->v = velocity;
	srand((unsigned)time(NULL));
	pointer->typeNumber = rand() % 10;
	return pointer;
}

//在动物块相应位置打印数学题
void displayQuestion(QUESTION *head) {
	QUESTION *question;
//	question = (QUESTION *)malloc(sizeof(QUESTION));
	question = head;
	while (question != NULL) {
		RECT rectangle = { question->animal.x, question->animal.y, question->animal.x + ANIMAL_WIDTH, question->animal.y + ANIMAL_HEIGHT };
		drawtext(_T("%d %c %d", question->first, question->sign, question->second), &rectangle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		question = question->next;
	}
}

int checkBorder(QUESTION *head) {
	QUESTION *p, *q;
	p = head;
	q = head->next;
	//moving question
	while (q != NULL) {
		if (q->x >= GAME_WIDTH - ANIMAL_WIDTH) {
			q->x = 0;
			return 0;
		}
		else {
			p = q;
			q = q->next;
		}
	}
}

/*将子弹，按钮，背景存入数组，并且初始化*/
BULLET *initBullet(BULLET &bullet) {
	BULLET *p = &bullet, *head;
	p = (BULLET*)malloc(sizeof(*p));
	head = p;
	for (int i = 0; i < 4; i++) {
		p->y = 470;
		p->x = BULLET_GAP * i;
		srand((unsigned)time(NULL));
		p->value = rand() % 21;
		//draw a ball and print the number on it 
		p = p->next;
	}
	p->next = NULL;
	return head;
}

void displayButtonNumber(BULLET *bullet) {
	BULLET *initBullet(); //declare function 
	bullet = initBullet();
	bullet = (BULLET *)malloc(sizeof(BULLET));
	while (bullet != NULL) {
		setfillcolor(BLUE);
		setlinecolor(BLUE);
		circle(bullet->x + BULLET_GAP / 2, bullet->y + BULLET_HEIGHT / 2, 30);
		RECT r = { bullet->x, bullet->y, bullet->x + BULLET_GAP, bullet->y + BULLET_HEIGHT };
		drawtext(_T(bullet->value), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		bullet = bullet->next;
	}
}
//int checkButton(int mouseX, int mouseY) {
//	if (mouseX >= 666 && mouseX < 786 && mouseY >= 160 && mouseY < 200) {
//		// PAUSE
//		return 1;
//	}
//	else if (mouseX >= 666 && mouseX < 786 && mouseY >= 260 && mouseY < 300) {
//		//DELETE
//		return 2;
//	}
//	else if (mouseX >= 666 && mouseX < 786 && mouseY >= 360 && mouseY < 400) {
//		//EXIT
//		return 3;
//	}
//	else return 0;
//}
//QUESTION checkQuestion(int mouseX, int mouseY, QUESTION *head) {
//QUESTION *p;
//p = head;
//while (p != NULL) {
//	if (p->x <= mouseX && p->x + ANIMAL_HEIGHT >= mouseX && p->y <= mouseY && p->y >= mouseY) {
//		return *p;
//	}
//	else {
//		p = p->next;
//	}
//}
//return *head;
//	}
//BULLET checkBullet(int mouseX, int mouseY, BULLET *head) {
//	BULLET *p;
//	p = head;
//	while (p != NULL) {
//		if (p->x <= mouseX && p->x + BULLET_GAP >= mouseX && p->y <= mouseY && p->y >= mouseY) {
//			return *p;
//		}
//		else {
//			p = p->next;
//		}
//	}
//	return *head;
//}
////tutorial
//
//void playMusic() {
//	//用作游戏背景音乐 异步播放 播放指定WAV文件 重复播放
//	PlaySound("相对路径", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
//	//触发指定音频 异步播放 播放指定WAV文件
//	PlaySound("相对路径", NULL, SND_ASYNC | SND_FILENAME);
//	//停止播放指定音频 第一个参数为NULL是停止全部音频
//	PlaySound("相对路径", NULL, SND_FILENAME | SND_PURGE);
//}