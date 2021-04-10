#ifndef CHANNEL_LINE_H
#define CHANNEL_LINE_H

#include "Channel_Base.h"

class Channel_Line : public Channel_Base
{
    Q_OBJECT
public:
    explicit Channel_Line(QObject *parent = nullptr);

    double PointSize() const;
    void setPointSize(double PointSize);

    double LineSize() const;
    void setLineSize(double LineSize);

    bool ShowPoints() const;
    void setShowPoints(bool ShowPoints);

    QVector<vVertex> *Points();

private:
    double m_PointSize;
    double m_LineSize;
    bool m_ShowPoints;
    QVector<vVertex>* m_Points;

};

#endif // CHANNEL_LINE_H
