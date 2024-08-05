#include "widget.h"
#include "./ui_widget.h"
#include <QTabBar>
#include <QDebug>
#include <QEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QScreen>
#include "stylehelper.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initInterface();
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    int type = event->type();

    switch (type) {
    case QEvent::FocusIn:
        /* Если объект получил фокус */
        if(object == ui->loginEdit){
            /* Если объект = поле Имя пользователя */
            ui->loginEdit->setPlaceholderText("");                                                  //Убираем замещающий текст поля Имя пользователя
            ui->errorMsgLabel->clear();                                                             //Очищаем сообщение об ошибке
            return false;
        }else if(object == ui->passwordEdit){
            /* Если объект = поле Пароль */
            ui->passwordEdit->setPlaceholderText("");                                               //Убираем замещающий текст поля Пароль
            ui->passwordModeButton->setStyleSheet(StyleHelper::getPasswordModeButtonFocusStyle());  //Меняем QSS кнопки Показать пароль
            resetPasswordModeButton(PasswordModeType::BLOCKED);                                     //Меняем иконку кнопки Показать пароль
            ui->errorMsgLabel->clear();                                                             //Очищаем сообщение об ошибке
            return false;
        }
        break;
    case QEvent::FocusOut:
        /* Если объект потерял фокус */
        if(object == ui->loginEdit){
            /* Если объект = поле Имя пользователя */
            ui->loginEdit->setPlaceholderText(loginPlaceholderText);                                //Устанавливаем замещающий текст поля Имя пользователя
            return false;
        }else if(object == ui->passwordEdit){
            /* Если объект = поле Пароль */
            ui->passwordEdit->setPlaceholderText(passwordPlaceholderText);                          //Устанавливаем замещающий текст поля Пароль
            ui->passwordModeButton->setStyleSheet(StyleHelper::getPasswordModeButtonStyle());       //Меняем QSS кнопки Показать пароль
            ui->passwordModeButton->setIcon(QIcon());                                               //Удаляем иконку кнопки Показать пароль
            return false;
        }
        break;
    case QEvent::Enter:
        /* Если указатель мыши вошёл в ганицы объекта */
        if(object==ui->passwordModeButton){
            /* Если объект = кнопка Показать пароль */
            resetPasswordModeButton(PasswordModeType::HOVER_BLOCKED);                               //Меняем QSS кнопки Показать пароль
            return false;
        }else if(object == ui->passwordEdit){
            /* Если объект = поле Пароль */
            resetPasswordModeButton(PasswordModeType::BLOCKED);                                     //Меняем QSS кнопки Показать пароль
            return false;
        }
        break;
    case QEvent::Leave:
        /* Если указатель мыши вышел за ганицы объекта */
        if(object==ui->passwordModeButton){
            /* Если объект = кнопка Показать пароль */
            if(ui->passwordEdit->hasFocus()&& ui->passwordEdit->echoMode() == QLineEdit::Password){
                /* Если поле Пароль имеет фокус и символы скрыты */
                resetPasswordModeButton(PasswordModeType::HOVER);
            }else if(ui->passwordEdit->hasFocus()&& ui->passwordEdit->echoMode() == QLineEdit::Normal){
                /* Если поле Пароль имеет фокус и символы открыты */
                resetPasswordModeButton(PasswordModeType::BLOCKED);
            }else{
                ui->passwordModeButton->setIcon(QIcon());
            }
            return false;
        }else if(object == ui->passwordEdit){
             /* Если объект = поле Пароль */
            if(ui->passwordEdit->hasFocus()&& ui->passwordEdit->echoMode() == QLineEdit::Password){
                /* Если поле Пароль имеет фокус и символы скрыты */
                resetPasswordModeButton(PasswordModeType::HOVER);
            }else if(ui->passwordEdit->hasFocus()&& ui->passwordEdit->echoMode() == QLineEdit::Normal){
                /* Если поле Пароль имеет фокус и символы открыты */
                resetPasswordModeButton(PasswordModeType::BLOCKED);
            }else{
                ui->passwordModeButton->setIcon(QIcon());
            }

            return false;
        }
        break;
    case QEvent::KeyPress:
            /* Если нажата клавиша */
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (object == ui->loginEdit && keyEvent->key() == Qt::Key_Tab ){
                /* Если нажата клавиша Tab и фокус на поле Имя пользователя */
                ui->passwordEdit->setFocus();                                               //Устанавливаем фокус в поле Пароль
                return true;
            }else if (object == ui->passwordEdit && keyEvent->key() == Qt::Key_Tab){
                /* Если нажата клавиша Tab и Пароль имеет фокус */
                if(ui->loginButton->isEnabled())
                    ui->loginButton->setFocus();                                            //Устанавливаем фокус на кнопке Войти
                else
                    ui->canselButton->setFocus();                                           //Устанавливаем фокус на кнопке Отмена
                return true;
            }else if(ui->canselButton->hasFocus() && keyEvent->key() == Qt::Key_Return){
                /* Если нажата клавиша Enter и фокус на кнопке Отмена */
                ui->canselButton->click();
            }else if(ui->loginButton->hasFocus() && keyEvent->key() == Qt::Key_Return){
                /* Если нажата клавиша Enter и фокус на кнопке Войти */
                ui->loginButton->click();
            }
    }
    event->ignore();
    return false;
}



void Widget::loginButtonClickSlot()
{
    if(!loginValid()){
        ui->errorMsgLabel->setText("Неверный логин или пароль");
        return;
    }
    ui->tabWidget->setCurrentWidget(ui->calendarTab);
    this->repaint();
    windowResize();


}

void Widget::updateLoginDataSlot(QString str)
{
    Q_UNUSED(str);
    if(ui->loginEdit->text().length() >= 4 && ui->passwordEdit->text().length() >= 4){
        ui->loginButton->setEnabled(true);
    }else{
        ui->loginButton->setDisabled(true);
    }
}

void Widget::changePasswordModeSlot()
{
    if(ui->passwordEdit->echoMode()==QLineEdit::Password){
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->passwordModeButton->setIcon(QIcon(":/images/eye-blocked-hover.png"));
    }else{
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->passwordModeButton->setIcon(QIcon(":/images/eye-hover.png"));
    }
}

void Widget::pressReturnSlot()
{
    ui->loginButton->click();

}




void Widget::initInterface()
{
    /* Устанавливаем размер */
    QSize winSize(400,300);                                                 //Для формы авторизации нужен небольшой размер
    resize(winSize);                                                        //Изменяем размер окна

    /* Меняем заголовок окна */
    setWindowTitle("Дневник тренировок");

    setWindowIcon(QIcon(":/images/appico.ico"));

    /* Скрываем названия вкладок */
    ui->tabWidget->tabBar()->hide();

    /* Выравниваем виджет с полями формы по центру
       (если пользователь захочет развернуть окно) */
    ui->loginContainerWidget->setFixedSize(300,280);
    ui->loginTabLayout->setAlignment(Qt::AlignHCenter);

    /* Устанавливаем внешний вид элементов интерфейса */
    setStyleSheet(StyleHelper::getMainStyle());                             //Меняем внешний вид основных элементов

    /* Устанавливаем замещающий текст для полей логин и пароль */
    ui->loginEdit->setPlaceholderText(loginPlaceholderText);                //Замещающий текст для поля Имя пользователя

    ui->passwordEdit->setEchoMode(QLineEdit::Password);                     //Скрываем символы пароля
    ui->passwordEdit->setPlaceholderText(passwordPlaceholderText);          //Замещающий текст для поля Имя пользователя

    /* Устанавливаем eventFilter, чтобы иметь возможность работать
       с изменением фокуса полей Имя пользователя и Пароль */
    ui->loginEdit->installEventFilter(this);
    ui->passwordEdit->installEventFilter(this);

    /* Устанавливаем eventFilter, чтобы отследить hover кнопки
    //    смены режима отображения пароля */
    ui->passwordModeButton->installEventFilter(this);

    /* Устанавливаем eventFilter, чтобы отследить нажатие Enter
        на кнопках */
    ui->canselButton->installEventFilter(this);
    ui->loginButton->installEventFilter(this);

    /* Задаём высоту полей для ввода Имени пользователя и Пароля */
    ui->loginEdit->setMinimumHeight(StyleHelper::lineEditHeight);
    ui->passwordEdit->setMinimumHeight(StyleHelper::lineEditHeight);

    /* Задаём высоту кнопки Показать пароль */
    ui->passwordModeButton->setMinimumHeight(StyleHelper::lineEditHeight);

    /* Устанавливаем пиктограммы рядом с полями ввода */
    ui->loginIcoLabel->setPixmap(QPixmap(":/images/user.png"));
    ui->passwordIcoLabel->setPixmap(QPixmap(":/images/lock.png"));

    /* Устанавливаем изображение логотипа */
    ui->logoLabel->setPixmap(QPixmap(":/images/logo.png"));

    /* Выравниваем изображения по центру */
    ui->loginIcoLabel->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter );
    ui->passwordIcoLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter );
    ui->logoLabel->setAlignment(Qt::AlignCenter );

    /* Устанавливаем внешний вид кнопки смены режима отображения пароля */
    ui->passwordModeButton->setStyleSheet(StyleHelper::getPasswordModeButtonStyle());

    /* Выключаем кнопку Войти */
    ui->loginButton->setDisabled(true);

    /* Очищаем сообщение об ошибке */
    ui->errorMsgLabel->clear();

    /* Меняем курсор для кнопок Забыл пароль и Новый пользователь */
    ui->repasswordButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->newUserButton->setCursor(QCursor(Qt::PointingHandCursor));

    /* Клик по кнопке Войти */
    connect(ui->loginButton,&QPushButton::clicked,this,&Widget::loginButtonClickSlot);

    /* Клик по кнопке Отмена */
    connect(ui->canselButton,&QPushButton::clicked,this,&QWidget::close);

    /* Убираем фокус с кнопки переключения режима отображения символов пароля */
    ui->passwordModeButton->setFocusPolicy(Qt::NoFocus);

    /* Кликаем по кнопке смены режима отображения символов пароля */
    connect(ui->passwordModeButton, &QPushButton::clicked, this, &Widget::changePasswordModeSlot);

    /* Меняем текст в полях формы */
    connect(ui->loginEdit, &QLineEdit::textChanged, this, &Widget::updateLoginDataSlot);
    connect(ui->passwordEdit, &QLineEdit::textChanged, this, &Widget::updateLoginDataSlot);

    /* Нажатие Enter в полях ввода */
    connect(ui->loginEdit, &QLineEdit::returnPressed, this, &Widget::pressReturnSlot);
    connect(ui->passwordEdit, &QLineEdit::returnPressed, this,  &Widget::pressReturnSlot);




}

void Widget::windowResize()
{

    resize(800,600);
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect rect      = screen->geometry();
    QPoint center   = rect.center();

    center.setX(center.x() - (width() /2));
    center.setY(center.y() - (height()/2));
    move(center);
}

bool Widget::loginValid()
{
    if(ui->loginEdit->text()=="user" && ui->passwordEdit->text() == "123456"){
        return true;
    }else{
        return false;
    }
}

void Widget::resetPasswordModeButton(PasswordModeType type)
{
    switch(type){
    case PasswordModeType::HOVER:
        if(ui->passwordEdit->echoMode()==QLineEdit::Password)
            ui->passwordModeButton->setIcon(QIcon(":/images/eye.png"));
        else
            ui->passwordModeButton->setIcon(QIcon(":/images/eye-hover.png"));
        break;
    case PasswordModeType::BLOCKED:
        if(ui->passwordEdit->echoMode()==QLineEdit::Password)
            ui->passwordModeButton->setIcon(QIcon(":/images/eye.png"));
        else
            ui->passwordModeButton->setIcon(QIcon(":/images/eye-blocked.png"));
        break;
    case PasswordModeType::HOVER_BLOCKED:
        if(ui->passwordEdit->echoMode()==QLineEdit::Password)
            ui->passwordModeButton->setIcon(QIcon(":/images/eye-hover.png"));
        else
            ui->passwordModeButton->setIcon(QIcon(":/images/eye-blocked-hover.png"));
        break;
    }
}


