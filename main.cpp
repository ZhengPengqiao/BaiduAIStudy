#include "mainwindow.h"
#include <QApplication>
#include <QLatin1String>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile qssFile(":/assert/qt.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qDebug()<< qssFile.fileName() << "Open OK";
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    else
    {
        qDebug()<< qssFile.fileName() << "Open Err";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
