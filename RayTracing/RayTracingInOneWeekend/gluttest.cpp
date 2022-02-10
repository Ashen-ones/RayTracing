#include "gluttest.h"
int gluttest::WIDTH = 0;
int gluttest::HEIGNT = 0;
GLubyte* gluttest::PixelBuffer;

 gluttest::gluttest(int w, int h, int ac, char* av[])
 {
	 WIDTH = w;
	 HEIGNT = h;
	 PixelBuffer = new GLubyte[WIDTH * HEIGNT * 3];
	 argc = ac;

 }
void gluttest::GlutInit()
{
	char* argv[] = {(char*)"", nullptr};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(gluttest::WIDTH, gluttest::HEIGNT);
	glutInitWindowPosition(200, 200);
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glutDisplayFunc(display);
}
void gluttest::GlutMainLoop()
{
	glutMainLoop();
}
void gluttest::GlutEnd()
{

}
void gluttest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(gluttest::WIDTH, gluttest::HEIGNT, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);
	glutSwapBuffers();
}

