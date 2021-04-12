#include "VChart_Radial.h"
#include <QtMath>

VChart_Radial::VChart_Radial(QWidget *parent) : VChart_Base(parent)
{
    m_CircleBufferCount                 = 4;
    m_CircleBufferLength                = 200;
    m_ShowCrossLines                    = false;
    m_CrossLineColor                    = Qt::white;
    m_ScopeMode                         = SMode_Polar;
    m_CircleBuffer                      = new GLuint[m_CircleBufferCount];
    for(int i = 0; i < m_CircleBufferCount; i++) m_CircleBuffer[i] = 0;

    m_MaxRange                          = qAbs(m_BoundaryLeft);
}

void VChart_Radial::setShowCrossLines(bool ShowCrossLines, QColor CrossLineColor)
{
    m_ShowCrossLines = ShowCrossLines;
    m_CrossLineColor = CrossLineColor;
}

void VChart_Radial::genCircleBuffer()
{
    for(int i = 0; i < m_CircleBufferCount; i++)
    {
        if( m_CircleBuffer[i] != 0 )
        {
            glDeleteBuffers(1, m_CircleBuffer + i );
        }

        glGenBuffers( 1, m_CircleBuffer + i );

        glBindBuffer( GL_ARRAY_BUFFER, m_CircleBuffer[i] );

        vVertex vertices[m_CircleBufferLength];
        double dt = 2.0 * M_PI / m_CircleBufferLength;
        double div = (double)m_MaxRange / (double)m_CircleBufferCount;
        for( int j = 0; j < m_CircleBufferLength; j++ )
        {
            double a = (i+1) * div * sin( j * dt );
            double b = (i+1) * div * cos( j * dt );
            vertices[j] = vVertex( a, b, 0, 1.0, 1.0, 1.0, 1.0 );
        }

        glBufferData( GL_ARRAY_BUFFER, sizeof(vVertex) * m_CircleBufferLength, vertices, GL_STATIC_DRAW );
    }
}

void VChart_Radial::initializeGL()
{
    VChart_Base::initializeGL();

    genCircleBuffer();
}

void VChart_Radial::DoBackGrnPaitings()
{
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    QColor ClearColor = m_BackColor;
    glClearColor( ClearColor.redF(), ClearColor.greenF(), ClearColor.blueF(), ClearColor.alphaF() );

    glClear( GL_COLOR_BUFFER_BIT );
    glClear( GL_DEPTH_BUFFER_BIT );

    double div = (double)m_MaxRange / (double)m_CircleBufferCount;
    if(m_ShowGridLines)
    {
        glEnableClientState( GL_VERTEX_ARRAY );

        glLineWidth( 2.0 );
        glColor4d( 200, 200, 200, 0.5 );
        for( int i = 0; i < m_CircleBufferCount; i++ )
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_CircleBuffer[i] );
            glVertexPointer( 3, GL_DOUBLE, sizeof(vVertex), 0 );
            glDrawArrays( GL_LINE_LOOP, 0, m_CircleBufferLength );
        }

        glDisableClientState( GL_VERTEX_ARRAY );
    }
    if( m_ShowGridLabelsX )
    {
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        QColor tColor = QColor( Qt::white );
        glColor3d( tColor.redF(), tColor.greenF(), tColor.blueF() );
        QFont font;
        font.setFamily("Arial");
        QFontMetrics fm(font);
        for( int i = 1; i <= m_CircleBufferCount; i++ )
        {
            QPointF Mouse = ScopeToMouseCoor( QPointF(0, i * div + 50) );
            renderText( -mouseToScopeRatio(QPointF( fm.width( N( i * div ) ) / 2.0, 0.0 )).x(), i * div, 0, N( i * div ) );
//            renderText( Mouse.x(), Mouse.y(), N( i * div ), fm );
        }
    }

    if(m_ShowCrossLines)
    {
//        glLineStipple(1, 0xCCCC);
//        glEnable(GL_LINE_STIPPLE);
        glColor4d( m_CrossLineColor.redF(), m_CrossLineColor.greenF(), m_CrossLineColor.blueF() ,0.1 );
        for(int i = 0 ; i < 180; i++)
        {
            glBegin( GL_LINE_STRIP );
            glVertex3d( qSin( ANGLE2RAD(i) ) * m_MaxRange,  qCos( ANGLE2RAD(i) ) * m_MaxRange, 0);
            glVertex3d( -qSin( ANGLE2RAD(i) ) * m_MaxRange,  -qCos( ANGLE2RAD(i) ) * m_MaxRange, 0 );
            glEnd();
        }
//        glDisable(GL_LINE_STIPPLE);
    }
}
