#include "matrix.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Matrix w;
    w.show();
    return a.exec();
}
