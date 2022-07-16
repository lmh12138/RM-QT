#include "Uart.h"

UART::UART() : QObject() {
    serial->setFlowControl(QSerialPort::NoFlowControl);
    connect(thread, &QThread::started, this, &UART::UartThread);
    moveToThread(thread);
}

void UART::SetCOMPort(const QString& com) {
    serial->setPortName(com);
}

void UART::SetCOMBaudRate(const QString& text) {
    QString temp = text;
    quint32 baudrate = temp.toUInt();
    serial->setBaudRate(baudrate);
}

void UART::SetCOMDataBits(const QString& text) {
    QString temp = text;
    quint8 databits = temp.toUInt();
    serial->setDataBits((QSerialPort::DataBits)databits);
}

void UART::SetCOMParity(const QString& text) {
    QSerialPort::Parity parity;
    if (text == "Even") {
        parity = QSerialPort::EvenParity;
    } else if (text == "Mark") {
        parity = QSerialPort::MarkParity;
    } else if (text == "None") {
        parity = QSerialPort::NoParity;
    } else if (text == "Odd") {
        parity = QSerialPort::OddParity;
    }
    serial->setParity(parity);
}

void UART::SetCOMStopBits(const QString& text) {
    QSerialPort::StopBits stopbits;
    if (text == "One") {
        stopbits = QSerialPort::OneStop;
    } else if (text == "OnePointFive") {
        stopbits = QSerialPort::OneAndHalfStop;
    } else if (text == "Two") {
        stopbits = QSerialPort::TwoStop;
    }
    serial->setStopBits(stopbits);
}

void UART::OpenCOM(const QString& com) {
    serial->setPortName(com);
    if (!serial->isOpen()) {
        bool open_flag;
        open_flag = serial->open(QSerialPort::ReadWrite);
        if (open_flag == true) {
            OpenCOMSuccess();
        } else {
            OpenCOMFailed();
        }
    }
}

void UART::CloseCOM(void) {
    if (serial->isOpen()) {
        serial->clear();
        serial->close();
        CloseCOMSuccess();
    }
}

void UART::OpenUartThread(void) {
    thread_is_open = true;
    thread->start();
}

void UART::CloseUartThread(void) {
    thread_is_open = false;
    thread->quit();
    thread->wait();
}

void UART::UartThread(void) {
    while (thread_is_open) {
        ReadData();
    }
}

const QByteArray UART::SendCMD(uint8_t cmd) {
    QByteArray data;
    data[0] = 'L';
    data[1] = 'C';
    data[2] = cmd;
    data[3] = 'M';
    data[4] = 'H';
    uint8_t* crc_data = (uint8_t*)data.data();
    data[5] = crc8(crc_data, 5);
    return data;
}

const QByteArray UART::SendReply(void) {
    QByteArray data;
    data[0] = 'L';
    data[1] = 'D';
    data[2] = 1;
    data[3] = 'M';
    data[4] = 'H';
    uint8_t* crc_data = (uint8_t*)data.data();
    data[5] = crc8(crc_data, 5);
    return data;
}

void UART::WriteData(QByteArray data) {
    if (serial->isOpen()) {
        serial->write(data);
    }
}

void UART::ReadData(void) {
    qint64 length = serial->read(uart_recv_data, MAX_BUF);
    if (0 != length) {
        SolveData(uart_recv_data, length);
        memset(uart_recv_data, 0, sizeof(uart_recv_data));
    }
}

void UART::SolveData(char* data, qint64 length) {
    uint8_t crc = crc8((uint8_t*)data, (uint16_t)(length - 1));
    if ('L' == data[0] && 'M' == data[length - 3] && 'H' == data[length - 2] && crc == (uint8_t)data[length - 1]) {
        if ('R' == data[1]) {
            ReplyCOMCmd();
        } else if ('D' == data[1]) {
            switch (data[2]) {
                case 10:
                    break;
                case 11:
                    int imu_data[4];
                    imu_data[0] = (uint8_t)data[3] - 180;
                    imu_data[1] = (uint8_t)data[4] - 180;
                    imu_data[2] = (uint8_t)data[5] - 180;
                    imu_data[3] = data[6];
                    PAGE_IMU_STATE(imu_data[0], imu_data[1], imu_data[2], imu_data[3]);
                    break;
                case 12:
                    break;
                case 20:
                    break;
                case 30:
                    break;
                default:
                    break;
            }
        }
    }
}

uint8_t UART::crc8(uint8_t* p_buffer, uint16_t buf_size) {
    uint8_t crc = 0;
    if (buf_size <= 0) {
        return crc;
    }
    while (buf_size--) {
        for (uint8_t i = 0x80; i != 0; i /= 2) {
            if ((crc & 0x80) != 0) {
                crc *= 2;
                crc ^= 0x07;  // 多项式：X8 + X2 + X + 1
            } else {
                crc *= 2;
            }

            if ((*p_buffer & i) != 0) {
                crc ^= 0x07;
            }
        }
        p_buffer++;
    }
    return crc;
}