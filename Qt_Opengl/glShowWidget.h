#pragma once

#include <QWidget>
#include "ui_glShowWidget.h"

#include <mutex>

class glShowWidget : public QWidget, public Ui::glShowWidgetClass
{
	Q_OBJECT

public:
	glShowWidget(QWidget *parent = nullptr);
	~glShowWidget();

public:
	void show_binary(unsigned char* pixel);

protected:
	virtual void paintEvent(QPaintEvent* e) override;

private:
	QImage m_image;

	std::mutex m_mutex;
};
