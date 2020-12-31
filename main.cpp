#include "qtsgraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTSGraph w(1024,768);
    w.show();
    return a.exec();
}

void QTSGraph::PaintBox()
{
    // Тут рисовать

    PutPixel(100,100);
    Delay(2000);
    PutPixel(300,100);
    int x=1;
    while(!MouseClicked() && x < 1024)
    {
        PutPixel(x,50);
        x+=1;
        Delay(200);
    }

    // Конец рисования
}
