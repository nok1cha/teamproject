/*게임판 확장, 게임 규칙 변경, 그래픽개선, 스코어 카운트*/
/*13011195 김성훈 2조 2017-05-16~2017-06-02 작업*/
/*project 5th*/
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

int bigboard[3][3];
char player1 = 0;
char player2 = 0;


int board[9][9];	// 3x3게임판 배열
int turn;			// 현재 player의 턴을 나타냄.
int result;			// 게임 결과
bool over;			// 게임 종료 여부

				
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
			exit(1);
		}
		break;
	default:
		exit(1);
	}
}

void OnMouseClick(int button, int state, int x, int y)//게임시작 후 마우스 버튼 지정.
{
	if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN || state == GLUT_UP)// 오른쪽 버튼 시 동작
	{
		if (turn == 1)//플레이어1 차례일때
		{
			if (board[(y - 50) / 50][x / 50] == 0)// 1칸에 100을 차지하고 50은 위의 글자부분을 커버함.만일 클릭한 그 칸의 배열이 0이면 플레이어 1일때 그 클릭한 칸에 해당하는 배열을 1로둠
			{
				board[(y - 50) / 50][x / 50] = 1;
				turn = 2;//그 후 플레이어를 다음 턴으로 넘김
			}
		}
		else if (turn == 2)
		{
			if (board[(y - 50) / 50][x / 50] == 0)
			{
				board[(y - 50) / 50][x / 50] = 2;
				turn = 1;
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
	int i=1;

	glBegin(GL_LINES);
	glColor3f(0.3, 0.3, 0.7);

	for (i = 1; i < 9; i++)
	{
		glVertex2f(50*i, 50);
		glVertex2f(50*i, 500);

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

void DrawXO()//보드판 배열 중 배열 값이 1 혹은 2일 시 판에 말을 그리도록 함.
{
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (board[i][j] == 1)
			{
				glBegin(GL_LINES);
				glVertex2f(25 + j * 50 - 12, 75 + i * 50 - 12);
				glVertex2f(25 + j * 50 + 12, 75 + i * 50 + 12);
				glVertex2f(25 + j * 50 - 12, 75 + i * 50 + 12);
				glVertex2f(25 + j * 50 + 12, 75 + i * 50 - 12);
				glEnd();
			}
			else if (board[i][j] == 2)
			{

				DrawCircle(25 + j * 50, 75 + i * 50, 12, 15);
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

bool CheckIfDraw()
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
	else if (CheckIfDraw() == true)// 누구의 승리로 끝나지 않고 칸이 다 차버린경우.
	{
		over = true;//게임오버를 표시함
		result = 0;//결과창을 0으로 바꿈.
	}
	if (over == true)//게임오버가 된 상태에서
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);//게임오버의 문자열을 출력

		if (result == 0)
		{
			if (player1 > player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);//플레이어1이 이겼을경우.
			}

			if (player1 < player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);//플레이어2가 이겼을경우.
			}

			if (player1 == player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);//비겼을 경우
			}

		}

		if (result == 1)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);//플레이어1이 이겼을경우.
		}

		if (result == 2)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);//플레이어2가 이겼을경우.
		}

		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);//재시작 할건지 물어봄
		
	}
}

void Display()
{


	if (playing == 2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glColor3f(0, 0, 0);



		shadeboard();
		DrawLines();//칸을 나누는 선 그리기 함수
		DrawXO();//말을 그리는 함수
		explain();

		checkgameover();
	}

	glutSwapBuffers();
}

void idle()
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
