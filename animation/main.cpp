#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <GL/glew.h>
#include <GL/glut.h>


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);


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
	glColor3f(1.0,0.75,0.0);
	glEnable(GL_MAP1_VERTEX_4);

	// application initialization

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
