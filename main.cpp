#include "mainwindow.h"
#include <QApplication>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置debug程序图标，注意：图标放在调试程序目录
    QString strPath = QApplication::applicationDirPath();
    strPath += "/img/ARG2-EE.jpg";
    a.setWindowIcon(QIcon(strPath));

    MainWindow w;
    w.show();

    return a.exec();
}
