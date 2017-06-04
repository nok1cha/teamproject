/*Third merge  (seonghoon+jieun+jeongeun)file + boseoung file merging)*/
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>

#define PI 3.141592 //PI를 3.141592로 정의해둠

int stage = 1;		// 시작화면(1), 게임화면(2), 종료화면(3)으로 나눔, 첫 화면은 시작화면이므로 1로 초기화

bool finish1 = false; //player1말 선택이 끝났는가를 알리는 변수  
bool finish2 = false; //player2의 말 선택이 끝났는가를 알리는 변수  
int kind1 = 1; //player1의 말을 나타내는 변수  
int kind2 = 2; //player2의 말을 나타내는 변수 
const GLfloat size = 2.0;

int bigboard[3][3];
char player1 = 0;
char player2 = 0;


int board[9][9];	// 3x3게임판 배열
int turn;			// 현재 player의 턴을 나타냄.
int result;			// 게임 결과
bool over;			// 게임 종료 여부

int timer1 = (int)time(NULL); //first start time

int timer2 = 0; // time limit, timer (int)time(NULL)

					/*
					START 버튼
					*/
void StartButton()
{
	glColor3f(1, 1, 1);
	glLineWidth(10);
	//S 나타내기
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
	//T 나타내기
	glBegin(GL_LINES);
	glVertex2f(70 * 1.5, 20 * 1.5);
	glVertex2f(120 * 1.5, 20 * 1.5);

	glVertex2f(95 * 1.5, 20 * 1.5);
	glVertex2f(95 * 1.5, 160 * 1.5);
	glEnd();
	//A 나타내기
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
	//R 나타내기
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
	//T 나타내기
	glBegin(GL_LINES);
	glVertex2f(240 * 1.5, 20 * 1.5);
	glVertex2f(290 * 1.5, 20 * 1.5);

	glVertex2f(265 * 1.5, 20 * 1.5);
	glVertex2f(265 * 1.5, 160 * 1.5);
	glEnd();
}

/*
말선택 메뉴 부분 자리
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

void DrawCircle(float cx, float cy, float r, int num_segments)//동그라미 그리기
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)//원점을 중심으로 num_segments의 수만큼 원의 테두리에 점을 찍어 선으로 연결한다.
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
	//사각형 만들기
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
규칙설명 메뉴 부분 자리
*/
void Rule(int x, int y)
{
	glBegin(GL_LINES);
	glColor3f(0.5, 0.7, 0.4);
	//사각형 만들기
	glVertex2f(160 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 190 * 1.5);

	glVertex2f(160 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 190 * 1.5);

	glVertex2f(290 * 1.5, 190 * 1.5);
	glVertex2f(290 * 1.5, 340 * 1.5);

	glVertex2f(290 * 1.5, 340 * 1.5);
	glVertex2f(160 * 1.5, 340 * 1.5);

	//R 나타내기
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

	//U 나타내기
	glVertex2f(200 * 1.5, 245 * 1.5);
	glVertex2f(200 * 1.5, 285 * 1.5);

	glVertex2f(200 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 285 * 1.5);

	glVertex2f(220 * 1.5, 285 * 1.5);
	glVertex2f(220 * 1.5, 245 * 1.5);

	//L 나타내기
	glVertex2f(230 * 1.5, 245 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	glVertex2f(250 * 1.5, 285 * 1.5);
	glVertex2f(230 * 1.5, 285 * 1.5);

	//E 나타내기
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
말 모양 ■를 그림
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

void Intialize()//초기화 값 지정. (플레이어 턴을 1로 한 후 보드판 배열을 전부 0으로 초기화)
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
void OnKeyPress(unsigned char key, int x, int y)//게임 오버 시 키보드 버튼 지정.
{
	switch (key)
	{
	case 'y'://게임오버 후 y 누를 시 재시작.
		if (over == true)
		{
			over = false;
			Intialize();
		}
		break;
	case 'n'://게임오버 후 n 누를 시 종료.
		if (over == true)
		{
			stage = 1;
		}
		break;

	}
}

void OnMouseClick(int button, int state, int x, int y)//게임시작 후 마우스 버튼 지정.
{
	if (stage == 1)
	{
		//START버튼을 누르면 게임 화면으로 넘어감
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
			if (x > 0 && x < 112 && y > 45 && y < 230 && kind2 != 1) //세모 선택했을 경우      
				kind1 = 1;
			else if (x > 112 && x < 224 && y > 45 && y < 230 && kind2 != 2)//네모 선택했을 경우 
				kind1 = 2;
			else if (x > 224 && x < 336 && y > 45 && y < 230 && kind2 != 3)//엑스 선택했을 경우  
				kind1 = 3;
			else if (x > 336 && x < 448 && y > 45 && y < 230 && kind2 != 4)//원 선택했을 경우  
				kind1 = 4;
			if (x > 150 && x < 250 && y < 45 * 1.5)
				stage = 1;

		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			if (x > 0 && x < 112 && y > 45 && y < 230 && kind1 != 1) //세모 선택했을 경우      
				kind2 = 1;
			else if (x > 112 && x < 224 && y > 45 && y < 230 && kind1 != 2)//네모 선택했을 경우 
				kind2 = 2;
			else if (x > 224 && x < 336 && y > 45 && y < 230 && kind1 != 3)//엑스 선택했을 경우  
				kind2 = 3;
			else if (x > 336 && x < 448 && y > 45 && y < 230 && kind1 != 4)//원 선택했을 경우  
				kind2 = 4;

		}
	}

	else if (stage == 3)
	{

		if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// 오른쪽 버튼 시 동작
		{

			if (turn == 1)//플레이어1 차례일때
			{
				if (board[(y - 50) / 50][x / 50] == 0)// 1칸에 100을 차지하고 50은 위의 글자부분을 커버함.만일 클릭한 그 칸의 배열이 0이면 플레이어 1일때 그 클릭한 칸에 해당하는 배열을 1로둠
				{
					board[(y - 50) / 50][x / 50] = 1;
					turn = 2;//그 후 플레이어를 다음 턴으로 넘김
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

void DrawString(void *font, const char s[], float x, float y)//윈도우창 윗 쪽에 플레이어의 상태를 나타낼 수 있도록 함.
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}

void DrawLines()//칸을 나누는 선
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



void DrawXO()//보드판 배열 중 배열 값이 1 혹은 2일 시 판에 말을 그리도록 함.
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


void CheckWinner(int a, int b)//수직 수평 대각선의 배열값을 검사함.
{
	int i, j;
	if (bigboard[a][b] == 0)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 1; j < 3; j++)
			{
				if (board[i + a * 3][b * 3] != 0 && board[i + a * 3][b * 3] == board[i + a * 3][j + b * 3])//수평 오른쪽방향으로 한 행 씩 그 행의 첫 열의 값과 나머지 열의 값과 비교하여 전부 같으면 true값을 리턴함. 오른쪽방향으로 첫 열의 값과 비교하다가 같지않으면 그 행을 검사하는걸 break함    
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
				if (board[a * 3][i + b * 3] != 0 && board[a * 3][i + b * 3] == board[j + a * 3][i + b * 3])//수직 아래 방향으로 한 열 씩 그 열의 첫 행의 값과 나머지 행의 값과 비교하여 전부 같으면 true값을 리턴함. 아래 방향으로 첫 행의 값과 비교하다가 같지 않으면 그 열을 검사하는걸 break함.
				{
					if (j == 2)
						bigboard[a][b] = turn;
				}
				else
					break;
			}
		}
		// Diagonal check
		if ((board[a * 3][b * 3] != 0 && board[a * 3][b * 3] == board[1 + a * 3][1 + b * 3] && board[a * 3][b * 3] == board[2 + a * 3][2 + b * 3])//왼쪽 위부터 오른쪽 아래로 그어지는 대각선 값들이 모두 같은지 검사함.
			|| (board[2 + a * 3][b * 3] != 0 && board[2 + a * 3][b * 3] == board[1 + a * 3][1 + b * 3] && board[2 + a * 3][b * 3] == board[a * 3][2 + b * 3]))//오른쪽쪽 위부터 왼쪽 아래로 그어지는 대각선 값들이 모두 같은지 검사함.
			bigboard[a][b] = turn;

	}
}

bool BigCheckWinner()//수직 수평 대각선의 배열값을 검사함.
{
	int i, j;

	for (i = 0; i<3; i++)
	{
		for (j = 1; j<3; j++)
		{
			if (bigboard[i][0] != 0 && bigboard[i][0] == bigboard[i][j])//수평 오른쪽방향으로 한 행 씩 그 행의 첫 열의 값과 나머지 열의 값과 비교하여 전부 같으면 true값을 리턴함. 오른쪽방향으로 첫 열의 값과 비교하다가 같지않으면 그 행을 검사하는걸 break함    
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
			if (bigboard[0][i] != 0 && bigboard[0][i] == bigboard[j][i])//수직 아래 방향으로 한 열 씩 그 열의 첫 행의 값과 나머지 행의 값과 비교하여 전부 같으면 true값을 리턴함. 아래 방향으로 첫 행의 값과 비교하다가 같지 않으면 그 열을 검사하는걸 break함.
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if ((bigboard[0][0] != 0 && bigboard[0][0] == bigboard[1][1] && bigboard[0][0] == bigboard[2][2])//왼쪽 위부터 오른쪽 아래로 그어지는 대각선 값들이 모두 같은지 검사함.
		|| (bigboard[2][0] != 0 && bigboard[2][0] == bigboard[1][1] && bigboard[2][0] == bigboard[0][2]))//오른쪽쪽 위부터 왼쪽 아래로 그어지는 대각선 값들이 모두 같은지 검사함.
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
				return false;//어느 한칸이라도 빈칸이 있으면 false를 나타냄



		}
	}
	return true;// 모든 보드판의 배열 값을 검사 한 후 전부 0이 아닌 값을 가지고 있다면 true값을 도출함.
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
				return false;//어느 한칸이라도 빈칸이 있으면 false를 나타냄



		}
	}
	return true;// 모든 보드판의 배열 값을 검사 한 후 전부 0이 아닌 값을 가지고 있다면 true값을 도출함.
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
	if (turn == 1)//플레이어 턴 상태창
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
	if (BigCheckWinner() == true)//수평 수직 대각선 중 배열값들이 전부 일치 할 경우 
	{
		if (turn == 1)//게임 오버가 됬을 때 플레이어1의 차례에서 끝나버릴 경우
		{
			over = true;//게임오버를 표시함.
			result = 2;//결과창을 플레이어 2가 승리로 바꿈.
		}
		else
		{
			over = true;
			result = 1;
		}
	}
	else if (CheckIfDraw1() == true || CheckIfDraw2() == true)// 누구의 승리로 끝나지 않고 칸이 다 차버린경우.
	{
		over = true;//게임오버를 표시함
		result = 0;//결과창을 0으로 바꿈.
	}
	if (over == true)//게임오버가 된 상태에서
	{
		glColor3f(1, 1, 1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 50, 250);//게임오버의 문자열을 출력

		if (result == 0)
		{
			if (player1 > player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 150, 200);//플레이어1이 이겼을경우.
			}

			if (player1 < player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 150, 200);//플레이어2가 이겼을경우.
			}

			if (player1 == player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 150, 200);//비겼을 경우
			}

		}

		if (result == 1)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 150, 200);//플레이어1이 이겼을경우.
		}

		if (result == 2)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 150, 200);//플레이어2가 이겼을경우.
		}

		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 150, 280);//재시작 할건지 물어봄

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
		DrawLines();//칸을 나누는 선 그리기 함수
		DrawXO();//말을 그리는 함수
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
		CheckWinner(0, 0);//포문 안돌리고 하는게 더 좋은 코딩
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
void Reshape(int x, int y)//윈도우 크기를 변경할시 면적만 늘어나게 함.
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
	glutInitWindowPosition(200, 200);//윈도우 창이 나타날 시 위치
	glutInitWindowSize(450, 500);//윈도우 창의 사이즈
	glutCreateWindow("Tic Tac Toe");//윈도우 창의 이름
	glutReshapeFunc(Reshape);//윈도우의 크기를 변경했을 경우의 상태
	glutDisplayFunc(Display);//화면에 무엇을 그릴것인지 표시


	glutKeyboardFunc(OnKeyPress);//키보드키를 눌렀을경우의 반응
	glutMouseFunc(OnMouseClick);//마우스키를 눌렀을경우의 반응
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
