#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScreen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    drawShape = BASELINE;
    pen = QPen(Qt::green, 5);
    cursor = QCursor(QPixmap(":/images/pencil.png"));
    setCursor(cursor);
    isDrawLine = false;
    isDrawCurve = false;
    isDrawRect = false;
    isDrawEllipse = false;

    QPushButton *startBtn = new QPushButton("Hide", this);

    connect(startBtn, SIGNAL(clicked()), this, SLOT(switchMode()));

    setWindowIcon(QIcon(":/images/idea48.png"));

    setWindowTitle("ShowIdea");

    showFullScreen();
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QScreen *screen = QGuiApplication::primaryScreen();

    pixmap = screen->grabWindow(QApplication::desktop()->winId(), 0, 0, -1, -1);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setPen(pen);

    switch(drawShape)
    {
    case BASELINE:
        drawBaseLine(&painter);
        break;
    case CURVE:
        drawCurve(&painter);
        break;
    case RECT:
        drawRectangle(&painter);
        break;
    case ELLIPSE:
        drawEllip(&painter);
        break;
    default:
        break;
    }

    QPainter p(this);
    p.drawPixmap(rect(), pixmap);
    isDrawLine = false;
    isDrawCurve = false;
    isDrawRect = false;
    isDrawEllipse = false;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    pixmap = QPixmap(size());
    screenPixmap = QPixmap(size());
}

void MainWindow::drawBaseLine(QPainter *painter)
{
    if(isDrawLine)
    {
        painter->drawPixmap(rect(), screenPixmap);
        painter->drawLine(startPoint, endPoint);
    }
}

void MainWindow::drawCurve(QPainter *painter)
{
    if(isDrawCurve)
        painter->drawLine(startPoint, endPoint);
}

void MainWindow::drawRectangle(QPainter *painter)
{
    if(isDrawRect)
    {
        QRectF rectf = QRectF(startPoint, endPoint);
        painter->drawPixmap(rect(), screenPixmap);
        painter->drawRect(rectf);
    }
}

void MainWindow::drawEllip(QPainter *painter)
{
    if(isDrawEllipse)
    {
        QRectF rectf = QRectF(startPoint, endPoint);
        painter->drawPixmap(rect(), screenPixmap);
        painter->drawEllipse(rectf);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        startPoint = event->pos();
        screenPixmap = pixmap;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endPoint = event->pos();

        switch(drawShape)
        {
        case BASELINE:
            isDrawLine = true;
            repaint();
            break;
        case CURVE:
            isDrawCurve = true;
            repaint();
            startPoint = endPoint;
            break;
        case RECT:
            isDrawRect = true;
            repaint();
            break;
        case ELLIPSE:
            isDrawEllipse = true;
            repaint();
            break;
        default:
            break;
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isDrawLine = true;
        isDrawCurve = true;
        isDrawRect = true;
        isDrawEllipse = true;
        repaint();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_B:
        {
            if(event->modifiers() & Qt::ControlModifier)
            {
                pen.setColor(Qt::blue);
                cursor = QCursor(QPixmap(":/sunsong/images/blue.png"));
                setCursor(cursor);
            }
            else
                drawShape = BASELINE;
        }
        break;
    case Qt::Key_C:
        drawShape = CURVE;
        break;
    case Qt::Key_R:
        {
            if(event->modifiers() & Qt::ControlModifier)
            {
                pen.setColor(Qt::red);
                cursor = QCursor(QPixmap(":/sunsong/images/red.png"));
                setCursor(cursor);
            }
            else
                drawShape = RECT;
        }
        break;
    case Qt::Key_E:
        drawShape = ELLIPSE;
        break;
    case Qt::Key_G:
        {
            if(event->modifiers() & Qt::ControlModifier)
            {
                pen.setColor(Qt::green);
                cursor = QCursor(QPixmap(":/sunsong/images/green.png"));
                setCursor(cursor);
            }
        }
        break;
    default:
        break;
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    update();
}

void MainWindow::switchMode()
{
    if (isFullScreen())
    {
        showMinimized();
    }
    else
    {
        showFullScreen();
    }

}
