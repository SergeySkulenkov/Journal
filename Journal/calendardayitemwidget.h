#ifndef CALENDARDAYITEMWIDGET_H
#define CALENDARDAYITEMWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QLabel;
QT_END_NAMESPACE

class QMouseEvent;
class QPaintEvent;

class CalendarDayItemWidget : public QWidget
{
    Q_OBJECT
public:
    enum ColorType{
        Red,
        Green,
        Blue
    };
    CalendarDayItemWidget( int type, QString timeStr, QString title, QWidget* parent = nullptr);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

signals:
    void doubleClickSignal(int id);

private:
    QLabel* typeLabel;
    QLabel* timeLabel;
    QLabel* titleLabel;
    int id;             //id тренировки в базе данных

    void setColorType(ColorType type);

};

#endif // CALENDARDAYITEMWIDGET_H
