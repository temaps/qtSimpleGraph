#include "qtsgraph.h"
using namespace Qt;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * Задаётся размер и положение окна
     * (int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr)
     * В случае отрицательного значения x или y, окно создаётся в центре экрана.
     */
    QTSGraph w(800, 600);

    w.show();
    return a.exec();
}

void QTSGraph::PaintBox()
{
    // Начало рисования

    SetColor(clGreen);
    Line(0, 0, 800, 600);
    SetColor(0xFF0000);
    Line(800, 0, 0, 600);

    // Конец рисования
}
