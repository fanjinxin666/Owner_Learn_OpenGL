#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Camera/camera.h>
#include <Shader/Shader.h>
#include <ModelLoading/Model.h>
//#include <ModelLoading/Mesh.h>


class ModelLoading
{
public:
	ModelLoading();
	~ModelLoading();

public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processEventLoop();

private:
	void grab_image();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mouse_callback(GLFWwindow*window, double xposIn, double yposIn);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	static float mixValue;
	static glm::vec3 cameraPos;// = glm::vec3(0.0f, 0.0f, 3.0f);
	static glm::vec3 cameraFront;// = glm::vec3(0.0f, 0.0f, -1.0f);
	static glm::vec3 cameraUp;// = glm::vec3(0.0f, 1.0f, 0.0f);


	static float yaw;//= -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	static float pitch;//= 0.0f;
	static float lastX;//= 800.0f / 2.0;
	static float lastY;//= 600.0 / 2.0;
	static float fov;//= 45.0f;

	static float cameraSpeed; // adjust accordingly

	static bool  firstMouse;
private:
	GLFWwindow* m_pGLWindow = nullptr;

	unsigned int VBO, VAO, EBO;
	unsigned int texture0;
	unsigned int texture1;

	Shader	*m_pOurShader = nullptr;

	Model	*m_pModel = nullptr;

	static Camera *m_pCamera;// (glm::vec3(0.0f, 0.0f, 3.0f));
};

