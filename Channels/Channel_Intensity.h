#ifndef CHANNEL_INTENSITY_H
#define CHANNEL_INTENSITY_H

#include <Channels/Channel_Base.h>

class Channel_Intensity : public Channel_Base
{
    Q_OBJECT
private:
    double m_StartX, m_StopX;
    double m_StartY, m_StopY;
    double m_StepX, m_StepY;
    int m_XReso, m_YReso;
    double m_MinVal, m_MaxVal;
    QColor m_MinColor, m_MaxColor;
    QString m_Title;
    bool m_isWriting;
    int m_PointSize;

public:
    explicit Channel_Intensity(QObject *parent = nullptr);
    void ConfigChannel(double StartX, double StopX, double StartY, double StopY, int XReso, int YReso, double MinValue, double MaxValue, QColor MinColor, QColor MaxColor);

    std::vector<GLuint> m_ValuePoints;
    double StartX() const;
    void setStartX(double StartX);
    double StopX() const;
    void setStopX(double StopX);
    double StartY() const;
    void setStartY(double StartY);
    double StopY() const;
    void setStopY(double StopY);
    double StepX() const;
    void setStepX(double StepX);
    double StepY() const;
    void setStepY(double StepY);
    int XReso() const;
    void setXReso(int XReso);
    int YReso() const;
    void setYReso(int YReso);
    double MinVal() const;
    void setMinVal(double MinVal);
    double MaxVal() const;
    void setMaxVal(double MaxVal);
    QColor MinColor() const;
    void setMinColor(const QColor &MinColor);
    QColor MaxColor() const;
    void setMaxColor(const QColor &MaxColor);
    QString Title() const;
    void setTitle(const QString &Title);

    void PushUp();

    void SetValue(double X, double Y, double Val);
    double GetValue(double X, double Y);
    double GetValue(int XIdx, int YIdx);
    bool isWriting() const;
    void setIsWriting(bool isWriting);

    int PointSize() const;
};

#endif // CHANNEL_INTENSITY_H
