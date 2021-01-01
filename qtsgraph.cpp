#include "qtsgraph.h"

void QTSGraph::Delay(int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
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
    this->setWindowTitle("Рисунок");
    Canvas = QPixmap(w, h);
    Canvas.fill(Qt::white);
    QRgb DefaultColor = 0x00000000;
    Pen = QPen(QBrush(QColor(DefaultColor)), 1);
    StartTimer = new QTimer();
    connect(StartTimer, SIGNAL(timeout()), this, SLOT(slotStartTimer()));
    StartTimer->start(500);
}

QTSGraph::~QTSGraph()
{
    // Деструктор
}

bool QTSGraph::MouseClicked()
{
    bool m = EventMouseClicked;
    EventMouseClicked = false;
    return m;
}

void QTSGraph::PutPixel(int x, int y, QRgb c, int PenWidth)
{
    QPainter painter(&Canvas);
    painter.setPen(QPen(QBrush(QColor(c)), PenWidth));
    painter.drawPoint(x, y);
    update();
}

void QTSGraph::SetColor(QRgb c)
{
    Pen.setColor(QColor(c));
}

void QTSGraph::SetWidth(int PenWidth)
{
    Pen.setWidth(PenWidth);
}

void QTSGraph::Line(int x1, int y1, int x2, int y2)
{
    QPainter painter(&Canvas);
    painter.setPen(Pen);
    painter.drawLine(x1, y1, x2, y2);
    update();
}

void QTSGraph::slotStartTimer()
{
    StartTimer->stop();
    PaintBox();
}

void QTSGraph::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, Canvas);
}

void QTSGraph::mousePressEvent(QMouseEvent *event)
{
    EventMouseClicked = true;
    if (event->buttons() & Qt::LeftButton)
    {
        // Левая кнопка
    }
    else if (event->buttons() & Qt::RightButton)
    {
        // Правая кнопка
    }
}
