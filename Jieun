/*
파일명 : TicTaeToe.cpp
작성자 : 박지은, ABHISHEK BIND(원저작자)
목적 : 2인용 발전된 오목게임을 실행 하기 위해 프로그램을 만들었다.
사용방식 : START버튼을 누른 후 게임을 시작 하면 된다.
사용파일 : 해당 사항 없음
제한사항 : 해당 사항 없음
오류처리 : Visual Studio 에서 빌드 할때 증분링크사용을 아니요로 설정해 주어야 한다.
이력사항 : 2015-12-1 : ABHISHEK BIND - 최초 작성
		  2017-04-26 ~ 2017-05-07 : 박 지은 - 시작화면,종료화면 추가 
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <glut.h>
#define PI 3.141592 //PI를 3.141592로 정의해둠

int stage=1;		// 시작화면(1), 게임화면(2), 종료화면(3)으로 나눔, 첫 화면은 시작화면이므로 1로 초기화
int board[3][3];	// 게임 보드판
int turn;			// 현재의 턴(player1 or player2)
int result;			// 게임의 결과
bool over;			// 게임 종료 여부

void DrawCircle(float cx, float cy, float r, int num_segments); //말 선택 메뉴에 이 함수를 쓰기 위해 미리 함수 원형을 선언함
void DrawCross(float cx, float cy);//말 선택 메뉴에 이 함수를 쓰기 위해 미리 함수 원형을 선언함

/*
	보드판을 초기화 하는 함수
*/
void Intialize()
{
	turn=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			board[i][j]=0;
	}
}

/*
	START 버튼
*/
void StartButton(int x,int y)
{
	glColor3f(1,1,1);
	glLineWidth(10);	
	//S 나타내기
	glBegin(GL_LINES);		
		glVertex2f(15,20);
		glVertex2f(60,20);

		glVertex2f(15,20);
		glVertex2f(15,90);
		
		glVertex2f(15,90);
		glVertex2f(60,90);
		
		glVertex2f(60,90);
		glVertex2f(60,160);
		
		glVertex2f(60,160);
		glVertex2f(15,160);
	glEnd();
	//T 나타내기
	glBegin(GL_LINES);	
		glVertex2f(70,20);
		glVertex2f(120,20);
		
		glVertex2f(95,20);
		glVertex2f(95,160);
	glEnd();
	//A 나타내기
	glBegin(GL_LINES);	
		glVertex2f(130,20);
		glVertex2f(130,160);
		
		glVertex2f(130,20);
		glVertex2f(175,20);
		
		glVertex2f(175,20);
		glVertex2f(175,160);
		
		glVertex2f(130,90);
		glVertex2f(175,90);
	glEnd();
	//R 나타내기
	glBegin(GL_LINES);	
		glVertex2f(185,20);
		glVertex2f(185,160);
		
		glVertex2f(185,20);
		glVertex2f(230,20);
		
		glVertex2f(185,90);
		glVertex2f(230,90);
		
		glVertex2f(230,20);
		glVertex2f(230,90);
		
		glVertex2f(185,90);
		glVertex2f(230,160);
	glEnd();
	//T 나타내기
	glBegin(GL_LINES);	
		glVertex2f(240,20);
		glVertex2f(290,20);
		
		glVertex2f(265,20);
		glVertex2f(265,160);
	glEnd();
}

/*
	말선택 메뉴 부분 자리
*/
void Select(int x,int y,int r) 
{
	glBegin(GL_LINES);
	glColor3f(0.5,0.7,0.4);
		//사각형 만들기
		glVertex2f(10,340);
		glVertex2f(10,190);
		
		glVertex2f(10,190);
		glVertex2f(140,190);
		
		glVertex2f(140,190);
		glVertex2f(140,340);
		
		glVertex2f(140,340);
		glVertex2f(10,340);

		glVertex2f(10,340);
		glVertex2f(140,190);
	glEnd();
	DrawCircle(45,240,25,15);
	DrawCross(105,300);
}

/*
	규칙설명 메뉴 부분 자리
*/
void Rule(int x,int y) 
{
	glBegin(GL_LINES);
	glColor3f(0.5,0.7,0.4);
		//사각형 만들기
		glVertex2f(160,340);
		glVertex2f(160,190);
		
		glVertex2f(160,190);
		glVertex2f(290,190);
		
		glVertex2f(290,190);
		glVertex2f(290,340);
		
		glVertex2f(290,340);
		glVertex2f(160,340);

		//R 나타내기
		glVertex2f(170,245);
		glVertex2f(190,245);
		
		glVertex2f(170,245);
		glVertex2f(170,265);
		
		glVertex2f(170,265);
		glVertex2f(190,265);
		
		glVertex2f(190,265);
		glVertex2f(190,245);
		
		glVertex2f(170,265);
		glVertex2f(190,285);
		
		glVertex2f(170,265);
		glVertex2f(170,285);
		
		//U 나타내기
		glVertex2f(200,245);
		glVertex2f(200,285);

		glVertex2f(200,285);
		glVertex2f(220,285);
		
		glVertex2f(220,285);
		glVertex2f(220,245);
		
		//L 나타내기
		glVertex2f(230,245);
		glVertex2f(230,285);
		
		glVertex2f(250,285);
		glVertex2f(230,285);
		
		//E 나타내기
		glVertex2f(260,245);
		glVertex2f(280,245);

		glVertex2f(260,245);
		glVertex2f(260,285);

		glVertex2f(260,265);
		glVertex2f(280,265);

		glVertex2f(260,285);
		glVertex2f(280,285);
	glEnd();
}

/*
	키보드함수 : y를 누르면 게임 다시 시작, n을 누르면 게임 종료, 다른 버튼 누르면 게임 종료
*/
void OnKeyPress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'y':
		if(over==true)
		{
			over=false;
			Intialize();
			stage=2;
		}
		break;
		case 'n':
		if(over==true)
		{
			exit(0);
		}
		break;
		default:
			exit(0);
	}
}

/*
	마우스함수 : stage가 1일때 start버튼을 누르면 게임 시작으로 stage가 2로 넘어감
	    stage가 2일때 player가 누른 자리에 아무 말도 놓여 있지 않을때 자신의 말을 놓고 turn을 넘겨줌
*/
void OnMouseClick(int button,int state,int x,int y)	
{
	if(stage==1)
	{
		//START버튼을 누르면 게임 화면으로 넘어감
		if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>10 && x<290 && y>20 && y<160)
		{
			stage=2;
			glutPostRedisplay();
		}

	}
	else if(stage==2)
	{
		if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		{
			if(turn==1)
			{
				if(board[(y-50)/100][x/100]==0)
				{
					board[(y-50)/100][x/100]=1;
					turn=2;
				}
			}
			else if(turn==2)
			{
				if(board[(y-50)/100][x/100]==0)
				{
					board[(y-50)/100][x/100]=2;
					turn=1;
				}
			}
		}
	}
	
}

/*
	누구의 순서인지, 누가 이겼는지 비트맵 형식으로 알려주는 함수
*/
void DrawString(void *font,const char s[],float x,float y)
{
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(font,s[i]);
	}
}

/*
	보드판 선을 그림
*/
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0,0,0);
		glVertex2f(100,50);
		glVertex2f(100,340);
	
		glVertex2f(200,340);
		glVertex2f(200,50);
	
		glVertex2f(0,150);
		glVertex2f(300,150);
	
		glVertex2f(0,250);
		glVertex2f(300,250);
	glEnd();		
}

/*
	Player1 말 모양인 X를 그림
*/
void DrawCross(float cx, float cy)
{
	glBegin(GL_LINES);
		glVertex2f(cx-25,cy-25);
		glVertex2f(cx+25,cy+25);
		glVertex2f(cx-25,cy+25);
		glVertex2f(cx+25,cy-25);
	glEnd();
}

/*
	Player2 말 모양인 O를 그림
*/
void DrawCircle(float cx, float cy, float r, int num_segments) 
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)   
    {
        float theta;
	theta = 2.0f * PI* float(i);
	theta = theta / float(num_segments);//현재 각도를 얻음 
        float x = r * cosf(theta);// x 값 계산 
        float y = r * sinf(theta);// y 값 계산
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


/*
	보드판 안에 X,O를 그리는 함수
*/
void DrawXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==1)
			{
				DrawCross(50+j*100,100+i*100);
				
			}
			else if(board[i][j]==2)
			{
				
				DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);
			}
		}
	}
}

/*
	규칙에 의거해 승리를 검사하는 함수 
*/
bool CheckWinner()
{
	int i, j;
	
	// 세로로 같은 말이 이어지는지 검사  
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[i][0]!=0 && board[i][0]==board[i][j])
			{
				if(j==2)
				{
					return true;//위의 검사를 만족하면 승리자가 있는 것으로 true를 반환함
				}
			}
			else
				break;
		}
	}
	
	//가로로 같은 말이 이어지는지 검사 
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[0][i]!=0 && board[0][i]==board[j][i])
			{
				if(j==2)
					return true;//위의 검사를 만족하면 승리자가 있는 것으로 true를 반환함
			}
			else
				break;
		}
	}

	// 대각선으로 같은 말이 이어지는지 검사
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2]) 
	|| (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
	{
		return true;//위의 검사를 만족하면 승리자가 있는 것으로 true를 반환함
	}

	return false;//위의 검사를 만족하지 않으면 승리자가 없는 것으로 false를 반환함
}

/*
	무승부 인지를 검사하는 함수
*/
bool CheckIfDraw()
{
	int i, j;
	for(i=0;i<3;i++)
	{ 
		for(j=0;j<3;j++)
		{ 
			if(board[i][j]==0)
				return false;//보드판이 다 말로 가득차지 않았으면 무승부가 결정나지 않으므로 false를 반환
		}
	}
	return true;//보드판이 모두 말로 가득 찼기에 무승부이므로 true를 반환함	
}

/*
	화면에 객체를 띄우는 함수
*/
void Display()
{
	//시작 화면 일때 
	if(stage==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7,0.4,0.7,1);
		Select(0,0,0);
		Rule(0,0);
		StartButton(0,0);
	}

	//게임 화면 일때
	else if(stage==2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glColor3f(0, 0, 0);
		if(turn == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);	
		else
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);	
	
		DrawLines();
		DrawXO();
	
		//승리자 검사 
		if(CheckWinner() == true)
		{
			if(turn == 1)
			{
				over = true;
				result = 2;
			}
			else
			{
				over = true;
				result = 1; 
			}
		}

		//무승부 검사
		else if(CheckIfDraw() == true)
		{
			over = true;
			result = 0;
		}
		if(over == true)
		{
			stage=3;
			
		}
	}

	//종료 화면 일때
	else if(stage==3)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.7,0.4,0.7,1);
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
			if(result == 0)
				DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw!", 110, 185);
			if(result == 1)
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins!", 95, 185);
			if(result == 2)
				DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins!", 95, 185);
				
			DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue? (y/n)", 40, 210);
	}
	glutSwapBuffers();
}

/*
	화면 크기가 변경될때 객체의 비율이 유지되도록 하는 함수
*/
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
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(300,350);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}
