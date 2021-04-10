#ifndef VCHART_SCATTER_H
#define VCHART_SCATTER_H

#include "ViewXY/VChart_XY.h"
#include "Channels/Channel_Scatter.h"

class VChart_Scatter : public VChart_XY
{
    Q_OBJECT
public:
    explicit VChart_Scatter(QWidget *parent = nullptr);

    void AddChannel(QString Title = "",
                    QColor Color = Qt::red,
                    Enum_PointShape PointShape = Shape_Point,
                    double PntSizeX = 5,
                    double PntSizeY = 5,
                    int FadeoutDuration = -1,
                    bool ShowLabels = true);

    void AddPoints(int Idx, const QVector<QPointF>& pnt);
    void AddPoints(int Idx, const QVector<QPointF>& Points, const QVector<QString> &Labels);


protected:

    virtual void paintGL() {}


};

#endif // VCHART_SCATTER_H
