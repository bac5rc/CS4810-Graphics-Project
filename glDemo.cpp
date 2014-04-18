#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#define _USE_MATH_DEFINES

#include <cstdlib>

#include <iostream>
using namespace std;

typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

int t;
int height = 150;
int width = 150;
double damping = .1;
int source[150][150];
int dest[150][150];

void drawLines(int i);
glutWindow win;

void print(int matrix[150][150]) {

for (int i = 0; i < 150; i++) {
	for (int j = 0 ; j < 150; j++) {
	cout << matrix[i][j] << " ";
}
	cout << endl;
}

}

void init() {
// Somewhere in the initialization part of your programâ¦
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);

// Create light components
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.0f, 0.0f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

// Assign created components to GL_LIGHT0
glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
glLightfv(GL_LIGHT0, GL_POSITION, position);
//GLfloat light_direction[] = {0,1,-1};
/*glClearColor(1.0,1.0,1.0,0.0);
//glViewPort(0,0,500,500);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

//glOrtho(10,10,0,10,1,-1);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
*/
glMatrixMode(GL_PROJECTION);		
    glViewport(0, 0, width, height);		
    glMatrixMode(GL_PROJECTION);			
    glLoadIdentity();					
    GLfloat aspect = (GLfloat) width / height;
    gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);	
    glMatrixMode(GL_MODELVIEW);							
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );						
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );		
    glClearColor(0.0, 0.0, 0.0, 1.0);						

glEnable(GL_NORMALIZE);
}

void light() {
GLfloat mat_specular[] = {0,1,0};
GLfloat specularMaterial[] = {1.0,1.0,1.0};
GLfloat mat_shininess[] = {50.0};

glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularMaterial);
glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);

GLfloat blackAmbient[] = {0,0,0};
glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbient);

}

void updateHeights(int source[150][150], int dest[150][150]) {
if (t % 23 == 0) {
cout << "switching it up" << endl;
int rand_num = rand() % 100;
rand_num = rand() % (height*width);
int x = rand()%(height-rand_num);
int y = rand()%(height-rand_num);
for (int i = 0 ; i < rand_num; i++) {
	int x = rand()%height;
	int y = rand()%width;
	int assign = rand() % 1000;
	source[x][y] = assign;
}

rand_num = rand() % (height*width);
for (int i = 0 ; i < rand_num; i++) {
	int x = rand()%height;
	int y = rand()%width;
	int assign = rand() % 1000;
	dest[x][y] = assign;
}
}
else {
  for (int i = 1; i < height-1; i++) {
    for (int j = 1; j < width-1; j++) {
      dest[i][j] = (source[i-1][j] + source[i+1][j] +
	source[i][j-1] + source[i][j+1]) / 2 - dest[i][j];
      dest[i][j] = (int)(dest[i][j] * damping);
    }
  }
}
}

void displayGrid() {
drawLines(0);
}

void drawLines(int i) {
t = t + 1;
cout << t << "!!" << endl;
int temp[150][150];
//temp = new int[150][150];
for (int i = 0; i < height; i++)
  for (int j= 0; j < width; j++)
    temp[i][j] = dest[i][j];
updateHeights(temp, source);

glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0,0,1);

for (int x = 0; x < 150; x++) {
	for (int y = 0; y < 149; y++) {
//	int z1 = rand() % 100;
//	int z2 = rand() % 100;
	float x1 = (float)x*2/150;
	x1 --;
	float y1 = (float)y*2/150;
	y1--;
//	int y1 = y;
	float y2 = (y1+1);
	y2 = y2*2/150;
	y2--;
	float x2 = (x1+1);
	x2 = x2*2/150;
	x2--;

//	double z1 = sin((double)x1*y1 * M_PI / 180);
	double z1 = dest[x][y];
	double z2 = dest[x][y+1];
	t+=1;
//	cout << z1 << " " << z2 << endl;
//	cout << x1 << " " << y1 << endl;
glBegin(GL_QUADS);
//	nomal = [y1*z2-z1*y2, z1*x2-x1*z2, x1*y2-y1*x2]
	double normX = y1*z2-z1*y2;
	double normY = z1*x2-x1*z2;
	double normZ = x1*y2-y1*x2;
	glNormal3f(normX,normY,normZ);
	glVertex3f(x1,0,y1);
//	glNormal3f(1,0,z1);
//	glVertex3f(x1,y1,z1);
//	glNormal3f(0,1,1);
	glVertex3f(x2,z1,y1);

//	glVertex2f(x1,y1);
//	glNormal3f(0,1,1);
//	glVertex3f(x2,y1,0);

//	glNormal3f(0,1,1);
//	glVertex3f(x2,y2,0);

//	glNormal3f(0,1,1);
//	glVertex3f(x2,y2,z2);


//	glNormal3f(1,0,z2);
	glVertex3f(x1,z2,y2);
//	glNormal3f(0,1,1);
	glVertex3f(x1,0,y2);
glEnd();
}
}


light();

glFlush();

int temp2[150][150];
//temp2 = new int[150][150];
for (int i = 0; i < height; i++)
  for (int j= 0; j < width; j++)
    temp2[i][j] = dest[i][j];
//dest = source;
for (int i = 0; i < height; i++)
  for (int j= 0; j < width; j++)
    dest[i][j] = source[i][j];
for (int i = 0; i < height; i++)
  for (int j= 0; j < width; j++)
    source[i][j] = temp2[i][j];
//print(source);
//source = temp2;
}

int main(int argv, char** argc) {
glutInit(&argv,argc);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
t= 0;
//source = new int[150][150];
//dest = new int[150][150];
int rand_num = rand() % 100;
rand_num = rand() % (height*width);
int x = rand()%(height-rand_num);
int y = rand()%(height-rand_num);
for (int i = 0 ; i < rand_num; i++) {
	int x = rand()%height;
	int y = rand()%width;
	int assign = rand() % 1000;
	source[x][y] = assign;
}

rand_num = rand() % (height*width);
for (int i = 0 ; i < rand_num; i++) {
	int x = rand()%height;
	int y = rand()%width;
	int assign = rand() % 1000;
	dest[x][y] = assign;
}
//print(source);
win.width = 150;
	win.height = 150;
	win.title = "OpenGL/GLUT Test";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

glutInitWindowPosition(100,100);
glutInitWindowSize(height,width);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutCreateWindow("hello");
init();
glutDisplayFunc(displayGrid);
glutTimerFunc(5, drawLines,0);
glutMainLoop();
return 0;
}
