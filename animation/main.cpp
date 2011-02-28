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

#include <GL/glew.h>
#include <GL/glut.h>

#define SEGMENTS 32
#define PI 3.14159265358979323846264
#define length(A) (sizeof(A)/sizeof((A)[0]))

void display()
{
	float circle[][4] = {{1,0,0,1},{0.70711,0.70711,0,0.70711},{0,1,0,1}};
	float line1[][4] = {{0,0,0,1},{0.35355,0,0,0.70711},{1,0,0,1}};
	float line2[][4] = {{0,0,0,1},{0.5,0,0,1},{1,0,0,1}};

	glClear(GL_COLOR_BUFFER_BIT);

	// draw circle quadrant with rational Bezier
	glPushMatrix();
		glTranslatef(45,45,0);
		glScalef(50,50,0);

		glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,3,&circle[0][0]);
		glEvalMesh1(GL_LINE,0,SEGMENTS);
	glPopMatrix();

	// again with sine/cosine
	glPushMatrix();
		glTranslatef(40,40,0);
		glScalef(50,50,0);

		glBegin(GL_LINE_STRIP);
			for(int i = 0 ; i <= SEGMENTS ; ++i)
				glVertex2f(cos(PI/2*i/SEGMENTS),sin(PI/2*i/SEGMENTS));
		glEnd();
	glPopMatrix();

	glDisable(GL_MULTISAMPLE);
	// draw straight line with rational Bezier and same weights as circle
	glPushMatrix();
		glTranslatef(40,35,0);
		glScalef(50,50,0);

		glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,3,&line1[0][0]);
		glEvalMesh1(GL_POINT,0,SEGMENTS);
	glPopMatrix();

	// draw straight line with rational Bezier and unit weights
	glPushMatrix();
		glTranslatef(40,30,0);
		glScalef(50,50,0);

		glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,3,&line2[0][0]);
		glEvalMesh1(GL_POINT,0,SEGMENTS);
	glPopMatrix();
	glEnable(GL_MULTISAMPLE);

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
		gluOrtho2D(0,100,0,100);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1.0,0.75,0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MAP1_VERTEX_4);
	glEnable(GL_MAP1_COLOR_4);
	glMapGrid1f(SEGMENTS,0.0,1.0);
	float colorCurve[][4] = {{1,0.75,0,1},{1,0.75,0,-2},{1,0.75,0,4},{1,0.75,0,-2},{1,0.75,0,1}};
	glMap1f(GL_MAP1_COLOR_4,0,1,4,length(colorCurve),&colorCurve[0][0]);

	// application initialization

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
