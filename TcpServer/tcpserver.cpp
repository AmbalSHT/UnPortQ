#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent) : QWidget(parent)
{
    qDebug() << "New TcpServer";
    GuiInit();
    Server = new QTcpServer(this);
}

TcpServer::~TcpServer()
{

}

// Запуск сервера
void TcpServer::butHostStart_Click()
{
    qDebug() << (Server->isListening());

    if (Server->isListening())
    {
        // Остановить
        //ClientSocket->close();
        Server->close();
        butHostStart->setEnabled(true);
        butHostStart->setText("Запустить");
        lblHostStatus->setText("Остановлен");
    }
    else
    {
        // Запустить
        if (Server->listen(QHostAddress::Any, linHostPort->text().toShort()))
        {
            butHostStart->setText("Остановить");
            butHostStart->setEnabled(true);
            lblHostStatus->setText("Запущен");
            connect(Server, SIGNAL(newConnection()), this, SLOT(TcpServer_ClientConnected()));
        }
        else
        {
            butHostStart->setEnabled(true);
            lblHostStatus->setText("Ошибка!");
        }
    }
}

// Событие подключения нового клиента
void TcpServer::TcpServer_ClientConnected()
{
    qDebug() << "TcpServer::TcpServer_ClientConnected()";
    ClientSocket = Server->nextPendingConnection();
    connect(ClientSocket, SIGNAL(disconnected()), this, SLOT(TcpServer_ClientDisconnected()));
    connect(ClientSocket, SIGNAL(readyRead()), this, SLOT(TcpServer_ReadClient()));

    /*
    QHostAddress addr(ClientSocket->peerAddress().toIPv4Address());
    qDebug() << addr.toString();
    qDebug() << ClientSocket->peerPort();
    */
}

// Событие отключения клиента от сокета
void TcpServer::TcpServer_ClientDisconnected()
{
    qDebug() << "TcpServer::TcpServer_ClientDisconnected()";
    ClientSocket->close();
}

// Событие чтения данных от клиента
void TcpServer::TcpServer_ReadClient()
{
    qDebug() << "TcpServer::TcpServer_ReadClient()";
    //QTcpSocket *ClientSocket = (QTcpSocket*)sender();
    QByteArray arr = ClientSocket->readAll();       // ->read(ClientSocket->bytesAvailable())

    // Чтение в ASCII
    QString str = QString::fromUtf8(arr);
    qDebug() << str;
}

// Отправка на сервер
void TcpServer::butSend_Click()
{
    qDebug() << "TcpServer::butSend_Click()";
    QByteArray arrBlock = QString("ASS Жопъ").toUtf8();
    ClientSocket->write(arrBlock);
}
