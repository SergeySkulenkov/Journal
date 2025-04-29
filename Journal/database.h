#ifndef DATABASE_H
#define DATABASE_H
#include "../sqlite/sqlite3.h"
#include <QObject>
#include <QVector>
#include <QMap>


class DataBase : public QObject
{
    Q_OBJECT
public:
    struct Trening{
        int     id;
        int     type;
        QString name;
        QString place;
        int     day;
        QString time;
        int     duration;
        QString description;
        QString keywords;
    };



    using TreningsInMonth = QMap<int, QVector<Trening>>;
    explicit DataBase(QObject *parent = nullptr);
    bool connectDb();

    TreningsInMonth getTreings(int month, int year);
    int login(const std::string &name, const std::string &password);

signals:

private:
    sqlite3* db;
    QString fname = "database.db";

    bool openDb();
    bool restoreDb();
    void closeDb();

};

#endif // DATABASE_H
