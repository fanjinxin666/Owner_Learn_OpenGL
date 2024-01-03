#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qt_Opengl.h"

class Qt_Opengl : public QMainWindow
{
    Q_OBJECT

public:
    Qt_Opengl(QWidget *parent = nullptr);
    ~Qt_Opengl();

private:
    Ui::Qt_OpenglClass ui;
};
