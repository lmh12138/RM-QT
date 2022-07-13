#ifndef MYTOOLBAR_H
#define MYTOOLBAR_H

#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QToolBar>

#include "UartComboBox.h"

class MyToolBar : public QToolBar {
    Q_OBJECT
   public:
    explicit MyToolBar(QWidget *parent = nullptr);
    explicit MyToolBar(QWidget *parent, int menu_height);

    void COMNone(void);

    void OpenCOMSuccess(void);
    void OpenCOMFailed(void);

    void CloseCOMSuccess(void);

    void ToOpenCOM(void);
    void ToCloseCOM(void);

    const QString NowCOMList(void);

   signals:
    void ToOpenCOM_SGN(const QString &com);
    void ToCloseCOM_SGN(void);

   private:
    int tool_height = 50;
    QSize tool_label_size = QSize(100, 50);
    QSize tool_list_size = QSize(100, 30);
    QSize tool_button_size = QSize(100, 30);
    QPoint tool_label_offset = QPoint(20, 0);
    QPoint tool_list_offset = QPoint(tool_label_offset.x() + tool_label_size.width(), 10);
    QPoint tool_button_offset = QPoint(tool_list_offset.x() + tool_list_size.width() + 20, 10);

    QLabel *uart_label = new QLabel(this);
    UartComboBox *uart_list = new UartComboBox(this);
    QPushButton *uart_button = new QPushButton(this);
};

#endif  // MYTOOLBAR_H
