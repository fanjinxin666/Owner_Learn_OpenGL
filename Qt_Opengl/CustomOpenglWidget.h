#pragma once


#include <QOpenGLWidget>
//#include <QOpenGLFunctions_3_3_Core>
//#include <QOpenGLShaderProgram>

#include "Model.h"
#include "TaskRender.h"
#include "Shader.h"
#include "Camera.h"
#include <QMouseEvent>

class CustomOpenglWidget  : public QOpenGLWidget
{
	Q_OBJECT

public:
	CustomOpenglWidget(QWidget *parent);
	~CustomOpenglWidget();

protected:
	virtual void initializeGL();

	virtual void resizeGL(int w, int h);

	virtual void paintGL();

	virtual void mouseMoveEvent(QMouseEvent *event);

	virtual void wheelEvent(QWheelEvent *e);
private:
	bool InitShader();

private:
//	QScopedPointer<QOpenGLShaderProgram> m_Program;

	std::shared_ptr<Model> m_pModel;
	std::shared_ptr<Shader> m_pShader;
	std::shared_ptr<Camera> m_pCamera;

	TaskRender		m_autom_render;
};
