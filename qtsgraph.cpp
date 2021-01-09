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

#include "qtsgraph.h"

void QTSGraph::Delay(int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
}

void QTSGraph::Ellipse(int x1, int y1, int x2, int y2)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    painter.setBrush(Brush);
    if(SwapYAxis) painter.drawEllipse(x1, Canvas.height() - y1 - abs(y2 - y1) - 1, abs(x2-x1), abs(y2-y1));
    else  painter.drawEllipse(x1, y1, abs(x2-x1), abs(y2-y1));
    update();
}

QRgb QTSGraph::GetPixel(int x, int y)
{
    if(SwapYAxis) y = Canvas.height() - y - 1;
    return Canvas.toImage().pixelColor(x, y).rgba();
}
QTSGraph::QTSGraph(int w, int h, int x, int y, QWidget *parent)
    : QMainWindow(parent)
{
    if(x < 0 || y < 0)
    {
        QDesktopWidget desktop;
        QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
        QPoint center = rect.center(); //координаты центра экрана
        x = center.x() - w / 2;
        y = center.y() - h / 2;
    }
    this->setGeometry(x, y, w, h);
    this->setMinimumHeight(h);
    this->setMinimumWidth(w);
    this->setMaximumHeight(h);
    this->setMaximumWidth(w);
    this->setWindowTitle("Рисунок");
    Canvas = QPixmap(w, h);
    Canvas.fill(Qt::white);
    QRgb DefaultColor = 0x00000000;
    Pen = QPen(QBrush(QColor(DefaultColor)), 1);
    Font = QFont();
    Brush = QBrush(QColor(DefaultColor),Qt::NoBrush);
    ResetInterval = 1000;
    ResetTimer = new QTimer();
    connect(ResetTimer, SIGNAL(timeout()), this, SLOT(slotResetTimer()));
    ResetTimer->start(ResetInterval);

    StartTimer = new QTimer();
    connect(StartTimer, SIGNAL(timeout()), this, SLOT(slotStartTimer()));
    StartTimer->start(500);
}

QTSGraph::~QTSGraph()
{
    // Деструктор
}

void QTSGraph::Circle(int x, int y, int radius)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    painter.setBrush(Brush);
    if(SwapYAxis) painter.drawEllipse(x - radius, Canvas.height() - (y - radius) - (radius * 2) - 1, radius * 2, radius * 2);
    else painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    update();
}

bool QTSGraph::MouseClicked()
{
    QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    bool m = EventMouseClicked;
    EventMouseClicked = false;
    return m;
}

void QTSGraph::OutTextXY(int x, int y, std::string caption)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    painter.setFont(Font);
    double r, b, sa, ca, sb, cb, xn, yn;
    if(SwapYAxis) y = Canvas.height() - y - 1;
    b = TextDirection*3.14159/180;
    r = sqrt(x * x + y * y);
    sa = y / r;
    ca = x / r;
    sb = sin(b);
    cb = cos(b);
    xn = r * (ca * cb - sa * sb);
    yn = r * (sa * cb + sb * ca);
    painter.translate(x - xn, y - yn);
    painter.rotate(TextDirection);
    painter.drawText(x, y, QString::fromStdString(caption));
    update();
}

void QTSGraph::PutPixel(int x, int y, QRgb c, int PenWidth)
{
    QPainter painter(&Canvas);
    painter.setPen(QPen(QBrush(QColor(c)), PenWidth));
    if(SwapYAxis) painter.drawPoint(x, Canvas.height() - y - 1);
    else painter.drawPoint(x, y);
    update();
}

int QTSGraph::ReadKey()
{
    if(IDPressedKey == -1)
    {
        while(!KeyPressed() && this->isVisible())
            Delay(1);
    }
    int t = IDPressedKey;
    IDPressedKey = -1;
    return t;
}

int QTSGraph::ReadMouseButton()
{
    if(IDMouseButton == -1)
    {
        while(!MouseClicked() && this->isVisible())
            Delay(1);
    }
    int t = IDMouseButton;
    IDMouseButton = -1;
    return t;
}

void QTSGraph::Rectangle(int x1, int y1, int x2, int y2)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    painter.setBrush(Brush);
    if(SwapYAxis) painter.drawRect(x1, Canvas.height() - y1 - abs(y2 - y1) - 1, x2 - x1, y2 - y1);
    else painter.drawRect(x1, y1, x2 - x1, y2 - y1);
    update();
}

void QTSGraph::SetColor(const QColor &c)
{
    Pen.setColor(c);
}

void QTSGraph::SetColor(const QRgb c)
{
    Pen.setColor(QColor(c));
}

void QTSGraph::SetFillStyle(int Pattern, QRgb Color)
{
    Brush.setStyle(Qt::BrushStyle(Pattern));
    Brush.setColor(QColor(Color));
}

void QTSGraph::SetPenStyle(int PenWidth, int PenStyle)
{
    Pen.setWidth(PenWidth);
    Pen.setStyle(Qt::PenStyle(PenStyle));
}

void QTSGraph::SetPenWidth(int PenWidth)
{
    Pen.setWidth(PenWidth);
}

void QTSGraph::SetTextStyle(int idFont, int Direction, int CharSize)
{
    QString f;
    if(idFont == 0) f = "serif";
    else if(idFont == 1) f = "sans";
    else if(idFont == 3) f = "mono";
    TextDirection = Direction;
    Font.setFamily(f);
    Font.setPointSize(CharSize);
}

void QTSGraph::Line(int x1, int y1, int x2, int y2)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    if(SwapYAxis) painter.drawLine(x1, Canvas.height() - y1 - 1, x2, Canvas.height() - y2 - 1);
    else painter.drawLine(x1, y1, x2, y2);
    update();
}

bool QTSGraph::KeyPressed()
{
    QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    bool m = EventKeyPressed;
    EventKeyPressed = false;
    return m;
}

void QTSGraph::slotStartTimer()
{
    StartTimer->stop();
    PaintBox();
}

void QTSGraph::slotResetTimer()
{
    ResetTimer->stop();
    EventKeyPressed = false;
    EventMouseClicked = false;
}

void QTSGraph::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, Canvas);
}

void QTSGraph::mousePressEvent(QMouseEvent *event)
{
    ResetTimer->stop();
    EventMouseClicked = true;
    if (event->buttons() & Qt::LeftButton)
    {
        // Левая кнопка
        IDMouseButton = 1;
    }
    else if (event->buttons() & Qt::RightButton)
    {
        // Правая кнопка
        IDMouseButton = 2;
    }
    else if (event->buttons() & Qt::MiddleButton)
    {
        // Средняя кнопка
        IDMouseButton = 3;
    }
    ResetTimer->start(ResetInterval);
}

void QTSGraph::keyPressEvent(QKeyEvent *event)
{
    ResetTimer->stop();
    EventKeyPressed = true;
    IDPressedKey = event->key();
    if (IDPressedKey == Qt::Key_Escape)
    {
        // Нажатие Esc
    }
    ResetTimer->start(ResetInterval);
}

void QTSGraph::closeEvent(QCloseEvent *event)
{
    //Закрытие окна
    delete ResetTimer;
    delete StartTimer;
    exit(0);
}
