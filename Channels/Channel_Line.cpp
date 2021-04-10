#include "Channel_Line.h"

Channel_Line::Channel_Line(QObject *parent) : Channel_Base(parent)
{
    m_Points = new QVector<vVertex>();

    m_PointSize = 1.0;
    m_LineSize = 1.0;
    m_ShowPoints = false;
}

double Channel_Line::PointSize() const
{
    return m_PointSize;
}

void Channel_Line::setPointSize(double PointSize)
{
    m_PointSize = PointSize;
}

double Channel_Line::LineSize() const
{
    return m_LineSize;
}

void Channel_Line::setLineSize(double LineSize)
{
    m_LineSize = LineSize;
}

bool Channel_Line::ShowPoints() const
{
    return m_ShowPoints;
}

void Channel_Line::setShowPoints(bool ShowPoints)
{
    m_ShowPoints = ShowPoints;
}

QVector<vVertex> *Channel_Line::Points()
{
    return m_Points;
}

