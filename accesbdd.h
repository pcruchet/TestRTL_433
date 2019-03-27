#ifndef ACCESBDD_H
#define ACCESBDD_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class AccesBDD : public QObject
{
    Q_OBJECT
public:
    explicit AccesBDD(QObject *parent = nullptr);

signals:

public slots:
private:
    QSqlDatabase db;
};

#endif // ACCESBDD_H
