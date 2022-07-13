#include "MyToolBar.h"

MyToolBar::MyToolBar(QWidget *parent) : QToolBar(parent) {
}

MyToolBar::MyToolBar(QWidget *parent, int menu_height) : QToolBar(parent) {
    this->setFixedSize(parent->width(), tool_height);
    this->move(0, menu_height);
    this->setStyleSheet("background-color:#E7E7EA");

    uart_label->setFont(QFont("宋体", 10));
    uart_label->setText("串口号：");
    uart_label->setFixedSize(tool_label_size);
    uart_label->move(tool_label_offset);

    uart_list->setFixedSize(tool_list_size);
    uart_list->move(tool_list_offset);
    uart_list->setCurrentIndex(0);
    connect(uart_list, &UartComboBox::NoneCOM, this, &MyToolBar::COMNone);

    uart_button->setFont(QFont("宋体", 10));
    uart_button->setText("打开串口");
    uart_button->setStyleSheet("background-color:(0.941176, 0.941176, 0.941176); color:black");
    uart_button->setFixedSize(tool_button_size);
    uart_button->move(tool_button_offset);
    connect(uart_button, &QPushButton::clicked, this, &MyToolBar::ToOpenCOM);
}

void MyToolBar::COMNone(void) {
    QMessageBox m(this);
    m.setWindowTitle("警告");
    m.setText("暂无可用串口！");
    m.exec();
}

void MyToolBar::ToOpenCOM(void) {
    ToOpenCOM_SGN(uart_list->currentText());
    
}

void MyToolBar::ToCloseCOM(void) {
    ToCloseCOM_SGN();
}

void MyToolBar::OpenCOMSuccess(void) {
    uart_button->setFont(QFont("宋体", 10));
    uart_button->setText("关闭串口");
    uart_button->setStyleSheet("background-color:#8ACD97; color:black");
    uart_button->setFixedSize(tool_button_size);
    uart_button->move(tool_button_offset);

    disconnect(uart_button, &QPushButton::clicked, this, &MyToolBar::ToOpenCOM);
    connect(uart_button, &QPushButton::clicked, this, &MyToolBar::ToCloseCOM);
}

void MyToolBar::OpenCOMFailed(void) {
    QMessageBox m(this);
    m.setWindowTitle("警告");
    m.setText("串口打开失败！");
    m.exec();
}

void MyToolBar::CloseCOMSuccess(void) {
    uart_button->setFont(QFont("宋体", 10));
    uart_button->setText("打开串口");
    uart_button->setStyleSheet("background-color:(0.941176, 0.941176, 0.941176); color:black");
    uart_button->setFixedSize(tool_button_size);
    uart_button->move(tool_button_offset);

    connect(uart_button, &QPushButton::clicked, this, &MyToolBar::ToOpenCOM);
    disconnect(uart_button, &QPushButton::clicked, this, &MyToolBar::ToCloseCOM);
}

const QString MyToolBar::NowCOMList(void) {
    return uart_list->currentText();
}
