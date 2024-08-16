#ifndef MONTHFRAME_H
#define MONTHFRAME_H

#include <QFrame>

namespace Ui {
class MonthFrame;
}

class MonthFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MonthFrame(QWidget *parent = nullptr);
    ~MonthFrame();

    int  getMonth();
    int  getYear();
    void setMonth(int month);
    void setYear(int year);
    void setMonthYear(int month, int year);
    bool addMonth(int value);

signals:
    void changeMonthSignal(int month, int year);
    void addButtonSignal(int month, int year);

private slots:
    void prevMonthSlot();
    void nextMonthSlot();
private:
    Ui::MonthFrame *ui;

    QStringList months {"Январь",
                        "Февраль",
                        "Март",
                        "Апрель",
                        "Март",
                        "Июнь",
                        "Июль",
                        "Август",
                        "Сентябрь",
                        "Октябрь",
                        "Ноябрь",
                        "Декабрь",};

    void setup();
};

#endif // MONTHFRAME_H
