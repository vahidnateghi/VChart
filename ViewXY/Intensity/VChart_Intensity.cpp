#include "VChart_Intensity.h"
#include <iostream>

VChart_Intensity::VChart_Intensity(QWidget *parent) : VChart_XY(parent)
{
    m_AddingChannel = false;
}

VChart_Intensity::~VChart_Intensity()
{

}

void VChart_Intensity::AddChannel(QString Title, double StartX, double StopX, double StartY, double StopY, int XReso, int YReso, double MinVal, double MaxVal, QColor MinColor, QColor MaxColor)
{
    m_AddingChannel = true;
    Channel_Intensity* tChannel = new Channel_Intensity();
    tChannel->ConfigChannel( StartX, StopX, StartY, StopY, XReso, YReso, MinVal, MaxVal, MinColor, MaxColor );
    tChannel->setTitle( Title );

    tChannel->m_ValuePoints.resize( tChannel->YReso() - 1 );
    glGenBuffers( tChannel->YReso() - 1, tChannel->m_ValuePoints.data() );

    for( int i = 0; i < tChannel->YReso() - 1; i++ )
    {
        vVertex Row[ 2 * tChannel->XReso() ];
//        glGenBuffers( 1, &tChannel->m_ValuePoints[i] );
        for( int j = 0; j < tChannel->XReso(); j++ )
        {
            Row[2 * j].x = tChannel->StartX() + tChannel->StepX() * j;
            Row[2 * j].y = tChannel->StartY() + tChannel->StepY() * i;
            Row[2 * j].z = 0.0;
            Row[2 * j].r = tChannel->MinColor().redF();
            Row[2 * j].g = tChannel->MinColor().greenF();
            Row[2 * j].b = tChannel->MinColor().blueF();
            Row[2 * j].a = 1.0;
            Row[2 * j].val = tChannel->MinVal();

            Row[2 * j + 1].x = tChannel->StartX() + tChannel->StepX() * j;
            Row[2 * j + 1].y = tChannel->StartY() + tChannel->StepY() * ( i + 1 );
            Row[2 * j + 1].z = 0.0;
            Row[2 * j + 1].r = tChannel->MinColor().redF();
            Row[2 * j + 1].g = tChannel->MinColor().greenF();
            Row[2 * j + 1].b = tChannel->MinColor().blueF();
            Row[2 * j + 1].a = 1.0;
            Row[2 * j + 1].val = tChannel->MinVal();
        }

        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.at(i) );
        glBufferData( GL_ARRAY_BUFFER, sizeof(vVertex) * 2 * tChannel->XReso(), Row, GL_STATIC_DRAW );
    }

    m_Channels.append( tChannel );

    if( m_AutoZoomMinX == MAX_VALUE || m_AutoZoomMinX > StartX )
        m_AutoZoomMinX = StartX;

    if( m_AutoZoomMaxX == MIN_VALUE || m_AutoZoomMaxX < StopX )
        m_AutoZoomMaxX = StopX;

    if( m_AutoZoomMinY == MAX_VALUE || m_AutoZoomMinY > StartY )
        m_AutoZoomMinY = StartY;

    if( m_AutoZoomMaxY == MIN_VALUE || m_AutoZoomMaxY < StopY )
        m_AutoZoomMaxY = StopY;

    m_AddingChannel = false;
}

void VChart_Intensity::SetValue(int Idx, int XIdx, int YIdx, double Val)
{
    if( Idx < 0 || Idx >= m_Channels.size() || m_AddingChannel )
        return;

    Channel_Intensity* tChannel = (Channel_Intensity*)m_Channels.at(Idx);

    if( YIdx == 0 )
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );

        vVertex NewV;
        NewV.x = tChannel->StartX() + tChannel->StepX() * XIdx;
        NewV.y = tChannel->StartY() + tChannel->StepY() * YIdx;
        NewV.z = 0.0;
        NewV.val = Val;
        NewV.r = tChannel->MinColor().redF() + ( tChannel->MaxColor().redF() - tChannel->MinColor().redF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.g = tChannel->MinColor().greenF() + ( tChannel->MaxColor().greenF() - tChannel->MinColor().greenF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.b = tChannel->MinColor().blueF() + ( tChannel->MaxColor().blueF() - tChannel->MinColor().blueF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.a = 1.0;

        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * 2 * XIdx, sizeof(vVertex), &NewV );
    }
    else if( YIdx == tChannel->YReso() - 1 )
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx - 1] );

        vVertex NewV;
        NewV.x = tChannel->StartX() + tChannel->StepX() * XIdx;
        NewV.y = tChannel->StartY() + tChannel->StepY() * ( YIdx + 1 );
        NewV.z = 0.0;
        NewV.val = Val;
        NewV.r = tChannel->MinColor().redF() + ( tChannel->MaxColor().redF() - tChannel->MinColor().redF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.g = tChannel->MinColor().greenF() + ( tChannel->MaxColor().greenF() - tChannel->MinColor().greenF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.b = tChannel->MinColor().blueF() + ( tChannel->MaxColor().blueF() - tChannel->MinColor().blueF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV.a = 1.0;

        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx + 1 ), sizeof(vVertex), &NewV );
    }
    else
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx - 1] );


        vVertex NewV1;
        NewV1.x = tChannel->StartX() + tChannel->StepX() * XIdx;
        NewV1.y = tChannel->StartY() + tChannel->StepY() * ( YIdx + 1 );
        NewV1.z = 0.0;
        NewV1.val = Val;
        NewV1.r = tChannel->MinColor().redF() + ( tChannel->MaxColor().redF() - tChannel->MinColor().redF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV1.g = tChannel->MinColor().greenF() + ( tChannel->MaxColor().greenF() - tChannel->MinColor().greenF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV1.b = tChannel->MinColor().blueF() + ( tChannel->MaxColor().blueF() - tChannel->MinColor().blueF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV1.a = 1.0;

        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx + 1 ), sizeof(vVertex), &NewV1 );

        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );

        vVertex NewV2;
        NewV2.x = tChannel->StartX() + tChannel->StepX() * XIdx;
        NewV2.y = tChannel->StartY() + tChannel->StepY() * YIdx;
        NewV2.z = 0.0;
        NewV2.val = Val;
        NewV2.r = tChannel->MinColor().redF() + ( tChannel->MaxColor().redF() - tChannel->MinColor().redF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV2.g = tChannel->MinColor().greenF() + ( tChannel->MaxColor().greenF() - tChannel->MinColor().greenF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV2.b = tChannel->MinColor().blueF() + ( tChannel->MaxColor().blueF() - tChannel->MinColor().blueF() ) * qAbs((Val - tChannel->MinVal()) / (tChannel->MaxVal() - tChannel->MinVal()));
        NewV2.a = 1.0;

        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx ), sizeof(vVertex), &NewV2 );
    }
}

void VChart_Intensity::SetValue(int Idx, double X, double Y, double Val)
{
    if( Idx < 0 || Idx >= m_Channels.size() )
        return;

    Channel_Intensity* tChannel = (Channel_Intensity*)m_Channels.at(Idx);
    tChannel->SetValue( X, Y, Val );
}

double VChart_Intensity::GetValue(int Idx, int XIdx, int YIdx)
{
    if( Idx < 0 || Idx >= m_Channels.size() )
        return 0.0;

    Channel_Intensity* tChannel = (Channel_Intensity*)m_Channels.at(Idx);
    double retVal = 0.0;
    vVertex retVertex;

    if( YIdx == 0 )
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );
        glGetBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx ), sizeof(vVertex), &retVertex );

        retVal = retVertex.val;

    }
    else if( YIdx == tChannel->YReso() - 1 )
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );
        glGetBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx + 1 ), sizeof(vVertex), &retVertex );

        retVal = retVertex.val;
    }
    else
    {
        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );
        glGetBufferSubData( GL_ARRAY_BUFFER, sizeof(vVertex) * ( 2 * XIdx + 1 ), sizeof(vVertex), &retVertex );

        retVal = retVertex.val;


//        glBindBuffer( GL_ARRAY_BUFFER, tChannel->m_ValuePoints.data()[YIdx] );
//        vVertex * Ptr1 = (vVertex *)glMapBuffer( GL_ARRAY_BUFFER, GL_READ_WRITE );

//        if( Ptr1 != NULL )
//        {
//            retVal = Ptr1[2 * XIdx].val;
//        }

//        glUnmapBuffer( GL_ARRAY_BUFFER );
    }

    return retVal;
}

void VChart_Intensity::UpdatePoints(int Idx)
{
    if( Idx < 0 || Idx >= m_Channels.size() )
        return;

    setBoundaries( m_AutoZoomMinX, m_AutoZoomMaxX, m_AutoZoomMinY, m_AutoZoomMaxY, false, true  );
//    TryUpdate();
}

void VChart_Intensity::PushUpPoints(int Idx)
{
    if( Idx < 0 || Idx >= m_Channels.size() )
        return;

    Channel_Intensity* tChannel = (Channel_Intensity*)m_Channels.at(Idx);
    for(int i = 0; i < tChannel->XReso(); i++)
    {
        for(int j = tChannel->YReso() - 1; j >= 0; j--)
        {
            if( j == 0 )
                SetValue(Idx, i, j, tChannel->MinVal() );
            else
                SetValue(Idx, i, j, GetValue( Idx, i, j - 1 )  );
        }
    }
}
