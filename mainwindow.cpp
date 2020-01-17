#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "Start programm";
    ui->setupUi(this);
    //ui->centralwidget->setLayout(ui->horizontalLayout);
    ui->tblLog->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    Client = new TcpClient(this);
    connect(Client, SIGNAL(ServerConnected(bool)), this, SLOT(TcpServerConnected(bool)));

    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat, this);
    ui->txtServerAddress->setText(settings->value("server/address", "0.0.0.0").toString());
    ui->txtServerPort->setText(settings->value("server/port", "585").toString());
    ui->txtSend->setText(settings->value("message/send", "").toString());
}

MainWindow::~MainWindow()
{
    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat, this);
    settings->setValue("server/address", ui->txtServerAddress->toPlainText());
    settings->setValue("server/port", ui->txtServerPort->toPlainText());
    settings->setValue("message/send", ui->txtSend->toPlainText());
    settings->sync();

    Client->~TcpClient();
    delete ui;
}

// Положение контроллов при изменении размеров окна
void MainWindow::resizeEvent(QResizeEvent* e)
{
    //qDebug() << e->size().height();

    // gbData
    QRect* rect = new QRect(
                ui->gbData->geometry().left(),
                ui->gbData->geometry().top(),
                e->size().width() - ui->gbData->geometry().left() - 10,
                e->size().height() - ui->gbData->geometry().top() - 130
                );
    ui->gbData->setGeometry(*rect);

    // tblLog
    rect = new QRect(
                ui->tblLog->geometry().left(),
                ui->tblLog->geometry().top(),
                ui->gbData->geometry().width() - 20,
                ui->gbData->geometry().height() - 40
                );
    ui->tblLog->setGeometry(*rect);

    // gbSend
    rect = new QRect(
                ui->gbSend->geometry().left(),
                e->size().height() - ui->gbSend->geometry().height() - 50,
                ui->gbSend->geometry().width(),
                ui->gbSend->geometry().height()
                );
    ui->gbSend->setGeometry(*rect);
}

void MainWindow::on_butConnect_clicked()
{
    //qDebug() << "MainWindow::on_butConnect_clicked()";
    qDebug() << Client->isOpen;
    if (Client->isOpen)
    {
        Client->Disconnect();
    }
    else
    {
        ui->butConnect->setText("Подключение...");
        ui->butConnect->setEnabled(false);
        Client->Connect(ui->txtServerAddress->toPlainText(), ui->txtServerPort->toPlainText().toUInt());
    }
}

void MainWindow::on_butSend_clicked()
{
    qDebug() << "MainWindow::on_butSend_clicked()";
    Client->SocketWrite(ui->txtSend->toPlainText());
}

// Событие подключения / отключения
void MainWindow::TcpServerConnected(bool state)
{
    if (state)
        ui->butConnect->setText("Отключить");
    else
        ui->butConnect->setText("Подключить");
    ui->butConnect->setEnabled(true);
}
