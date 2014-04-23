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
double damping = .95;
float source[150][150];
float dest[150][150];
int minHeight = 10;
int t = 0;
void drawGrid();
int height = 150; //change!
int width = 150; //change!
int dropHeight = 10;
int dropX = 75;
int dropY = 75;

int angle1 = 0;
int angle2 = 0;
int angle3 = 0;
int angle4 = 0;
int angle5 = 0;
int angle6 = 0;
int angle7 = 0;
int angle8 = 0;
float translate1 = 0.0;
float translate2 = 0.0;
float translate3 = 0.0;
float translate4 = 0.0;
float translate5 = 0.0;
float translate6 = 0.0;
float translate7 = 0.0;
float translate8 = 0.0;
float translate9 = 0.0;
float rotateComp1 = 0.0;
float rotateComp2 = 0.0;
float rotateComp3 = 0.0;
float rotateComp4 = 0.0;
float rotateComp5 = 0.0;
float rotateComp6 = 0.0;
float rotateComp7 = 0.0;
float rotateComp8 = 0.0;


void displayMaze()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(1.0f, 0.0f, -15.0f);
  glRotatef(75, 1.0f, 0.0f, 0.0f);
  glRotatef(180, 0.0f, 1.0f, 0.0f);
  glScalef(0.5f, 0.5f, 0.5f);
  glPushMatrix();

  drawGrid();
  glBegin(GL_QUADS);
/*
  //floor
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
*/
  //wall 1
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(3.0f, 1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, -2.0f);
  glVertex3f(3.0f, 1.0f, -2.0f);

  //wall 2
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-5.0f, -1.0f, -2.0f);
  glVertex3f(1.0f, -1.0f, -2.0f);
  glVertex3f(1.0f, 1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, -2.0f);

  //wall 3
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-5.0f, -1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, 6.0f);
  glVertex3f(-5.0f, -1.0f, 6.0f);

  //wall 4
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(3.0f, 1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, 6.0f);
  glVertex3f(-3.0f, -1.0f, 6.0f);
  glVertex3f(-3.0f, 1.0f, 6.0f);

  //wall 5
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-3.0f, 1.0f, 6.0f);
  glVertex3f(-3.0f, 1.0f, 0.0f);
  glVertex3f(-3.0f, -1.0f, 0.0f);
  glVertex3f(-3.0f, -1.0f, 6.0f);

  //wall 6
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(-1.0f, 1.0f, -2.0f);
  glVertex3f(-1.0f, -1.0f, -2.0f);
  glVertex3f(-1.0f, -1.0f, 2.0f);
  glVertex3f(-1.0f, 1.0f, 2.0f);

  //wall 7
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glVertex3f(3.0f, -1.0f, 0.0f);
  glVertex3f(3.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  
  //wall 8
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(1.0f, 1.0f, 2.0f);
  glVertex3f(-1.0f, 1.0f, 2.0f);
  glVertex3f(-1.0f, -1.0f, 2.0f);
  glVertex3f(1.0f, -1.0f, 2.0f);

  //wall 9
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-1.0f, -1.0f, 4.0f);
  glVertex3f(-1.0f, 1.0f, 4.0f);
  glVertex3f(1.0f, 1.0f, 4.0f);
  glVertex3f(1.0f, -1.0f, 4.0f);

  //wall 10
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(1.0f, 1.0f, 6.0f);
  glVertex3f(1.0f, -1.0, 6.0f);
  glVertex3f(1.0f, -1.0f, 4.0f);
  glVertex3f(1.0f, 1.0f, 4.0f);
  
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glutSwapBuffers();
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(1.0f, 0.0f, -5.0f);
  glRotatef(180, 0.0f, 1.0f, 0.0f);
  glScalef(0.5f, 0.5f, 0.5f);
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -1 * translate1);
  glRotatef(angle1, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, rotateComp1);
  glTranslatef(translate2, 0.0f, 0.0f);
  glRotatef(-1 * angle2, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1 * rotateComp2, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -1 * translate3);
  glRotatef(-1 * angle3, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -1 * rotateComp3);
  glTranslatef(-1 * translate4, 0.0f, 0.0f);
  glRotatef(angle4, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1 * rotateComp4, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -1 * translate5);
  glRotatef(angle5, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1 * rotateComp5, 0.0f, -1 * rotateComp5/3);
  glTranslatef(translate6, 0.0f, 0.0f);
  glRotatef(angle6, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1 * rotateComp6, 0.0f, -2 * rotateComp6);
  glTranslatef(0.0f, 0.0f, translate7);
  glRotatef(-1 * angle7, 0.0f, 1.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, rotateComp7);
  glTranslatef(translate8, 0.0f, translate8/2);
  glRotatef(-1 * angle8, 0.0f, 1.0f, 0.0f);
  glTranslatef(rotateComp8, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -1 * translate9);
  drawGrid();
  glBegin(GL_QUADS);
/*
  //floor
  glColor3f(0.0, 0.0, 0.0);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, -1.0f);
  glVertex3f(3.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
*/

  //wall 1
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(3.0f, 1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, -2.0f);
  glVertex3f(3.0f, 1.0f, -2.0f);

  //wall 2
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-5.0f, -1.0f, -2.0f);
  glVertex3f(1.0f, -1.0f, -2.0f);
  glVertex3f(1.0f, 1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, -2.0f);

  //wall 3
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-5.0f, -1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, -2.0f);
  glVertex3f(-5.0f, 1.0f, 6.0f);
  glVertex3f(-5.0f, -1.0f, 6.0f);

  //wall 4
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(3.0f, 1.0f, 6.0f);
  glVertex3f(3.0f, -1.0f, 6.0f);
  glVertex3f(-3.0f, -1.0f, 6.0f);
  glVertex3f(-3.0f, 1.0f, 6.0f);

  //wall 5
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-3.0f, 1.0f, 6.0f);
  glVertex3f(-3.0f, 1.0f, 0.0f);
  glVertex3f(-3.0f, -1.0f, 0.0f);
  glVertex3f(-3.0f, -1.0f, 6.0f);

  //wall 6
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(-1.0f, 1.0f, -2.0f);
  glVertex3f(-1.0f, -1.0f, -2.0f);
  glVertex3f(-1.0f, -1.0f, 2.0f);
  glVertex3f(-1.0f, 1.0f, 2.0f);

  //wall 7
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glVertex3f(3.0f, -1.0f, 0.0f);
  glVertex3f(3.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  
  //wall 8
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f(1.0f, 1.0f, 2.0f);
  glVertex3f(-1.0f, 1.0f, 2.0f);
  glVertex3f(-1.0f, -1.0f, 2.0f);
  glVertex3f(1.0f, -1.0f, 2.0f);

  //wall 9
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(-1.0f, -1.0f, 4.0f);
  glVertex3f(-1.0f, 1.0f, 4.0f);
  glVertex3f(1.0f, 1.0f, 4.0f);
  glVertex3f(1.0f, -1.0f, 4.0f);

  //wall 10
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(1.0f, 1.0f, 6.0f);
  glVertex3f(1.0f, -1.0, 6.0f);
  glVertex3f(1.0f, -1.0f, 4.0f);
  glVertex3f(1.0f, 1.0f, 4.0f);
  
  glEnd();

  glPopMatrix();
  glPushMatrix();
  glutSwapBuffers();
}

void t1(int value)
{ 
  if(translate1 <= 6.0)
    {
      translate1 += 0.1;
    }

  glutPostRedisplay();
  glutTimerFunc(5, t1, 0);
}

void r1(int value)
{
  if (angle1 <= 90)
    {
      angle1 += 1;
    }
  if (rotateComp1 <= 3.0)
    {
      rotateComp1 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r1, 0);
}

void t2(int value)
{
  if(translate2 <= 1.0)
    {
      translate2 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t2, 0);
}

void r2(int value)
{
  if(angle2 <= 90)
    {
      angle2 += 1;
    }
  if (rotateComp2 <= 1.5)
    {
      rotateComp2 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r2, 0);
}

void t3(int value)
{
  if (translate3 <= 1.0)
    {
      translate3 += 0.1; 
    }
  glutPostRedisplay();
  glutTimerFunc(5, t3, 0);
}

void r3(int value)
{
  if (angle3 <= 90)
    {
      angle3 += 1;
    }
  if (rotateComp3 <= 1.0)
    {
      rotateComp3 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r3, 0);
}

void t4(int value)
{
  if (translate4 <= 1.5)
    {
      translate4 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t4, 0);
}
void r4(int value)
{
  if (angle4 <= 90)
    {
      angle4 += 1;
    }
  if (rotateComp4 <= 2.0 && angle4 >= 45)
    {
      rotateComp4 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r4, 0);
}

void t5(int value)
{
  if (translate5 <= 2.0)
    {
      translate5 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t5, 0);
}

void r5(int value)
{
  if (angle5 <= 90)
    {
      angle5 += 1;
    }
  if (rotateComp5 <= 5.5 && angle5 >= 5)
    {
      rotateComp5 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r5, 0);
}

void t6(int value)
{
  if (translate6 <= 3.0)
    {
      translate6 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t6, 0);
}

void r6(int value)
{
  if (angle6 <= 90)
    {
      angle6 += 1;
    }
  if (rotateComp6 <= 1.0)
    {
      rotateComp6 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r6, 0);
}

void t7(int value)
{
  if (translate7 <= 2.0)
    {
      translate7 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t7, 0);
}

void r7(int value)
{
  if (angle7 <= 90)
    {
      angle7 += 1;
    }
  if (rotateComp7 <= 2.0 && angle7 >= 60)
    {
      rotateComp7 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r7, 0);
}

void t8(int value)
{
  if (translate8 <= 2.0)
    {
      translate8 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t8, 0);
}

void r8(int value)
{
  if (angle8 <= 90)
    {
      angle8 += 1;
    }
  if (rotateComp8 <= 3.0 && angle8 >= 45)
    {
      rotateComp8 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, r8, 0);
}

void t9(int value)
{
  if (translate9 <= 8.0)
    {
      translate9 += 0.1;
    }
  glutPostRedisplay();
  glutTimerFunc(5, t9, 0);
}

void update(int value)
{
   t+= 1;
  drawGrid();

  glutPostRedisplay();
  glutTimerFunc(2, update, 0);
  
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
//  source[dropX][dropY] = minHeight+dropHeight;

  //source[dropX][dropY] = (minHeight+dropHeight)*damping;

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
  glutCreateWindow("Overall Maze");
  glutDisplayFunc(displayMaze);
  initialize();

  glutCreateWindow(win.title.c_str());
  glutDisplayFunc(display);									// register Display Function
  initialize();

  //glutIdleFunc( makeMaze );									// register Idle Function
//  initialize();
  //drawGrid();
  glutTimerFunc(2, update, 0);
  glutTimerFunc(5, t1, 0);
  glutTimerFunc(1000, r1, 0);
  glutTimerFunc(2500, t2, 0);
  glutTimerFunc(4000, r2, 0);
  glutTimerFunc(5500, t3, 0);
  glutTimerFunc(6000, r3, 0);
  glutTimerFunc(6500, t4, 0);
  glutTimerFunc(8000, r4, 0);
  glutTimerFunc(9500, t5, 0);
  glutTimerFunc(11500, r5, 0);
  glutTimerFunc(13500, t6, 0);
  glutTimerFunc(15000, r6, 0);
  glutTimerFunc(17000, t7, 0);
  glutTimerFunc(18000, r7, 0);
  glutTimerFunc(20000, t8, 0);
  glutTimerFunc(21000, r8, 0);
  glutTimerFunc(23000, t9, 0);

  glutMainLoop();												// run GLUT mainloop
  return 0;
}

void updateHeights(float source[150][150], float dest[150][150], bool updated[150][150]) {
  float delta = .00001; //some small number to account for floating point

  if (true) {
    int dropX_rand = rand() % 150;
    int dropY_rand = rand() % 150;
    source[dropX_rand][dropY_rand] = source[dropX][dropY] + dropHeight;
//    cout << "drop!" << endl;
  }
  {
    for (int i = 1; i < height-1; i++) {
      for (int j = 1; j < width-1; j++) {
	float temp = dest[i][j];
	dest[i][j] = (source[i-1][j] + source[i+1][j] +
		      source[i][j-1] + source[i][j+1]) / 2 - dest[i][j];
//	dest[i][j] = (dest[i][j] * damping);
	//if (temp - dest[i][j] < delta)  
	if (temp != dest[i][j])
//		cout << temp-dest[i][j] << endl;
		dest[i][j] = (dest[i][j] * damping);
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
  glColor3f(.13,0.3,.52);
  for (int x = 0; x < height-1; x++) {
    for (int y = 0; y < width-1; y++) {
      //if (!updated[x][y] && !updated[x][y+1]) continue;
      float x1 = (float)x*2/(150);
      x1 --;
      x1 *= 5;
      float y1 = (float)y*2/(150);
      y1--;
      y1 *= 6;
      float y2 = (y+1);
      y2 = y2*2.0/(150);
      y2--;
      y2 *= 6;
      float x2 = (x+1);
      x2 = x2*2.0/(150);
      x2--;
      x2 *=5;

      float z11 = dest[x][y];
      z11 = z11/(minHeight*4);
      z11--;
      float z12 = dest[x+1][y];
      z12 = z12/(minHeight*4);
      z12--;

      //z1 *= 3;
      float z21 = dest[x][y+1];
      z21 = z21/(minHeight*4);
      z21--;
      float z22 = dest[x+1][y+1];
      z22 = z22/(minHeight*4);
      z22--;

      if (z11 < -1)
	z11 = -1;
      if (z12 < -1)
	z12 = -1;
      if (z21 < -1)
	z21 = -1;
      if (z22 < -1)
	z22 = -1;

      //cout << z1 << " ";
      //z2 *= 3;
/*	cout << z11 << " ";
	cout << z12 << " ";
	cout << z21 << " ";
	cout << z22 << endl;*/
      glBegin(GL_QUADS);
	//faces: x1, x2, y1, y2, z1, z2
      //double normX = z1*y2-y1*z2;
      //double normY = y1*x2-x1*y2;
      //double normZ = x1*z2-z1*x2;
      //glNormal3f(normX,normY,normZ);
	
      //face 1 -- x1
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x1,z11,y1);
      glVertex3f(x1,z11,y2);
      glVertex3f(x1,-1.0f,y2);
      //face 2 -- x2
      glVertex3f(x2,-1.0f,y1);
      glVertex3f(x2,z11,y1);
      glVertex3f(x2,z11,y2);
      glVertex3f(x2,-1.0f,y2);
      //face 3 -- y1
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x1,z11,y1);
      glVertex3f(x2,z11,y1);
      glVertex3f(x2,-1.0f,y1);
      //face 4 -- y2
      glVertex3f(x1,z11,y2);
      glVertex3f(x1,-1.0f,y2);
      glVertex3f(x2,-1.0f,y2);
      glVertex3f(x2,z11,y2);
      //FACE 5 -- top
      glVertex3f(x1,z11,y1);
      glVertex3f(x2,z11,y1);
      glVertex3f(x2,z11,y2);
      glVertex3f(x1,z11,y2);
      //FACE 6 -- bottom
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x2,-1.0f,y1);
      glVertex3f(x2,-1.0f,y2);
      glVertex3f(x1,-1.0f,y2);
/*
      glVertex3f(x1,-1.0f,y1);
      glVertex3f(x1,z11,y1);
      glVertex3f(x1,z12,y2);
      glVertex3f(x1,-1.0f,y2);
      glVertex3f(x2,-1.0f,y2);
      glVertex3f(x2,z22,y2);
      glVertex3f(x2,z21,y1);
      glVertex3f(x2,-1.0f,y1);
*/
//      glVertex3f(x1,z2,y2);
//      glVertex3f(x1,0.0f,y2);
//      glVertex3f(x1,0.0f,y1);
      //	glVertex3f(x1,y2,0);
      glEnd();
    }
  }



  glFlush();

  for (int i = 0; i < height; i++) {
    for (int j= 0; j < width; j++) {
      float temp2 = dest[i][j];
      dest[i][j] = source[i][j];
      source[i][j] = temp2;
    }
  }
}

