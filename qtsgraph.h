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

#define clRed       0x00FF0000
#define clGreen     0x0000FF00
#define clBlue      0x000000FF
#define clBlack     0x00000000
#define clWhite     0x00FFFFFF

class QTSGraph : public QMainWindow
{
    Q_OBJECT

public:
    QTSGraph(int w = 640, int h = 480, int x = -1, int y = -1, QWidget *parent = nullptr);
    ~QTSGraph();

    void Circle(int x, int y, int radius);
    void Delay(int ms = 1000);
    void Line(int x1, int y1, int x2, int y2);
    bool KeyPressed();
    bool MouseClicked();
    void OutTextXY(int x, int y, std::string caption);
    void PutPixel(int x, int y, QRgb c = 0x00000000, int PenWidth = 1);
    int ReadKey();
    void Rectangle(int x1, int y1, int x2, int y2);
    void SetColor(QRgb c);
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

private slots:
    void slotStartTimer();

private:
    QPixmap Canvas;
    QTimer *StartTimer;
    bool EventMouseClicked = false;
    bool EventKeyPressed = false;
    int IDPressedKey = -1;
    void PaintBox();
    QPen Pen;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event)  override;
};
