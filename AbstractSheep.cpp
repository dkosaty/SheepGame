#include "AbstractSheep.h"

#include "GameField.h"

#include <QApplication>
#include <QDebug>
#include <QStylePainter>
#include <QStyleOption>
#include <math.h>

void AbstractSheep::rotate()
{
    m_degree += 3;
    m_rotate = true;
}

void AbstractSheep::rotateOff()
{
    m_rotate = false;
}

void AbstractSheep::paintEvent(QPaintEvent *)
{
    if (m_rotate)
    {
    setAttribute(Qt::WA_TranslucentBackground, true);
    QStyleOption o;
    o.initFrom(this);
    QStylePainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing, true);

    painter.translate(rect().center());
    painter.rotate(m_degree);
    painter.translate(-rect().center());
    style()->drawPrimitive(QStyle::PE_Widget, &o, &painter, this);
    }
}

AbstractSheep::AbstractSheep(QWidget *parent) :
    QWidget(parent), m_rotate(false), m_degree(0)
{
    m_gameField = 0;

}

void AbstractSheep::setGameField(GameField *gamefield)
{
    m_gameField = gamefield;
    this->setParent(m_gameField);
}

bool AbstractSheep::tick()
{
    if  (fabs(m_vx) < 0.1 && fabs(m_vy) < 0.1)
        return false;

    m_x += m_vx;
    m_y += m_vy;

    if (m_x < 0)
    {
        m_x *= -1.0;
        m_vx *= -1.0;
    }
    if (m_x + width() > m_gameField->width())
    {
        m_x = m_gameField->width() - width();
        m_vx *= -1.0;
    }

    if (m_y < 0)
    {
        m_y *= -1.0;
        m_vy *= -1.0;
    }
    if (m_y + height() > m_gameField->height())
    {
        m_y = m_gameField->height() - height();
        m_vy *= -1.0;
    }

////    static int n = 0;
////    static int k = 0;
////    k = (k + 1) % 4;

////    QString style = QString(""
////                            ""
////                            "QWidget#sheep {"
////                            "background:url(:img/texture/Rosy_sheep/Real_run_small/rosy_step_%0.png);"
////                            "}"
////                            "").arg(k);

////    if (n++ % 3 == 0)
////    {
//////        setStyleSheet(style);
////    }


//    const QVector<QPoint> *points = m_gameField->points();

//    for (int i = 0; i < points->size() / 2;  ++i)
//    {
//        QVector<QPoint> line;
//        QPoint a = points->at(2 * i);
//        QPoint b = points->at(2 * i + 1);
//        QPoint n(b.y() - a.y(),b.x() - a.x());
//        n /= n.manhattanLength();
//        n *= 2;
//        QPoint c(b);
//        c += n;
//        QPoint d(a);
//        d += n;
////        QPoint c(a.x() + b.y() - a.y(), a.y() + b.x() - a.x());
////        QPoint d(b.x() + b.y() - a.y(), b.y() + b.x() - a.x());

//        line.append(a);
//        line.append(b);
//        line.append(c);
//        line.append(d);
//        QPolygon p(line);
//        QRegion r(p);


//        if (r.intersects(geometry()))
//        {
//            m_vx *= -1.0;
//            m_vy *= -1.0;
//            break;
////            return true;
//        }

//    }

    QList<QWidget*> *m_sweats = m_gameField->getSweets();
    foreach(QWidget* w, *m_sweats)
    {
        if (w != 0 && geometry().intersects(w->geometry()))
        {
            w->hide();
            w->deleteLater();
            m_sweats->removeAll(w);
            m_gameField->decCount();
//            w = 0;
        }
    }


    move(m_x, m_y);
    m_vx *= 0.98;
    m_vy *= 0.98;


    return true;
}

int AbstractSheep::vx() const
{
    return m_vx;
}

void AbstractSheep::setVx(int vx)
{
    m_vx = vx;
}
int AbstractSheep::vy() const
{
    return m_vy;
}

void AbstractSheep::setVy(int vy)
{
    m_vy = vy;
}

double AbstractSheep::y() const
{
    return m_y;
}

void AbstractSheep::setY(double y)
{
    m_y = y;
    move(m_x, m_y);
}

void AbstractSheep::setPos(double x, double y)
{
    m_x = x;
    m_y = y;
    move(m_x, m_y);
    qDebug() << x << y;
}

double AbstractSheep::x() const
{
    return m_x;
}

void AbstractSheep::setX(double x)
{
    m_x = x;
    move(m_x, m_y);
}


