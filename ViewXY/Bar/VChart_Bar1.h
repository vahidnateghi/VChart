#ifndef VCHART_BAR1_H
#define VCHART_BAR1_H

#include "VChart_Bar.h"

class VChart_Bar1 : public VChart_Bar
{
    Q_OBJECT
public:
    explicit VChart_Bar1(QWidget *parent = nullptr);

protected:
    void paintGL();
};

#endif // VChart_Bar1_H
