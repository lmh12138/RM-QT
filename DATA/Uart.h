#ifndef UART_H
#define UART_H

#include <QByteArray>
#include <QDebug>
#include <QIODevice>
#include <QObject>
#include <QString>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class UART : public QObject {
    Q_OBJECT
   public:
    explicit UART();
    void SetCOMPort(const QString& com);
    void SetCOMBaudRate(const QString& text);
    void SetCOMDataBits(const QString& text);
    void SetCOMParity(const QString& text);
    void SetCOMStopBits(const QString& text);

    void OpenCOM(const QString& com);
    void CloseCOM(void);

    void UartThread(void);
    void OpenUartThread(void);
    void CloseUartThread(void);

    void ReadData(void);
    void SolveData(void);

   signals:
    void ReturnCOMData(QByteArray data);
    void OpenCOMSuccess(void);
    void OpenCOMFailed(void);
    void CloseCOMSuccess(void);

   private:
    QSerialPort* serial = new QSerialPort;
    QThread* thread = new QThread(this);
    bool thread_is_open = true;
    const int uart_data_max = 64 * 1024;
    QByteArray uart_data;
};

#endif  // UART_H
