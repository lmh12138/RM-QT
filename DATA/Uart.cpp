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

void UART::ReadData(void) {
    QByteArray data;
    for (;;) {
        data = serial->readAll();
        if (data.isEmpty()) {
            break;
        }
        uart_data.append(data);
        if (uart_data.size() > uart_data_max) {
            uart_data = uart_data.right(uart_data_max);
        }
    }
    if (!uart_data.isEmpty()) {
        ReturnCOMData(uart_data);
        uart_data.clear();
    }
}