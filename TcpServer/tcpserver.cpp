#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent) : QWidget(parent)
{
    qDebug() << "New TcpServer";
    GuiInit();
}

TcpServer::~TcpServer()
{

}

// Запуск сервера
void TcpServer::butHostStart_Click()
{
    qDebug() << "TcpServer::butStart_Click()";
    Server = new QTcpServer(this);
    Server->listen(QHostAddress::Any, (quint16)1585);
    connect(Server, SIGNAL(newConnection()), this, SLOT(TcpServer_ClientConnected()));
}

// Событие подключения нового клиента
void TcpServer::TcpServer_ClientConnected()
{
    qDebug() << "TcpServer::TcpServer_ClientConnected()";
    ClientSocket = Server->nextPendingConnection();
    connect(ClientSocket, SIGNAL(disconnected()), this, SLOT(TcpServer_ClientDisconnected()));
    connect(ClientSocket, SIGNAL(readyRead()), this, SLOT(TcpServer_ReadClient()));

    QHostAddress addr(ClientSocket->peerAddress().toIPv4Address());
    qDebug() << addr.toString();
    qDebug() << ClientSocket->peerPort();
}

// Событие отключения клиента от сокета
void TcpServer::TcpServer_ClientDisconnected()
{
    qDebug() << "TcpServer::TcpServer_ClientDisconnected()";
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
