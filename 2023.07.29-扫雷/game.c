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
	printf("����������(��x,y����ʽ����)��");
	while (1)
	{
		scanf("%d,%d", x, y);
		if (((*x) < 1 || (*x) > ROW) || ((*y) < 1 || (*y) > COLUMN))
		{
			printf("�Ƿ�������ֵ�����������룺");
			continue;
		}
		else if (markboard[*x][*y] == 'p')
		{
			printf("����������ʾ�����������룺");
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
        for(i = x1 - 1; i <= x1 + 1; i++)//��֤��һ�������������Χ��������
			for (j = y1 - 1; j <= y1 + 1; j++)
			{
				if (x == i && y == j)
				{
					t = 1;
					goto judgement;//ʹ��goto�����������˫��ѭ��
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
			showboard[i][j] = count + 48;//'0'��ASCII��ֵΪ48
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
	char mineboard[ROW + 2][COLUMN + 2] = { 0 };//���׵Ĵ洢����
	char showboard[ROW + 2][COLUMN + 2] = { 0 };//��Ҫ��ӡ�Ĵ洢����
	char displayboard[ROW][COLUMN] = { 0 };//�ڴ�ӡʱ����Щ��Ҫ���أ������ø�����
	char markboard[ROW + 2][COLUMN + 2] = { 0 };//�����Ҫ��ӡ��λ�õ�����
	int x = -1, y = -1;//������������
	int win = 0;//�ж���Ӯ�ı���
	initialize_mark(markboard);//��ʼ��������飬������Ȧ��'p'
	initialize_display(displayboard);//��ʼ����Ҫչʾ�����飬�ʼ����'#'+
	print_display(displayboard, showboard, markboard, x, y);//��ӡ��Ҫչʾ������
	printf("��һ�ε�����ᴥ��\n");
	input(&x, &y, markboard);
	initialize_mine(mineboard, x, y);//���׵�λ�ý��г�ʼ��
	initialize_show(showboard, mineboard);//����������Χ�׵ĸ���������
	while (1)
	{
		if (mineboard[x][y] == '*')
		{
			printf("��λ�����ף���Ϸ����\n");
			break;
		}
		else if (showboard[x][y] == '0')
			alter_mark(markboard, showboard, x, y);//�Ա��������б任
		else
			markboard[x][y] = 'p';//p����print��ָ��Ҫ��ӡ��λ��
		system("cls");
		print_display(displayboard, showboard, markboard, x, y);
		win = is_win(markboard);//�ж���Ӯ�ĺ���
		if (win == 1)
		{
			printf("��Ӯ�ˣ���Ϸ����\n");
			break;
		}
		input(&x, &y, markboard);
	}
}