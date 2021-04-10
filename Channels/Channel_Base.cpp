#include "Channel_Base.h"

Channel_Base::Channel_Base(QObject *parent) : QObject(parent)
{
    m_IsVisible = true;
    m_ShowLabels = false;
    m_Title = "";
    m_PointColor = Qt::red;
    m_LineColor = Qt::green;
}

QString Channel_Base::Title() const
{
    return m_Title;
}

void Channel_Base::setTitle(const QString &Title)
{
    m_Title = Title;
}

bool Channel_Base::IsVisible() const
{
    return m_IsVisible;
}

void Channel_Base::setIsVisible(bool IsVisible)
{
    m_IsVisible = IsVisible;
}

bool Channel_Base::ShowLabels() const
{
    return m_ShowLabels;
}

QColor Channel_Base::PointColor() const
{
    return m_PointColor;
}

void Channel_Base::setPointColor(const QColor &PointColor)
{
    m_PointColor = PointColor;
}

QColor Channel_Base::LineColor() const
{
    return m_LineColor;
}

void Channel_Base::setLineColor(const QColor &LineColor)
{
    m_LineColor = LineColor;
}

void Channel_Base::setShowLabels(bool ShowLabels)
{
    m_ShowLabels = ShowLabels;
}
