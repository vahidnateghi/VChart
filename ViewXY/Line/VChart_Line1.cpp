#include "VChart_Line1.h"
#include "Channels/Channel_Line.h"

VChart_Line1::VChart_Line1(QWidget *parent) : VChart_Line(parent)
{

}

void VChart_Line1::paintGL()
{
    makeCurrent();

    DoBackGrnPaitings();

    // ------------

    glLineWidth( 2 );
    glEnableClientState( GL_VERTEX_ARRAY );
    for( int i = 0; i < m_Channels.count(); i++ )
    {
        Channel_Line* tChannel = (Channel_Line *)m_Channels.at(i);

        if( tChannel->IsVisible() )
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexPointer( 3, GL_DOUBLE, sizeof(vVertex), &(tChannel->Points()->data()[0].x) );
            if(tChannel->ShowLines())
            {
                glColor3d( tChannel->LineColor().redF(), tChannel->LineColor().greenF(), tChannel->LineColor().blueF() );
                glDrawArrays(GL_LINE_STRIP, 0, tChannel->Points()->count());
            }
            if( tChannel->ShowPoints() )
            {
                glColor3d( tChannel->PointColor().redF(), tChannel->PointColor().greenF(), tChannel->PointColor().blueF() );
                glPointSize( 8 );
                glDrawArrays(GL_POINTS, 0, tChannel->Points()->count());
            }
        }
    }

    glDisableClientState( GL_VERTEX_ARRAY );

    // ------------

    DoForeGrnPaitings();
}
