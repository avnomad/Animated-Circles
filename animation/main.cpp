#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <cmath>

#include <GL/glew.h>
#include <GL/glut.h>

#define SEGMENTS 32
#define PI 3.14159265358979323846264

void display()
{
	float curve[][4] = {{1,0,0,1},{0.70711,0.70711,0,0.70711},{0,1,0,1}};
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(50,50,0);
	glScalef(100,100,0);

	glMap1f(GL_MAP1_VERTEX_4,0.0,1.0,4,3,&curve[0][0]);
	glEvalMesh1(GL_POINT,0,SEGMENTS);

	glLoadIdentity();
	glTranslatef(45,45,0);
	glScalef(100,100,0);

	glBegin(GL_POINTS);
		for(int i = 0 ; i <= SEGMENTS ; ++i)
			glVertex2f(cos(PI/2*i/SEGMENTS),sin(PI/2*i/SEGMENTS));
	glEnd();

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
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,0,h);
	glMatrixMode(GL_MODELVIEW);
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640,640);
	glutInitWindowPosition(620,160);
	glutCreateWindow("animated circles");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glEnable(GL_BLEND);
	glColor3f(1.0,0.75,0.0);
	glEnable(GL_MAP1_VERTEX_4);
	glMapGrid1f(SEGMENTS,0.0,1.0);

	// application initialization

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
