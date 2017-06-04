/*������ Ȯ��, ���� ��Ģ ����, �׷��Ȱ���, ���ھ� ī��Ʈ*/
/*13011195 �輺�� 2�� 2017-05-16~2017-06-02 �۾�*/
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


int board[9][9];	// 3x3������ �迭
int turn;			// ���� player�� ���� ��Ÿ��.
int result;			// ���� ���
bool over;			// ���� ���� ����

				
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
			exit(1);
		}
		break;
	default:
		exit(1);
	}
}

void OnMouseClick(int button, int state, int x, int y)//���ӽ��� �� ���콺 ��ư ����.
{
	if (over == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN || state == GLUT_UP)// ������ ��ư �� ����
	{
		if (turn == 1)//�÷��̾�1 �����϶�
		{
			if (board[(y - 50) / 50][x / 50] == 0)// 1ĭ�� 100�� �����ϰ� 50�� ���� ���ںκ��� Ŀ����.���� Ŭ���� �� ĭ�� �迭�� 0�̸� �÷��̾� 1�϶� �� Ŭ���� ĭ�� �ش��ϴ� �迭�� 1�ε�
			{
				board[(y - 50) / 50][x / 50] = 1;
				turn = 2;//�� �� �÷��̾ ���� ������ �ѱ�
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

void DrawXO()//������ �迭 �� �迭 ���� 1 Ȥ�� 2�� �� �ǿ� ���� �׸����� ��.
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

bool CheckIfDraw()
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
	else if (CheckIfDraw() == true)// ������ �¸��� ������ �ʰ� ĭ�� �� ���������.
	{
		over = true;//���ӿ����� ǥ����
		result = 0;//���â�� 0���� �ٲ�.
	}
	if (over == true)//���ӿ����� �� ���¿���
	{
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);//���ӿ����� ���ڿ��� ���

		if (result == 0)
		{
			if (player1 > player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);//�÷��̾�1�� �̰������.
			}

			if (player1 < player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);//�÷��̾�2�� �̰������.
			}

			if (player1 == player2)
			{
				DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);//����� ���
			}

		}

		if (result == 1)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);//�÷��̾�1�� �̰������.
		}

		if (result == 2)
		{
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);//�÷��̾�2�� �̰������.
		}

		DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);//����� �Ұ��� ���
		
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
		DrawLines();//ĭ�� ������ �� �׸��� �Լ�
		DrawXO();//���� �׸��� �Լ�
		explain();

		checkgameover();
	}

	glutSwapBuffers();
}

void idle()
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
