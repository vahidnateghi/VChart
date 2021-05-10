#ifndef VCHARTDEFINES_H
#define VCHARTDEFINES_H

#include <QSettings>
#include <QColor>
#include <QGLWidget>
#include <QDateTime>
#include <QtMath>

#define N(x)                                QString::number((x))
#define NH(x)                               QString::number((x), 16).toUpper().rightJustified(2, '0')
#define NN(x,n)                             QString::number((x)).rightJustified((n),'0')
#define ROUND(x,y)                          floor((x) * pow(10., (y)) + .5) / pow(10., (y))
#define Str2Arr(x,y)                        memcpy( (y), (x).toLower().toUtf8().constData(), (x).size() );
#define Arr2Str(x,y)                        (y) = QString::fromUtf8((char *)(x))
#define RAD2ANGL(x)                         ((x) * 180.0 / M_PI)
#define ANGLE2RAD(x)                        ((x) * M_PI / 180.0)

#define vVertex_COLOR_OFFSET 3 * sizeof(double)
#define HOR_GRID_CNT                    10
#define VER_GRID_CNT                    5
#define FADEOUT_STEP                    0.02

enum MsgType
{
    MsgType_Title,
    MsgType_Msg,
    MsgType_None
};

enum Enum_ZoomType
{
    ZoomType_None,
    ZoomType_MouseWheel,
    ZoomType_Square,
    ZoomType_WheelAndSquare
};

enum Enum_AutoZoomType
{
    AutoZoom_Default,
    AutoZoom_Calculated,
    AutoZoom_PeriodicCalculated
};

enum Enum_PointShape
{
    Shape_Bleep = 6,
    Shape_Circle = 20,
    Shape_Triangle = 3,
    Shape_Square = 4,
    Shape_Point = 1
};

enum ScopeMode
{
    SMode_PointLineNormal,
    SMode_PointLineTrace,
    SMode_Scatter,
    SMode_IntensityGrid,
    SMode_Polar,
    SMode_Undefined
};

enum Enum_Orientation
{
    Orien_Horizontal,
    Orien_Verical
};

enum Enum_AxisStyle
{
    AxisStyle_Near,
    AxisStyle_Far
};

struct vVertex
{
    double x;
    double y;
    double z;
    double r;
    double g;
    double b;
    double a;
    double val;

public:
    vVertex(double x = 0.0, double y = 0.0, double z = 0.0)
    {
        this->x = x;
        this->y = y;
        this->z = z;

        this->r = 1.0;
        this->g = 0.0;
        this->b = 1.0;
        this->a = 1.0;
        this->val = 0.0;
    }

    vVertex(double x, double y, double z, double r, double g, double b, double a)
    {
        this->x = x;
        this->y = y;
        this->z = z;

        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        this->val = 0.0;
    }
};

struct ScatterGroup
{
    GLuint                  BufferID;
    int                     PointCnt;
    QVector<QPointF>        BasePoints;
    QDateTime               StartTime;
    double                  Opacity;

public:
    ScatterGroup()
    {
        Opacity = 1.0;
        StartTime = QDateTime::currentDateTime();
    }
};



#endif // VCHARTDEFINES_H
