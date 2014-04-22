//Monica Liu, mfl4an
//CS 4810 HW 4
//maze.cpp

#include <stdio.h>
#include <iostream>
#include <GL/gl.h>	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;
int angle = 0;
float translate = 0.0;
//Glfloat transformMatrix[16];

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glRotatef(180, 0.0f, 1.0f, 0.0f);
  glScalef(0.5f, 0.5f, 0.5f);
  glTranslatef(-1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -1 * translate);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 1.0);
  glBegin(GL_QUADS);

  //floor
  glColor3f(0.25, 0.25, 0.85);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);

  //left wall
  glColor3f(0.85, 0.25, 0.25);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(3.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  
  //right wall
  glColor3f(0.85, 0.25, 0.85);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);

  //back wall
  glColor3f(0.25, 0.85, 0.85);
  glVertex3f(3.0f, 1.0f, 2.0f);
  glVertex3f(3.0f, -1.0f, 2.0f);
  glVertex3f(3.0f, -1.0f, -2.0f);
  glVertex3f(3.0f, 1.0f, -2.0f);

  glEnd();
  glPopMatrix();
  glPushMatrix();
  glutSwapBuffers();
}

void update(int value)
{ 
  if(translate < 8.0)
    {
      translate += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, update, 0);
}

void updateR(int value)
{
  if (angle < 90)
    {
      angle += 1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, updateR, 0);
}


void initialize () 
{
    glMatrixMode(GL_PROJECTION);		
    glViewport(0, 0, win.width, win.height);		
    glMatrixMode(GL_PROJECTION);			
    glLoadIdentity();					
    GLfloat aspect = (GLfloat) win.width / win.height;
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);	
    glMatrixMode(GL_MODELVIEW);							
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );						
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		
    glClearColor(0.0, 0.0, 0.0, 1.0);						
    }

int main(int argc, char **argv) 
{

  // set window values
  win.width = 640;
  win.height = 480;
  win.title = "CS 4810 Project: Maze Walkthrough";
  win.field_of_view_angle = 45;
  win.z_near = 1.0f;
  win.z_far = 500.0f;
  
  // initialize and run program
  glutInit(&argc, argv);                                      
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  
  glutInitWindowSize(win.width, win.height);		
  glutInitWindowPosition(150, 150);
  glutCreateWindow(win.title);
  initialize();
  glutDisplayFunc(display);
  glutTimerFunc(5, update, 0);
  glutTimerFunc(2000, updateR, 0);
  translate = 0.0;
  angle = 0;
  glutMainLoop();											       
  return 0;
}
