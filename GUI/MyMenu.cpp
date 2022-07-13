#include "MyMenu.h"

MyMenu::MyMenu(QWidget *parent) : QMenuBar(parent) {
    this->setFixedSize(parent->width(), menu_height);

    myac1->setText("新建");
    myac1->setStatusTip("This is ac1.");
    myac1->setShortcut(QKeySequence("Ctrl+1"));  //随意指定快捷方式

    connect(myac1, SIGNAL(triggered()), this, SLOT(pop1()));

    myac2->setText("打开");
    myac2->setStatusTip("This is ac2");
    myac2->setShortcut(QKeySequence("Ctrl+2"));  //随意指定快捷方式

    connect(myac2, SIGNAL(triggered()), this, SLOT(pop2()));

    myac3->setText("另存为");
    myac3->setStatusTip("This is ac3");
    myac3->setShortcut(QKeySequence("Ctrl+3"));  //随意指定快捷方式

    connect(myac3, SIGNAL(triggered()), this, SLOT(pop3()));

    this->addMenu(filemenu);
    this->addMenu(editmenu);
    filemenu->addAction(myac1);
    filemenu->addAction(myac2);
    filemenu->addAction(myac3);
}

void MyMenu::pop1() {
    QMessageBox m(this);
    m.setWindowTitle("MyAction1");
    m.setText("This is a messagebox for my action1.");
    m.exec();
}

void MyMenu::pop2() {
    QMessageBox m(this);
    m.setWindowTitle("MyAction2");
    m.setText("This is a messagebox for my action2.");
    m.exec();
}

void MyMenu::pop3() {
    QMessageBox m(this);
    m.setWindowTitle("MyAction3");
    m.setText("This is a messagebox for my action3.");
    m.exec();
}

void MyMenu::SetHeight(int height) {
    this->setFixedHeight(height);
}

int MyMenu::Height() {
    return menu_height;
}