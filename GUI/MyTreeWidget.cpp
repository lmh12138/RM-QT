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
        return 10;
    } else if (item == item11) {
        return 11;
    } else if (item == item12) {
        return 12;
    } else if (item == item2) {
        return 20;
    } else if (item == item3) {
        return 30;
    } else {
        return 0;
    }
}
