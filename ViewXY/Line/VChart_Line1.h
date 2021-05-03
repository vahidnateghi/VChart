#ifndef VCHART_LINE1_H
#define VCHART_LINE1_H

#include "VChart_Line.h"

class VChart_Line1 : public VChart_Line
{
    Q_OBJECT
    Q_PROPERTY(int TestProp)
public:
    explicit VChart_Line1(QWidget *parent = nullptr);

protected:
    void paintGL();
};

#endif // VCHART_LINE1_H
