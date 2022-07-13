#include "MyTreeWidget.h"

MyTreeWidget::MyTreeWidget(QWidget *parent) : QTreeWidget(parent) {
}

MyTreeWidget::MyTreeWidget(QWidget *parent, int menutoolbar_height) : QTreeWidget(parent) {
    this->setParent(parent);
    this->setFixedSize(tree_width, parent->height() - menutoolbar_height);
    this->move(0, menutoolbar_height);
    this->setStyleSheet("background-color:#D6D6D4;");
    this->setHeaderHidden(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFrameStyle(QFrame::NoFrame);
    this->setIndentation(ident_height);
}

int MyTreeWidget::CheckTreeItem(QTreeWidgetItem *item) {
    if (item == item1) {
        return 1;
    } else if (item == item2) {
        return 2;
    } else if (item == item3) {
        return 3;
    } else {
        return 0;
    }
}
