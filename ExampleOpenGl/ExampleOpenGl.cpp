// ExampleOpenGl.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>

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
	GLfloat cntrlpoints[100][5];
	double  Gamma = 10016.6311911 * 0.0000005 / 0.25;;
    double z[5] = {0, 0.25, 0.5, 0.75, 0}, schema[100][5], buf[5] = {0, 151.99, 156, 147.99, 0};
    memset(schema, 0, sizeof(schema));

    for(int i = 0; i < 5; i++)
    {
       schema[0][i] = buf[i];
    }

    // DEFINED FOR ALL SCHEMA

    for(int i = 1; i < 100; i++)   // n: t
    {
       for(int j = 1; j < 4; j++)  // i: z
       {
           //schema[i][j] = ( (1 - (2*Gamma) ) * schema[i-1][j] ) + ( Gamma *(schema[i-1][j+1] + schema[i-1][j-1])) - ((i*0.02));
		   schema[i][j] = (-Gamma) * ( schema[i-1][j+1] + schema[i-1][j-1] ) + schema[i-1][j] - (i*0.02);
       }
    }

    for(int i = 0; i < 100; i++)
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
        glVertex2f(50, 50);  // one point of coordinates axis x
        glVertex2f(900, 50);

		glVertex2f(900, 50);  // one part point of axis x
        glVertex2f(890, 55);
		glVertex2f(900, 50);  // two part point of axis x
        glVertex2f(890, 45);

        glVertex2f(50, 50);  // one point of coordinates axis y
	    glVertex2f(50, 480);
    
		glVertex2f(50, 480);  // one part point of axis y
        glVertex2f(45, 470);
		glVertex2f(50, 480);  // two part point of axis y
        glVertex2f(55, 470);		

	//  Drawing lines on axis y:     ( x = 2.56;  156 * x = 400 )
	    glVertex2f(45, 400);  // 151.99
        glVertex2f(55, 400);
		//output(35,400, "151.99");

		glVertex2f(45, 390);  // 156
        glVertex2f(55, 390);
		//output(35,410, "156");

	    glVertex2f(45, 379);  // 147.99
        glVertex2f(55, 379);
		//output(35,420, "147.99");

		for(short i = 60; i < 890; i += 10)
		{
		    glVertex2f(i, 45);  // other lines on axis x
            glVertex2f(i, 55);
		}

	//  Drawing function to lines:
		for(short i = 0; i < 5; ++i)
		{
			float xbuf = 50;
			for(short m = 0; m < 99; ++m)
			{
			   float buf = 2.56 * cntrlpoints[m][i];
	           glVertex2f(xbuf, buf); 

			   xbuf += 10;  // step

			   buf = 2.56 * cntrlpoints[m+1][i];
               glVertex2f(xbuf, buf);
			}
		}
		

	glEnd();
    glFlush();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(900, 780);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world :D");

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 900, 0, 780);

	glutDisplayFunc(displayMe);
    glutMainLoop();

    return 0;
}

