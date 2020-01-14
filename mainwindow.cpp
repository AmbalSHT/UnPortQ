#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "Start programm";

    Client = new TcpClient(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    Client->~TcpClient();
    delete ui;
}


void MainWindow::on_butConnect_clicked()
{
    qDebug() << "MainWindow::on_butConnect_clicked()";
    Client->Connect();
}
