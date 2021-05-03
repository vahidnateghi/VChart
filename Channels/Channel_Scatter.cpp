#include "Channel_Scatter.h"

Channel_Scatter::Channel_Scatter(QObject *parent) : Channel_Base(parent)
{
    m_Groups = new QVector<ScatterGroup *>();

    m_PointShape = Shape_Point;
    m_FadeDuration = 0;
    m_PointSizeX = 1.0;
    m_PointSizeY = 1.0;
}

Enum_PointShape Channel_Scatter::PointShape() const
{
    return m_PointShape;
}

void Channel_Scatter::PrepToRemove()
{

}

double Channel_Scatter::PointSizeX() const
{
    return m_PointSizeX;
}

void Channel_Scatter::setPointSizeX(double PointSizeX)
{
    m_PointSizeX = PointSizeX;
}

double Channel_Scatter::PointSizeY() const
{
    return m_PointSizeY;
}

void Channel_Scatter::setPointSizeY(double PointSizeY)
{
    m_PointSizeY = PointSizeY;
}

QVector<ScatterGroup *> *Channel_Scatter::Groups() const
{
    return m_Groups;
}

QVector<QString> Channel_Scatter::Labels() const
{
    return m_Labels;
}

void Channel_Scatter::setLabels(const QVector<QString> &Labels)
{
    m_Labels = Labels;
}

void Channel_Scatter::Clear()
{
    for( int i = 0; i < m_Groups->count(); i++ )
        delete m_Groups->at(i);

    m_Groups->clear();
}

void Channel_Scatter::setPointShape(const Enum_PointShape &PointShape)
{
    m_PointShape = PointShape;
}

int Channel_Scatter::FadeDuration() const
{
    return m_FadeDuration;
}

void Channel_Scatter::setFadeDuration(int FadeDuration)
{
    m_FadeDuration = FadeDuration;
}
