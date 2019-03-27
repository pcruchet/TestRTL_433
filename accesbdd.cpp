#include "accesbdd.h"
#include <QDebug>

AccesBDD::AccesBDD(QObject *parent) : QObject(parent)
{
    db =  QSqlDatabase::addDatabase(("QMYSQL"));
    db.setHostName("192.168.1.57");
    db.setUserName("philippe");
    db.setPassword("123");
   // db.setDatabaseName("meteo");

    if(db.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName() ;
        db.close();
    }
    else
    {
        qDebug() << "La connexion a échouée, désolé" ;
    }
}
