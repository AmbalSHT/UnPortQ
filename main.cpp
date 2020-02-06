#include <QApplication>
#include "mainwindow.h"
#include "TcpServer/tcpserver.h"
#include "mylineedit.h"

QT_BEGIN_NAMESPACE
namespace UnPortQ {
    class MainWindow;
    class TcpServer;
    class MyLineEdit;
}
QT_END_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    TcpServer w;
    w.show();
    return a.exec();
}
