#include "../qtsgraph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Задаётся размер и положение окна
     * (int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr)
     * В случае отрицательного значения x или y, окно создаётся в центре экрана.
     */
    QTSGraph w(1024, 768);

    w.show();
    return a.exec();
}

void QTSGraph::PaintBox()
{
    // Начало рисования

    SetColor(0x00AAAAAA);
    Line(120, 120, 135, 260);
    SetWidth(5);
    SetColor(clBlue);
    Line(110, 110, 125, 250);
    PutPixel(100, 100, 0x00FF0000, 10);
    Delay(2000);
    PutPixel(300, 100);
    int x = 1;
    while(!MouseClicked() && x < 1024)
    {
        PutPixel(x, 50, 0x555555+x*16, 5);
        x += 1;
        Delay(1);
    }

    // Конец рисования
}
