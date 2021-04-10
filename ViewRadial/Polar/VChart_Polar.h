#ifndef VCHART_POLAR_H
#define VCHART_POLAR_H

#include "Channels/Channel_Polar.h"
#include "ViewRadial/VChart_Radial.h"

class VChart_Polar : public VChart_Radial
{
    Q_OBJECT
public:
    explicit VChart_Polar(QWidget *parent = nullptr);

    void AddChannel(
            QString Title = "",
            QColor PointColor = Qt::red,
            double PointSize = 1.0,
            bool ShowLabels = true,
            int FadeoutDuration = -1);

    void AddPoints(int Idx, const QVector<QPointF>& pnt);
    void AddPoints(int Idx, const QVector<QPointF>& Points, const QVector<QString> &Labels);

protected:
    virtual void paintGL(){}
    void            resizeGL(int w, int h);
};

#endif // VCHART_POLAR_H
