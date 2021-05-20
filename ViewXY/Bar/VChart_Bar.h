#ifndef VCHART_BAR_H
#define VCHART_BAR_H

#include "ViewXY/VChart_XY.h"
#include "Channels/Channel_Bar.h"

class VChart_Bar : public VChart_XY
{
    Q_OBJECT
public:
    explicit VChart_Bar(QWidget *parent = nullptr);

    void AddChannel(QString Title = "", int BarCount = 4, Enum_Orientation Orientation = Orien_Verical, QColor BarColor = Qt::red, double LineWidth = 2.0);

    void SetPointsForHistogram(int ChnlIdx, const QVector<QPointF>& Points, bool update = true);

    void SetPointsForBarItems(int ChnlIdx, const QVector<QPointF>& Points, bool update = true);

private:
    const double m_HistStep = 0.1;
};

#endif // VCHART_BAR_H
