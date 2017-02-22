#include "inputdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputDialog w;
    w.show();

    return a.exec();
}
