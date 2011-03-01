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

#define SEGMENTS 32
#define ANIMATION_DURATION 150 /* frames*/
#define PI 3.14159265358979323846264
#define ROOT2 1.41421356237309504880
#define length(A) (sizeof(A)/sizeof((A)[0]))

float curveUp[][4] = {{0,1,0,1},{ROOT2/4,(ROOT2+2)/4,0,(ROOT2+2)/4},{(ROOT2+1)/4,(ROOT2+1)/4,0,(ROOT2+2)/4}};
float curveDown[][4] = {{1,0,0,1},{(ROOT2+2)/4,ROOT2/4,0,(ROOT2+2)/4},{(ROOT2+1)/4,(ROOT2+1)/4,0,(ROOT2+2)/4}};
unsigned int current_frame = 0;
float w_endpoints[2] = {(ROOT2+2)/4,1};
float xy_endpoints[2] = {ROOT2/2,1};
float mid_endpoints[2] = {ROOT2-1,1};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(current_frame >= ANIMATION_DURATION)
	{
		current_frame = 0;
		swap(w_endpoints[0],w_endpoints[1]);
		swap(xy_endpoints[0],xy_endpoints[1]);
		swap(mid_endpoints[0],mid_endpoints[1]);
	} // end if

	float t = 0.5*cos(PI*current_frame/ANIMATION_DURATION+PI)+0.5;
	//t = 0.5*cos(PI*t+PI)+0.5;
	curveDown[2][3] = curveUp[2][3] = t*w_endpoints[1] + (1-t)*w_endpoints[0];
	curveDown[2][0] = curveDown[2][1] = curveUp[2][0] = curveUp[2][1] = (t*xy_endpoints[1] + (1-t)*xy_endpoints[0])*curveDown[2][3];
	curveDown[1][1] = curveUp[1][0] = (t*mid_endpoints[1] + (1-t)*mid_endpoints[0])*curveUp[1][3];
	current_frame++;


	// draw shape
	for(int i = 0 ; i < 360 ; i += 90)
	{
		glPushMatrix();
			glRotatef(i,0,0,1);	// in degrees
			// draw up segment
			glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,length(curveUp),&curveUp[0][0]);
			glEvalMesh1(GL_LINE,0,SEGMENTS);
			// draw down segment
			glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,length(curveDown),&curveDown[0][0]);
			glEvalMesh1(GL_LINE,0,SEGMENTS);
		glPopMatrix();
	} // end for


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
		gluOrtho2D(-1.1,1.1,-1.1,1.1);
	glMatrixMode(GL_MODELVIEW);
	glPointSize(5);
	glColor3f(0.0,0.25,1.0);	// azure
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MAP1_VERTEX_4);
	glEnable(GL_MAP1_COLOR_4);
	glMapGrid1f(SEGMENTS,0.0,1.0);
	float colorCurve[][4] = {{1,0.75,0,1},/*{1,0.75,0,-2},*/{1,0.75,0,4},/*{1,0.75,0,-2},*/{1,0.75,0,1}};
	glMap1f(GL_MAP1_COLOR_4,0,1,4,length(colorCurve),&colorCurve[0][0]);

	// application initialization

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
