#include <stdio.h>
#include <windows.h>//Windows窗口，COORD结构体实现光标随方向键移动
#include <conio.h>//通过按键盘产生的对应操作，如getch()，gotoxy()
#include <time.h>//以时间作为随机数的种子来产生随机数（下面用到）
#pragma warning(disable:4996)//屏蔽vs2017报4996的错
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


#define Esc 27 //退出
#define Up 72 //上
#define Down 80 //下
#define Left 75 //左
#define Right 77 //右
#define Fire 32 //发射子弹
#define 回车 13 //进rank

int x = 10; //自己横坐标
int y = 18; //自己纵坐标
int d = 10;//敌机0横坐标
int d1 = 10;//敌机1横坐标
int d2 = 10;//敌机2横坐标
int d3 = 10;//障碍物横坐标
int d4 = 10;//障碍物横坐标

int r = 1;//敌机0纵坐标
int r1 = 1;//敌机1纵坐标
int r2 = 1;//敌机2纵坐标
int r3 = 1;//障碍物纵坐标
int r4 = 1;//障碍物纵坐标

int f = 0; // 计分数
int m = 1; // 敌机数
int j = 0; // 歼敌数
int Y;//后来发射子弹时暂时替换
char p; // 接受按键
int F[10];//历史分数
int i, j, temp, isSorted;


void gotoxy(int x, int y) //移动光标至（x，y）
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//使光标coord移动到（x,y）的位置（调用此函数需要windows.h头文件）
}
void hidden()//光标的隐藏,这两个函数参考来源于https://zhidao.baidu.com/question/557336915.html
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;//赋1为显示，赋0为隐藏
	SetConsoleCursorInfo(hOut, &cci);
	gotoxy(x, y);
}

void rank()//排行榜
{
	system("cls");
	gotoxy(0, 0);
	printf("\t\t\t分数排行榜如下\n\n\n\n");
	for (i = 9; i >= 0; i--)
	{
		printf("\t\t%d\n ", F[i]);
	}
	printf("\n");
	system("pause");//暂停
	system("cls");//清屏
	Guide();

}

void map()//构出地图
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

void GameInstructions()//游戏说明
{
	system("cls");
	printf("\n\n\n\n\t\t\t\t作");
	Sleep(100);
	printf("战");
	Sleep(100);
	printf("控");
	Sleep(100);
	printf("制");
	Sleep(100);
	printf("连");
	Sleep(100);
	printf("线");
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
	printf(" 分数:");
	printf("\n\n\n\t\t\t控制\n\n"
		"\t\t\t上 ↑\n\n"
		"\t\t\t下 ↓\n\n"
		"\t\t\t左 ←\n\n"
		"\t\t\t右 →\n\n"
		"\t\t\t子弹 空格\n\n"
		"\t\t\t退出请按 ESC\n");
}

void Guide() //引导界面
{

	printf("\n 欢迎来到飞机大战\n\n\n\n  你即将面对的是\n   3种不同的敌\n   人和几个无法\n   摧毁的障碍物");
	printf("\n \n \n    按空格进入战斗");
	printf("\n\n   按回车进入分数界面");
	printf("\n\n      按ESC退出");

	GuideChoice();
}

void GuideChoice()//引导判断
{

	p = getch();//把这个按键赋给p

	switch (p)
		{
			case Fire:
				{
					GameInstructions();
				}
			break;
			case 回车:
				{
					rank();
				}
			break;
			case Esc:
				{
					exit(0);
				}
			break; //退出
			default:
				{
					printf("\n错误,请重新输入");
					GuideChoice();
				}
			break;
		}
}


void Hit()// 杀敌&记分
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

void Control()//操控飞机
{
	while (kbhit())//如果有按键，则进入循环
	{
		p = getch();//把这个按键赋给p
		switch (p)
		{//控制方向
		case Up:if (y != 1)//如果自己不在地图顶端，则向上走一格，下同
		{
			gotoxy(x, y); printf("  ");
			y--;
			gotoxy(x, y); printf("Ж");
		}break;
		case Down:if (y != 18)
		{
			gotoxy(x, y); printf("  ");
			y++;
			gotoxy(x, y); printf("Ж");
		}break;
		case Left:if (x != 1)
		{
			gotoxy(x, y); printf("  ");
			x--;
			gotoxy(x, y); printf("Ж");
		}break;
		case Right:if (x != 18)
		{
			gotoxy(x, y); printf("  ");
			x++;
			gotoxy(x, y); printf("Ж");
		}break;

		case Fire:
		{ Y = y;
		while (y > 1)
		{
			Hit();//调用上面的void Hit函数
			y--;
			gotoxy(x, y); printf("Λ");
			Sleep(15);
			gotoxy(x, y); printf("  ");

		}
		y = Y;
		}break;

		case Esc:exit(0);
			break; //退出

		default:
			break;
		}
	}
}

void Die()//游戏结束
{
	if ((x == d && y == r) || (x == d1 && y == r1) || (x == d2 && y == r2) || (x == d3 && y == r3))//如果敌方战机和自己坐标重合，则判断为死亡
	{
		while (!_kbhit())//如果没有按键，则显示如下
		{
			gotoxy(1, 3);//光标移动至1,3开始显示
			printf(" !!! 游戏结束 !!!\n"
				"********************\n"
				"*  您的总得分: %d\n\n"
				"*   敌机数: %d\n"
				"*   歼敌数: %d\n"
				"*   命中率: %.0f %%\n"
				"********************\n", f, m, j, ((float)j / (float)m) * 100);
			ranking();
			printf("\n* 继续请按任意键...\n\n\n");
		}
		system("cls");
		//重新定位坐标
		x = 10; //自己横坐标
		y = 18; //自己纵坐标
		d = 10;//敌机0横坐标
		d1 = 10;//敌机1横坐标
		d2 = 10;//敌机2横坐标
		d3 = 10;//障碍1物横坐标
		d4 = 10;//障碍2物横坐标

		r = 1;//敌机0纵坐标
		r1 = 1;//敌机1纵坐标
		r2 = 1;//敌机2纵坐标
		r3 = 1;//障碍1物纵坐标
		r4 = 1;//障碍2物纵坐标
		main();
	}
}

void Enemy()//敌机的生成
{
	while (1)
	{
		if (!r) { d = rand() % 17 + 1; m++; }  //如果r等于0，则在1~18的横坐标之间随机产生，然后敌机数＋1
		if (!r1) { d1 = rand() % 17 + 1; m++; }
		if (!r2) { d2 = rand() % 17 + 1; m++; }
		if (f >= 10 && !r3) { d3 = rand() % 17 + 1; m++; }
		if (f >= 20 && !r4) { d4 = rand() % 17 + 1; m++; }

		while (1)//敌机向前走
		{
			"Sleep 50";
			r++; r1++; r2++; r3++, r4++;
			gotoxy(d, r); printf("Ψ");
			gotoxy(d1, r1); printf("ж");
			gotoxy(d2, r2); printf("♀");
			gotoxy(d3, r3); printf("▓");
			gotoxy(d4, r4); printf("▓");
			Sleep(300);//每隔300ms进行下一帧
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
			if (r == 0 || r1 == 0 || r2 == 0 || r3 == 0 || r4 == 0) break;//如果有一个敌机纵坐标为0，则开始下一种敌机随机生成
		}
	}
}
int ranking()//排行榜冒泡排序
{
	F[9] = f;
	//优化算法：最多进行 n-1 轮比较
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

void main()//定义入口
{
	Guide();//进入引导界面
	srand((unsigned)time(NULL));//srand(time(NULL));//随机函数
	map();
	hidden();//隐藏指针
	gotoxy(x, y);
	printf("Ж");//确保游戏开始就有自己的Ж
	Control();//控制作战连线
	Enemy();
}
