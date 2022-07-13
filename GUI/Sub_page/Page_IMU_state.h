#ifndef PAGE_IMU_STATE_H
#define PAGE_IMU_STATE_H

#include <QColor>
#include <QPainter>
#include <QWidget>

class Page_IMU_State : public QWidget {
    Q_OBJECT
   public:
    explicit Page_IMU_State(QWidget *parent);
    explicit Page_IMU_State(QWidget *parent, int x, int y);

   signals:

   private:
};

#endif  // PAGE_IMU_H
