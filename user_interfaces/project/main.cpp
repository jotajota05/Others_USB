#include <QtGui/QApplication>
#include "arepera.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arepera w;
    w.show();
    return a.exec();
}
