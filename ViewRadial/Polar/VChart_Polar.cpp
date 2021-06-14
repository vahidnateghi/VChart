#include "VChart_Polar.h"
#include <QtMath>

VChart_Polar::VChart_Polar(QWidget *parent) : VChart_Radial(parent)
{

}

void VChart_Polar::AddChannel(QString Title, Enum_PointShape PointShape, QColor PointColor, double PointSize, bool ShowLabels, int FadeoutDuration)
{
    Channel_Polar* Chnl = new Channel_Polar();

    Chnl->setTitle( Title );
    Chnl->setPointColor( PointColor );
    Chnl->setPointSizeX( PointSize );
    Chnl->setPointSizeY( PointSize );
    Chnl->setShowLabels( ShowLabels );
    Chnl->setPointShape( PointShape );
    Chnl->setFadeDuration( FadeoutDuration );

    m_Channels.append( Chnl );
}

void VChart_Polar::AddPoints(int Idx, const QList<QPointF> &pnt)
{
    if(Idx < 0 || Idx >= m_Channels.count())
        return;

    Channel_Polar* tChannel = (Channel_Polar *)m_Channels[Idx];

    QVector<vVertex> tPoints;
    int tPntSize = 0;

    QPointF tSize = QPointF(tChannel->PointSizeX(), tChannel->PointSizeY());

    if(tChannel->PointShape() == Shape_Bleep)
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

                tPoints.append( vVertex(x + pnt[i].x(), y + pnt[i].y(), 0) );
            }
        }
    }
    else if(tChannel->PointShape() == Shape_FilledCircle)
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

                tPoints.append( vVertex(x + pnt[i].x(), y + pnt[i].y(), 0) );
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
    else if(tChannel->PointShape() == Shape_GLSLPoint)
    {
        int Reso = (int)tChannel->PointShape();
        tPntSize = pnt.count() * 1;
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

    glBufferData( GL_ARRAY_BUFFER, sizeof(vVertex) * tPntSize, tPoints.data(), GL_DYNAMIC_DRAW );

    ScatterGroup *grp = new ScatterGroup();
    grp->BasePoints  = pnt;
    grp->BufferID    = id;
    grp->PointCnt    = tPoints.count();
    grp->Opacity     = 1.0;
    grp->StartTime   = QDateTime::currentDateTime();

    if( tChannel->FadeDuration() == -1 )
    {
        for( int i = 0; i < tChannel->Groups()->size(); i++ )
        {
            GLuint buffToBeDeleted = tChannel->Groups()->at(i)->BufferID;
            glDeleteBuffers( 1, &buffToBeDeleted );
            delete tChannel->Groups()->at(i);
        }
    }
    tChannel->Groups()->clear();

    tChannel->Groups()->append( grp );
}

void VChart_Polar::AddPoints(int Idx, const QList<QPointF> &Points, const QList<QString> &Labels)
{
    if(Idx < 0 || Idx >= m_Channels.count())
        return;

    Channel_Polar* tChannel = (Channel_Polar *)m_Channels[Idx];

    AddPoints(Idx, Points);
    tChannel->setLabels( Labels );
}

void VChart_Polar::resizeGL(int w, int h)
{
    VChart_Base::resizeGL(w, h);

    AdjustAsceptRatio();
}

