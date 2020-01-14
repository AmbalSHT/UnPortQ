#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

class TcpClient : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
    void Connect();

private:
    QTcpSocket *tcpSocket;

private slots:
    void SocketConnected();
    void SocketDisconnected();
    void SocketRead();
    void SocketError(QAbstractSocket::SocketError error);

signals:

};

#endif // TCPCLIENT_H
