#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class QEvent;
class MonthFrame;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    enum class PasswordModeType{
        HOVER,
        BLOCKED,
        HOVER_BLOCKED
    };

protected:
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void loginButtonClickSlot();
    void updateLoginDataSlot(QString);
    void changePasswordModeSlot();
    void pressReturnSlot();
    void changeCurrentPageSlot();

private:
    Ui::Widget *ui;
    const QString loginPlaceholderText    = "Имя пользователя";
    const QString passwordPlaceholderText = "Пароль";

    void initInterface();
    void windowResize();
    bool loginValid();

    void resetPasswordModeButton(PasswordModeType type);

    //-------------------------------

    MonthFrame* monthFrame;
    DataBase db;                           //Объект для взаимодействия с базой данных





};
#endif // WIDGET_H
