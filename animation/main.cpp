#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <cmath>
#include <algorithm>
using std::min;
using std::swap;

#include <GL/glew.h>
#include <GL/glut.h>

#define SLICES 128
#define ANIMATION_DURATION 150 /* frames*/
#define PI 3.14159265358979323846264
#define length(A) (sizeof(A)/sizeof((A)[0]))

GLUquadricObj *arc = gluNewQuadric();
unsigned int current_frame = 0;
float endpoints[2] = {0,180};
float degrees;	// in degrees
bool to_circle = false;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(current_frame >= ANIMATION_DURATION)
	{
		current_frame = 0;
		to_circle = !to_circle;
	} // end if

	float t = (float)current_frame/ANIMATION_DURATION;
	if(to_circle)
		t = 1-t;
	//t = 0.5*cos(PI*current_frame/ANIMATION_DURATION+PI)+0.5;
	current_frame++;

	degrees = t*endpoints[1] + (1-t)*endpoints[0];
	float radians = degrees*PI/180;

	// draw shape
	float x1 = cos(radians);
	float y1 = sin(radians);
	float x2 = x1+radians*y1;
	float y2 = y1-radians*x1;
	glBegin(GL_LINES);
		glVertex2f(y1,x1);
		glVertex2f(y2,x2);
		glVertex2f(-y1,x1);
		glVertex2f(-y2,x2);
	glEnd();
	gluPartialDisk(arc,1,1,SLICES,1,degrees,2*(180-degrees));

	// check for errors
	GLenum error;
	if((error = glGetError()) != GL_NO_ERROR)
		cerr << gluErrorString(error) << endl;
	glutPostRedisplay();
	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape(int w, int h)
{
	glViewport(0,0,min(w,h),min(w,h));
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowSize(640,640);
	glutInitWindowPosition(620,160);
	glutCreateWindow("animated circles");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glMatrixMode(GL_PROJECTION);
		gluOrtho2D(-3.2,3.2,-3.2,3.2);
	glMatrixMode(GL_MODELVIEW);
	glPointSize(5);
	glColor3f(1.0,0.75,0.0);	// gold
	//glColor3f(0.0,0.25,1.0);	// azure
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// application initialization
	gluQuadricDrawStyle(arc,GLU_LINE);

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
