#pragma once

enum env_learn_type
{
	env_introduce_opengl = 1,
	env_introduce_create_widnow = 2,
	env_introduce_hello_window = 3,
	env_introduce_hello_triangle = 4,
	env_introduce_shaders = 5,
	env_introduce_texture = 6,
	env_introduce_transform = 7,
	env_introduce_CoordinateSystems = 8,
	env_introduce_CameraView = 9,

	env_model_loading = 10,

};
class Learn_OpenGL_App
{

public:
	Learn_OpenGL_App();
	~Learn_OpenGL_App();


public:
	void Initialize(env_learn_type type = env_introduce_opengl);

};

