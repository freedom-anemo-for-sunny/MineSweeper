#include"game.h"

void initialize_mark(char markboard[ROW + 2][COLUMN + 2])
{
	int i = 0;
	for (i = 0; i < ROW + 2; i++)
	{
		markboard[i][0] = 'p';
		markboard[i][COLUMN + 1] = 'p';
	}
	for (i = 0; i < COLUMN + 2; i++)
	{
		markboard[0][i] = 'p';
		markboard[ROW + 1][i] = 'p';
	}
}

void initialize_display(char displayboard[ROW][COLUMN])
{
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COLUMN; j++)
			displayboard[i][j] = '#';
}

void print_display(char displayboard[ROW][COLUMN], char showboard[ROW + 2][COLUMN + 2], char markboard[ROW + 2][COLUMN + 2], int x, int y)
{
	int i = 0, j = 0;
	printf("   ");
	for (j = 0; j < COLUMN - 1; j++)
		printf(" %2d ",j + 1);
	printf(" %2d  ---> y\n", COLUMN);
	for(i = 0; i < ROW - 1; i++)
	{
		printf(" %2d ", i + 1);
		for (j = 0; j < COLUMN - 1; j++)
		{
			if (markboard[i + 1][j + 1] == 'p')
				displayboard[i][j] = showboard[i + 1][j + 1];
			printf(" %c \|", displayboard[i][j]);
		}
		if(markboard[i + 1][COLUMN ]== 'p')
		    displayboard[i][COLUMN - 1] = showboard[i + 1][COLUMN];
		printf(" %c \n",displayboard[i][COLUMN - 1]);
		printf("    ");
		for (j = 0; j < COLUMN - 1; j++)
			printf("---\|");
		printf("---\n");
	}
	printf(" %2d ", ROW);
	for (j = 0; j < COLUMN - 1; j++)
	{
		if (markboard[ROW][j + 1] == 'p')
			displayboard[ROW - 1][j] = showboard[ROW][j + 1];
		printf(" %c \|", displayboard[i][j]);
	}
	if(markboard[ROW][COLUMN]=='p')
		displayboard[ROW - 1][COLUMN - 1] = showboard[ROW][COLUMN];
	printf(" %c \n", displayboard[ROW - 1][COLUMN - 1]);
	printf(" \|\n \|\n x\n");
}

void input(int* x, int* y, char markboard[ROW + 2][COLUMN + 2])
{
	printf("请输入坐标(以x,y的形式输入)：");
	while (1)
	{
		scanf("%d,%d", x, y);
		if (((*x) < 1 || (*x) > ROW) || ((*y) < 1 || (*y) > COLUMN))
		{
			printf("非法的输入值，请重新输入：");
			continue;
		}
		else if (markboard[*x][*y] == 'p')
		{
			printf("该坐标已显示，请重新输入：");
			continue;
		}
		else
			break;
	}
}

void initialize_mine(char board[ROW + 2][COLUMN + 2], int x, int y)
{
	int count = 0;
	int x1 = 0, y1 = 0;
	int i = 0, j = 0;

	while (count < MINECOUNT)
	{	
		int t = 0;
		x1 = rand() % ROW + 1;
		y1 = rand() % COLUMN + 1;
        for(i = x1 - 1; i <= x1 + 1; i++)//保证第一次输入的坐标周围不存在雷
			for (j = y1 - 1; j <= y1 + 1; j++)
			{
				if (x == i && y == j)
				{
					t = 1;
					goto judgement;//使用goto语句用于跳出双层循环
				}
			}
		judgement:
		if (t == 1)
			continue;
		if (board[x1][y1] == '*')
			continue;
		board[x1][y1] = '*';
		count++;
	}
}

void initialize_show(char showboard[ROW + 2][COLUMN + 2], char mineboard[ROW + 2][COLUMN + 2])
{
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
        for (j = 1; j <= COLUMN; j++)
		{
			int i1 = 0, j1 = 0;
			int count = 0;
			for(i1 = i - 1; i1 <= i + 1; i1++)
				for (j1 = j - 1; j1 <= j + 1; j1++)
					if (mineboard[i1][j1] == '*')
						count++;
			showboard[i][j] = count + 48;//'0'的ASCII码值为48
		}
}

void alter_mark(char markboard[ROW + 2][COLUMN + 2], char showboard[ROW + 2][COLUMN + 2], int x, int y)
{
	int i = 0, j = 0;
	markboard[x][y] = 'p';
	for(i = x - 1; i <= x + 1; i++)
		for (j = y - 1; j <= y + 1; j++)
		{
			if (markboard[i][j] == 'p')
				continue;
			else if (showboard[i][j] == '0')
			{
				markboard[i][j] = 'p';
				alter_mark(markboard, showboard, i, j);
			}
			else
				markboard[i][j] = 'p';
		}
}

int is_win(char markboard[ROW + 2][COLUMN + 2])
{
	int count = 0;
	int i = 0, j = 0;
	for (i = 1; i <= ROW; i++)
		for (j = 1; j <= COLUMN; j++)
			if (markboard[i][j] == 'p')
				count++;
	if (count == (ROW * COLUMN - MINECOUNT))
		return 1;
	else
		return 0;
}


void game()
{
	srand((unsigned int)time(NULL));
	char mineboard[ROW + 2][COLUMN + 2] = { 0 };//地雷的存储数组
	char showboard[ROW + 2][COLUMN + 2] = { 0 };//需要打印的存储数组
	char displayboard[ROW][COLUMN] = { 0 };//在打印时，有些需要隐藏，故设置该数组
	char markboard[ROW + 2][COLUMN + 2] = { 0 };//标记需要打印的位置的数组
	int x = -1, y = -1;//玩家输入的坐标
	int win = 0;//判断输赢的变量
	initialize_mark(markboard);//初始化标记数组，对最外圈标'p'
	initialize_display(displayboard);//初始化需要展示的数组，最开始均标'#'+
	print_display(displayboard, showboard, markboard, x, y);//打印需要展示的数组
	printf("第一次点击不会触雷\n");
	input(&x, &y, markboard);
	initialize_mine(mineboard, x, y);//对雷的位置进行初始化
	initialize_show(showboard, mineboard);//建立格子周围雷的个数的数组
	while (1)
	{
		if (mineboard[x][y] == '*')
		{
			printf("此位置是雷，游戏结束\n");
			break;
		}
		else if (showboard[x][y] == '0')
			alter_mark(markboard, showboard, x, y);//对标记数组进行变换
		else
			markboard[x][y] = 'p';//p代表print，指需要打印的位置
		system("cls");
		print_display(displayboard, showboard, markboard, x, y);
		win = is_win(markboard);//判断输赢的函数
		if (win == 1)
		{
			printf("你赢了，游戏结束\n");
			break;
		}
		input(&x, &y, markboard);
	}
}