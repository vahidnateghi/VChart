#include "VChart_Polar1.h"
#include "Channels/Channel_Polar.h"

VChart_Polar1::VChart_Polar1(QWidget *parent) : VChart_Polar(parent)
{

}

void VChart_Polar1::paintGL()
{
    makeCurrent();

    DoBackGrnPaitings();

    glEnable( GL_DEPTH_TEST );

    glEnableClientState( GL_VERTEX_ARRAY );
    glLineWidth( 1 );

    for(int chnli = 0; chnli < m_Channels.count(); chnli++)
    {
        Channel_Polar* tChannel = (Channel_Polar*)m_Channels[chnli];
        for(int i = tChannel->Groups()->count() - 1; i >= 0; i--)
        {
            qint64 age = tChannel->Groups()->at(i)->StartTime.msecsTo( QDateTime::currentDateTime() );
            if( age > tChannel->FadeDuration() )
            {
                GLuint buffToBeDeleted = tChannel->Groups()->at(i)->BufferID;
                glDeleteBuffers( 1, &buffToBeDeleted );
                delete tChannel->Groups()->at(i);
                tChannel->Groups()->removeAt(i);
                continue;
            }
            glBindBuffer( GL_ARRAY_BUFFER, tChannel->Groups()->at(i)->BufferID );
            glVertexPointer( 3, GL_DOUBLE, sizeof(vVertex), 0 );
            glColor4d( tChannel->PointColor().redF(), tChannel->PointColor().greenF(), tChannel->PointColor().blueF(), tChannel->Groups()->at(i)->Opacity );
            if(tChannel->PointShape() == Shape_Bleep)
            {
                glDrawArrays( GL_TRIANGLES, 0, tChannel->Groups()->at(i)->PointCnt );
            }
            else if(tChannel->PointShape() == Shape_Circle)
            {
                int Reso = (int)tChannel->PointShape();
                int tPntSize = tChannel->Groups()->at(i)->PointCnt / Reso;
                for(int j = 0; j < tPntSize; j++)
                {
                    glDrawArrays( GL_LINE_LOOP, j * Reso, Reso );
                }
            }
            else if(tChannel->PointShape() == Shape_Square)
            {
                int Reso = (int)tChannel->PointShape();
                int tPntSize = tChannel->Groups()->at(i)->PointCnt / Reso;
                for(int j = 0; j < tPntSize; j++)
                {
                    glDrawArrays( GL_LINE_LOOP, j * Reso, Reso );
                }
            }
            else if(tChannel->PointShape() == Shape_Point)
            {
                QPointF tpSize = ScopeToMouseRatio( QPointF( tChannel->PointSizeX(), tChannel->PointSizeX() ) );
                glPointSize( tpSize.x() );
                int Reso = (int)tChannel->PointShape();
                int tPntSize = tChannel->Groups()->at(i)->PointCnt / Reso;
                for(int j = 0; j < tPntSize; j++)
                {
                    glDrawArrays( GL_POINTS, j * Reso, Reso );
                }
                glPointSize( 1 );
            }
            else if(tChannel->PointShape() == Shape_Triangle)
            {
                int Reso = (int)tChannel->PointShape();
                int tPntSize = tChannel->Groups()->at(i)->PointCnt / Reso;
                for(int j = 0; j < tPntSize; j++)
                {
                    glDrawArrays( GL_LINE_STRIP, j * Reso, Reso );
                }
            }
            tChannel->Groups()->at(i)->Opacity =  1.0 - (double)age / (double)tChannel->FadeDuration();
        }
    }

    glDisableClientState( GL_VERTEX_ARRAY );

    glDisable( GL_DEPTH_TEST );


    glPointSize( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // Writing Labels
    for(int chnli = 0; chnli < m_Channels.count(); chnli++)
    {
        Channel_Polar* tChannel = (Channel_Polar*)m_Channels[chnli];
        if(!tChannel->ShowLabels())
            continue;
        int tPntSize = tChannel->Groups()->last()->BasePoints.count();
        for(int j = 0; j < tPntSize; j++)
        {
            if(j < tChannel->Labels().count() && tChannel->ShowLabels() )
            {
                QFont font;
                font.setFamily( "Calibri" );
                font.setWeight( 50 );
                font.setPixelSize( 13 );

                glColor4d( 1.0, 1.0, 1.0, 1.0 );
                QPointF Offset = mouseToScopeRatio(QPointF( 15 , 10 ));
                double StartX = tChannel->Groups()->last()->BasePoints[j].x() + Offset.x();
                double StartY = tChannel->Groups()->last()->BasePoints[j].y() + Offset.y();
                QString Label = tChannel->Labels()[j];
                QStringList Lines = Label.split("\n");
                for(int i = 0; i < Lines.count(); i++)
                {
                    renderText( StartX,
                                StartY,
                                0.0,
                                Lines[i],
                                font);
                    StartY -= ( Offset.y() * 1.5 );
                }

            }
        }
        break;
    }

    DoForeGrnPaitings();
}
