#include "tcpclient.h"

QTcpSocket *tcpSocket;

TcpClient::TcpClient(QWidget *parent) : QWidget(parent)
{
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), SLOT(SocketConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), SLOT(SocketDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(SocketRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(SocketError(QAbstractSocket::SocketError)));
    isOpen = tcpSocket->isOpen();

    //qDebug() << tcpSocket->state();
}

TcpClient::~TcpClient()
{
    delete tcpSocket;
}

// ---------------------------- Public ----------------------------

// Подключение к серверу
void TcpClient::Connect(QString ServerAddress, quint16 address)
{
    tcpSocket->connectToHost(ServerAddress, address);
    //qDebug() << tcpSocket->state();
}

// Отключение от сервера
void TcpClient::Disconnect()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

// Отправка данных на сервер
void TcpClient::SocketWrite(QString message)
{
    QByteArray arrBlock;                                        // Создаем блок данных с размером, равным 0
    QDataStream outData(&arrBlock, QIODevice::WriteOnly);       // Создаем поток для записи данных
    /*
    //outData << quint16(0) << "ASS\n";                         // Записываем строку в поток
    outData << (quint16)0 << (quint8)0xA5;                      // Записываем байт в поток (нулефой байт - количество байт в блоке)
    outData.device()->seek(0);                                  // Перемещаем указатель на начало блока
    outData << quint16(arrBlock.size() - sizeof(quint16));      // Записываем размер блока данных для передачи, минус размер quint16 для исключения данных о размере при подсчете количества байт
    */

    //outData << (quint8)0xA5;                                    // Простая передача байта
    outData << message;                                         // Простая передача строки

    tcpSocket->write(arrBlock);                                 // Передача данных на сервер
}

// ---------------------------- Private ----------------------------

// Событие подключения к серверу
void TcpClient::SocketConnected()
{
    //qDebug() << "TcpClient::slotConnected() << Socket is connected";
    isOpen = tcpSocket->isOpen();
    emit ServerConnected(true);
}

// Событие отключения от сервера
void TcpClient::SocketDisconnected()
{
    //qDebug() << "TcpClient::SocketDisconnected() << Socket is disconnected";
    isOpen = tcpSocket->isOpen();
    emit ServerConnected(false);
}

// Чтение данных, полученных от сервера
void TcpClient::SocketRead()
{
    qDebug() << "TcpClient::SocketRead() << Socket is ready to read";
    QDataStream inData(tcpSocket);
    qDebug() << "bytesAvailable: " << tcpSocket->bytesAvailable();

    QByteArray arrBlock;;
    arrBlock = tcpSocket->read(tcpSocket->bytesAvailable());
    //qDebug() << arrBlock.length();
    /*
    // Побайтный вывод
    for (int i = 0; i < arrBlock.length(); i++)
    {
        qDebug() << arrBlock[i];
    }
    */

    // Вывод в UTF8
    QString str = QString::fromUtf8(arrBlock);
    qDebug() << str;
}

// Событие, вызванное ошибками
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
