#include "glShowWidget.h"
#include <QPainter>


glShowWidget::glShowWidget(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
}

glShowWidget::~glShowWidget()
{

}

#include <windows.h>
void glShowWidget::show_binary(unsigned char * pixel)
{
//	QImage image((uint8_t*)pixel, 800, 600, QImage::Format_RGBA8888);
//
//	std::lock_guard<std::mutex> locker(m_mutex);
//
//	m_image = image;
//
////	m_image.save("F:/pppp.jpg");
//
//	update();

	//rgba -> bgra

	auto *temp = pixel;
	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 600; j++) {
			int r = temp[0];
			int g = temp[1];
			int b = temp[2];
			int a = temp[3];

			temp[0] = b;
			temp[1] = g;
			temp[2] = r;
			temp[3] = a;

			temp = temp + 4;
		}
		
	}
	
	HWND hwnd = (HWND)winId();

	HDC hdc = GetDC(hwnd);//获取当前的显示设备上下文

	RECT rect;
	GetClientRect(hwnd, &rect);
	int cxClient = rect.right;
	int cyClient = rect.bottom;

	HDC  hdcsource = CreateCompatibleDC(NULL);//创建存放图象的显示缓冲
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);

	SelectObject(hdcsource, bitmap);    //将位图资源装入显示缓冲

	SetStretchBltMode(hdcsource, COLORONCOLOR);

	BITMAPINFO  bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 800;
	bmi.bmiHeader.biHeight = -600;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	//bmi.bmiHeader.biClrUsed = 0;
	//bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biSizeImage = 0;

	StretchDIBits(hdcsource, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 
		0, 0, 800, 600, pixel, &bmi, DIB_RGB_COLORS, SRCCOPY);

	BitBlt(hdc, 0, 0, cxClient, cyClient, hdcsource, 0, 0, SRCCOPY);//将图象显示缓冲的内容直接显示到屏幕

	DeleteObject(bitmap);
	DeleteDC(hdcsource);
	ReleaseDC(hwnd, hdc);
}

void glShowWidget::paintEvent(QPaintEvent * e)
{
	//std::lock_guard<std::mutex> locker(m_mutex);

	//QPainter painter(this);

	//m_image.scaled(size(), Qt::KeepAspectRatio);
	//painter.drawPixmap(rect(), QPixmap::fromImage(m_image), QRect());
}
