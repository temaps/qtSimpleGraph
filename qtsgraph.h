/*
"qtSimpleGraph" - Проект для изучения машинной графики на основе последовательного рисования примитивов

Copyright (c) 2020 Проскурнев Артем Сергеевич

Этот файл — часть проекта qtSimpleGraph.

qtSimpleGraph - свободная программа: вы можете перераспространять ее и/или
изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
в каком она была опубликована Фондом свободного программного обеспечения;
либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
версии.

Весы распространяется в надежде, что она будет полезной,
но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
общественной лицензии GNU.

Вы должны были получить копию Стандартной общественной лицензии GNU
вместе с этой программой. Если это не так, см.
<http://www.gnu.org/licenses/>.

This file is part of qtSimpleGraph.

qtSimpleGraph is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Vesi is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Vesi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QDesktopWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>
#include <string>
#include <QDebug>
#include <math.h>

#define clRed       0xFF0000
#define clGreen     0x00FF00
#define clBlue      0x0000FF
#define clBlack     0x000000
#define clWhite     0xFFFFFF
#define clYellow    0xFFFF00
#define clMagenta   0xFF00FF
#define clCyan      0x00FFFF

struct TPixel
{
    int x, y;
    unsigned int color;
};

class QTSGraph : public QMainWindow
{
    Q_OBJECT

public:
    QTSGraph(int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr);
    ~QTSGraph();

    bool SwapYAxis = false;

    void ShowAxes();
    void HideAxes();

    void Circle(int x, int y, int radius);
    void Delay(int ms = 1000);
    void Ellipse(int x1, int y1, int x2, int y2);
    QRgb GetPixel(int x, int y);
    void Line(int x1, int y1, int x2, int y2);
    bool KeyPressed();
    bool MouseClicked();
    void OutTextXY(int x, int y, std::string caption);
    void PutPixel(int x, int y, QRgb c = 0x00000000, int PenWidth = 1);
    int ReadKey();
    int ReadMouseButton();
    TPixel ReadMousePosition();
    void Rectangle(int x1, int y1, int x2, int y2);
    void SetColor(const QColor &c = Qt::black);
    void SetColor(const QRgb c = 0x00000000);
    void SetFillStyle(int Pattern, QRgb Color); // Стиль и цвет заливки
    /*
        0 - NoBrush
        1 - SolidPattern
        2 - Dense1Pattern
        3 - Dense2Pattern
        4 - Dense3Pattern
        5 - Dense4Pattern
        6 - Dense5Pattern
        7 - Dense6Pattern
        8 - Dense7Pattern
        9 - HorPattern
        10 - VerPattern
        11 - CrossPattern
        12 - BDiagPattern
        13 - FDiagPattern
        14 - DiagCrossPattern
        15 - LinearGradientPattern
        16 - RadialGradientPattern
        17 - ConicalGradientPattern
     */
    void SetPenStyle(int PenWidth, int PenStyle = 1); // Толщина и стиль линии
    /*
        0 - NoPen
        1 - SolidLine
        2 - DashLine
        3 - DotLine
        4 - DashDotLine
        5 - DashDotDotLine
     */
    void SetPenWidth(int PenWidth);
    void SetTextStyle(int CharSize, int Direction = 0, int idFont = 0);
    /*
        0 - serif
        1 - sans
        2 - mono
     */

private slots:
    void slotResetTimer();
    void slotStartTimer();

private:
    bool AxesVisible = false;
    bool EventMouseClicked = false;
    bool EventKeyPressed = false;
    int IDPressedKey = -1;
    int IDMouseButton = -1;
    int ResetInterval;
    int TextDirection = 0;
    QPoint LastMouseClickPosition;

    QBrush Brush;
    QPixmap Canvas;
    QFont Font;
    QPen Pen;
    QTimer *ResetTimer;
    QTimer *StartTimer;

    void PaintBox();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event)  override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};
