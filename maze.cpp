//Monica Liu, mfl4an
//CS 4810 HW 4
//OpenGLTest.cpp

#include <stdio.h>
#include <GL/gl.h>	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <math.h>

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;
double angle;

void makeMaze()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  glTranslatef(0.0f, 0.0f, -5.0f);
  glPushMatrix();
  glScalef(0.5f, 0.5f, 0.5f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  
  //floor
  glColor3f(0.25, 0.25, 0.85);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  
  //ceiling
  //glColor3f(0.25, 0.85, 0.25);
  //glVertex3f(-1.0f, 1.0f, -1.0f);
  //glVertex3f(1.0f, 1.0f, -1.0f);
  //glVertex3f(1.0f, 1.0f, 1.0f);
  //glVertex3f(-1.0f, 1.0f, 1.0f);

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

  //front wall
  //glColor3f(0.85, 0.85, 0.85);
  //glVertex3f(-1.0f, 1.0f, 1.0f);
  //glVertex3f(-1.0f, -1.0f, 1.0f);
  //glVertex3f(-1.0f, -1.0f, -1.0f);
  //glVertex3f(-1.0f, 1.0f, -1.0f);

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
  //  glTranslatef(-1.0f, 0.0, 0.0);
  //glRotatef(90, 0.0f, 0.0f, 0.0f);
  
  angle += 1;
  if(angle > 360)
    {
      angle = 0;
    }
  glutPostRedisplay();
  glutTimerFunc(5, update, 0);
  
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
	win.title = "OpenGL/GLUT Test";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(makeMaze);									// register Display Function
	//glutIdleFunc( makeMaze );									// register Idle Function
	initialize();
	glutTimerFunc(5, update, 0);
	glutMainLoop();												// run GLUT mainloop
	return 0;
}
