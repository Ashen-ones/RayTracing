#pragma once
#include <glut.h>
class Gluttest
{
public:

	static int WIDTH;
	static int HEIGNT;
	static GLubyte* PixelBuffer;
public:
	int argc;
	static void display();
public:
	Gluttest(int w, int h,int ac,char* av[]);
	void GlutInit();
	void GlutMainLoop();
	void GlutEnd();
};

