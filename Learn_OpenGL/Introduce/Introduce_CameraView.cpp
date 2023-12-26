#include "Introduce_CameraView.h"

#include <iostream>
#include <thread>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float Introduce_CameraView::mixValue = 0.2f;

float Introduce_CameraView::vertices_36[] = {
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		 0.5f, 0.5f,  0.5f,		1.0f, 1.0f,
		 0.5f, 0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f,  0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f

};

glm::vec3 Introduce_CameraView::cameraPos	= glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 Introduce_CameraView::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Introduce_CameraView::cameraUp	= glm::vec3(0.0f, 1.0f, 0.0f);


// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float Introduce_CameraView::yaw = -90.0f;
float Introduce_CameraView::pitch = 0.0f;
float Introduce_CameraView::lastX = 800.0f / 2.0;
float Introduce_CameraView::lastY = 600.0 / 2.0;
float Introduce_CameraView::fov = 45.0f;
float Introduce_CameraView::cameraSpeed = 0.05f; // adjust accordingly
bool  Introduce_CameraView::firstMouse = true;

Camera *Introduce_CameraView::m_pCamera = nullptr;

Introduce_CameraView::Introduce_CameraView()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_pGLWindow = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (m_pGLWindow == nullptr) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_pGLWindow);

	glfwSetFramebufferSizeCallback(m_pGLWindow, framebuffer_size_callback);

	glfwSetKeyCallback(m_pGLWindow, key_callback);

	glfwSetCursorPosCallback(m_pGLWindow, mouse_callback);

	glfwSetScrollCallback(m_pGLWindow, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return;
	}

	m_pOurShader = new Shader{ "ShaderConfig/1_9_shader.vs", "ShaderConfig/1_9_shader.fs" };

	m_pCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));


	float vertices[] = {
		//     ---- 位置 ----     -纹理坐标-           
		 0.5f,  0.5f, 0.0f,		 1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,		 1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,		 0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,		 0.0f, 1.0f    // 左上
	};

	unsigned int indices[] = {
		// note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_36), vertices_36, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	{
		glGenTextures(1, &texture0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 加载并生成纹理
		int width, height, nrChannels;

		unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	{
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		//为当前绑定的纹理对象设置环绕、过滤方式
		//set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 加载并生成纹理
		int width, height, nrChannels;
		unsigned char *data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	glEnable(GL_DEPTH_TEST);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	m_pOurShader->use(); // don't forget to activate/use the shader before setting uniforms!
	// set it via the texture class
	m_pOurShader->setInt("texture0", 0);
	m_pOurShader->setInt("texture1", 1);
}

Introduce_CameraView::~Introduce_CameraView()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	if (m_pOurShader) {
		delete m_pOurShader;
		m_pOurShader = nullptr;
	}
}

void Introduce_CameraView::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void Introduce_CameraView::processEventLoop()
{
	while (!glfwWindowShouldClose(m_pGLWindow))
	{
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		// create transformations
	
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		m_pOurShader->setMaxtrix("model", 1, GL_FALSE, glm::value_ptr(model));

		float radius = 10.0f;
		float camX = (float)sin(glfwGetTime()) * radius;
		float camZ = (float)cos(glfwGetTime()) * radius;
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		// camera/view transformation
		view = m_pCamera->GetViewMatrix();
		m_pOurShader->setMaxtrix("view", 1, GL_FALSE, glm::value_ptr(view));
		
		//glm::mat4 projection = glm::mat4(1.0f);
		//projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 projection = glm::perspective(glm::radians(m_pCamera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		m_pOurShader->setMaxtrix("projection", 1, GL_FALSE, glm::value_ptr(projection));

		m_pOurShader->use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		m_pOurShader->setFloat("mixValue", mixValue);

		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(m_pGLWindow);
		glfwPollEvents();
	}
}

void Introduce_CameraView::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.1f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.1f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//cameraPos += cameraSpeed * cameraFront;
		//cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
		m_pCamera->ProcessKeyboard(FORWARD, cameraSpeed);
	}	
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//cameraPos -= cameraSpeed * cameraFront;
		//cameraPos += glm::normalize(cameraUp) * cameraSpeed;
		m_pCamera->ProcessKeyboard(BACKWARD, cameraSpeed);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		m_pCamera->ProcessKeyboard(LEFT, cameraSpeed);
	}		
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		m_pCamera->ProcessKeyboard(RIGHT, cameraSpeed);
	}
		
}


void Introduce_CameraView::mouse_callback(GLFWwindow*window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	m_pCamera->ProcessMouseMovement(xoffset, yoffset);
}

void Introduce_CameraView::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_pCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}