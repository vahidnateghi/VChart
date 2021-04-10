#ifndef VCHART_POLAR1_H
#define VCHART_POLAR1_H

#include "VChart_Polar.h"

class VChart_Polar1 : public VChart_Polar
{
    Q_OBJECT
public:
    explicit VChart_Polar1(QWidget *parent = nullptr);

protected:
    void paintGL();

};

#endif // VCHART_POLAR1_H
