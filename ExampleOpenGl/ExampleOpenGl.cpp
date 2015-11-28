#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include "Setka.h"

using namespace std;


void output(GLfloat x, GLfloat y, char* text)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
	GLfloat ficks = -0.5f;
	glScalef(ficks, ficks, 1.0f);
	for( char* p = text; *p; p++)
    {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
    }
    glPopMatrix();
}


void displayMe()
{
	GLfloat cntrlpoints[1000][5];
	double  t = 0.00000000895985, Gamma = 7812623.224021 * t / 140; // 10016.6311911
    double  schema[1000][5], buf[5] = {0, 156, 151.99, 147.99, 0};
    memset(schema, 0, sizeof(schema));

    for(int i = 0; i < 5; i++)
    {
       schema[0][i] = buf[i];
    }

    // DEFINED FOR ALL SCHEMA

    for(int i = 1; i < 1000; i++)   // n: t
    {
       for(int j = 1; j < 4; j++)  // i: z
       {
           //schema[i][j] = ( (1 - (2*Gamma) ) * schema[i-1][j] ) + ( Gamma *(schema[i-1][j+1] + schema[i-1][j-1])) - ((i*0.02));
		   //schema[i][j] = (-Gamma) * ( schema[i-1][j+1] + schema[i-1][j-1] ) + schema[i-1][j] - (i*0.02);
		   //schema[i][j] = schema[i-1][j] * ( (-Gamma) - (t * 0.001) + 1) + (Gamma * schema[i-1][j-1]) + (t * 0.001 * 120);
		   schema[i][j] = schema[i-1][j] * ( (Gamma) - (t * 0.001) + 1) - (Gamma * schema[i-1][j-1]) + (t * 0.001 * 120);
       }
    }

	
    for(int i = 0; i < 1000; i++)
    {
       for(int j = 0; j < 5; j++)
       {
		   cntrlpoints[i][j] = schema[i][j];
       }
       cout << endl;
    }

	//------------------------------------------------------------------------------------------------

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

	 // Drawing axis coordinates:
        glVertex2f(25, 5);  // one point of coordinates axis x
        glVertex2f(1000, 5);

		glVertex2f(1000, 5);  // one part point of axis x
        glVertex2f(990, 10);
		glVertex2f(1000, 5);  // two part point of axis x
        glVertex2f(990, 0);

        glVertex2f(25, 5);  // one point of coordinates axis y
	    glVertex2f(25, 680);
    
		glVertex2f(25, 680);  // one part point of axis y
        glVertex2f(20, 670);
		glVertex2f(25, 680);  // two part point of axis y
        glVertex2f(30, 670);		

	//  Drawing lines on axis y:     ( x = 3.846153 ;  156 * x = 600 ) 
	    glVertex2f(27, 600);  // 156
        glVertex2f(23, 600);

		glVertex2f(27, 584.576923);  // 151.99
        glVertex2f(23, 584.576923);

	    glVertex2f(27, 569.192182);  // 147.99
        glVertex2f(23, 569.192182);

		for(short i = 25; i < 990; i += 5)
		{
		    glVertex2f(i, 7.5);  // other lines on axis x
            glVertex2f(i, 2.5);
		}


	//  Drawing function to lines:
		for(short i = 0; i < 5; ++i)
		{
			float xbuf = 25;
			for(short m = 0; m < 999; ++m)
			{
				float buf = 0;
				/*
				if(cntrlpoints[m][i] < 20)
				{
					buf = 3.846153 * cntrlpoints[m][i];
				glVertex2f(xbuf, buf);	
				xbuf += 10;  // step
				buf = 3.846153 * cntrlpoints[m+1][i];
                glVertex2f(xbuf, buf);
					continue;
				}
				*/
				buf = 3.846153 * cntrlpoints[m][i];
				glVertex2f(xbuf, buf);	

				xbuf += 1 + (m/10);  // step

				buf = 3.846153 * cntrlpoints[m+1][i];
                glVertex2f(xbuf, buf);
			}


	    }
		

	glEnd();
    glFlush();


	/*
    for(int i = 0; i < 1000; i++)
    {
       for(int j = 0; j < 5; j++)
       {
		   cout << schema[i][j] << " / ";
       }
       cout << endl;
    }
	*/

}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1000, 680);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 680);

	glutDisplayFunc(displayMe);
    glutMainLoop();

    return 0;
}