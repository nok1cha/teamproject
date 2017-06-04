#include <stdlib.h>  
#include <glut.h> 
#include <iostream> 
#include <math.h>  
#include <time.h>  
#include <string.h>  
#define pi 3.14 
//모양: 세모, 네모, 원 
int board[3][3];   // board for gameplay   
int turn;         // current move  
int result;         // Result of the game   
bool over;         // Is the game Over?   

int kind1; //player1의 말(세모, 네모, 원)을 나타내는 변수 세모=1, 네모=2, 원=3  
int kind2; //player2의 말 (세모, 네모, 원)을 나타내는 변수 세모=1, 네모=2, 원=3 
const GLfloat size = 2.0;

int stage = 2;
void DrawString(void *font, const char s[], float x, float y) // string 함수 
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i<strlen(s); i++)
	{
		glutBitmapCharacter(font, s[i]);
	}
}
void Triangle(int x, int y, int r) // 삼각형 만드는 함수 x좌표, y좌표, 크기를 나타낼 r 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x, y + r + size);
	glVertex2f(x + r*cos(330 * pi / 180) - size, y + r*sin(330 * pi / 180) - size);
	glVertex2f(x + r*cos(210 * pi / 180) + size, y + r*sin(210 * pi / 180) - size);
	glEnd();
}
void Rectangular(int x, int y, int r) // 사각형 만드는 함수 
{
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.5, 0.0);
	glVertex2f(x + r, y + r);
	glVertex2f(x - r, y + r);
	glVertex2f(x - r, y - r);
	glVertex2f(x + r, y - r);
	glEnd();
}

void Circle(float cx, float cy, float r, int num_segments)  //원 만드는 함수 
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle  현재의 angle 얻기       
		float x = r * cosf(theta);//calculate the x component  얻은 angle토대로 x좌표 구하기      
		float y = r * sinf(theta);//calculate the y component  얻은 angle토대로 y좌표 구하기      
		glVertex2f(x + cx, y + cy);//output vertex    
	}
	glEnd();
}
void SetKinkByMouse(int button, int state, int x, int y)//마우스함수 이용해서 구간 나눠서 x좌표가 0~100이면 세모, 101~200이면 네모, 201~300이면 원으로
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
	glutInitWindowSize(450, 500); //윈도우 사이즈는 x=300, y=350    
	glutCreateWindow("Tic Tac Toe"); //윈도우 명    
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(SetKinkByMouse);
	glutIdleFunc(Display);
	glutMainLoop();
	return 0;
}