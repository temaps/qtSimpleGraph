#include "../qtsgraph.h"
#include <iostream>
using namespace std;
using namespace Qt;

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

    SetColor(clRed);
    Circle(300, 300, 100);
    int k;
    k = ReadKey();
    OutTextXY(20, 40, "Код нажатой клавиши: " + to_string(k));
    if(k == 16777220)
    {
        PutPixel(300, 300, clRed, 3);
        for(int i = 0; i <= 5; i++)
        {
            SetPenStyle(1, 1);
            SetColor(clBlue);
            Rectangle(5, 390 + i * 20, 220, 410 + i * 20);
            SetColor(clBlack);
            OutTextXY(10, 405 + i * 20, to_string(i));
            SetPenStyle(1, i);
            Line(30, 400 + i * 20, 200, 400 + i * 20);
        }
        SetColor(0x00AAAAAA);
        Line(120, 120, 135, 260);
        SetPenWidth(5);
        SetColor(clBlue);
        Line(110, 110, 125, 250);
        PutPixel(100, 100, 0x00FF0000, 10);
        Delay(1000);
        PutPixel(300, 100);
        int x = 1;
        while(!MouseClicked() && x < 1024)
        {
            PutPixel(x, 50, 0x555555 + x * 16, 5);
            x += 1;
            Delay(10);
        }
    }

    // Конец рисования
}
