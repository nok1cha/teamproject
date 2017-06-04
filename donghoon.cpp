#include <stdlib.h>  
#include <glut.h> 
#include <iostream> 
#include <math.h>  
#include <time.h>  
#include <string.h>  
#define pi 3.14 
//���: ����, �׸�, �� 
int board[3][3];   // board for gameplay   
int turn;         // current move  
int result;         // Result of the game   
bool over;         // Is the game Over?   

int kind1; //player1�� ��(����, �׸�, ��)�� ��Ÿ���� ���� ����=1, �׸�=2, ��=3  
int kind2; //player2�� �� (����, �׸�, ��)�� ��Ÿ���� ���� ����=1, �׸�=2, ��=3 
const GLfloat size = 2.0;

int stage = 2;
void DrawString(void *font, const char s[], float x, float y) // string �Լ� 
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}
void Triangle(int x, int y, int r) // �ﰢ�� ����� �Լ� x��ǥ, y��ǥ, ũ�⸦ ��Ÿ�� r 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x, y + r + size);
	glVertex2f(x + r*cos(330 * pi / 180) - size, y + r*sin(330 * pi / 180) - size);
	glVertex2f(x + r*cos(210 * pi / 180) + size, y + r*sin(210 * pi / 180) - size);
	glEnd();
}
void Rectangular(int x, int y, int r) // �簢�� ����� �Լ� 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x + r, y + r);
	glVertex2f(x - r, y + r);
	glVertex2f(x - r, y - r);
	glVertex2f(x + r, y - r);
	glEnd();
}

void Circle(float cx, float cy, float r, int num_segments)  //�� ����� �Լ� 
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle  ������ angle ���       
		float x = r * cosf(theta);//calculate the x component  ���� angle���� x��ǥ ���ϱ�      
		float y = r * sinf(theta);//calculate the y component  ���� angle���� y��ǥ ���ϱ�      
		glVertex2f(x + cx, y + cy);//output vertex    
	}
	glEnd();
}
void SetKinkByMouse(int button, int state, int x, int y)//���콺�Լ� �̿��ؼ� ���� ������ x��ǥ�� 0~100�̸� ����, 101~200�̸� �׸�, 201~300�̸� ������
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (x > 150 && x < 250 && y < 45 * 1.5)
			stage = 1;

	}


}

void explain()
{
	glColor3f(0.2, 0.1, 0);
	DrawString(GLUT_BITMAP_HELVETICA_18, "BACK to START", 160, 45);
	DrawString(GLUT_BITMAP_HELVETICA_18, "In horses select stage,", 0, 80);
	DrawString(GLUT_BITMAP_HELVETICA_18, "Mouse left button = Select symbol of player1", 0, 100);
	DrawString(GLUT_BITMAP_HELVETICA_18, "Mouse right button = Select symbol of player2", 0, 120);
	glColor3f(0.2, 0.1, 0.3);
	DrawString(GLUT_BITMAP_HELVETICA_18, "It is possible to place any symbol freely in 9 * 9 board.", 0, 150);
	DrawString(GLUT_BITMAP_HELVETICA_18, "3 * 3 If you draw 3 symbols in horizontal, vertical, and", 0, 180);
	DrawString(GLUT_BITMAP_HELVETICA_18, "diagonal lines inside the board, you win the 3 * 3 board, ", 0, 210);
	DrawString(GLUT_BITMAP_HELVETICA_18, "and the board changes to the winning player color.", 0, 240);
	DrawString(GLUT_BITMAP_HELVETICA_18, "The changed 3 * 3 board is treated as another symbols,", 0, 270);
	DrawString(GLUT_BITMAP_HELVETICA_18, "and if the 3 * 3 board are connected in horizontal,", 0, 300);
	DrawString(GLUT_BITMAP_HELVETICA_18, "vertical, and diagonal lines, the final win is achieved", 0, 330);
	glColor3f(0.1, 0.2, 0.1);
	DrawString(GLUT_BITMAP_HELVETICA_18, "There is a time limit of 10 seconds per turn.", 0, 370);
	DrawString(GLUT_BITMAP_HELVETICA_18, "If anybody do not win until the end, you must fill", 0, 400);
	DrawString(GLUT_BITMAP_HELVETICA_18, " all the spaces to finish the game.", 0, 430);
	glColor3f(0.0, 0.0, 0.0);
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.7, 0.4, 0.7, 1);
	if (stage == 2)
	{
		explain();

	}
	glutSwapBuffers();
}

void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(450, 500); //������ ������� x=300, y=350    
	glutCreateWindow("Tic Tac Toe"); //������ ��    
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(SetKinkByMouse);
	glutIdleFunc(Display);
	glutMainLoop();
	return 0;
}