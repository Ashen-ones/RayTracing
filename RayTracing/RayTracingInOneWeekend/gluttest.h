#pragma once
#include <glut.h>
class gluttest
{
public:

	static int WIDTH;
	static int HEIGNT;
	static GLubyte* PixelBuffer;

public:
	int argc;
	char* argv[];
	static void display();

public:
	gluttest(int w, int h,int ac,char* av[]);
	void GlutInit();
	void GlutMainLoop();
	void GlutEnd();
};

