#ifndef GLINTENSITYGRID_H
#define GLINTENSITYGRID_H

//#include <QObject>
//#include <QWidget>
//#include <QOpenGLFunctions_3_0>
//#include <QGLWidget>
//#include <QMouseEvent>
//#include <QGLFormat>
//#include <QDebug>
#include <ViewXY/VChart_XY.h>
#include <Channels/Channel_Intensity.h>

class VChart_Intensity : public  VChart_XY
{
    Q_OBJECT
public:
    explicit VChart_Intensity(QWidget *parent = nullptr);
    ~VChart_Intensity();

    void AddChannel(QString Title, double MinX, double MaxX, double MinY, double MaxY, int XReso, int YReso, double MinVal, double MaxVal, QColor MinColor, QColor MaxColor );

public slots:
    void    SetValue(int Idx, int XIdx, int YIdx, double Val);
    void    SetValue(int Idx, double X, double Y, double Val);
    double  GetValue(int Idx, int XIdx, int YIdx);
    void    UpdatePoints(int Idx);
    void    PushUpPoints(int Idx);

private:
    bool    m_AddingChannel;
};

#endif // GLINTENSITYGRID_H
