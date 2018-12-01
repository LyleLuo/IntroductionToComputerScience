#include <stdio.h>
#include <stdlib.h>


#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define SNAKE_FOOD '$'

//  -1表示向上(dy)或者向左(dy)  +1表示向下(dy)或者向右(dx)
void snakeMove(int, int);
//输出二维数组图形 
void output(void);
//游戏结束 
void gameover(void);


char map[12][12] =
{ "***********",
"*XXXXH    *",
"*         *",
"*         *",
"*         *",
"*         *",
"*         *",
"*         *",
"*         *",
"*         *",
"*         *",
"***********" };
int snakeX[SNAKE_MAX_LENGTH] = { 1,2,3,4,5 };
int snakeY[SNAKE_MAX_LENGTH] = { 1,1,1,1,1 };
int moneyX, moneyY;
int snakeLength = 5;
int continuegame = 1;


int main() {
	char ch = 0;                              //  首先投放食物 
	output();
	while (continuegame == 1) {                      //  每次循环都要判断是否游戏已经结束
		ch = getchar();
		system("cls");
		system("clear");
		switch (ch) {
		case 'A':
		case 'a':
			snakeMove(-1, 0);		//  向左移动 
			break;
		case 'D':
		case 'd':
			snakeMove(1, 0);		//  向右移动 
			break;
		case 'W':
		case 'w':
			snakeMove(0, -1);		//  向上移动 
			break;
		case 'S':
		case 's':
			snakeMove(0, 1);		//  向下移动 
			break;
		default: break;
		}
			output();
			gameover();
	}
	printf("Game Over");
}

void snakeMove(int dx, int dy) {
	int i;
	map[snakeY[0]][snakeX[0]] = BLANK_CELL;
	//以前的最后一节变成空白
	map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = SNAKE_BODY;
	//  以前的头变成身子
	for (i = 0; i < snakeLength - 1; i++) {
		//  以前所有的坐标都向前移动
		snakeX[i] = snakeX[i + 1];
		snakeY[i] = snakeY[i + 1];
	}
	snakeX[snakeLength - 1] += dx;
	snakeY[snakeLength - 1] += dy;
	map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = SNAKE_HEAD;
	//  新的头
}

void output(void) {
	int i, j; 
	for (i = 0; i < 12; ++i) {
		for (j = 0; j < 12; ++j) {
			printf("%c", map[i][j]);
		}
		putchar('\n');
	}
}

void gameover(void) {
	if (snakeX[snakeLength - 1] == 0 || snakeX[snakeLength - 1] == 10
		|| snakeY[snakeLength - 1] == 0 || snakeY[snakeLength - 1] == 10) {
		continuegame = 0;
		printf("撞到墙了！") ; 
	}
	int i;
	for (i = 0; i < snakeLength - 1; i++) {
		//  以前所有的坐标都向前移动
		if (snakeX[i] == snakeX[snakeLength - 1] &&
			snakeY[i] == snakeY[snakeLength - 1]) {
			printf("咬到自己了！") ; 
			continuegame = 0;
			}
	}
	if (SNAKE_MAX_LENGTH == snakeLength) {
		continuegame = 0;
		printf("congratulations！\twin!\n");
	}
}


