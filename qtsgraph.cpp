#include "qtsgraph.h"
#include "ui_qtsgraph.h"

void QTSGraph::delay(int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QTSGraph::QTSGraph(int w, int h, int x, int y, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTSGraph)
{
    ui->setupUi(this);
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
    m_Pixmap = QPixmap(w, h);
    m_Pixmap.fill(Qt::white);
    starttimer = new QTimer();
    connect(starttimer, SIGNAL(timeout()), this, SLOT(slotstarttimer()));
    starttimer->start(500);
}

QTSGraph::~QTSGraph()
{
    delete ui;
}

void QTSGraph::putpixel(int x, int y, Qt::GlobalColor c)
{
    QPainter painter(&m_Pixmap);
    painter.setPen(QPen(QBrush(QColor(c)), 5 ));
    painter.drawPoint( x, y );
    update();
}

void QTSGraph::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0,m_Pixmap);
}

void QTSGraph::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        // Левая кнопка
    }
    else if (event->buttons() & Qt::RightButton)
    {
        // Правая кнопка
    }
}
