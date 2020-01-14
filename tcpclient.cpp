#include "tcpclient.h"

QTcpSocket *tcpSocket;

TcpClient::TcpClient(QWidget *parent) : QWidget(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), SLOT(SocketConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), SLOT(SocketDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(SocketRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(SocketError(QAbstractSocket::SocketError)));

    qDebug() << tcpSocket->state();
}

TcpClient::~TcpClient()
{
    delete tcpSocket;
}

// ---------------------------- Public ----------------------------

void TcpClient::Connect()
{
    qDebug() << "TcpClient::Connect()";
    tcpSocket->connectToHost("10.0.0.100", 1585);
    qDebug() << tcpSocket->state();
}


// ---------------------------- Private ----------------------------

void TcpClient::SocketConnected()
{
    qDebug() << "TcpClient::slotConnected() << Socket is connected";
}

void TcpClient::SocketDisconnected()
{
    qDebug() << "TcpClient::SocketDisconnected() << Socket is disconnected";
}

void TcpClient::SocketRead()
{
    qDebug() << "TcpClient::SocketRead() << Socket is ready to read";
}

void TcpClient::SocketError(QAbstractSocket::SocketError error)
{
    /*
    QString error_string;
    switch (error)
    {
    case QAbstractSocket::HostNotFoundError:
        error_string = "The host was not found";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        error_string = "The remote host is closed";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        error_string = "The connection was refused";
        break;
    default:
        error_string = tcpSocket->errorString();
        break;
    }

    qDebug() << error_string;
    */
    qDebug() << tcpSocket->errorString();
    qDebug() << tcpSocket->state();
}
