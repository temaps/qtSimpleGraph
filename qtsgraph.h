#include <QMainWindow>
#include <QPainter>
#include <QDesktopWidget>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class QTSGraph; }
QT_END_NAMESPACE

class QTSGraph : public QMainWindow
{
    Q_OBJECT

public:
    QTSGraph(int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr);
    ~QTSGraph();
    void putpixel(int x, int y, Qt::GlobalColor c = Qt::red);
    void delay(int ms = 1000);

private slots:
    void slotstarttimer();

private:
    Ui::QTSGraph *ui;
    QPixmap   m_Pixmap;
    QTimer *starttimer;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
};
