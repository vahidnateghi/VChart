#ifndef VCHART_HISTOGRAM1_H
#define VCHART_HISTOGRAM1_H

#include "VChart_Historgram.h"

class VChart_Histogram1 : public VChart_Historgram
{
    Q_OBJECT
public:
    explicit VChart_Histogram1(QWidget *parent = nullptr);

protected:
    void paintGL();
};

#endif // VCHART_HISTOGRAM1_H
