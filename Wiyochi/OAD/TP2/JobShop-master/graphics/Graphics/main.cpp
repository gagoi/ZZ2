#include <iostream>
//#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include "../../window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;


   // MainWindow w;
   // w.show();

    return a.exec();
}
