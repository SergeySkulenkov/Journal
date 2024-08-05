#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class QEvent;

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

private:
    Ui::Widget *ui;
    const QString loginPlaceholderText    = "Имя пользователя";
    const QString passwordPlaceholderText = "Пароль";

    void initInterface();
    void windowResize();
    bool loginValid();

    void resetPasswordModeButton(PasswordModeType type);




};
#endif // WIDGET_H
