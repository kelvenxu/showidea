#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void drawBaseLine(QPainter *painter);
    void drawCurve(QPainter *painter);
    void drawRectangle(QPainter *painter);
    void drawEllip(QPainter *painter);
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent*event);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);

protected slots:
    void switchMode();

private:
    enum DrawShape{BASELINE, CURVE, RECT, ELLIPSE} drawShape;
    bool isDrawLine;
    bool isDrawCurve;
    bool isDrawRect;
    bool isDrawEllipse;
    QPixmap pixmap;
    QPixmap screenPixmap;
    QPointF startPoint;
    QPointF endPoint;
    QPen pen;
    QCursor cursor;
};

#endif // MAINWINDOW_H
