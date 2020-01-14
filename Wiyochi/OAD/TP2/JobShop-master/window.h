#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QKeyEvent>
#include <sstream>

class Window : public QWidget{
    Q_OBJECT
public:
    Window();
    ~Window();
    void keyPressEvent(QKeyEvent* event);

private:
QPushButton *btn_fileDialog;
QPushButton *btn_launchAlgo;
QPushButton *btn_showData;
std::string fileName_instance;
std::stringstream data_algo;


signals:

public slots:
    void showFileDialog();
    void launchAlgo();
    void showData();

};

#endif // WINDOW_H
