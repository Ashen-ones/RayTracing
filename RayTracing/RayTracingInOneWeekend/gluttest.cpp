#include "gluttest.h"
int Gluttest::WIDTH = 0;
int Gluttest::HEIGNT = 0;
GLubyte* Gluttest::PixelBuffer;

 Gluttest::Gluttest(int w, int h, int ac, char* av[])
 {
	 WIDTH = w;
	 HEIGNT = h;
	 PixelBuffer = new GLubyte[WIDTH * HEIGNT * 3];
	 argc = ac;

 }
void Gluttest::GlutInit()
{
	char* argv[] = {(char*)"", nullptr};
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Gluttest::WIDTH, Gluttest::HEIGNT);
	glutInitWindowPosition(200, 200);
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glutDisplayFunc(display);
}
void Gluttest::GlutMainLoop()
{
	glutMainLoop();
}
void Gluttest::GlutEnd()
{

}
void Gluttest::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(Gluttest::WIDTH, Gluttest::HEIGNT, GL_RGB, GL_UNSIGNED_BYTE, PixelBuffer);
	glutSwapBuffers();
}

