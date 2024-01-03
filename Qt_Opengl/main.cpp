#include "Qt_Opengl.h"
#include <QtWidgets/QApplication>

#include "glOffScreenEigen.h"
#include "glShowWidget.h"

#include <thread>

int main(int argc, char*argv[]) 
{
	QApplication a(argc, argv);

	glShowWidget window;
	window.resize(800, 600);

	window.show();
	glOffScreenEigen eigen;
	eigen.render_widget = [&](unsigned char* pixels) {
		window.show_binary(pixels);
	};


	std::thread([&]() {
		eigen.InitGl();

		eigen.ProcessEventLoop();
	
	}).detach();
	


	

	return a.exec();

//	return 0;
}


//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//
//
//
//    Qt_Opengl w;
//    w.show();
//	w.resize(1500, 1000);
//    return a.exec();
//}
