#include "VChart_Scatter.h"
#include <QtMath>

VChart_Scatter::VChart_Scatter(QWidget *parent) : VChart_XY(parent)
{
    m_ScopeMode = SMode_Scatter;
}

/////////////////////////

void VChart_Scatter::AddChannel(QString Title, QColor Color, Enum_PointShape PointShape, double PntSizeX, double PntSizeY, int FadeoutDuration, bool ShowLabels)
{
    Channel_Scatter* Chnl = new Channel_Scatter();

    Chnl->setPointColor( Color );
    Chnl->setTitle( Title );
    Chnl->setPointShape( PointShape );
    Chnl->setPointSizeX( PntSizeX );
    Chnl->setPointSizeY( PntSizeY );
    Chnl->setFadeDuration( FadeoutDuration );
    Chnl->setShowLabels( ShowLabels );

    m_Channels.append( Chnl );
}

/////////////////////////

void VChart_Scatter::AddPoints(int Idx, const QList<QPointF> &pnt, bool Update)
{
    if(Idx < 0 || Idx >= m_Channels.count() || pnt.count() == 0)
        return;

    Channel_Scatter* tChannel = (Channel_Scatter *)m_Channels[Idx];

    QVector<vVertex> tPoints;
    int tPntSize = 0;

    QPointF tSize = QPointF(tChannel->PointSizeX(), tChannel->PointSizeY());

    if( tChannel->PointShape() == Shape_Bleep )
    {
        tPntSize = pnt.count() * 6;
        for(int i = 0; i < pnt.count(); i++)
        {
            m_AutoZoomMaxX = qMax(m_AutoZoomMaxX, pnt.at(i).x());
            m_AutoZoomMinX = qMin(m_AutoZoomMinX, pnt.at(i).x());
            m_AutoZoomMaxY = qMax(m_AutoZoomMaxY, pnt.at(i).y());
            m_AutoZoomMinY = qMin(m_AutoZoomMinY, pnt.at(i).y());

            tPoints.append( vVertex(pnt[i].x() - tSize.x()/2.0, pnt[i].y() + tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() - tSize.x()/2.0, pnt[i].y() - tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x()/2.0, pnt[i].y() + tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() - tSize.x()/2.0, pnt[i].y() - tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x()/2.0, pnt[i].y() + tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x()/2.0, pnt[i].y() - tSize.y()/2.0, 0) );
        }
    }
    else if(tChannel->PointShape() == Shape_Circle)
    {
        int Reso = (int)tChannel->PointShape();
        tPntSize = pnt.count() * Reso;

        tSize = ScopeToMouseRatio( tSize );
        tSize = QPointF( qMax( tSize.x(), tSize.y() ), qMax( tSize.x(), tSize.y() ) );
        tSize = mouseToScopeRatio( tSize );

        for(int i = 0; i < pnt.count(); i++)
        {
            m_AutoZoomMaxX = qMax(m_AutoZoomMaxX, pnt[i].x());
            m_AutoZoomMinX = qMin(m_AutoZoomMinX, pnt[i].x());
            m_AutoZoomMaxY = qMax(m_AutoZoomMaxY, pnt[i].y());
            m_AutoZoomMinY = qMin(m_AutoZoomMinY, pnt[i].y());

            for(int j = 0; j < Reso; j++)
            {
                float theta = 2.0f * M_PI * float(j) / float(Reso);//get the current angle

                float x = tSize.x() / 2.0 * cosf(theta);//calculate the x component
                float y = tSize.y() / 2.0 * sinf(theta);//calculate the y component

                tPoints.append( vVertex(x + pnt[i].x(), y + pnt[i].y(), 0/*-( MAX_DEPTH - (double)Idx / MAX_DEPTH )*/) );
            }
        }
    }
    else if(tChannel->PointShape() == Shape_Triangle)
    {
        int Reso = (int)tChannel->PointShape();
        tPntSize = pnt.count() * Reso;

        tSize = ScopeToMouseRatio( tSize );
        tSize = QPointF( qMax( tSize.x(), tSize.y() ), qMax( tSize.x(), tSize.y() ) );
        tSize = mouseToScopeRatio( tSize );

        for(int i = 0; i < pnt.count(); i++)
        {
            m_AutoZoomMaxX = qMax(m_AutoZoomMaxX, pnt[i].x());
            m_AutoZoomMinX = qMin(m_AutoZoomMinX, pnt[i].x());
            m_AutoZoomMaxY = qMax(m_AutoZoomMaxY, pnt[i].y());
            m_AutoZoomMinY = qMin(m_AutoZoomMinY, pnt[i].y());

            tPoints.append( vVertex(pnt[i].x(), pnt[i].y() + tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() - tSize.x()/2.0, pnt[i].y() - tSize.y()/2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x()/2.0, pnt[i].y() - tSize.y()/2.0, 0) );
        }
    }
    else if(tChannel->PointShape() == Shape_Square)
    {
        int Reso = (int)tChannel->PointShape();
        tPntSize = pnt.count() * Reso;

        tSize = ScopeToMouseRatio( tSize );
        tSize = QPointF( qMax( tSize.x(), tSize.y() ), qMax( tSize.x(), tSize.y() ) );
        tSize = mouseToScopeRatio( tSize );

        for(int i = 0; i < pnt.count(); i++)
        {
            m_AutoZoomMaxX = qMax(m_AutoZoomMaxX, pnt[i].x());
            m_AutoZoomMinX = qMin(m_AutoZoomMinX, pnt[i].x());
            m_AutoZoomMaxY = qMax(m_AutoZoomMaxY, pnt[i].y());
            m_AutoZoomMinY = qMin(m_AutoZoomMinY, pnt[i].y());


            tPoints.append( vVertex(pnt[i].x() - tSize.x() / 2.0, pnt[i].y() - tSize.y() / 2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() - tSize.x() / 2.0, pnt[i].y() + tSize.y() / 2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x() / 2.0, pnt[i].y() + tSize.y() / 2.0, 0) );
            tPoints.append( vVertex(pnt[i].x() + tSize.x() / 2.0, pnt[i].y() - tSize.y() / 2.0, 0) );
        }
    }
    else if(tChannel->PointShape() == Shape_Point)
    {
        int Reso = (int)tChannel->PointShape();
        tPntSize = pnt.count() * Reso;
        for(int i = 0; i < pnt.count(); i++)
        {
            m_AutoZoomMaxX = qMax(m_AutoZoomMaxX, pnt[i].x());
            m_AutoZoomMinX = qMin(m_AutoZoomMinX, pnt[i].x());
            m_AutoZoomMaxY = qMax(m_AutoZoomMaxY, pnt[i].y());
            m_AutoZoomMinY = qMin(m_AutoZoomMinY, pnt[i].y());

            tPoints.append( vVertex(pnt[i].x(), pnt[i].y(), 0) );
        }
    }
    makeCurrent();
    GLuint id;
    glGenBuffers( 1, &id );

    glBindBuffer( GL_ARRAY_BUFFER, id );

    glBufferData( GL_ARRAY_BUFFER, sizeof(vVertex) * tPntSize, tPoints.data(), GL_STATIC_DRAW );

    ScatterGroup *grp = new ScatterGroup();
    grp->BasePoints  = pnt;
    grp->BufferID    = id;
    grp->PointCnt    = tPoints.count();
    grp->Opacity     = 1.0;
    grp->StartTime   = QDateTime::currentDateTime();

    if( tChannel->FadeDuration() <= 0 )
    {
        for( int i = tChannel->Groups()->count() - 1 ; i >= 0 ; i-- )
        {
            GLuint buffToBeDeleted = tChannel->Groups()->at(i)->BufferID;
            glDeleteBuffers( 1, &buffToBeDeleted );
            delete tChannel->Groups()->at(i);
            tChannel->Groups()->removeAt(i);
        }
    }

    tChannel->Groups()->append( grp );

    if( Update )
        TryUpdate();
}

/////////////////////////

void VChart_Scatter::AddPoints(int Idx, const QList<QPointF> &Points, const QList<QString> &Labels, bool Update)
{
    if(Idx < 0 || Idx >= m_Channels.count() || Points.count() == 0)
        return;

    Channel_Scatter* tChannel = (Channel_Scatter *)m_Channels[Idx];

    AddPoints(Idx, Points);
    tChannel->setLabels( Labels );

    if( Update )
        TryUpdate();
}

/////////////////////////

void VChart_Scatter::Clear(int Idx)
{
    if( Idx < 0 || Idx >= m_Channels.count() )
        return;

    Channel_Scatter* tChannel = (Channel_Scatter *)m_Channels[Idx];
    tChannel->Clear();

    TryUpdate();
}

/////////////////////////
