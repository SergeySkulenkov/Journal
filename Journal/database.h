#ifndef DATABASE_H
#define DATABASE_H
#include "../sqlite/sqlite3.h"
#include <QObject>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    bool connectDb();

signals:

private:
    sqlite3* db;
    QString fname = "database.db";

    bool openDb();
    bool restoreDb();
    void closeDb();

};

#endif // DATABASE_H
