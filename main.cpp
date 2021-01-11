#include "qtsgraph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Задаётся размер и положение окна
     * (int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr)
     * В случае отрицательного значения x или y, окно создаётся в центре экрана.
     */
    QTSGraph w(600, 600);

    w.show();
    return a.exec();
}

void QTSGraph::PaintBox()
{
    // Начало рисования

    ShowAxes();
    SetColor(clGreen);
    Line(0, 0, 600, 600);
    SetColor(0xFF0000);
    Line(600, 0, 0, 600);
    Rectangle(0, 0, 599, 599);
    QColor c = Qt::blue;
    SetColor(c);
    SetTextStyle(0, 45, 10);
    OutTextXY(70, 70, "Hello world!");
    SetTextStyle(1, 0, 20);
    OutTextXY(170, 50, "Кликните мышкой...");
    int m = ReadMouseButton();
    SetColor(clRed);
    SetTextStyle(1, 0, 20);
    if(m == 1) OutTextXY(150, 80, "Нажата левая кнопка");
    else if(m == 2) OutTextXY(150, 80, "Нажата правая кнопка");
    else if(m == 3) OutTextXY(150, 80, "Нажата средняя кнопка");
    else OutTextXY(150, 80, "Нажата неизвестная кнопка");
    SetTextStyle(2, 180, 30);
    OutTextXY(460, 550, "Hello world!");
    SetColor(0x999999);
    SetPenStyle(5);
    SetFillStyle(1, clMagenta);
    Ellipse(250, 280, 350, 320);

    // Конец рисования
}
