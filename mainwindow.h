#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QSettings>
#include <QMenuBar>
#include <QTime>
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TcpClient *Client;
    QTime *CurrentTime;

private slots:
    void on_butConnect_clicked();
    void on_butSend_clicked();
    void TcpServerConnected(bool state);
    void TcpServerRead(QByteArray arrBytes);
    void mnuFile_New_Clicked();

protected:
    virtual void resizeEvent(QResizeEvent *);

};
#endif // MAINWINDOW_H
