// snack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

void DrawChar(int x,int y, char ch);

//��Ϸ�����б�
//1.̰�������������ƶ�
//2.̰���߳�ʳ�ﳤ��
//3.̰����ײǽ�����Լ���GG
//4.��Ϸ��������ӡ�÷�

#define MAP_WIDTH 60
#define MAP_HEIGHT 20

typedef struct Postion
{
	//x����
	int x;

	//y����
	int y;
}Position;

//̰���߽ṹ��
typedef struct Snack
{
	//̰���߳���
	int size;

	Position pos[MAP_WIDTH * MAP_HEIGHT];

}Snack;


Snack g_snack;

Position g_food;

void InitFood()
{
	srand( (unsigned)time( NULL));

	g_food.x = rand() % MAP_WIDTH;
	g_food.y = rand() % MAP_HEIGHT;

	DrawChar(g_food.x, g_food.y ,'#');

}


//��Ϸ��ʼ̰���ߵĴ�С
void InitSnack()
{
	g_snack.size=3;
	
	g_snack.pos[0].x = MAP_WIDTH/ 2;
	g_snack.pos[0].y = MAP_HEIGHT/ 2;

	g_snack.pos[1].x = MAP_WIDTH/ 2 - 1;
	g_snack.pos[1].y = MAP_HEIGHT/ 2;

	g_snack.pos[2].x =MAP_WIDTH/2-2;
	g_snack.pos[2].y = MAP_HEIGHT/2;
}


//����̰����
void DrawSnack()
{
	for(int i = 0;i < g_snack.size; i++)
	{
		if(i == 0)
		{
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y, '*');

		}
		else
		{
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y, '#');
		}
	}
}


//��x,y�����ַ�ch
void DrawChar(int x,int y, char ch)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

	putchar(ch);
}


void InitMap()
{
	for(int i= 0; i<= MAP_HEIGHT; i++)
	{
		for(int j=0; j <=MAP_WIDTH; j++)
		{
			
			if (j == MAP_WIDTH)
			{
				//�ұ߿�
				printf("|\n");
			}
			else if(i == MAP_HEIGHT)
			{
				//�ױ�
				printf("-");
			}
			else
			{
				printf(" ");
			}
		
		}

	}
}



void Init()
{


	//���Ƶ�ͼ
	InitMap();
	InitSnack();
	InitFood();
}

void UpdateScreen()
{
	DrawSnack();
}



//��������
void SnackMove(int key)
{
	int delta_x = 0;
	int delta_y = 0;

	if (key == 'w' || key == 'W')//w��
	{
		delta_x = 0;
		delta_y = -1;
	}
	else if(key == 's' || key == 'S')//s��
	{
		delta_x = 0;
		delta_y = 1;
	}
	else if(key == 'a' || key == 'A')//a��
	{
		delta_x = -1;
		delta_y = 0;
	}
	else if(key == 'd' || key == 'D')//d��
	{
		delta_x = 1;
		delta_y = 0;
	}
	else
	{
		//��Ч����
		return;
	}

	DrawChar(g_snack.pos[g_snack.size - 1].x,g_snack.pos[g_snack.size - 1].y,' ');


	for(int i = g_snack.size - 1; i > 0; i--)
	{
		g_snack.pos[i].x = g_snack.pos[i-1].x;
		g_snack.pos[i].y = g_snack.pos[i-1].y;
	}
	
	g_snack.pos[0].x += delta_x;
	g_snack.pos[0].y += delta_y;
}

void EatFood()
{
	if (g_snack.pos[0].x == g_food.x &&
		g_snack.pos[0].y == g_food.y )
	{
		g_snack.size++;
		g_snack.pos[g_snack.size - 1].x = g_food.x;
		g_snack.pos[g_snack.size - 1].y = g_food.y;
		InitFood();
	}
}


void GameLoop()
{
	int key = 0;
	while(1)
	{
		//�����������
		
		//����Ƿ��а�������
		if(_kbhit())
		{
			key = _getch();
		}
		if(key == 'q' || key == 'Q')
		{
			return;
		}

		//�����ƶ�̰����
		SnackMove(key);
		//����ײǽ�¼�
		EatFood();

		//���»���
		UpdateScreen();
		//��ʱ
		Sleep(100);

	}
}


void Score()
{
}




int main(int argc, char* argv[])
{
	//��ʼ��������ͼ
	Init();


	//��Ϸ��ѭ��������������Ϸ����ˢ�£�����ײǽ���¼�
	GameLoop();

	
	//��ӡ�÷�
	Score();
	return 0;
}

