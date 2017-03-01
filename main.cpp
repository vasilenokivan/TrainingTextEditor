#include "mainwindow.h"
#include <QApplication>
#include <QLatin1String>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if(argc>1)
    {
        if(argv[1]!=0)
        {
            //w.myOpenFile(QString (argv[1]));
            w.myOpenFile(QString (QLatin1String(argv[1])));
            //w.myArgument=QString (QLatin1String(argv[1]));
        }
    }

    return a.exec();
}
