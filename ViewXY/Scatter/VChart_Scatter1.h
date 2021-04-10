#ifndef VCHART_SCATTER1_H
#define VCHART_SCATTER1_H

#include "VChart_Scatter.h"

class VChart_Scatter1 : public VChart_Scatter
{
    Q_OBJECT
public:
    explicit VChart_Scatter1(QWidget *parent = nullptr);

protected:
    void paintGL();
};

#endif // VCHART_SCATTER1_H
