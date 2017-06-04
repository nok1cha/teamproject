/*Third merge  (seonghoon+jieun+jeongeun)file + boseoung file merging)*/
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>

#define PI 3.141592 //PI�� 3.141592�� �����ص�

int stage = 1;		// ����ȭ��(1), ����ȭ��(2), ����ȭ��(3)���� ����, ù ȭ���� ����ȭ���̹Ƿ� 1�� �ʱ�ȭ

bool finish1 = false; //player1�� ������ �����°��� �˸��� ����  
bool finish2 = false; //player2�� �� ������ �����°��� �˸��� ����  
int kind1 = 1; //player1�� ���� ��Ÿ���� ����  
int kind2 = 2; //player2�� ���� ��Ÿ���� ���� 
const GLfloat size = 2.0;

int bigboard[3][3];
char player1 = 0;
char player2 = 0;


int board[9][9];	// 3x3������ �迭
int turn;			// ���� player�� ���� ��Ÿ��.
int result;			// ���� ���
bool over;			// ���� ���� ����

int timer1 = (int)time(NULL); //first start time

int timer2 = 0; // time limit, timer (int)time(NULL)

					/*
					START ��ư
					*/
void StartButton()
{
	glColor3f(1, 1, 1);
	glLineWidth(10);
	//S ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(15 * 1.5, 20 * 1.5);
	glVertex2f(60 * 1.5, 20 * 1.5);

	glVertex2f(15 * 1.5, 20 * 1.5);
	glVertex2f(15 * 1.5, 90 * 1.5);

	glVertex2f(15 * 1.5, 90 * 1.5);
	glVertex2f(60 * 1.5, 90 * 1.5);

	glVertex2f(60 * 1.5, 90 * 1.5);
	glVertex2f(60 * 1.5, 160 * 1.5);

	glVertex2f(60 * 1.5, 160 * 1.5);
	glVertex2f(15 * 1.5, 160 * 1.5);
	glEnd();
	//T ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(70 * 1.5, 20 * 1.5);
	glVertex2f(120 * 1.5, 20 * 1.5);

	glVertex2f(95 * 1.5, 20 * 1.5);
	glVertex2f(95 * 1.5, 160 * 1.5);
	glEnd();
	//A ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(130 * 1.5, 20 * 1.5);
	glVertex2f(130 * 1.5, 160 * 1.5);

	glVertex2f(130 * 1.5, 20 * 1.5);
	glVertex2f(175 * 1.5, 20 * 1.5);

	glVertex2f(175 * 1.5, 20 * 1.5);
	glVertex2f(175 * 1.5, 160 * 1.5);

	glVertex2f(130 * 1.5, 90 * 1.5);
	glVertex2f(175 * 1.5, 90 * 1.5);
	glEnd();
	//R ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(185 * 1.5, 20 * 1.5);
	glVertex2f(185 * 1.5, 160 * 1.5);

	glVertex2f(185 * 1.5, 20 * 1.5);
	glVertex2f(230 * 1.5, 20 * 1.5);

	glVertex2f(185 * 1.5, 90 * 1.5);
	glVertex2f(230 * 1.5, 90 * 1.5);

	glVertex2f(230 * 1.5, 20 * 1.5);
	glVertex2f(230 * 1.5, 90 * 1.5);

	glVertex2f(185 * 1.5, 90 * 1.5);
	glVertex2f(230 * 1.5, 160 * 1.5);
	glEnd();
	//T ��Ÿ����
	glBegin(GL_LINES);
	glVertex2f(240 * 1.5, 20 * 1.5);
	glVertex2f(290 * 1.5, 20 * 1.5);

	glVertex2f(265 * 1.5, 20 * 1.5);
	glVertex2f(265 * 1.5, 160 * 1.5);
	glEnd();
}

/*
������ �޴� �κ� �ڸ�
*/
void DrawCross(float cx, float cy)
{
	glBegin(GL_LINES);
	glVertex2f(cx - 12, cy - 12);
	glVertex2f(cx + 12, cy + 12);
	glVertex2f(cx - 12, cy + 12);
	glVertex2f(cx + 12, cy - 12);
	glEnd();
}

void DrawCross1(float cx, float cy)
{
	glBegin(GL_LINES);
	glVertex2f(cx - 40, cy - 40);
	glVertex2f(cx + 40, cy + 40);
	glVertex2f(cx - 40, cy + 40);
	glVertex2f(cx + 40, cy - 40);
	glEnd();
}

void DrawCircle(float cx, float cy, float r, int num_segments)//���׶�� �׸���
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)//������ �߽����� num_segments�� ����ŭ ���� �׵θ��� ���� ��� ������ �����Ѵ�.
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void Select(int x, int y, int r)
{
	glBegin(GL_LINES);
	glColor3f(0.5*1.5, 0.7*1.5, 0.4*1.5);
	//�簢�� �����
	glVertex2f(10 * 1.5, 340 * 1.5);
	glVertex2f(10 * 1.5, 190 * 1.5);

	glVertex2f(10 * 1.5, 190 * 1.5);
	glVertex2f(140 * 1.5, 190 * 1.5);

	glVertex2f(140 * 1.5, 190 * 1.5);
	glVertex2f(140 * 1.5, 340 * 1.5);

	glVertex2f(140 * 1.5, 340 * 1.5);
	glVertex2f(10 * 1.5, 340 * 1.5);

	glVertex2f(10 * 1.5, 340 * 1.5);
	glVertex2f(140 * 1.5, 190 * 1.5);
	glEnd();
	DrawCircle(45 * 1.5, 240 * 1.5, 25 * 1.5, 15 * 1.5);

	glBegin(GL_LINES);
	glVertex2f(105 * 1.5 - 25, 300 * 1.5 - 25);
	glVertex2f(105 * 1.5 + 25, 300 * 1.5 + 25);
	glVertex2f(105 * 1.5 - 25, 300 * 1.5 + 25);
	glVertex2f(105 * 1.5 + 25, 300 * 1.5 - 25);
	glEnd();

}

/*
��Ģ���� �޴� �κ� �ڸ�
*/
void Rule(int x, int y)
{
	glBegin(GL_LINES);
	glColor3f(0.5, 0.7, 0.4);
	//�簢�� �����
	glVertex2f(160 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 190 * 1.5);

	glVertex2f(160 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 190 * 1.5);

	glVertex2f(290 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 340 * 1.5);

	glVertex2f(290 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 340 * 1.5);

	//R ��Ÿ����
	glVertex2f(170 * 1.5, 245 * 1.5);
	glVertex2f(190 * 1.5, 245 * 1.5);

	glVertex2f(170 * 1.5, 245 * 1.5);
	glVertex2f(170 * 1.5, 265 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 265 * 1.5);

	glVertex2f(190 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 245 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(190 * 1.5, 285 * 1.5);

	glVertex2f(170 * 1.5, 265 * 1.5);
	glVertex2f(170 * 1.5, 285 * 1.5);

	//U ��Ÿ����
	glVertex2f(200 * 1.5, 245 * 1.5);
	glVertex2f(200 * 1.5, 285 * 1.5);

	glVertex2f(200 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 285 * 1.5);

	glVertex2f(220 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 245 * 1.5);

	//L ��Ÿ����
	glVertex2f(230 * 1.5, 245 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	glVertex2f(250 * 1.5, 285 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	//E ��Ÿ����
	glVertex2f(260 * 1.5, 245 * 1.5);
	glVertex2f(280 * 1.5, 245 * 1.5);

	glVertex2f(260 * 1.5, 245 * 1.5);
	glVertex2f(260 * 1.5, 285 * 1.5);

	glVertex2f(260 * 1.5, 265 * 1.5);
	glVertex2f(280 * 1.5, 265 * 1.5);

	glVertex2f(260 * 1.5, 285 * 1.5);
	glVertex2f(280 * 1.5, 285 * 1.5);
	glEnd();
}

void Triangle(int x, int y, int r)
{

	glBegin(GL_POLYGON);
	glVertex2f(x, y + r + size);
	glVertex2f(x + r*cos(330 * PI / 180) - size, y + r*sin(330 * PI / 180) - size);
	glVertex2f(x + r*cos(210 * PI / 180) + size, y + r*sin(210 * PI / 180) - size);
	glEnd();
}

/*
�� ��� �Ḧ �׸�
*/
void Rectangular(int x, int y, int r)
{
	glBegin(GL_POLYGON);
	glVertex2f(x + r, y + r);
	glVertex2f(x - r, y + r);
	glVertex2f(x - r, y - r);
	glVertex2f(x + r, y - r);
	glEnd();
}

void Intialize()//�ʱ�ȭ �� ����. (�÷��̾� ���� 1�� �� �� ������ �迭�� ���� 0���� �ʱ�ȭ)
{
	turn = 1;
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
			board[i][j] = 0;
	}

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
			bigboard[i][j] = 0;
	}
	player1 = 0;
	player2 = 0;

}
/*
Called when any key from keyboard is pressed
*/
void OnKeyPress(unsigned char key, int x, int y)//���� ���� �� Ű���� ��ư ����.
{
	switch (key)
	{
	case 'y'://���ӿ��� �� y ���� �� �����.
		if (over == true)
		{
			over = false;
			Intialize();
		}
		break;
	case 'n'://���ӿ��� �� n ���� �� ����.
		if (over == true)
		{
			stage = 1;
		}
		break;

	}
}

void OnMouseClick(int button, int state, int x, int y)//���ӽ��� �� ���콺 ��ư ����.
{
	if (stage == 1)
	{
		//START��ư�� ������ ���� ȭ������ �Ѿ
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>10 && x<290 * 1.5 && y>20 && y<160 * 1.5)
		{

			stage = 3;

			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>10 && x< 140 * 1.5 && y>190 * 1.5 && y<340 * 1.5)
		{
			stage = 2;
			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>160 * 1.5 && x< 290 * 1.5 && y>190 * 1.5 && y<340 * 1.5)
		{
			stage = 5;
			glutPostRedisplay();
		}
	}

	else if (stage == 2)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (x > 0 && x < 112 && y > 45 && y < 230 && kind2 != 1) //���� �������� ���      
				kind1 = 1;
			else if (x > 112 && x < 224 && y > 45 && y < 230 && kind2 != 2)//�׸� �������� ��� 
				kind1 = 2;
			else if (x > 224 && x < 336 && y > 45 && y < 230 && kind2 != 3)//���� �������� ���  
				kind1 = 3;
			else if (x > 336 && x < 448 && y > 45 && y < 230 && kind2 != 4)//�� �������� ���  
				kind1 = 4;
			if (x > 150 && x < 250 && y < 45 * 1.5)
				stage = 1;

		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			if (x > 0 && x < 112 && y > 45 && y < 230 && kind1 != 1) //���� �������� ���      
				kind2 = 1;
			else if (x > 112 && x < 224 && y > 45 && y < 230 && kind1 != 2)//�׸� �������� ��� 
				kind2 = 2;
			else if (x > 224 && x < 336 && y > 45 && y < 230 && kind1 != 3)//���� �������� ���  
				kind2 = 3;
			else if (x > 336 && x < 448 && y > 45 && y < 230 && kind1 != 4)//�� �������� ���  
				kind2 = 4;

		}
	}

	else if (stage == 3)
	{

		if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// ������ ��ư �� ����
		{

			if (turn == 1)//�÷��̾�1 �����϶�
			{
				if (board[(y - 50) / 50][x / 50] == 0)// 1ĭ�� 100�� �����ϰ� 50�� ���� ���ںκ��� Ŀ����.���� Ŭ���� �� ĭ�� �迭�� 0�̸� �÷��̾� 1�϶� �� Ŭ���� ĭ�� �ش��ϴ� �迭�� 1�ε�
				{
					board[(y - 50) / 50][x / 50] = 1;
					turn = 2;//�� �� �÷��̾ ���� ������ �ѱ�
					timer1 = (int)time(NULL); //restart timer
				}
			}
			else if (turn == 2)
			{
				if (board[(y - 50) / 50][x / 50] == 0)
				{
					board[(y - 50) / 50][x / 50] = 2;
					turn = 1;
					timer1 = (int)time(NULL); //restart timer
				}
			}
			for (int i = 0; i < 9; i++)
			{
				printf("\n");
				for (int j = 0; j < 9; j++)
				{
					printf("board[%d][%d]=%d  ", i, j, board[i][j]);
				}
			}

			for (int i = 0; i < 3; i++)
			{
				printf("\n");
				for (int j = 0; j < 3; j++)
				{
					printf("bigboard[%d][%d]=%d  ", i, j, bigboard[i][j]);
				}
			}

		}
	}
}

void DrawString(void *font, const char s[], float x, float y)//������â �� �ʿ� �÷��̾��� ���¸� ��Ÿ�� �� �ֵ��� ��.
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

void DrawLines()//ĭ�� ������ ��
{
	int i = 1;

	glBegin(GL_LINES);
	glColor3f(0.3, 0.3, 0.7);

	for (i = 1; i < 9; i++)
	{
		glVertex2f(50 * i, 50);
		glVertex2f(50 * i, 500);

		glVertex2f(0, 50 + 50 * i);
		glVertex2f(450, 50 + 50 * i);
	}

	glColor3f(0.0, 0.0, 0.0);

	for (i = 1; i < 3; i++)
	{
		glVertex2f(150 * i, 50);
		glVertex2f(150 * i, 500);

		glVertex2f(0, 50 + 150 * i);
		glVertex2f(450, 50 + 150 * i);
	}


	glEnd();
}



void DrawXO()//������ �迭 �� �迭 ���� 1 Ȥ�� 2�� �� �ǿ� ���� �׸����� ��.
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (board[i][j] == 1)
			{

				if (kind1 == 1)
				{
					Triangle(25 + j * 50, 75 + i * 50, 15);
				}
				else if (kind1 == 2)
				{
					Rectangular(25 + j * 50, 75 + i * 50, 15);
				}
				else if (kind1 == 3)
				{
					DrawCross(25 + j * 50, 75 + i * 50);
				}
				else if (kind1 == 4)
				{
					DrawCircle(25 + j * 50, 75 + i * 50, 15, 10);
				}

			}
			else if (board[i][j] == 2)
			{

				if (kind2 == 1)
				{
					Triangle(25 + j * 50, 75 + i * 50, 15);
				}
				else if (kind2 == 2)
				{
					Rectangular(25 + j * 50, 75 + i * 50, 15);
				}
				else if (kind2 == 3)
				{
					DrawCross(25 + j * 50, 75 + i * 50);
				}
				else if (kind2 == 4)
				{
					DrawCircle(25 + j * 50, 75 + i * 50, 15, 10);
				}

			}
		}
	}
}


void CheckWinner(int a, int b)//���� ���� �밢���� �迭���� �˻���.
{
	int i, j;
	if (bigboard[a][b] == 0)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j < 3; j++)
			{
				if (board[i + a * 3][b * 3] != 0 && board[i + a * 3][b * 3] == board[i + a * 3][j + b * 3])//���� �����ʹ������� �� �� �� �� ���� ù ���� ���� ������ ���� ���� ���Ͽ� ���� ������ true���� ������. �����ʹ������� ù ���� ���� ���ϴٰ� ���������� �� ���� �˻��ϴ°� break��    
				{
					if (j == 2)
					{
						bigboard[a][b] = turn;
					}

				}
				else
					break;
			}
		}

		for (i = 0; i < 3; i++)
		{
			for (j = 1; j < 3; j++)
			{
				if (board[a * 3][i + b * 3] != 0 && board[a * 3][i + b * 3] == board[j + a * 3][i + b * 3])//���� �Ʒ� �������� �� �� �� �� ���� ù ���� ���� ������ ���� ���� ���Ͽ� ���� ������ true���� ������. �Ʒ� �������� ù ���� ���� ���ϴٰ� ���� ������ �� ���� �˻��ϴ°� break��.
				{
					if (j == 2)
						bigboard[a][b] = turn;
				}
				else
					break;
			}
		}
		// Diagonal check
		if ((board[a * 3][b * 3] != 0 && board[a * 3][b * 3] == board[1 + a * 3][1 + b * 3] && board[a * 3][b * 3] == board[2 + a * 3][2 + b * 3])//���� ������ ������ �Ʒ��� �׾����� �밢�� ������ ��� ������ �˻���.
			|| (board[2 + a * 3][b * 3] != 0 && board[2 + a * 3][b * 3] == board[1 + a * 3][1 + b * 3] && board[2 + a * 3][b * 3] == board[a * 3][2 + b * 3]))//�������� ������ ���� �Ʒ��� �׾����� �밢�� ������ ��� ������ �˻���.
			bigboard[a][b] = turn;

	}
}

bool BigCheckWinner()//���� ���� �밢���� �迭���� �˻���.
{
	int i, j;

	for (i = 0; i<3; i++)
	{
		for (j = 1; j<3; j++)
		{
			if (bigboard[i][0] != 0 && bigboard[i][0] == bigboard[i][j])//���� �����ʹ������� �� �� �� �� ���� ù ���� ���� ������ ���� ���� ���Ͽ� ���� ������ true���� ������. �����ʹ������� ù ���� ���� ���ϴٰ� ���������� �� ���� �˻��ϴ°� break��    
			{
				if (j == 2)
				{
					return true;
				}
			}
			else
				break;
		}
	}

	for (i = 0; i<3; i++)
	{
		for (j = 1; j<3; j++)
		{
			if (bigboard[0][i] != 0 && bigboard[0][i] == bigboard[j][i])//���� �Ʒ� �������� �� �� �� �� ���� ù ���� ���� ������ ���� ���� ���Ͽ� ���� ������ true���� ������. �Ʒ� �������� ù ���� ���� ���ϴٰ� ���� ������ �� ���� �˻��ϴ°� break��.
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if ((bigboard[0][0] != 0 && bigboard[0][0] == bigboard[1][1] && bigboard[0][0] == bigboard[2][2])//���� ������ ������ �Ʒ��� �׾����� �밢�� ������ ��� ������ �˻���.
		|| (bigboard[2][0] != 0 && bigboard[2][0] == bigboard[1][1] && bigboard[2][0] == bigboard[0][2]))//�������� ������ ���� �Ʒ��� �׾����� �밢�� ������ ��� ������ �˻���.
		return true;

	return false;
}

bool CheckIfDraw1()
{
	int i, j;
	bool draw;
	for (i = 0; i<3; i++)
	{
		for (j = 0; j<3; j++)
		{
			if (bigboard[i][j] == 0)
				return false;//��� ��ĭ�̶� ��ĭ�� ������ false�� ��Ÿ��



		}
	}
	return true;// ��� �������� �迭 ���� �˻� �� �� ���� 0�� �ƴ� ���� ������ �ִٸ� true���� ������.
}

bool CheckIfDraw2()
{
	int i, j;
	bool draw;
	for (i = 0; i<9; i++)
	{
		for (j = 0; j<9; j++)
		{
			if (board[i][j] == 0)
				return false;//��� ��ĭ�̶� ��ĭ�� ������ false�� ��Ÿ��



		}
	}
	return true;// ��� �������� �迭 ���� �˻� �� �� ���� 0�� �ƴ� ���� ������ �ִٸ� true���� ������.
}

void shadeboard()
{
	int i, j;

	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if (bigboard[j][i] == 3)
			{
				glColor3f(0.5, 0.5, 0.5);
				glBegin(GL_POLYGON);
				glVertex2d(0 + i * 150, 50 + j * 150);
				glVertex2d(0 + (i + 1) * 150, 50 + j * 150);
				glVertex2d(0 + (i + 1) * 150, 50 + (j + 1) * 150);
				glVertex2d(0 + i * 150, 50 + (j + 1) * 150);
				glEnd();

			}
			else if (bigboard[j][i] == 4)
			{
				glColor3f(0.1, 0.5, 0.4);
				glBegin(GL_POLYGON);
				glVertex2d(0 + i * 150, 50 + j * 150);
				glVertex2d(0 + (i + 1) * 150, 50 + j * 150);
				glVertex2d(0 + (i + 1) * 150, 50 + (j + 1) * 150);
				glVertex2d(0 + i * 150, 50 + (j + 1) * 150);
				glEnd();
			}


		}
	}

}

void explain()
{
	if (turn == 1)//�÷��̾� �� ����â
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 50, 30);
	else
		DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 50, 30);


	if (player1 == 0) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 0 ", 200, 15);
	if (player1 == 1) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 1 ", 200, 15);
	if (player1 == 2) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 2 ", 200, 15);
	if (player1 == 3) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 3 ", 200, 15);
	if (player1 == 4) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 4 ", 200, 15);
	if (player1 == 5) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 5 ", 200, 15);
	if (player1 == 6) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 6 ", 200, 15);
	if (player1 == 7) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 7 ", 200, 15);
	if (player1 == 8) DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's Score : 8 ", 200, 15);

	if (player2 == 0) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 0 ", 200, 45);
	if (player2 == 1) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 1 ", 200, 45);
	if (player2 == 2) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 2 ", 200, 45);
	if (player2 == 3) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 3 ", 200, 45);
	if (player2 == 4) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 4 ", 200, 45);
	if (player2 == 5) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 5 ", 200, 45);
	if (player2 == 6) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 6 ", 200, 45);
	if (player2 == 7) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 7 ", 200, 45);
	if (player2 == 8) DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's Score : 8 ", 200, 45);


}

void takescore()
{
	int i, j;

	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 3; i++)
		{
			if (bigboard[j][i] == 1)
			{
				player2++;
				bigboard[j][i] = 3;
			}
			else if (bigboard[j][i] == 2)
			{
				player1++;
				bigboard[j][i] = 4;
			}


		}
	}


}

void checkgameover()
{
	if (BigCheckWinner() == true)//���� ���� �밢�� �� �迭������ ���� ��ġ �� ��� 
	{
		if (turn == 1)//���� ������ ���� �� �÷��̾�1�� ���ʿ��� �������� ���
		{
			over = true;//���ӿ����� ǥ����.
			result = 2;//���â�� �÷��̾� 2�� �¸��� �ٲ�.
		}
		else
		{
			over = true;
			result = 1;
		}
	}
	else if (CheckIfDraw1() == true || CheckIfDraw2() == true)// ������ �¸��� ������ �ʰ� ĭ�� �� ���������.
	{
		over = true;//���ӿ����� ǥ����
		result = 0;//���â�� 0���� �ٲ�.
	}
	if (over == true)//���ӿ����� �� ���¿���
	{
		glColor3f(1, 1, 1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 50, 250);//���ӿ����� ���ڿ��� ���

		if (result == 0)
		{
			if (player1 > player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 150, 200);//�÷��̾�1�� �̰������.
			}

			if (player1 < player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 150, 200);//�÷��̾�2�� �̰������.
			}

			if (player1 == player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 150, 200);//����� ���
			}

		}

		if (result == 1)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 150, 200);//�÷��̾�1�� �̰������.
		}

		if (result == 2)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 150, 200);//�÷��̾�2�� �̰������.
		}

		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 150, 280);//����� �Ұ��� ���

	}
}

void selectstage()
{
	glColor3f(0, 0, 0);
	DrawString(GLUT_BITMAP_HELVETICA_18, "BACK to START", 160, 30 * 1.5);
	Triangle(56, 100 * 1.5, 30 * 1.5);
	Rectangular(168, 100 * 1.5, 30 * 1.5);
	DrawCross1(280, 100 * 1.5);
	DrawCircle(392, 100 * 1.5, 30 * 1.5, 15 * 1.5);
	DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER1", 75 * 1.5, 180 * 1.5);
	DrawString(GLUT_BITMAP_HELVETICA_18, "PLAYER2", 175 * 1.5, 180 * 1.5);
	glFlush();
	switch (kind1)
	{
	case 1:
		Triangle(100 * 1.5, 230 * 1.5, 30 * 1.5);
		break;
	case 2:
		Rectangular(100 * 1.5, 230 * 1.5, 30 * 1.5);
		break;
	case 3:
		DrawCross1(100 * 1.5, 230 * 1.5);
		break;
	case 4:
		DrawCircle(100 * 1.5, 230 * 1.5, 30 * 1.5, 15 * 1.5);
		break;
	}
	switch (kind2)
	{
	case 1:
		Triangle(200 * 1.5, 230 * 1.5, 30 * 1.5);
		break;
	case 2:
		Rectangular(200 * 1.5, 230 * 1.5, 30 * 1.5);
		break;
	case 3:
		DrawCross1(200 * 1.5, 230 * 1.5);
		break;
	case 4:
		DrawCircle(200 * 1.5, 230 * 1.5, 30 * 1.5, 15 * 1.5);
		break;
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);

	if (stage == 1)
	{

		glClearColor(0.7, 0.4, 0.7, 1);
		Select(0, 0, 0);
		Rule(0, 0);
		StartButton();
	}

	if (stage == 2)
	{
		selectstage();

	}


	if (stage == 3)
	{
		shadeboard();
		DrawLines();//ĭ�� ������ �� �׸��� �Լ�
		DrawXO();//���� �׸��� �Լ�
		explain();

		checkgameover();

		timer2 = (int)time(NULL); // real time

		switch (timer2 - timer1) { // time passed
		case 0: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 10", 200, 30); break;
		case 1: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 10", 200, 30); break;
		case 2: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 09", 200, 30); break;
		case 3: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 08", 200, 30); break;
		case 4: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 07", 200, 30); break;
		case 5: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 06", 200, 30); break;
		case 6: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 05", 200, 30); break;
		case 7: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 04", 200, 30); break;
		case 8: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 03", 200, 30); break;
		case 9: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 02", 200, 30); break;
		case 10: DrawString(GLUT_BITMAP_HELVETICA_18, "00 : 01", 200, 30); break; // display left seconds
		
		case 11: 
			bool randompick = true;


			while (randompick)
			{
				srand((unsigned)time(NULL));
				int a = rand() % 9;
				int b = rand() % 9;

				if (board[a][b] == 0)
				{
					board[a][b] = turn;
					printf("%d", board[a][b]);

					randompick = false;
				}

			}


			if (turn == 1) turn = 2; else turn = 1;// over turn if not finished in limit seconds
			timer1 = (int)time(NULL); break;  //intialize time
		}


	}
	glutSwapBuffers();
}

void idle()
{
	if (stage == 3)
	{
		CheckWinner(0, 0);//���� �ȵ����� �ϴ°� �� ���� �ڵ�
		CheckWinner(0, 1);
		CheckWinner(0, 2);
		CheckWinner(1, 0);
		CheckWinner(1, 1);
		CheckWinner(1, 2);
		CheckWinner(2, 0);
		CheckWinner(2, 1);
		CheckWinner(2, 2);

		takescore();
	}
	glutPostRedisplay();
}


/*
Function to reshape
*/
void Reshape(int x, int y)//������ ũ�⸦ �����ҽ� ������ �þ�� ��.
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

/*
Driver Function
*/
int main(int argc, char **argv)
{
	
	Intialize();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 200);//������ â�� ��Ÿ�� �� ��ġ
	glutInitWindowSize(450, 500);//������ â�� ������
	glutCreateWindow("Tic Tac Toe");//������ â�� �̸�
	glutReshapeFunc(Reshape);//�������� ũ�⸦ �������� ����� ����
	glutDisplayFunc(Display);//ȭ�鿡 ������ �׸������� ǥ��


	glutKeyboardFunc(OnKeyPress);//Ű����Ű�� ����������� ����
	glutMouseFunc(OnMouseClick);//���콺Ű�� ����������� ����
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
