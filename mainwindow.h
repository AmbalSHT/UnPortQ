#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QSettings>
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

private slots:
    void on_butConnect_clicked();
    void on_butSend_clicked();
    void TcpServerConnected(bool state);

protected:
    virtual void resizeEvent(QResizeEvent *);

};
#endif // MAINWINDOW_H
