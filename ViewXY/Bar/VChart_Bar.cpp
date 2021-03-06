#include "VChart_Bar.h"

VChart_Bar::VChart_Bar(QWidget *parent) : VChart_XY(parent)
{

}

void VChart_Bar::AddChannel(QString Title, int BarCount, Enum_Orientation Orientation, QColor BarColor, double LineWidth)
{
    Channel_Bar* Chnl = new Channel_Bar();

    Chnl->setTitle( Title );
    Chnl->setBarCount( BarCount );
    Chnl->setLineColor( BarColor );
    Chnl->setOrientation( Orientation );
    Chnl->setLineWidth( LineWidth );

    m_Channels.append( Chnl );
}

void VChart_Bar::SetPointsForHistogram(int ChnlIdx, const QList<QPointF> &Points, bool update)
{
    if( ChnlIdx < 0 || ChnlIdx >= m_Channels.count() )
        return;

    Channel_Bar* tChnl = (Channel_Bar *)m_Channels.at(ChnlIdx);
    double Min = 100000000000000, Max = -100000000000000;

    // Finding Max and Min
    double SectionStep = 1.0;
    if( tChnl->Orientation() == Orien_Horizontal )
    {
        for( int i = 0; i < Points.count(); i++ )
        {
                if( Points.at(i).y() > Max )
                    Max = Points.at(i).y();
                if( Points.at(i).y() < Min )
                    Min = Points.at(i).y();
        }

        SectionStep = (Max - Min) / (double)( tChnl->BarCount()  - 1 );

        tChnl->LineStarts()->clear();
        tChnl->LineLength()->clear();

        for( int i = 0; i < tChnl->BarCount(); i++ )
        {
            tChnl->LineStarts()->append( QPointF( 0.0, Min + i * SectionStep ) );
            tChnl->LineLength()->append( 0.0 );
        }
    }
    else if( tChnl->Orientation() == Orien_Verical )
    {
        for( int i = 0; i < Points.count(); i++ )
        {
            if( Points.at(i).x() > Max )
                Max = Points.at(i).x();
            if( Points.at(i).x() < Min )
                Min = Points.at(i).x();
        }

        SectionStep = (Max - Min) / (double)( tChnl->BarCount()  - 1 );

        tChnl->LineStarts()->clear();
        tChnl->LineLength()->clear();

        for( int i = 0; i < tChnl->BarCount(); i++ )
        {
            tChnl->LineStarts()->append( QPointF( Min + i * SectionStep, 0.0 ) );
            tChnl->LineLength()->append( 0.0 );
        }
    }

    for( int i = 0; i < Points.count(); i++ )
    {
        if( tChnl->Orientation() == Orien_Horizontal )
        {
            for( int j = 0; j < tChnl->BarCount(); j++ )
            {
                if( Points.at(i).y() <= qMin( Max, Min + ( SectionStep * j + SectionStep / 2.0 ) ) &&
                    Points.at(i).y() >= qMax( Min, Min + ( SectionStep * j - SectionStep / 2.0 ) ))
                {
                    tChnl->LineLength()->replace( j, tChnl->LineLength()->at(j) + m_HistStep );
                    break;
                }
            }
        }
        else if( tChnl->Orientation() == Orien_Verical )
        {
            for( int j = 0; j < tChnl->BarCount(); j++ )
            {
                if( Points.at(i).x() <= qMin( Max, Min + ( SectionStep * j + SectionStep / 2.0 ) ) &&
                    Points.at(i).x() >= qMax( Min, Min - ( SectionStep * j - SectionStep / 2.0 ) ))
                {
                    tChnl->LineLength()->replace( j, tChnl->LineLength()->at(j) + m_HistStep );
                    break;
                }
            }
        }
    }

    double maxLen = -100000000;
    for( int i = 0; i < tChnl->LineLength()->count(); i++ )
       if( tChnl->LineLength()->at(i) > maxLen ) maxLen = tChnl->LineLength()->at(i);

    if( tChnl->Orientation() == Orien_Horizontal )
    {
        m_AutoZoomMinX = 0.0;//-0.1 * maxLen;
        m_AutoZoomMaxX = maxLen;
        if( m_AutoZoomYType == AutoZoom_PeriodicCalculated )
        {
            m_AutoZoomMinY = Min;
            m_AutoZoomMaxY = Max;
        }

    }
    else if( tChnl->Orientation() == Orien_Verical )
    {
        if( m_AutoZoomXType == AutoZoom_PeriodicCalculated )
        {
            m_AutoZoomMinX = Min - qAbs(Max - Min) / m_AutoZoomXCoef;
            m_AutoZoomMaxX = Max + qAbs(Max - Min) / m_AutoZoomXCoef;
        }
        m_AutoZoomMinY = 0.1 * maxLen;
        m_AutoZoomMaxY = maxLen + maxLen * 0.1;
    }


    if( update )
    {
        TryUpdate();
    }
}

void VChart_Bar::SetPointsForBarItems(int ChnlIdx, const QVector<QPointF> &Points, bool update)
{
    Channel_Bar* tChnl = (Channel_Bar *)m_Channels.at(ChnlIdx);

    tChnl->LineStarts()->clear();
    tChnl->LineLength()->clear();

    double MinX = 100000000000000, MaxX = -100000000000000;
    double MinY = 100000000000000, MaxY = -100000000000000;
    double maxLen = -100000000;

    if( tChnl->Orientation() == Orien_Horizontal )
    {
        for( int i = 0; i < Points.length(); i++ )
        {
            tChnl->LineStarts()->append( QPointF( 0, Points.at(i).x() ) );
            tChnl->LineLength()->append( Points.at(i).y() );

            if( Points.at(i).y() > maxLen ) maxLen = Points.at(i).y();

            if( Points.at(i).y() > MaxX ) MaxX = Points.at(i).y();
            if( Points.at(i).y() < MinX ) MinX = Points.at(i).y();
            if( Points.at(i).x() > MaxY ) MaxY = Points.at(i).x();
            if( Points.at(i).x() < MinY ) MinY = Points.at(i).x();
        }
    }
    else if( tChnl->Orientation() == Orien_Verical )
    {
        for( int i = 0; i < Points.length(); i++ )
        {
            tChnl->LineStarts()->append( QPointF( Points.at(i).x(), 0 ) );
            tChnl->LineLength()->append( Points.at(i).y() );

            if( Points.at(i).y() > maxLen ) maxLen = Points.at(i).y();

            if( Points.at(i).x() > MaxX ) MaxX = Points.at(i).x();
            if( Points.at(i).x() < MinX ) MinX = Points.at(i).x();
            if( Points.at(i).y() > MaxY ) MaxY = Points.at(i).y();
            if( Points.at(i).y() < MinY ) MinY = Points.at(i).y();
        }
    }

    if( m_AutoZoomXType == AutoZoom_PeriodicCalculated )
    {
        m_AutoZoomMinX = MinX ;
        m_AutoZoomMaxX = MaxX ;
    }
    m_AutoZoomMinY = MinY ;
    m_AutoZoomMaxY = MaxY ;

    if( update )
    {
        TryUpdate();
    }
}
