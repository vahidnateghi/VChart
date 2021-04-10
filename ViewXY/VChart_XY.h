#ifndef VCHART_XY_H
#define VCHART_XY_H

#include "VChart_Base.h"
#include "Channels/Channel_Line.h"

class VChart_XY : public VChart_Base
{
    Q_OBJECT
public:
    explicit VChart_XY(QWidget *parent = nullptr);

    void AddChannel(
            QString Title = "",
            QColor PointColor = Qt::red,
            QColor LineColor = Qt::green,
            double PointSize = 1,
            double LineSize = 1,
            bool ShowPoints = false);


    void Clear();
};

#endif // VCHART_XY_H
