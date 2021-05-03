#include "Channel_Bar.h"

Channel_Bar::Channel_Bar(QObject *parent) : Channel_Base(parent)
{
    m_LineWidth = 3.0;
    m_BarCount = 4;
    m_Orientation = Orien_Verical;

    m_LineStarts = new QList<QPointF>();
    for( int i = 0; i < m_BarCount; i++ )
        m_LineStarts->append( QPointF( 0, 0 ) );
    m_LineLength = new QList<double>();
    for( int i = 0; i < m_BarCount; i++ )
        m_LineLength->append( 0 );
}

Channel_Bar::~Channel_Bar()
{
    delete m_LineStarts;
    delete m_LineLength;
}

double Channel_Bar::LineWidth() const
{
    return m_LineWidth;
}

void Channel_Bar::setLineWidth(double LineWidth)
{
    m_LineWidth = LineWidth;
}

int Channel_Bar::BarCount() const
{
    return m_BarCount;
}

void Channel_Bar::setBarCount(int BarCount)
{
    m_BarCount = BarCount;
    m_LineStarts->clear();
    for( int i = 0; i < m_BarCount; i++ )
        m_LineStarts->append( QPointF( 0, 0 ) );
    m_LineLength->clear();
    for( int i = 0; i < m_BarCount; i++ )
        m_LineLength->append( 0 );
}

Enum_Orientation Channel_Bar::Orientation() const
{
    return m_Orientation;
}

void Channel_Bar::setOrientation(const Enum_Orientation &Orientation)
{
    m_Orientation = Orientation;
}

QList<QPointF>* Channel_Bar::LineStarts() const
{
    return m_LineStarts;
}

QList<double> *Channel_Bar::LineLength() const
{
    return m_LineLength;
}
