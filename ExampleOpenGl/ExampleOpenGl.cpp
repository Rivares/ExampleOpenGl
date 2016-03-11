#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include <vector>
#include <thread>
#include <cstdarg>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <time.h>
 
using namespace std;


void x1Thread(int N, vector<vector<double> > &x1, double buf1[]);
void y1Thread(int N, vector<vector<double> > &y1, double buf2[]);

long double timeBeg = clock();



void output(GLfloat x, GLfloat y, char* text)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
	GLfloat ficks = 0.1f;
	glScalef(ficks, ficks, 0);
	for( char* p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
    }
    glPopMatrix();
}


void displayMe()
{
	GLfloat cntrlpointsP[10000][5];
	int N =10000, z = 5;
	//GLfloat cntrlpointsJ[10000][5];
	double  Rp = 0.0191806, Rj = 0.0000777, t1 = 3, Gamma1 = (0.05654433 * t1) / 0.5, Gamma2 = (0.0002291314 * t1) / 0.5;
	double buf1[5] = {160, 160,  156, 151.99, 147.99},
	buf2[5] = {120.37, 120.37, 124.38, 128.38, 132.39};

    /*
    vector<double> bmp(5, 0.0);
    vector<vector<double> > x1(N,bmp);
    vector<vector<double> > y1(N,bmp);
*/
    vector<double> bmp(5, 0);
    vector<vector<double> > x1(N,bmp);
    vector<vector<double> > y1(N,bmp);

    thread t0(x1Thread, N, ref(x1), buf1);
    thread t9(y1Thread, N, ref(y1), buf2);

    t0.join();
    t9.join();
/*
	double **x1 = new double *[N];  // 1(1)
	for(int i = 0; i < N; i++)
    {
        x1[i] = new double [5];
    }


	double **y1 = new double *[N];  // 1(2)
	for(int i = 0; i < N; i++)
    {
        y1[i] = new double [5];
    }


    for(int i = 0; i < N; i++)
    {
       x1[i][0] = 160;  // 2(1)
       x1[i][1] = 0; x1[i][2] = 0; x1[i][3] = 0;
       x1[i][4] = 147.99;

       y1[i][0] = 120.37;  // 2(2)
       y1[i][1] = 0; y1[i][2] = 0; y1[i][3] = 0;
       y1[i][4] = 132.39;
    }


    for(int i = 0; i < 5; i++)  // 3(1)
    {
       x1[0][i] = buf1[i];
    }

	for(int i = 0; i < 5; i++) // 3(2)
    {
       y1[0][i] = buf2[i];
    }
*/

    // DEFINED FOR ALL SCHEMA

    for(int i = 1, c = 0; i < N; i++)   // n: t
    {

       for(int j = 1; j < (z-1); j++)  // i: z
       {
		   x1[i][j] = x1[i-1][j] * (-Gamma1 + 1 - (t1 * Rp)) + (Gamma1 * x1[i-1][j-1]) + (t1 * Rp * y1[i-1][(z-1)-j]);
		   y1[i][j] = y1[i-1][j] * (-Gamma2 + 1 - (t1 * Rj)) + (Gamma2 * y1[i-1][j-1]) + (t1 * Rj * x1[i-1][(z-1)-j]);   	   
       }
    }


    for(int i = 0; i < N; i++)
    {
       for(int j = 0; j < z; j++)
       {
		   cntrlpointsP[i][j] = x1[i][j];
		   //cntrlpointsJ[i][j] = y1[i][j];
       }
       cout << endl;
    }
	
	//------------------------------------------------------------------------------------------------
	
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

	    short x0 = 25, xN = 1000, y0 = 5, yN = 680;
	    // Drawing axis coordinates:
        glVertex2f(x0, y0);                          // one point of coordinates axis x
        glVertex2f(xN, y0);

		glVertex2f(xN, y0);							// one part point of axis x
        glVertex2f(xN-10, y0+5);
		glVertex2f(xN, y0);							// two part point of axis x
        glVertex2f(xN-10, y0-5);

        glVertex2f(x0, y0);							// one point of coordinates axis y
	    glVertex2f(x0, yN);
    
		glVertex2f(x0, yN);							// one part point of axis y
        glVertex2f(x0-4, yN-10);
		glVertex2f(x0, yN);							// two part point of axis y
        glVertex2f(x0+4, yN-10);		

	    //  Drawing lines on axis y:     ( x = 3.846153 - coeff scalability;  156 * x = 600 ); 3.846153*0.66666*cntrlpointsP[0][1]
	    glVertex2f( x0+3, 3.846153*0.66666*cntrlpointsP[0][1] );		// 160
        glVertex2f( x0-3, 3.846153*0.66666*cntrlpointsP[0][1] );

		glVertex2f( x0+3, 3.846153*cntrlpointsP[0][2]/2 );			   // 156
        glVertex2f( x0-3, 3.846153*cntrlpointsP[0][2]/2 );

		glVertex2f( x0+3, 3.846153*cntrlpointsP[0][3]/3 );			   // 151.99
        glVertex2f( x0-3, 3.846153*cntrlpointsP[0][3]/3 );


		for(short i = 25; i < N-10; i += 25)
		{
		    glVertex2f(i, y0+3);									   // other lines on axis x
            glVertex2f(i, y0-3);
		}

				
	    //  Drawing function to lines:
		
		for(short i = 1; i < (z-1); ++i)
		{
			float xbuf = 25;
			for(short m = 0; m < N-1; ++m)
			{
				float buf1 = 0;			
				buf1 = (3.846153) * cntrlpointsP[m][i];
				if (i == 1)										// for scalability
					glVertex2f(xbuf, buf1/(i/0.66666));
				else 
					glVertex2f(xbuf, buf1/i);	

				xbuf += 1;									   // step

				buf1 = (3.846153) * cntrlpointsP[m+1][i];
				if (i == 1)
					glVertex2f(xbuf, buf1/(i/0.66666));
                else 
					glVertex2f(xbuf, buf1/i);
			}


	    }
		
	
		
	glEnd();
	
	output(35, 660, "T,'C");
	output(860, 50, "t*10^(4) sec");
	output(10, 5, "0");

	output(x0, 3.846153*0.66666*cntrlpointsP[0][1], "160");
	output(x0, 3.846153*cntrlpointsP[0][2]/2, "156");
	output(x0, 3.846153*cntrlpointsP[0][3]/3, "151.99");
	
/*  union cnvrt
	{
	    float dt;
		char bdt[sizeof(float)];
	};

    cnvrt it;
*/


	
	char it[]={"0.40.81.21.6  2   2.42.8  3  3.4 3.8"};
	/*for(short i = 1; i < (11); ++i) // 25 - step on time i < (N-1/25)
	{	output(x0+(i*25), y0+10,  &it[i-1]);
	}*/
	output(x0+(10), y0+10,  it);



    glFlush();

		
	cout << "Difference time: " << (clock() - timeBeg) / 1000 << endl;
	
/*
	
    for(int i = 0; i < 10; i++)
    {
       for(int j = 0; j < 5; j++)
       {
		   cout << x1[i][j] << " / ";
       }
       cout << endl;
    }

	cout << endl << endl;

	for(int i = 0; i < 10000; i++)
    {
       for(int j = 0; j < 5; j++)
       {
		   cout << y1[i][j] << " / ";
       }
       cout << endl;
    }
	*/
}

int main(int argc, char** argv)
{
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simulated:");

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 680);

	glutDisplayFunc(displayMe);
    glutMainLoop();
	
	
    return 0;
}












void x1Thread(int N, vector<vector<double> > &x1, double buf1[])
{
    for(int i = 0; i < N; i++)
    {
       x1[i][0] = 160;  // 2(1)
       x1[i][1] = 0; x1[i][2] = 0; x1[i][3] = 0;
       x1[i][4] = 147;
    }

    for(int i = 0; i < 5; i++)  // 3(1)
    {
       x1[0][i] = buf1[i];
    }
    cout << "1" << endl;
}

void y1Thread(int N, vector<vector<double> > &y1, double buf2[])
{
    for(int i = 0; i < N; i++)
    {
       y1[i][0] = 120;  // 2(2)
       y1[i][1] = 0; y1[i][2] = 0; y1[i][3] = 0;
       y1[i][4] = 132;
    }

	for(int i = 0; i < 5; i++) // 3(2)
    {
       y1[0][i] = buf2[i];
    }
    cout << "2" << endl;
}
