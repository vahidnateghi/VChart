#include "Channel_Intensity.h"

double Channel_Intensity::StartX() const
{
    return m_StartX;
}

void Channel_Intensity::setStartX(double StartX)
{
    m_StartX = StartX;
}

double Channel_Intensity::StopX() const
{
    return m_StopX;
}

void Channel_Intensity::setStopX(double StopX)
{
    m_StopX = StopX;
}

double Channel_Intensity::StartY() const
{
    return m_StartY;
}

void Channel_Intensity::setStartY(double StartY)
{
    m_StartY = StartY;
}

double Channel_Intensity::StopY() const
{
    return m_StopY;
}

void Channel_Intensity::setStopY(double StopY)
{
    m_StopY = StopY;
}

double Channel_Intensity::StepX() const
{
    return m_StepX;
}

void Channel_Intensity::setStepX(double StepX)
{
    m_StepX = StepX;
}

double Channel_Intensity::StepY() const
{
    return m_StepY;
}

void Channel_Intensity::setStepY(double StepY)
{
    m_StepY = StepY;
}

int Channel_Intensity::XReso() const
{
    return m_XReso;
}

void Channel_Intensity::setXReso(int XReso)
{
    m_XReso = XReso;
}

int Channel_Intensity::YReso() const
{
    return m_YReso;
}

void Channel_Intensity::setYReso(int YReso)
{
    m_YReso = YReso;
}

double Channel_Intensity::MinVal() const
{
    return m_MinVal;
}

void Channel_Intensity::setMinVal(double MinVal)
{
    m_MinVal = MinVal;
}

double Channel_Intensity::MaxVal() const
{
    return m_MaxVal;
}

void Channel_Intensity::setMaxVal(double MaxVal)
{
    m_MaxVal = MaxVal;
}

QColor Channel_Intensity::MinColor() const
{
    return m_MinColor;
}

void Channel_Intensity::setMinColor(const QColor &MinColor)
{
    m_MinColor = MinColor;
}

QColor Channel_Intensity::MaxColor() const
{
    return m_MaxColor;
}

void Channel_Intensity::setMaxColor(const QColor &MaxColor)
{
    m_MaxColor = MaxColor;
}

QString Channel_Intensity::Title() const
{
    return m_Title;
}

void Channel_Intensity::setTitle(const QString &Title)
{
    m_Title = Title;
}

void Channel_Intensity::PushUp()
{
    for(int i = 0; i < m_XReso; i++)
    {
        for(int j = m_YReso - 1; j >= 0; j--)
        {
            if( j == 0 )
                SetValue( i, j, m_MinVal  );
            else
                SetValue( i, j, GetValue( i, j - 1 )  );
        }
    }

}

void Channel_Intensity::SetValue(double X, double Y, double Val)
{
    if(X > m_StopX || X < m_StartX)
        return;
    if(Y > m_StopY || Y < m_StartY)
        return;

    int XIdx = qRound( (X - m_StartX) / m_StepX );
    int YIdx = qRound( (Y - m_StartY) / m_StepY );
}

double Channel_Intensity::GetValue(double X, double Y)
{
    if(X > m_StopX || X < m_StartX)
        return 0;
    if(Y > m_StopY || Y < m_StartY)
        return 0;

    int XIdx = qRound( (X - m_StartX) / m_StepX );
    int YIdx = qRound( (Y - m_StartY) / m_StepY );

    return GetValue( XIdx, YIdx );
}

double Channel_Intensity::GetValue(int XIdx, int YIdx)
{
    if(XIdx < 0 || XIdx >= m_XReso)
        return 0;
    if(YIdx < 0 || YIdx >= m_YReso)
        return 0;

//    if( YIdx == 0 )
//    {
//        return m_ValuePoints.data()[YIdx].data()[2 * XIdx].val;
//    }
//    else if( YIdx == m_YReso - 1 )
//    {
//        return m_ValuePoints.data()[YIdx].data()[2 * XIdx - 1].val;
//    }
//    else
//    {
//        return m_ValuePoints.data()[YIdx].data()[2 * XIdx - 1].val;
//    }

    return 0;
}

bool Channel_Intensity::isWriting() const
{
    return m_isWriting;
}

void Channel_Intensity::setIsWriting(bool isWriting)
{
    m_isWriting = isWriting;
}

int Channel_Intensity::PointSize() const
{
    return m_PointSize;
}

Channel_Intensity::Channel_Intensity(QObject *parent) : Channel_Base(parent)
{
    m_StartX = -10;
    m_StopX = 10;
    m_StartY = -10;
    m_StopY = 10;
    m_XReso = 10;
    m_YReso = 10;
    m_MinVal = 0;
    m_MaxVal = 10;
    m_MinColor = Qt::blue;
    m_MaxColor = Qt::red;
    m_Title = "";
    m_PointSize = 0;
}

void Channel_Intensity::ConfigChannel(double StartX, double StopX, double StartY, double StopY, int XReso, int YReso, double MinValue, double MaxValue, QColor MinColor, QColor MaxColor)
{
    m_StartX = StartX; m_StopX = StopX;
    m_StartY = StartY; m_StopY = StopY;
    m_XReso = XReso; m_YReso = YReso;
    m_MinVal = MinValue; m_MaxVal = MaxValue;
    m_MinColor = MinColor; m_MaxColor = MaxColor;

    m_StepX = ( m_StopX - m_StartX ) / ( m_XReso - 2 );
    m_StepY = ( m_StopY - m_StartY ) / ( m_YReso - 2 );
}
