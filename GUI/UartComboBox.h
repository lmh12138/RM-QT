#ifndef UARTCOMBOBOX_H
#define UARTCOMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>
#include <QString>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class UartComboBox : public QComboBox {
    Q_OBJECT
   public:
    explicit UartComboBox(QWidget *parent = nullptr);

    // 重写鼠标点击事件
    void mousePressEvent(QMouseEvent *event);

   signals:
    void NoneCOM(void);

   private:
    void scanActivePort();
};

#endif  // UARTCOMBOBOX_H