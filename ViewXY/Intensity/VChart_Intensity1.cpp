#include "VChart_Intensity1.h"

VChart_Intensity1::VChart_Intensity1(QWidget *parent) : VChart_Intensity(parent)
{

}

void VChart_Intensity1::paintGL()
{

    makeCurrent();

    DoBackGrnPaitings();

    // ------------

//    glEnable( GL_DEPTH_TEST );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
    glLineWidth( 2 );

    for( int i = 0; i < m_Channels.size(); i++ )
    {
        Channel_Intensity* tChannel = (Channel_Intensity*)m_Channels.at(i);
        if( !tChannel->isWriting() && tChannel->IsVisible() )
        {
            for( int j = 0; j < tChannel->m_ValuePoints.size(); j++ )
            {
                glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints[j] );

//                glColor3d( 1.0, 0.0, 0.0 );
                glVertexPointer( 3, GL_DOUBLE, sizeof(vVertex), 0 );
                glColorPointer( 4, GL_DOUBLE, sizeof(vVertex), ((GLubyte*) NULL + (3 * sizeof(double))) );

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 2 * tChannel->XReso() );

            }

        }
    }

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

//    glDisable( GL_DEPTH_TEST );

    DoForeGrnPaitings();
}
