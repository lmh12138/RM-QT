#ifndef PAGE_IMU_STATE_H
#define PAGE_IMU_STATE_H

#include <QDebug>
#include <QWidget>

namespace Ui {
class Page_IMU_State;
}

class Page_IMU_State : public QWidget {
    Q_OBJECT

   public:
    explicit Page_IMU_State(QWidget *parent = nullptr);
    explicit Page_IMU_State(QWidget *parent, int x, int y);
    ~Page_IMU_State();

    void Refresh(int pitch, int roll, int yaw, int temp);

   private:
    Ui::Page_IMU_State *ui;
    int label_width = 150;
    int label_height = 40;
};

#endif  // PAGE_IMU_STATE_H
