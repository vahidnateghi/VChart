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

    m_MaxRange                          = 2.0;
}

void VChart_Radial::setShowCrossLines(bool ShowCrossLines, QColor CrossLineColor)
{
    m_ShowCrossLines = ShowCrossLines;
    m_CrossLineColor = CrossLineColor;
}

int VChart_Radial::MaxRange() const
{
    return m_MaxRange;
}

void VChart_Radial::setMaxRange(int MaxRange)
{
    m_MaxRange = qAbs( MaxRange );

    m_BoundaryLeftDefault       = -1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomXCoef ) );
    m_BoundaryRightDefault      = +1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomXCoef ) );
    m_BoundaryBottomDefault     = -1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomYCoef ) );
    m_BoundaryTopDefault        = +1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomYCoef ) );

    m_BoundaryLeft              = -1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomXCoef ) );
    m_BoundaryRight             = +1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomXCoef ) );
    m_BoundaryBottom            = -1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomYCoef ) );
    m_BoundaryTop               = +1 * ( m_MaxRange + ( m_MaxRange / m_AutoZoomYCoef ) );

    genCircleBuffer();
//    resizeGL(width(), height());
    AdjustAsceptRatio();
    m_MaxRange = MaxRange;
}

void VChart_Radial::genCircleBuffer()
{
    makeCurrent();
    for(int i = 0; i < m_CircleBufferCount; i++)
    {
        if( m_CircleBuffer[i] == 0 )
        {
            glDeleteBuffers(1, &m_CircleBuffer[i] );
            m_CircleBuffer[i] = 0;
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

void VChart_Radial::DoForeGrnPaitings()
{
    double horDiff = m_BoundaryRight - m_BoundaryLeft;
    double verDiff = m_BoundaryTop - m_BoundaryBottom;

    double HorGapMult = 0.1;
    double VerGapMult = 0.2;

    double horStep = 0.0;
    double verStep = 0.0;

    if( m_AxisStyleX == AxisStyle_Near )
        VerGapMult = 0.0;
    else if( m_AxisStyleX == AxisStyle_Far )
        VerGapMult = 0.1;
    if( m_AxisStyleY ==  AxisStyle_Near )
        HorGapMult = 0.0;
    else if( m_AxisStyleY ==  AxisStyle_Far )
        HorGapMult = 0.1;

    if( m_AxisStyleX == AxisStyle_Near )
        verStep = ( m_BoundaryTop - m_BoundaryBottom ) / (VER_GRID_CNT+1);
    else if( m_AxisStyleX == AxisStyle_Far )
        verStep = ( verDiff - ( ( verDiff ) * VerGapMult ) ) / (VER_GRID_CNT+1);

    if( m_AxisStyleY == AxisStyle_Near )
        horStep = ( m_BoundaryRight - m_BoundaryLeft ) / (HOR_GRID_CNT+1);
    else if( m_AxisStyleY == AxisStyle_Far )
        horStep = ( horDiff - ( ( horDiff ) * HorGapMult ) ) / (HOR_GRID_CNT+1);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    if( m_IsMouseInside && m_ShowMouseAnnot )
    {
        QPointF pos = mouseToScopeCoor( m_LastMousePos );
        QFont font;
        font.setFamily( "Calibri" );
        font.setWeight( 75 );
        font.setPixelSize( 15 );

        glColor4d( 1.0, 1.0, 1.0, 1.0 );
        renderText( m_LastMousePos.x() + 13,
                    m_LastMousePos.y() + 25,
                    tr("( ")+QString::number(pos.x(), 'F', m_DecimalRoundNumber) + m_XScale+tr(", ")+QString::number(pos.y(), 'F', m_DecimalRoundNumber) + m_YScale +tr(" )"),
                    font);
    }

    if( m_IsMouseLeftBtnPressed && ( m_ZoomType == ZoomType_Square || m_ZoomType == ZoomType_WheelAndSquare ) )
    {
        QPointF pos1 = mouseToScopeCoor( m_LastMousePos );
        QPointF pos2 = mouseToScopeCoor( m_MouseBasePos );
        glColor4d( 0.5, 0.5, 0, 0.5 );
        glBegin( GL_QUADS );
        glVertex3d( pos1.x(), pos1.y(), 0 );
        glVertex3d( pos2.x(), pos1.y(), 0 );
        glVertex3d( pos2.x(), pos2.y(), 0 );
        glVertex3d( pos1.x(), pos2.y(), 0 );
        glEnd();
        glColor4d( 0.0, 1.0, 0, 0.5 );
        glBegin( GL_LINE_STRIP );
        glVertex3d( pos1.x(), pos1.y(), 0 );
        glVertex3d( pos2.x(), pos1.y(), 0 );
        glVertex3d( pos2.x(), pos2.y(), 0 );
        glVertex3d( pos1.x(), pos2.y(), 0 );
        glVertex3d( pos1.x(), pos1.y(), 0 );
        glEnd();
    }

    if( m_ShowLabels )
    {

        QFont font;
        font.setFamily( "Calibri" );
        font.setWeight( 75 );
        font.setPixelSize( 15 );
        glColor3d( 1.0, 1.0, 1.0 );
        for( int i = 0; i < m_Labels.count(); i++)
        {
            QPointF pos = ScopeToMouseCoor( m_Labels.at(i).first );
            renderText( pos.x(),
                        height() - pos.y(),
                        m_Labels.at(i).second,
                        font);
        }
    }

    if( m_InforAlpha > 0.0 )
    {
        if( m_InfoType == MsgType_Title )
        {
            glColor4d( 1.0, 1.0, 1.0, m_InforAlpha);
            QFont font;
            font.setPixelSize( 30 );
            font.setBold( true );
            QFontMetrics *fm = new QFontMetrics( font );
            int len = fm->horizontalAdvance( m_Title );
            renderText( width() / 2 - len / 2, 50, m_Title, font );
        }
        else if( m_InfoType == MsgType_Msg )
        {
            glColor4d( 1.0, 0.3, 0.0, m_InforAlpha );
            QFont font;
            font.setPixelSize( 30 );
            font.setBold( true );
            QFontMetrics *fm = new QFontMetrics( font );
            int len = fm->horizontalAdvance( m_Message );
            renderText( width() / 2 - len / 2, 50, m_Message, font );
        }
    }
}
