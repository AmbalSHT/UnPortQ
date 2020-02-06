#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkInterface>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QTabWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QWidget>

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private:
    void GuiInit();
    QTcpServer *Server;
    QTcpSocket *ClientSocket;

private slots:
    void butSend_Click();
    void butHostStart_Click();
    void TcpServer_ClientConnected();
    void TcpServer_ClientDisconnected();
    void TcpServer_ReadClient();
};

#endif // TCPSERVER_H
