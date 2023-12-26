#include "Learn_OpenGL_App.h"
#include "Introduce/Introduce_Opengl.h"
#include "Introduce/Introduce_Create_Window.h"
#include "Introduce/Introduce_Hello_Window.h"
#include "Introduce/Introduce_Hello_Triangle.h"
#include "Introduce/Introduce_Shaders.h"
#include "Introduce/Introduce_Texture.h"
#include "Introduce/Introduce_Transform.h"
#include "Introduce/Introduce__CoordinateSystems.h"
#include "Introduce/Introduce_CameraView.h"
#include "ModelLoading/ModelLoading.h"

Learn_OpenGL_App::Learn_OpenGL_App()
{

}

Learn_OpenGL_App::~Learn_OpenGL_App()
{

}

void Learn_OpenGL_App::Initialize(env_learn_type type /*= 0*/)
{
	switch (type)
	{
	case env_introduce_opengl:
	{
		Introduce_Opengl window;
		break;
	}
	case env_introduce_create_widnow:
	{
		Introduce_Create_Window window;
		break;
	}
	case env_introduce_hello_window:
	{
		static Introduce_Hello_Window window;
		window.processEventLoop();
		break;
	}	
	case env_introduce_hello_triangle:
	{
		static Introduce_Hello_Triangle window;
		window.processEventLoop();
		break;
	}
	case env_introduce_shaders:
	{
		static Introduce_Shaders window;
		window.processEventLoop();
		break;
	}
	case env_introduce_texture:
	{
		static Introduce_Texture window;
		window.processEventLoop();
		break;
	}
	case env_introduce_transform:
	{
		static Introduce_Transform window;
		window.processEventLoop();
		break;
	}
	case env_introduce_CoordinateSystems:
	{
		static Introduce__CoordinateSystems window;
		window.processEventLoop();
		break;
	}
	case env_introduce_CameraView:
	{
		static Introduce_CameraView window;
		window.processEventLoop();
		break;
	}
	case env_model_loading:
	{
		static ModelLoading window;
		window.processEventLoop();
		break;
	}
	default:
		break;
	}
}
