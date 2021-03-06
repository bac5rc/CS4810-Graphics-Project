//Monica Liu, mfl4an
//CS 4810 HW 4
//OpenGLTest.cpp

#include <stdio.h>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header

#define KEY_ESCAPE 27

float scale = 0.0;
float rotate = 0.0;

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;


void display() 
{
  scale += 0.01;
  rotate += 5.0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-3.0f);	
  glScalef(scale, scale, scale);
  glRotatef(rotate, rotate, rotate, rotate);
  if(scale > 2.0)
    {
      scale = 0.0;
    }
  /*
   * Triangle code starts here
   * 3 verteces, 3 colors.
   */
  glBegin(GL_TRIANGLES);					
  glColor3f(0.0f,0.0f,1.0f);			
  glVertex3f( 0.0f, 1.0f, 0.0f);		
  glColor3f(0.0f,1.0f,0.0f);			
  glVertex3f(-1.0f,-1.0f, 0.0f);		
  glColor3f(1.0f,0.0f,0.0f);			
  glVertex3f( 1.0f,-1.0f, 0.0f);		
  glEnd();				
  //glFlush();
  //gfPosX += gfDeltaX;
  //if (gfPosX >= 1.0 || gfPosX <= 0.0)
  //  {
  //    gfDeltaX = -gfDeltaX;
  //  }
  glutSwapBuffers();
}


void initialize () 
{
    glMatrixMode(GL_PROJECTION);		// select projection matrix
    glViewport(0, 0, win.width, win.height);		// set the viewport
    glMatrixMode(GL_PROJECTION);			// set matrix mode
    glLoadIdentity();					// reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);	// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);							//specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );						// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		// specify implementation-specific hints
    glClearColor(0.0, 0.0, 0.0, 1.0);				// specify clear values for the color buffers			
}


int main(int argc, char **argv) 
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "OpenGL/GLUT Test";
	win.field_of_view_angle = 90;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc( display );									// register Idle Function
	initialize();
	glutMainLoop();												// run GLUT mainloop
	return 0;
}
