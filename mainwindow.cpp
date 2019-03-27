#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    processus = new QProcess(parent);
    connect(processus, &QProcess::readyReadStandardOutput,this,&MainWindow::MettreAJour);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLancer_clicked()
{   QStringList arguments;
    arguments << "-R" << "32" << "-F" << "json";
    processus->start("rtl_433",arguments);
}

void MainWindow::MettreAJour()
{
    QByteArray tableau = processus->readAllStandardOutput();


    int indice = 0;
    while(tableau[indice] != '}' && indice < tableau.count())
    {

        chaine += tableau[indice++];
    }
    if(tableau[indice] == '}')
    {
        chaine += "}";
        if(chaine.at(0)== '"')
            chaine.remove(0,1);

        QJsonDocument doc = QJsonDocument::fromJson(chaine.toUtf8());
        QJsonObject jsonObject = doc.object();

        ui->lcdNumberTemperature->display(jsonObject.value(QString("temperature_C")).toDouble());
        ui->lcdNumberHumidite->display(jsonObject.value(QString("humidity")).toDouble());


        qDebug() << jsonObject.value(QString("battery"));
        qDebug() << jsonObject.value(QString("direction_deg"));
        qDebug() << jsonObject.value(QString("gust"));

        qDebug() << jsonObject.value(QString("id"));

        qDebug() << jsonObject.value(QString("time"));
        qDebug() << jsonObject.value(QString("rain"));
        qDebug() << jsonObject.value(QString("speed"));
        chaine.clear();
    }


}
