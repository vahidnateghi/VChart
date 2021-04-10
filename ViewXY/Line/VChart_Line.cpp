#include "VChart_Line.h"

VChart_Line::VChart_Line(QWidget *parent) : VChart_XY(parent)
{

}

void VChart_Line::SetPoints(int Idx, const QVector<double> &XPoints, const QVector<double> &YPoints)
{
    if( Idx >= m_Channels.count() )
        return;

    Channel_Line* tChannel = (Channel_Line*)m_Channels.at(Idx);

    tChannel->Points()->clear();

    for( int i = 0; i < XPoints.count(); i++ )
    {
        vVertex Pnt(XPoints.at(i), YPoints.at(i), 0);
        tChannel->Points()->append( Pnt );

        if( (m_AutoZoomMaxY ) <= Pnt.y )
            m_AutoZoomMaxY = Pnt.y + Pnt.y * 0.1;
        if( (m_AutoZoomMinY ) >= Pnt.y )
            m_AutoZoomMinY = Pnt.y - Pnt.y * 0.1;

        if( (m_AutoZoomMaxX ) <= Pnt.x )
            m_AutoZoomMaxX = Pnt.x + Pnt.x * 0.1;
        if( (m_AutoZoomMinX) >= Pnt.x )
            m_AutoZoomMinX = Pnt.x - Pnt.x * 0.1;
    }

    if(m_AutoZoomMinX == 0) m_AutoZoomMinX = -1.0 * (m_AutoZoomMaxX * 0.1);
    if(m_AutoZoomMaxX == 0) m_AutoZoomMaxX = -1.0 * ( m_AutoZoomMinX * 0.1);

    if(m_AutoZoomMinY == 0) m_AutoZoomMinY = -1.0 * (m_AutoZoomMaxY * 0.1);
    if(m_AutoZoomMaxY == 0) m_AutoZoomMaxY = -1.0 * ( m_AutoZoomMinY * 0.1);

    TryUpdate();
}

void VChart_Line::SetPoints(int Idx, const QVector<long long> &YPoints)
{
    if( Idx >= m_Channels.count() )
        return;

    Channel_Line* tChannel = (Channel_Line*)m_Channels.at(Idx);

    tChannel->Points()->clear();

    for( int i = 0; i < YPoints.count(); i++ )
    {
        vVertex Pnt(i, YPoints.at(i), 0);
        tChannel->Points()->append( Pnt );

        if( (m_AutoZoomMaxY ) <= Pnt.y )
            m_AutoZoomMaxY = Pnt.y + Pnt.y * 0.1;
        if( (m_AutoZoomMinY ) >= Pnt.y )
            m_AutoZoomMinY = Pnt.y - Pnt.y * 0.1;

        if( (m_AutoZoomMaxX ) <= Pnt.x )
            m_AutoZoomMaxX = Pnt.x + Pnt.x * 0.1;
        if( (m_AutoZoomMinX) >= Pnt.x )
            m_AutoZoomMinX = Pnt.x - Pnt.x * 0.1;
    }

    if(m_AutoZoomMinX == 0) m_AutoZoomMinX = -1.0 * (m_AutoZoomMaxX * 0.1);
    if(m_AutoZoomMaxX == 0) m_AutoZoomMaxX = -1.0 * ( m_AutoZoomMinX * 0.1);

    if(m_AutoZoomMinY == 0) m_AutoZoomMinY = -1.0 * (m_AutoZoomMaxY * 0.1);
    if(m_AutoZoomMaxY == 0) m_AutoZoomMaxY = -1.0 * ( m_AutoZoomMinY * 0.1);

    TryUpdate();
}
