#ifndef VCHART_LINE_H
#define VCHART_LINE_H

#include "ViewXY/VChart_XY.h"

class VChart_Line : public VChart_XY
{
    Q_OBJECT
public:
    explicit VChart_Line(QWidget *parent = nullptr);

    void SetPoints(int Idx, const QVector<double>& XPoints, const QVector<double>& YPoints);
    void SetPoints(int Idx, const QVector<long long>& YPoints);
};

#endif // VCHART_LINE_H
