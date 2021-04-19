#ifndef VCHART_HISTORGRAM_H
#define VCHART_HISTORGRAM_H

#include "ViewXY/VChart_XY.h"
#include "Channels/Channel_Bar.h"

class VChart_Historgram : public VChart_XY
{
    Q_OBJECT
public:
    explicit VChart_Historgram(QWidget *parent = nullptr);

    void AddChannel(QString Title = "", int BarCount = 4, Enum_Orientation Orientation = Orien_Verical, QColor BarColor = Qt::red, double LineWidth = 2.0);

    void AddPoints(int ChnlIdx, const QVector<QPointF>& Points, bool update = true);

private:
    const double m_HistStep = 0.1;
};

#endif // VCHART_HISTORGRAM_H
