//Monica Liu, mfl4an
//Bethany Connor, bac5rc
//CS 4810 HW 4
//project.cpp

#include <stdio.h>
#include <GL/gl.h>	   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <math.h>
#include <iostream>
#include <string>
using namespace std;

typedef struct {
  int width;
  int height;
  string title;

  float field_of_view_angle;
  float z_near;
  float z_far;
} glutWindow;

glutWindow win;
double angle;
double damping = .1;
float source[150][150];
float dest[150][150];
int minHeight = 10;
int t = 0;
void drawGrid();
int height = 150; //change!
int width = 150; //change!
int dropHeight = 2;
int dropX = 50;
int dropY = 1;
float translate = 0.0;
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  glTranslatef(0.0f, 0.0f, -5.0f);
  glRotatef(180, 0.0f, 1.0f, 0.0f);
  glScalef(0.5f, 0.5f, 0.5f);
  glTranslatef(-1.0f, 0.0f, 0.0f);
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -1 * translate);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, 1.0);
  drawGrid();
  glBegin(GL_QUADS);

  //floor
  /*
  glColor3f(0.25, 0.25, 0.85);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
*/
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
  //  glTranslatef(-1.0f, 0.0, 0.0);
  /*glRotatef(90, 0.0f, 0.0f, 0.0f);
  angle += 1;
  if(angle > 360)
    {
      angle = 0;
    }*/
  if(translate < 8.0)
    {
      translate += 0.1;
    }

  t+= 1;
  drawGrid();

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

  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width; y++) {
      source[x][y] = minHeight;
      dest[x][y] = minHeight;
    }

  }
  source[dropX][dropY] = dropHeight+minHeight;
  dest[dropX][dropY] = (dropHeight+minHeight)*damping;

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
  glutInit(&argc, argv);                                      // GLUT initialization
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
  glutInitWindowSize(win.width,win.height);					// set window size
  glutInitWindowPosition(150, 150);
  glutCreateWindow(win.title.c_str());
  initialize();

  glutDisplayFunc(display);									// register Display Function
  //glutIdleFunc( makeMaze );									// register Idle Function
//  initialize();
  //drawGrid();
  glutTimerFunc(10, update, 0);
  glutTimerFunc(2000, updateR, 0);
  translate = 0.0;
  angle = 0;
  glutMainLoop();												// run GLUT mainloop
  return 0;
}

void updateHeights(float source[150][150], float dest[150][150], bool updated[150][150]) {
  if (t % 23 == 0) {
/*    unsigned int rand_num = rand() % 100;
    unsigned int x = rand()%(height);
    unsigned int y = rand()%(width);
    cout << "switching it up at " << x << " " << y << endl;
    source[x][y] = rand_num;*/
    source[dropX][dropY] = source[dropX][dropY] + dropHeight;
    cout << "drop!" << endl;
  }
  {
    for (int i = 1; i < height-1; i++) {
      for (int j = 1; j < width-1; j++) {
	int temp = dest[i][j];
	dest[i][j] = (source[i-1][j] + source[i+1][j] +
		      source[i][j-1] + source[i][j+1]) / 2 - dest[i][j];
	dest[i][j] = (int)(dest[i][j] * damping);
	if (temp != dest[i][j]) 
		updated[i][j] = true;
	else
		updated[i][j] = false;
      }
    }
  }
}

void drawGrid() {
 // int temp[100][100];
  /*for (int i = 0; i < height; i++)
    for (int j= 0; j < width; j++)
    temp[i][j] = dest[i][j];*/
  bool updated[150][150];
  updateHeights(dest, source,updated);

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,0,1);
  for (int x = 0; x < height; x++) {
    for (int y = 0; y < width-1; y++) {
      if (!updated[x][y] && !updated[x][y+1]) continue;
      float x1 = (float)x*2/50;
      x1 --;
//      x1 *= 3;
      float y1 = (float)y*2/50;
      y1--;
     // y1 *= 3;
      float y2 = (y1+1);
      y2 = y2*2/50;
      y2--;
     // y2 *= 3;
      float x2 = (x1+1);
      x2 = x2*2/50;
      x2--;
    //  x2 *= 3;

      double z1 = dest[x][y];
      z1 = z1*2/150;
      z1--;
      //z1 *= 3;
      double z2 = dest[x][y+1];
      z2 = z2*2/150;
      z2--;
      //cout << z1 << " ";
      //z2 *= 3;
      t+=1;
      glBegin(GL_QUADS);
	//faces: x1, x2, y1, y2, z1, z2
      double normX = z1*y2-y1*z2;
      double normY = y1*x2-x1*y2;
      double normZ = x1*z2-z1*x2;
      glNormal3f(normX,normY,normZ);
      //face 1 -- x1
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x1,z1,y1);
      glVertex3f(x1,z2,y2);
      glVertex3f(x1,-1.0f,y2);
      //face 2 -- x2
      glVertex3f(x2,z1,y1);
      glVertex3f(x2,-1.0f,y1);
      glVertex3f(x2,-1.0f,y2);
      glVertex3f(x2,z2,y2);
      //face 3 -- y1
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x1,z1,y1);
      glVertex3f(x2,z1,y1);
      glVertex3f(x2,-1.0f,y1);
      //face 4 -- y2
      glVertex3f(x1,z2,y2);
      glVertex3f(x1,-1.0f,y2);
      glVertex3f(x2,-1.0f,y2);
      glVertex3f(x2,z2,y2);
      //FACE 5 -- z1
      glVertex3f(x1,z1,y1);
      glVertex3f(x2,z1,y1);
      glVertex3f(x1,z1,y2);
      glVertex3f(x2,z1,y2);
      //FACE 6 -- z2
      glVertex3f(x1,z2,y1);
      glVertex3f(x2,z2,y1);
      glVertex3f(x1,z2,y2);
      glVertex3f(x2,z2,y2);

//      glVertex3f(x1,z2,y2);
//      glVertex3f(x1,0.0f,y2);
//      glVertex3f(x1,0.0f,y1);
      //	glVertex3f(x1,y2,0);
      glEnd();
    }
  }


  //light();

  glFlush();

  for (int i = 0; i < height; i++) {
    for (int j= 0; j < width; j++) {
      float temp2 = dest[i][j];
      dest[i][j] = source[i][j];
      source[i][j] = temp2;
    }
  }
}

