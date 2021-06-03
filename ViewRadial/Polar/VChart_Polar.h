#ifndef VCHART_POLAR_H
#define VCHART_POLAR_H

#include "Channels/Channel_Polar.h"
#include "ViewRadial/VChart_Radial.h"

class VChart_Polar : public VChart_Radial
{
    Q_OBJECT
public:
    explicit VChart_Polar(QWidget *parent = nullptr);

    void AddChannel(QString Title = "", Enum_PointShape PointShape = Shape_Point,
            QColor PointColor = Qt::red,
            double PointSize = 1.0,
            bool ShowLabels = true,
            int FadeoutDuration = -1);

    void AddPoints(int Idx, const QList<QPointF> &pnt);
    void AddPoints(int Idx, const QList<QPointF> &Points, const QList<QString> &Labels);

protected:
    virtual void paintGL(){}
    void            resizeGL(int w, int h);
};

#endif // VCHART_POLAR_H
