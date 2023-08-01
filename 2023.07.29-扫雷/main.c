#include"game.h"

void menu()
{
	printf("****************************\n");
	printf("***********1.play***********\n");
	printf("***********0.exit***********\n");
	printf("****************************\n");
}

void main_structure()
{
	int input = 0;
	menu();
	do
	{
		printf("请选择(1/0)：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("游戏已开始，祝您游戏愉快\n");
			Sleep(2500);
			system("cls");
			game();
			printf("是否要再来一局？\n");
			break;
		case 0:
			printf("游戏已退出");
			break;
		default:
			printf("非法的输入值，请重新输入\n");
			break;
		}
	} while (input);
}

int main()
{
	main_structure();
	return 0;
}