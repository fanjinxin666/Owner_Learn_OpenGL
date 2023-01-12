#include "Learn_OpenGL_App.h"
#include "Introduce/Introduce_Opengl.h"
#include "Introduce/Introduce_Create_Window.h"
#include "Introduce/Introduce_Hello_Window.h"
#include "Introduce/Introduce_Hello_Triangle.h"
#include "Introduce/Introduce_Shaders.h"

Learn_OpenGL_App::Learn_OpenGL_App()
{

}

Learn_OpenGL_App::~Learn_OpenGL_App()
{

}

void Learn_OpenGL_App::Initialize(int type /*= 0*/)
{
	static Introduce_Shaders window;
	window.processEventLoop();

}
