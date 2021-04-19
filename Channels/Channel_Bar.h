#ifndef CHANNEL_BAR_H
#define CHANNEL_BAR_H

#include "Channel_Base.h"

class Channel_Bar : public Channel_Base
{
    Q_OBJECT
public:
    explicit Channel_Bar(QObject *parent = nullptr);
    ~Channel_Bar();

    double LineWidth() const;
    void setLineWidth(double LineWidth);

    int BarCount() const;
    void setBarCount(int BarCount);

    Enum_Orientation Orientation() const;
    void setOrientation(const Enum_Orientation &Orientation);

    QList<QPointF> *LineStarts() const;

    QList<double> *LineLength() const;

private:
    double m_LineWidth;
    int m_BarCount;
    Enum_Orientation m_Orientation;
    QList<QPointF> *m_LineStarts;
    QList<double> *m_LineLength;

};

#endif // CHANNEL_BAR_H
