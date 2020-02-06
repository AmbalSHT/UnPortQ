#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "MainWindow --> UI setup";

    // MainWindow
    this->setGeometry(0, 0, 500, 500);

    QGridLayout *gl = new QGridLayout(this);
    this->setLayout(gl);

    MyLineEdit *lin = new MyLineEdit(this);
    //lin->setInputMask(">HH-HH;_");
    gl->addWidget(lin);
}

MainWindow::~MainWindow()
{

}
