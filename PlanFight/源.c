#include <stdio.h>
#include <windows.h>//Windows���ڣ�COORD�ṹ��ʵ�ֹ���淽����ƶ�
#include <conio.h>//ͨ�������̲����Ķ�Ӧ��������getch()��gotoxy()
#include <time.h>//��ʱ����Ϊ�����������������������������õ���
#pragma warning(disable:4996)//����vs2017��4996�Ĵ�
void gotoxy(int x, int y);
void hidden();
void rank();
void map();
void GameInstructions();
void Guide();
void GuideChoice();
void Hit();
void Control();
void Die();
void Enemy();
int ranking();
void main();


#define Esc 27 //�˳�
#define Up 72 //��
#define Down 80 //��
#define Left 75 //��
#define Right 77 //��
#define Fire 32 //�����ӵ�
#define �س� 13 //��rank

int x = 10; //�Լ�������
int y = 18; //�Լ�������
int d = 10;//�л�0������
int d1 = 10;//�л�1������
int d2 = 10;//�л�2������
int d3 = 10;//�ϰ��������
int d4 = 10;//�ϰ��������

int r = 1;//�л�0������
int r1 = 1;//�л�1������
int r2 = 1;//�л�2������
int r3 = 1;//�ϰ���������
int r4 = 1;//�ϰ���������

int f = 0; // �Ʒ���
int m = 1; // �л���
int j = 0; // �ߵ���
int Y;//���������ӵ�ʱ��ʱ�滻
char p; // ���ܰ���
int F[10];//��ʷ����
int i, j, temp, isSorted;


void gotoxy(int x, int y) //�ƶ��������x��y��
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//ʹ���coord�ƶ�����x,y����λ�ã����ô˺�����Ҫwindows.hͷ�ļ���
}
void hidden()//��������,�����������ο���Դ��https://zhidao.baidu.com/question/557336915.html
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;//��1Ϊ��ʾ����0Ϊ����
	SetConsoleCursorInfo(hOut, &cci);
	gotoxy(x, y);
}

void rank()//���а�
{
	system("cls");
	gotoxy(0, 0);
	printf("\t\t\t�������а�����\n\n\n\n");
	for (i = 9; i >= 0; i--)
	{
		printf("\t\t%d\n ", F[i]);
	}
	printf("\n");
	system("pause");//��ͣ
	system("cls");//����
	Guide();

}

void map()//������ͼ
{
	gotoxy(0, 0);
	int i, n;
	for (i = 0; i <= 19; i++)
	{
		for (n = 0; n <= 19; n++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (i = 1; i <= 18; i++)
	{
		for (n = 1; n <= 18; n++)
		{
			gotoxy(i, n);
			printf(" ");
		}
	}

}

void GameInstructions()//��Ϸ˵��
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t��");
	Sleep(100);
	printf("ս");
	Sleep(100);
	printf("��");
	Sleep(100);
	printf("��");
	Sleep(100);
	printf("��");
	Sleep(100);
	printf("��");
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".");
	Sleep(300);
	printf(".");
	Sleep(300);
	system("cls");
	printf("\t\t\t\n\n\n\n");
	gotoxy(22, 2);
	printf(" ����:");
	printf("\n\n\n\t\t\t����\n\n"
		"\t\t\t�� ��\n\n"
		"\t\t\t�� ��\n\n"
		"\t\t\t�� ��\n\n"
		"\t\t\t�� ��\n\n"
		"\t\t\t�ӵ� �ո�\n\n"
		"\t\t\t�˳��밴 ESC\n");
}

void Guide() //��������
{

	printf("\n ��ӭ�����ɻ���ս\n\n\n\n  �㼴����Ե���\n   3�ֲ�ͬ�ĵ�\n   �˺ͼ����޷�\n   �ݻٵ��ϰ���");
	printf("\n \n \n    ���ո����ս��");
	printf("\n\n   ���س������������");
	printf("\n\n      ��ESC�˳�");

	GuideChoice();
}

void GuideChoice()//�����ж�
{

	p = getch();//�������������p

	switch (p)
		{
			case Fire:
				{
					GameInstructions();
				}
			break;
			case �س�:
				{
					rank();
				}
			break;
			case Esc:
				{
					exit(0);
				}
			break; //�˳�
			default:
				{
					printf("\n����,����������");
					GuideChoice();
				}
			break;
		}
}


void Hit()// ɱ��&�Ƿ�
{
	if (x == d && y == r)
	{
		gotoxy(d, r); printf("3");
		Sleep(200);
		gotoxy(d, r); printf("  ");
		f += 3; r = 0; j++;
	}
	if (x == d1 && y == r1)
	{
		gotoxy(d1, r1); printf("1");
		Sleep(200);
		gotoxy(d1, r1); printf("  ");
		f += 1; r1 = 0; j++;
	}
	if (x == d2 && y == r2)
	{
		gotoxy(d2, r2); printf("2");
		Sleep(200);
		gotoxy(d2, r2); printf("  ");
		f += 2; r2 = 0; j++;
	}

	gotoxy(29, 2);
	printf(" %d \n", f);
}

void Control()//�ٿطɻ�
{
	while (kbhit())//����а����������ѭ��
	{
		p = getch();//�������������p
		switch (p)
		{//���Ʒ���
		case Up:if (y != 1)//����Լ����ڵ�ͼ���ˣ���������һ����ͬ
		{
			gotoxy(x, y); printf("  ");
			y--;
			gotoxy(x, y); printf("��");
		}break;
		case Down:if (y != 18)
		{
			gotoxy(x, y); printf("  ");
			y++;
			gotoxy(x, y); printf("��");
		}break;
		case Left:if (x != 1)
		{
			gotoxy(x, y); printf("  ");
			x--;
			gotoxy(x, y); printf("��");
		}break;
		case Right:if (x != 18)
		{
			gotoxy(x, y); printf("  ");
			x++;
			gotoxy(x, y); printf("��");
		}break;

		case Fire:
		{ Y = y;
		while (y > 1)
		{
			Hit();//���������void Hit����
			y--;
			gotoxy(x, y); printf("��");
			Sleep(15);
			gotoxy(x, y); printf("  ");

		}
		y = Y;
		}break;

		case Esc:exit(0);
			break; //�˳�

		default:
			break;
		}
	}
}

void Die()//��Ϸ����
{
	if ((x == d && y == r) || (x == d1 && y == r1) || (x == d2 && y == r2) || (x == d3 && y == r3))//����з�ս�����Լ������غϣ����ж�Ϊ����
	{
		while (!_kbhit())//���û�а���������ʾ����
		{
			gotoxy(1, 3);//����ƶ���1,3��ʼ��ʾ
			printf(" !!! ��Ϸ���� !!!\n"
				"********************\n"
				"*  �����ܵ÷�: %d\n\n"
				"*   �л���: %d\n"
				"*   �ߵ���: %d\n"
				"*   ������: %.0f %%\n"
				"********************\n", f, m, j, ((float)j / (float)m) * 100);
			ranking();
			printf("\n* �����밴�����...\n\n\n");
		}
		system("cls");
		//���¶�λ����
		x = 10; //�Լ�������
		y = 18; //�Լ�������
		d = 10;//�л�0������
		d1 = 10;//�л�1������
		d2 = 10;//�л�2������
		d3 = 10;//�ϰ�1�������
		d4 = 10;//�ϰ�2�������

		r = 1;//�л�0������
		r1 = 1;//�л�1������
		r2 = 1;//�л�2������
		r3 = 1;//�ϰ�1��������
		r4 = 1;//�ϰ�2��������
		main();
	}
}

void Enemy()//�л�������
{
	while (1)
	{
		if (!r) { d = rand() % 17 + 1; m++; }  //���r����0������1~18�ĺ�����֮�����������Ȼ��л�����1
		if (!r1) { d1 = rand() % 17 + 1; m++; }
		if (!r2) { d2 = rand() % 17 + 1; m++; }
		if (f >= 10 && !r3) { d3 = rand() % 17 + 1; m++; }
		if (f >= 20 && !r4) { d4 = rand() % 17 + 1; m++; }

		while (1)//�л���ǰ��
		{
			"Sleep 50";
			r++; r1++; r2++; r3++, r4++;
			gotoxy(d, r); printf("��");
			gotoxy(d1, r1); printf("��");
			gotoxy(d2, r2); printf("��");
			gotoxy(d3, r3); printf("��");
			gotoxy(d4, r4); printf("��");
			Sleep(300);//ÿ��300ms������һ֡
			gotoxy(d, r); printf("  ");
			gotoxy(d1, r1); printf("  ");
			gotoxy(d2, r2); printf("  ");
			gotoxy(d3, r3); printf("  ");
			gotoxy(d3, r3); printf("  ");
			gotoxy(d4, r4); printf("  ");

			Control();
			Die();
			if (r == 18) r = 0;
			if (r1 == 18) r1 = 0;
			if (r2 == 18) r2 = 0;
			if (r3 == 18) r3 = 0;
			if (r4 == 18) r4 = 0;
			if (r == 0 || r1 == 0 || r2 == 0 || r3 == 0 || r4 == 0) break;//�����һ���л�������Ϊ0����ʼ��һ�ֵл��������
		}
	}
}
int ranking()//���а�ð������
{
	F[9] = f;
	//�Ż��㷨�������� n-1 �ֱȽ�
	for (i = 0; i < 9 - 1; i++)
	{
		for (j = 0; j < 9 - 1 - i; j++)
		{
			if (F[j] > F[j + 1])
			{
				temp = F[j];
				F[j] = F[j + 1];
				F[j + 1] = temp;
			}
		}

		return 0;
	}
}

void main()//�������
{
	Guide();//������������
	srand((unsigned)time(NULL));//srand(time(NULL));//�������
	map();
	hidden();//����ָ��
	gotoxy(x, y);
	printf("��");//ȷ����Ϸ��ʼ�����Լ��ħ�
	Control();//������ս����
	Enemy();
}
