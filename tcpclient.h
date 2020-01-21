#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTime>

class TcpClient : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void Connect(QString ServerAddress, quint16 address);
    void Disconnect();
    void SocketWrite(QString message);
    bool isOpen;

signals:
    void ServerConnected(bool state);
    void Read(QByteArray arrBytes);

private:
    QTcpSocket *tcpSocket;

private slots:
    void SocketConnected();
    void SocketDisconnected();
    void SocketRead();
    void SocketError(QAbstractSocket::SocketError error);
};

#endif // TCPCLIENT_H
