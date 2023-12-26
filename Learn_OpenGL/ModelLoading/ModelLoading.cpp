#include "ModelLoading.h"
#include <iostream>

#include "stb_image.h"

float ModelLoading::mixValue = 0.2f;

glm::vec3 ModelLoading::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 ModelLoading::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 ModelLoading::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float ModelLoading::yaw = -90.0f;
float ModelLoading::pitch = 0.0f;
float ModelLoading::lastX = 800.0f / 2.0;
float ModelLoading::lastY = 600.0 / 2.0;
float ModelLoading::fov = 45.0f;
float ModelLoading::cameraSpeed = 0.05f; // adjust accordingly
bool  ModelLoading::firstMouse = true;

Camera *ModelLoading::m_pCamera = nullptr;


ModelLoading::ModelLoading()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	m_pGLWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (m_pGLWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_pGLWindow);

	glfwSetFramebufferSizeCallback(m_pGLWindow, framebuffer_size_callback);

	glfwSetKeyCallback(m_pGLWindow, key_callback);

	glfwSetCursorPosCallback(m_pGLWindow, mouse_callback);

	glfwSetScrollCallback(m_pGLWindow, scroll_callback);


	// tell GLFW to capture our mouse
	glfwSetInputMode(m_pGLWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	m_pOurShader = new Shader{ "ShaderConfig/3_1_model_loading.vs", "ShaderConfig/3_1_model_loading.fs" };

	// load models
	// -----------
	m_pModel = new Model(("resources/Model/nanosuit.obj"));


	m_pCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

}

ModelLoading::~ModelLoading()
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

	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

}

void ModelLoading::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void ModelLoading::processEventLoop()
{
	while (!glfwWindowShouldClose(m_pGLWindow))
	{

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		m_pOurShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(m_pCamera->GetZoom()), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = m_pCamera->GetViewMatrix();

		m_pOurShader->setMaxtrix("view", 1, GL_FALSE, glm::value_ptr(view));
		m_pOurShader->setMaxtrix("projection", 1, GL_FALSE, glm::value_ptr(projection));

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		m_pOurShader->setMaxtrix("model", 1, GL_FALSE, glm::value_ptr(model));

		m_pModel->Draw(*m_pOurShader);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(m_pGLWindow);
		glfwPollEvents();

	
	}
}

void ModelLoading::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
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

void ModelLoading::mouse_callback(GLFWwindow * window, double xposIn, double yposIn)
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

void ModelLoading::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	m_pCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}
