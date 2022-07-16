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

#define MAX_BUF 2048

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
    const QByteArray SendCMD(uint8_t cmd);
    const QByteArray SendReply(void);
    const QByteArray SendDATA(QByteArray& data);
    void WriteData(QByteArray data);
    void SolveData(char* data, qint64 length);

    uint8_t crc8(uint8_t* p_buffer, uint16_t buf_size);

   signals:
    void ReturnCOMData(QByteArray data);
    void OpenCOMSuccess(void);
    void OpenCOMFailed(void);
    void CloseCOMSuccess(void);
    void ReplyCOMCmd(void);

    void PAGE_IMU_STATE(int pitch, int roll, int yaw, int temp);

   private:
    QSerialPort* serial = new QSerialPort;
    QThread* thread = new QThread(this);
    bool thread_is_open = true;
    char uart_recv_data[MAX_BUF];
};

#endif  // UART_H
