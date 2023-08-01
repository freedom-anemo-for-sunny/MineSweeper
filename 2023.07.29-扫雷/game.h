#define  _CRT_SECURE_NO_WARNINGS  1
#pragma  warning(disable:6031)

#define ROW 9
#define COLUMN 9
#define MINECOUNT 9

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void initialize_mark(char markboard[ROW + 2][COLUMN + 2]);
void initialize_display(char displayboard[ROW][COLUMN]);
void print_display(char displayboard[ROW][COLUMN], char showboard[ROW + 2][COLUMN + 2], char markboard[ROW + 2][COLUMN + 2], int x, int y);
void input(int* x, int* y, char markboard[ROW + 2][COLUMN + 2]);
void initialize_mine(char board[ROW + 2][COLUMN + 2], int x, int y);
void initialize_show(char showboard[ROW + 2][COLUMN + 2], char mineboard[ROW + 2][COLUMN + 2]);
void alter_mark(char markboard[ROW + 2][COLUMN + 2], char showboard[ROW + 2][COLUMN + 2], int x, int y);
int is_win(char markboard[ROW + 2][COLUMN + 2]);

void game();