#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "Start programm";
    ui->setupUi(this);
    ui->tblLog->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    // Настройки
    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat, this);
    ui->txtServerAddress->setText(settings->value("server/address", "0.0.0.0").toString());
    ui->txtServerPort->setText(settings->value("server/port", "585").toString());
    ui->txtSend->setText(settings->value("message/send", "").toString());

    // Menu
    QMenu *menuFile = menuBar()->addMenu("Файл");
    QAction *menuFile_New = new QAction("Новый", this);
    menuFile_New->setShortcut(tr("Ctrl+N"));
    connect(menuFile_New, SIGNAL(triggered()), this, SLOT(mnuFile_New_Clicked()));
    menuFile->addAction(menuFile_New);
}

MainWindow::~MainWindow()
{
    QSettings *settings = new QSettings("settings.conf", QSettings::IniFormat, this);
    settings->setValue("server/address", ui->txtServerAddress->toPlainText());
    settings->setValue("server/port", ui->txtServerPort->toPlainText());
    settings->setValue("message/send", ui->txtSend->toPlainText());
    settings->sync();

    if (Client != nullptr) Client->~TcpClient();
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


// ---------------------------- TcpClient ----------------------------

// Подключение / отключение
void MainWindow::on_butConnect_clicked()
{
    //qDebug() << "MainWindow::on_butConnect_clicked()";
    //qDebug() << (Client == nullptr);

    if (Client == nullptr)
    {
        ui->butConnect->setText("Подключение...");
        ui->butConnect->setEnabled(false);
        Client = new TcpClient(this);
        connect(Client, SIGNAL(ServerConnected(bool)), this, SLOT(TcpServerConnected(bool)));
        connect(Client, SIGNAL(Read(QByteArray)), this, SLOT(TcpServerRead(QByteArray)));
        Client->Connect(ui->txtServerAddress->toPlainText(), ui->txtServerPort->toPlainText().toUInt());
    }
    else
    {
        Client->Disconnect();
        Client = nullptr;
    }
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

// Отправка данных на сервер
void MainWindow::on_butSend_clicked()
{
    //qDebug() << "MainWindow::on_butSend_clicked()";
    Client->SocketWrite(ui->txtSend->toPlainText());
}

// Событие получения данных от сервера
void MainWindow::TcpServerRead(QByteArray arrBytes)
{
    // Вывод в UTF8
    //QString str = QString::fromUtf8(arrBytes);
    //qDebug() << str;
    //ui->tblLog->insertRow(0);

    QString strCurrentTime = CurrentTime->currentTime().toString("hh:mm:ss.zzz");
    uint rows = ui->tblLog->rowCount();
    ui->tblLog->insertRow(rows);
    ui->tblLog->setItem(rows, 0, new QTableWidgetItem(strCurrentTime));
    ui->tblLog->setItem(rows, 1, new QTableWidgetItem("От сервера"));
    ui->tblLog->setItem(rows, 2, new QTableWidgetItem(QString::fromUtf8(arrBytes)));    // Вывод в UTF8
    ui->tblLog->scrollToBottom();

}

// ---------------------------- Меню ----------------------------
void MainWindow::mnuFile_New_Clicked()
{
    qDebug() << "MainWindow::mnuFile_New_Clicked()";
}
