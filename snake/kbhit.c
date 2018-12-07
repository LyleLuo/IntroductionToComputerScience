#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

//将你的 snake 代码放在这里
#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define WALL_CELL '*'
#define SNAKE_FOOD '$'

//  -1表示向上(dy)或者向左(dy)  +1表示向下(dy)或者向右(dx)
void snakeMove(int, int);
//随机投放食物 
void put_money(void);
//输出二维数组图形 
void output(void);
//游戏结束 
void gameover(void);
//吃食物
int eat_money(int dx, int dy);

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

int main()
{	
	put_money();                               //  首先投放食物 
	output();
        //设置终端进入非缓冲状态
        int tty_set_flag;
        tty_set_flag = tty_set();
	int key;
        while(continuegame == 1) {

		if( kbhit() ) {
                        key = getchar();
                        if(key == 'w' || key == 'W'){
				snakeMove(0, -1);
			}
			if(key == 's' || key == 'S'){
				snakeMove(0, 1);
			}
			if(key == 'a' || key == 'A'){
				snakeMove(-1, 0);
			}
			if(key == 'd' || key == 'D'){
				snakeMove(1, 0);
			}
		system("clear");//对于 VT100 终端, printf("\033[2J")； 也可以实现清屏。
		output();
		gameover();
                } 
        }

        //恢复终端设置
        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}

void snakeMove(int dx, int dy) {
	int i;
	//判断是否吃到食物
	if (eat_money(dx, dy));
	else {
		map[snakeY[0]][snakeX[0]] = BLANK_CELL;
		//  如果不是，那么以前的最后一节变成空白
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
}

void put_money(void) {
	int i;
	srand(time(NULL));
	moneyX = rand() % 9 + 1;
	//  钱的横纵坐标随机产生
	srand(time(NULL));
	moneyY = rand() % 9 + 1;
	//  如果钱砸身子上了，就换
	for (i = 0; i < snakeLength; i++) {
		while (moneyX == snakeX[i] && moneyY == snakeY[i]) {
			srand(time(NULL));
			moneyX = rand() % 9 + 1;
			srand(time(NULL));
			moneyY = rand() % 9 + 1;
			i = -1;
		}
	}
	map[moneyY][moneyX] = '$';
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

int eat_money(int dx, int dy) {
	if (snakeX[snakeLength - 1] + dx == moneyX && snakeY[snakeLength - 1] + dy == moneyY) {
		//  判断是否吃到了money，即两者坐标是否完全相等
		snakeLength++;
		//  如果是，长度加 1
		snakeX[snakeLength - 1] = snakeX[snakeLength - 2] + dx;
		//  头坐标向前移动，表示头向前走了一步
		snakeY[snakeLength - 1] = snakeY[snakeLength - 2] + dy;
		map[snakeY[0]][snakeX[0]] = SNAKE_BODY;
		//  因为新生了一节，所以以前的最后一节依然是SNAKE_BODY
		map[snakeY[snakeLength - 2]][snakeX[snakeLength - 2]] = SNAKE_BODY;
		//  以前的头变成了身子
		map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = SNAKE_HEAD;
		//  现在的头
		put_money();
		//  再生一个'$'
		return 1;
	}
	else return 0;
}