#ifndef VCHART_RADIAL_H
#define VCHART_RADIAL_H

#include "VChart_Base.h"



class VChart_Radial : public VChart_Base
{
    Q_OBJECT
public:
    explicit VChart_Radial(QWidget *parent = nullptr);

    void setShowCrossLines(bool ShowCrossLines, QColor CrossLineColor);

    int MaxRange() const;
    void setMaxRange(int MaxRange);

protected:
    int                     m_CircleBufferCount;
    int                     m_CircleBufferLength;
    GLuint *                m_CircleBuffer;
    double                  m_MaxRange;
    bool                    m_ShowCrossLines;
    QColor                  m_CrossLineColor;

    void                    DoBackGrnPaitings() override;
    void                    DoForeGrnPaitings() override;
    void                    genCircleBuffer();

    void                    initializeGL();
};

#endif // VCHART_RADIAL_H
