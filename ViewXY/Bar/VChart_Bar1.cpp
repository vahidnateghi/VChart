#include "VChart_Bar1.h"

VChart_Bar1::VChart_Bar1(QWidget *parent) : VChart_Bar(parent)
{

}

void VChart_Bar1::paintGL()
{
    makeCurrent();

    DoBackGrnPaitings();

    glEnable( GL_DEPTH_TEST );

    for(int chnli = 0; chnli < m_Channels.count(); chnli++)
    {
        Channel_Bar* tChannel = (Channel_Bar*)m_Channels[chnli];
        double LWidth = 1.0;
        QPointF LinePnt = mouseToScopeRatio( QPointF(  ) );
        if( tChannel->Orientation() == Orien_Horizontal )

        glLineWidth( tChannel->LineWidth() );
        glColor3d( tChannel->LineColor().redF(), tChannel->LineColor().greenF(), tChannel->LineColor().blueF() );
        for( int i = 0; i < tChannel->LineStarts()->count(); i++ )
        {
            glBegin( GL_LINE_STRIP );
            glVertex3d( tChannel->LineStarts()->at(i).x(), tChannel->LineStarts()->at(i).y(), 0 );
            if( tChannel->Orientation() == Orien_Horizontal )
            {
                glVertex3d( tChannel->LineStarts()->at(i).x() + tChannel->LineLength()->at(i), tChannel->LineStarts()->at(i).y(), 0 );
            }
            else if( tChannel->Orientation() == Orien_Verical )
            {
                glVertex3d( tChannel->LineStarts()->at(i).x(), tChannel->LineStarts()->at(i).y() + tChannel->LineLength()->at(i), 0 );
            }
            glEnd();
        }
    }

    glDisable( GL_DEPTH_TEST );

    glPointSize( 1 );
    glLineWidth( 1.0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    DoForeGrnPaitings();
}
