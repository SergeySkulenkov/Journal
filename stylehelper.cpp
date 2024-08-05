#include "stylehelper.h"
#include <QString>

QString StyleHelper::getMainStyle()
{
    return "QWidget#Widget{"
           "    background:#fff;"
           "}"

           //TabWidget
           "QTabWidget::pane{"
           "    border:none;"
           "}"

           //-----------------------
           //   Поля вкладки Логин
           //-----------------------

           //Поле Имя пользователя
           "QLineEdit#loginEdit{"
           "    border:1px solid #ccc;"
           "    background: #eee;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    padding:3px;"
           "    font-size:12px;"
           "}"
           "QLineEdit#loginEdit[text=\"\"]{"
           "    color:#555;"
           "}"

           //Поле Пароль
           "QLineEdit#passwordEdit{"
           "    border:1px solid #ccc;"
           "    border-right:none;"
           "    background: #eee;"
           "    padding:3px;"
           "    font-size:12px;"
           "}"
           "QLineEdit#passwordEdit[text=\"\"]{"
           "    color:#555;"
           "}"

           //Наведение на поля Имя пользователя и Пароль
           "QWidget#loginTab QLineEdit::hover{"
           "    background-color: #f2f2f2;"
           "}"

           //Фокус полей Имя пользователя и Пароль
           "QWidget#loginTab QLineEdit::focus{"
           "    background-color: #fafafa;"
           "}"

           //Пиктограммы рядом с полями ввода
           "QLabel#loginIcoLabel, QLabel#passwordIcoLabel{"
           "    background: #f5f5f5;"
           "    border-top-left-radius:3px;"
           "    border-bottom-left-radius:3px;"
           "    border:1px solid #ccc;"
           "    border-right:none;"
           "    min-width:25px;"
           "}"


           //Кнопки Войти и Отмена
           "QPushButton#loginButton{"
           "    background:#5E98D1;"
           "    color:#fff;"
           "    border-radius:3px;"
           "    padding:5px;"
           "    font-size:14px;"
           "}"
           "QPushButton#loginButton::disabled{"
           "    background:#aaa;"
           "}"
           "QPushButton#loginButton::hover{"
           "    background:#1E83E1;"
           "}"
           "QPushButton#loginButton::focus{"
           "    border: 1px solid #00538e;"
           "    background:#1E83E1;"
           "}"
           "QPushButton#canselButton{"
           "    background:#ccc;"
           "    color:#fff;"
           "    border-radius:3px;"
           "    padding:5px;"
           "    font-size:14px;"
           "}"
           "QPushButton#canselButton::hover{"
           "    background:#E16053;"
           "}"
           "QPushButton#canselButton::focus{"
           "    background:#E16053;"
           "    border:1px solid #2ba4fb;"
           "}"


           //Кнопки Забыл пароль и  Новый пользователь
           "QPushButton#repasswordButton, QPushButton#newUserButton{"
           "    border:none;"
           "    color: #aaa;"
           "    font-size:12px;"
           "    text-align:left;"
           "    margin-top:10px;"
           "}"
           "QPushButton#repasswordButton::hover, QPushButton#newUserButton::hover{"
           "    color:#7098e5;"
           "    text-decoration:underline;"
           "}"

           //Сообщение об ошибке
           "QLabel#errorMsgLabel{"
           "    color:red;"
           "}";

}

QString StyleHelper::getPasswordModeButtonStyle()
{
    return "QPushButton#passwordModeButton{"
           "    border-top:1px solid #ccc;"
           "    border-right:1px solid #ccc;"
           "    border-bottom:1px solid #ccc;"
           "    background: #eee;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    margin:0px;"
           "}";
}

QString StyleHelper::getPasswordModeButtonFocusStyle()
{
    return "QPushButton#passwordModeButton{"
           "    border-top:1px solid #ccc;"
           "    border-right:1px solid #ccc;"
           "    border-bottom:1px solid #ccc;"
           "    background: #fafafa;"
           "    border-top-right-radius:3px;"
           "    border-bottom-right-radius:3px;"
           "    margin:0px;"
           "}";
}

