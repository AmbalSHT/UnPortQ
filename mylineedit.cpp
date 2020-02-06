#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->setInputMask(">HH-HH-HH;_");
}

MyLineEdit::~MyLineEdit()
{

}

void MyLineEdit::keyPressEvent(QKeyEvent *e)
{
    // Перехват нажатия
    qDebug() << e->text();

    // Сгенерить событие повторно
    QLineEdit::keyPressEvent(e);
}
