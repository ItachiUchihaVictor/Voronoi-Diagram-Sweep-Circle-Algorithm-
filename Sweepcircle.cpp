// Sweepcircle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#include <GL/glew.h> // Include the GLEW header file
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <math.h>
#include <algorithm>
#include <time.h>
#include<Windows.h>

#include "Voronoic.h"
#include "VPoint.h"
	double qx=0;
	double qy=0;
void display (void);
void onEF (int n);
void reshape (int width, int height);

vorc::Voronoi * v;
vorc::Vertices * ver; // vrcholy
vorc::Vertices * dir; // smìry, kterými se pohybují
vorc::Edges * edg;	 // hrany diagramu

double w = 10000;

int main (int argc, char **argv) 
{
	using namespace vorc;

	v = new Voronoi();
	ver = new Vertices();
	dir = new Vertices();

	srand ( time(NULL) );

	for(int i=0; i<1000; i++) 
	{

		ver->push_back(new VPoint(2* w * (double)rand()/(double)RAND_MAX-w , 2*w * (double)rand()/(double)RAND_MAX-w ,0,0)); 
		dir->push_back(new VPoint( (double)rand()/(double)RAND_MAX - 0.5, (double)rand()/(double)RAND_MAX - 0.5,0,0)); 
	}
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER start,finish;
	double time=0;
	QueryPerformanceFrequency(&m_nFreq);
	QueryPerformanceCounter(&start);
	edg = v->GetEdges(ver, 2*w, 2*w);
	QueryPerformanceCounter(&finish);
	printf( "Time: %f\n", (double)((finish.QuadPart-start.QuadPart)*1000000.0/m_nFreq.QuadPart));
	std::cout << "voronois done!\n";
	getchar();

	for(vorc::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
			if( (*i)->start == 0 )
			{
				std::cout << "chybi zacatek hrany!\n";
				continue;
			}
			if( (*i)->end == 0 )
			{
				std::cout << "chybi konec hrany!\n";
				continue;
			}	
	}
	
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode (GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize (600, 600); // Set the width and height of the window
	glutInitWindowPosition (100, 100); // Set the position of the window
	glutCreateWindow ("You’re first OpenGL Window"); // Set the title for the window
	
//	glutTimerFunc(100, onEF, 0);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping

	//glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	//glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

	glutMainLoop(); // Enter GLUT's main loop
	
	return 0;
}

void drawVoronoi()
{
	std::cout << "drarVD\n";
	glColor3f(1.0f, 0.0f, 0.0f);
/*	vorc::Vertices::iterator j = dir->begin();
	for(vorc::Vertices::iterator i = ver->begin(); i != ver->end(); ++i)
	{
		(*i)->x += (*j)->x * w/50;
		(*i)->y += (*j)->y * w/50;
		if( (*i)->x > w ) (*j)->x *= -1;
		if( (*i)->x < 0 ) (*j)->x *= -1;

		if( (*i)->y > w ) (*j)->y *= -1;
		if( (*i)->y < 0 ) (*j)->y *= -1;
		++j;
	}
	
	*/
//	edg = v->GetEdges(ver, w, w);
	std::cout << "voronoi done";
	glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f( -0.01,  - 0.01);
		glVertex2f(  0.01,  - 0.01);
		glVertex2f( 0.01,  0.01);
		glVertex2f( -0.01,   0.01);
		glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	for(vorc::Vertices::iterator i = ver->begin(); i!= ver->end(); ++i)
	{
		glBegin(GL_QUADS);
		//std::cout << (*i)->x << "\n";
		glVertex2f( (*i)->x/w -0.01,  (*i)->y/w - 0.01);
		glVertex2f( (*i)->x/w +0.01,  (*i)->y/w - 0.01);
		glVertex2f( (*i)->x/w +0.01,  (*i)->y/w + 0.01);
		glVertex2f( (*i)->x/w -0.01,  (*i)->y/w + 0.01);
		glEnd();
	}

	glFlush();
	for(vorc::Edges::iterator i = edg->begin(); i!= edg->end(); ++i)
	{
		/*
		glBegin(GL_LINES);
		glVertex2f( -1+2*(*i)->left->x/w,  -1+2*(*i)->left->y/w);
		glVertex2f( -1+2*(*i)->right->x/w, -1+2*(*i)->right->y/w);
		glEnd();
		*/
	//	printf("%f %f %f %f\n",(*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y);
		glBegin(GL_LINES);
		glVertex2f( (*i)->start->x/w,  (*i)->start->y/w);
		glVertex2f( (*i)->end->x/w, (*i)->end->y/w);
		glEnd();
		glFlush();
	}
}

void display (void) 
{
	//std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	glTranslatef(0.0f, 0.0f, -5.0f); 
	drawVoronoi();
	glFlush();
}


void onEF(int n)
{
	//std::cout << "onEF\n";
	glutTimerFunc(20, onEF, 0);
	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Clear the background of our window to red  
	
	drawVoronoi();
	glutSwapBuffers();
	//Draw everything to the screen
}

void reshape (int width, int height) 
{
	
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}
