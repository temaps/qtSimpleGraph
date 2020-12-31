#include "qtsgraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTSGraph w(1024,768);
    w.show();
    return a.exec();
}

void QTSGraph::slotstarttimer()
{
    // Тут рисовать

    putpixel(100,100);
    delay(2000);
    putpixel(300,100);

    // Конец рисования
    starttimer->stop();
}
