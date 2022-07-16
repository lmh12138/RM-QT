#include "Page_IMU_State.h"

#include "ui_Page_IMU_State.h"

Page_IMU_State::Page_IMU_State(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::Page_IMU_State) {
    ui->setupUi(this);
}

Page_IMU_State::Page_IMU_State(QWidget *parent, int x, int y) : QWidget(parent),
                                                                ui(new Ui::Page_IMU_State) {
    ui->setupUi(this);
    this->setParent(parent);
    this->setGeometry(x, y, parent->width() - x, parent->height() - y);

    ui->gaugeMini->setGeometry(this->width() / 7, this->height() / 20, this->width() / 7, this->width() / 7);
    ui->gaugeMini->setRange(-180.0, 180.0);
    ui->gaugeMini->setPrecision(255);
    ui->gaugeMini->setShowValue(true);
    ui->gaugeMini->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 禁用鼠标事件

    ui->gaugeMini_2->setGeometry(this->width() / 7 * 3, this->height() / 20, this->width() / 7, this->width() / 7);
    ui->gaugeMini_2->setRange(-180.0, 180.0);
    ui->gaugeMini_2->setPrecision(255);
    ui->gaugeMini_2->setShowValue(true);
    ui->gaugeMini_2->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->gaugeMini_3->setGeometry(this->width() / 7 * 5, this->height() / 20, this->width() / 7, this->width() / 7);
    ui->gaugeMini_3->setRange(-180.0, 180.0);
    ui->gaugeMini_3->setPrecision(255);
    ui->gaugeMini_3->setShowValue(true);
    ui->gaugeMini_3->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    int label_x_1 = ui->gaugeMini->x() + ui->gaugeMini->width() / 2 - label_width / 2;
    int label_x_2 = ui->gaugeMini_2->x() + ui->gaugeMini_2->width() / 2 - label_width / 2;
    int label_x_3 = ui->gaugeMini_3->x() + ui->gaugeMini_3->width() / 2 - label_width / 2;
    int label_y = ui->gaugeMini->y() + ui->gaugeMini->height() + 20;
    ui->navLabel->setGeometry(label_x_1, label_y, label_width, label_height);
    ui->navLabel_2->setGeometry(label_x_2, label_y, label_width, label_height);
    ui->navLabel_3->setGeometry(label_x_3, label_y, label_width, label_height);

    int simple_width = this->width() / 5;
    ui->gaugeSimple->setGeometry(ui->gaugeMini_2->x() + ui->gaugeMini_2->width() / 2 - simple_width / 2,
                                 ui->navLabel_2->y() + label_height + 70, simple_width, simple_width);
    int label_x_4 = ui->gaugeSimple->x() + ui->gaugeSimple->width() / 2 - label_width / 2;
    ui->navLabel_4->setGeometry(label_x_4, ui->gaugeSimple->y() + ui->gaugeSimple->height() + 20, label_width, label_height);

    this->hide();
}

Page_IMU_State::~Page_IMU_State() {
    delete ui;
}

void Page_IMU_State::Refresh(int pitch, int roll, int yaw, int temp) {
    ui->gaugeMini->setValue(pitch);
    ui->gaugeMini_2->setValue(roll);
    ui->gaugeMini_3->setValue(yaw);
    ui->gaugeSimple->setValue(temp);
}