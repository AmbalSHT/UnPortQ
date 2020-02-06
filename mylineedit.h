#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;

};

#endif // MYLINEEDIT_H
