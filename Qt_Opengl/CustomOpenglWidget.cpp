
#include <glad/glad.h>
#include "CustomOpenglWidget.h"

#include "stb_image.h"


CustomOpenglWidget::CustomOpenglWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	//setFocusPolicy(Qt::StrongFocus);

	//m_Program.reset(new QOpenGLShaderProgram(this));

}

CustomOpenglWidget::~CustomOpenglWidget()
{

}

void CustomOpenglWidget::initializeGL()
{
	gladLoadGL();
	/*if (InitShader() == false) {
		return;
	}*/

	//makeCurrent();
	//stbi_set_flip_vertically_on_load(true);
	//initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	m_pShader = std::make_shared<Shader>("shader/face_shader.vs", "shader/face_shader.fs");

	m_pModel = std::make_shared<Model>("resource/Model/IronMan/IronMan.obj");

	m_pCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 30.0f));

	//构建taskRender所需要数据


}

void CustomOpenglWidget::resizeGL(int w, int h)
{
	const qreal retinaScale = devicePixelRatio();
	//glViewport(0, 0, w * retinaScale, h * retinaScale);
	//repaint();
}

void CustomOpenglWidget::paintGL()
{
	makeCurrent();
	//m_Program->bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_autom_render.Render();

	m_pShader->use();

	// view/projection transformations
	const qreal retinaScale = devicePixelRatio();
	glm::mat4 projection = glm::perspective(m_pCamera->GetZoom(), (float)1.5, 0.1f, 100.0f);

	glm::mat4 view = m_pCamera->GetViewMatrix();

	m_pShader->setMat4("view",view);
	m_pShader->setMat4("projection", projection);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

	m_pShader->setMat4("model",model);

	m_pModel->Draw(m_pShader->ID);
}

void CustomOpenglWidget::mouseMoveEvent(QMouseEvent * event)
{
	static int last_x = event->pos().x() , last_y = event->pos().y();


	m_pCamera->ProcessMouseMovement(event->pos().x() - last_x, event->pos().y() - last_y);

	last_x = event->pos().x();
	last_y = event->pos().y();
	update();
}

void CustomOpenglWidget::wheelEvent(QWheelEvent * e)
{
	m_pCamera->ProcessMouseScroll(static_cast<float>(e->delta()));
	update();
}

bool CustomOpenglWidget::InitShader()
{
	bool success = true;

	//success &= m_Program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/face_shader.vs");
	//success &= m_Program->addShaderFromSourceFile(QOpenGLShader::Fragment, "shader/face_shader.fs");
	//success &= m_Program->link();

	return success;
}
