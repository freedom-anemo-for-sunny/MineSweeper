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
		printf("��ѡ��(1/0)��");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			printf("��Ϸ�ѿ�ʼ��ף����Ϸ���\n");
			Sleep(2500);
			system("cls");
			game();
			printf("�Ƿ�Ҫ����һ�֣�\n");
			break;
		case 0:
			printf("��Ϸ���˳�");
			break;
		default:
			printf("�Ƿ�������ֵ������������\n");
			break;
		}
	} while (input);
}

int main()
{
	main_structure();
	return 0;
}