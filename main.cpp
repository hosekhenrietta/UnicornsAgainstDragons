#include "unicornsagainstdragons.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UnicornsAgainstDragons w;
    w.show();
    return a.exec();
}
