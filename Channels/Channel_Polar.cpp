#include "Channel_Polar.h"

Channel_Polar::Channel_Polar(QObject *parent) : Channel_Base(parent)
{
    m_Groups = new QList<ScatterGroup *>();

    m_PointShape = Shape_Point;
    m_FadeDuration = 0;
    m_PointSizeX = 1.0;
    m_PointSizeY = 1.0;
}

Enum_PointShape Channel_Polar::PointShape() const
{
    return m_PointShape;
}

void Channel_Polar::PrepToRemove()
{

}

double Channel_Polar::PointSizeX() const
{
    return m_PointSizeX;
}

void Channel_Polar::setPointSizeX(double PointSizeX)
{
    m_PointSizeX = PointSizeX;
}

double Channel_Polar::PointSizeY() const
{
    return m_PointSizeY;
}

void Channel_Polar::setPointSizeY(double PointSizeY)
{
    m_PointSizeY = PointSizeY;
}

QList<ScatterGroup *> *Channel_Polar::Groups() const
{
    return m_Groups;
}

QList<QString> Channel_Polar::Labels() const
{
    return m_Labels;
}

void Channel_Polar::setLabels(const QList<QString> &Labels)
{
    m_Labels = Labels;
}

void Channel_Polar::setPointShape(const Enum_PointShape &PointShape)
{
    m_PointShape = PointShape;
}

int Channel_Polar::FadeDuration() const
{
    return m_FadeDuration;
}

void Channel_Polar::setFadeDuration(int FadeDuration)
{
    m_FadeDuration = FadeDuration;
}
