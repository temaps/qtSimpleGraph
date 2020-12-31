#include "qtsgraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Задаётся размер и положение окна
     * (int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr)
     * В случае отрицательнго значения x или y, окно создаётся в центре экрана.
     */
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
