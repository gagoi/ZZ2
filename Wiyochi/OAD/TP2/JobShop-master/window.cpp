#include <iostream>
#include <QApplication>
#include "../../window.h"
#include "../../Operation.hpp"
#include "../../Data.h"
#include "../../Bierwirth.hpp"
#include "../../bkr.hpp"
#include "../../compare.hpp"
#include <QTextEdit>
#include <QDesktopWidget>

Window::Window(){
  //  setFixedSize(width, height);

    // init bouton chargement
    btn_fileDialog = new QPushButton("Ouvrir un fichier :)", this);
    btn_fileDialog->setFont(QFont("Comic Sans MS", 10));
    btn_fileDialog->setCursor(Qt::PointingHandCursor);
    btn_fileDialog->setIcon(QIcon("smile.png"));

    // init bouton chargement algo
    btn_launchAlgo = new QPushButton("Masennnnkoooo !", this);
    btn_launchAlgo->setFont(QFont("Comic Sans MS", 10));
    btn_launchAlgo->setCursor(Qt::PointingHandCursor);
    btn_launchAlgo->setIcon(QIcon("smile.png"));
    btn_launchAlgo->move(200, 0);

    // init bouton de visibilité des données de l'algo
    btn_showData = new QPushButton("Show data", this);
    btn_showData->setFont(QFont("Comic Sans MS", 10));
    btn_showData->setCursor(Qt::PointingHandCursor);
    btn_showData->setIcon(QIcon("smile.png"));
    btn_showData->move(400, 0);

    // init file dialog
    fileName_instance = "../../INSTANCES/la01.dat";

    // affichage de la fenetre
    this->showMaximized();

    // event des boutons
    QObject::connect(btn_fileDialog, SIGNAL(clicked()), this, SLOT(showFileDialog()));
    QObject::connect(btn_launchAlgo, SIGNAL(clicked()), this, SLOT(launchAlgo()));
    QObject::connect(btn_showData, SIGNAL(clicked()), this, SLOT(showData()));
}

Window::~Window(){
    delete btn_fileDialog;
    delete btn_launchAlgo;
    delete btn_showData;
}


/**
 * quit du program
 * @brief Window::keyPressEvent
 * @param event
 */
void Window::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape) // si c'est echape on quitte
        close();
}


void Window::showFileDialog(){
   QString f = QFileDialog::getOpenFileName(this,"Ouvrir", "../../INSTANCES/");
   fileName_instance = f.toUtf8().constData(); ;
}

void Window::launchAlgo(){
    std::cout << "launchAlgo" << std::endl;

    std::cout << "fileName : " << fileName_instance << std::endl;
    Data data(fileName_instance);
    data_algo << data;
    Bierwirth bierwirth(data.getNbEtape(), data.getNbOp());
    data_algo << bierwirth << std::endl;


    std::cout << "compareSolution" << std::endl;
    compareSolution();
    std::cout << "iron" << std::endl;
    std::cout << std::endl;
    std::cout << "drawf" << std::endl;
    compareSolution(10);
}

 void Window::showData(){
     std::cout << "showData" << std::endl;
    // std::cout << "--- " << data_algo << std::endl;

     QString t = QString::fromStdString(data_algo.str());

     QTextEdit* texte = new QTextEdit(this);
     texte->insertPlainText(t);
     texte->move(0, 210);
     texte->resize(this->width(), this ->height() - 300);
     texte->show();
 }
