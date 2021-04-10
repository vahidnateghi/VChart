#ifndef CHANNEL_POLAr_H
#define CHANNEL_POLAr_H

#include <QGLWidget>
#include "Channel_Base.h"

class Channel_Polar : public Channel_Base
{
    Q_OBJECT
public:
    explicit Channel_Polar(QObject *parent = nullptr);

    void setPointShape(const Enum_PointShape &PointShape);
    void setFadeDuration(int FadeDuration);

    int FadeDuration() const;
    Enum_PointShape PointShape() const;

    void PrepToRemove();

    double PointSizeX() const;
    void setPointSizeX(double PointSizeX);

    double PointSizeY() const;
    void setPointSizeY(double PointSizeY);

    QVector<ScatterGroup*> *Groups() const;

    QVector<QString> Labels() const;
    void setLabels(const QVector<QString> &Labels);

private:
    Enum_PointShape m_PointShape;
    int m_FadeDuration;
    double m_PointSizeX;
    double m_PointSizeY;

    QVector<QString> m_Labels;
    QVector<ScatterGroup*> *m_Groups;

};

#endif // CHANNEL_POLAR_H
