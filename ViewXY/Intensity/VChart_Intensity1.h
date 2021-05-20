#ifndef VCHART_INTENSITY1_H
#define VCHART_INTENSITY1_H

#include <VChart/ViewXY/Intensity/VChart_Intensity.h>

class VChart_Intensity1 : public VChart_Intensity
{
    Q_OBJECT
public:
    explicit VChart_Intensity1(QWidget *parent = nullptr);

protected:
    void paintGL();

};

#endif // VCHART_INTENSITY1_H


// 7.5 --> 820
