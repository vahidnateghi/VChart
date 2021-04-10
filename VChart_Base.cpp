#include "VChart_Base.h"
#include <QDebug>

VChart_Base::VChart_Base(QWidget *parent) : QGLWidget(parent)
{
    this->setMouseTracking( true );
    m_RenderETimer.start();
    m_AutoZoomETimer.start();

    m_IsMouseLeftBtnPressed                 = false;
    m_IsMouseRightBtnPressed                = false;
    m_IsMouseInside                         = false;
    m_ShowInfo                              = false;
    m_ShowGridLabels                        = true;
    m_ShowGridLines                         = true;
    m_ShowMouseAnnot                        = true;
    m_RestrictionLeftEn                     = false;
    m_RestrictionRightEn                    = false;
    m_RestrictionTopEn                      = false;
    m_RestrictionBotEn                      = false;
    m_TrackClick                            = false;

    m_Title                                 = "";
    m_XScale                                = "";
    m_YScale                                = "";
    m_Message                               = "";

    m_LastMousePos                          = QPointF(0,0);
    m_MousePanBasePos                       = QPointF(0,0);
    m_MouseBasePos                          = QPointF(0,0);

    m_BackColor                             = Qt::black;
    m_GridColor                             = Qt::white;
    m_GridLabelColor                        = Qt::cyan;

    m_ZoomType                              = ZoomType_WheelAndSquare;
    m_ScopeMode                             = SMode_Undefined;

    m_BoundaryLeft                          = -1000;
    m_BoundaryRight                         = 1000;
    m_BoundaryTop                           = 1000;
    m_BoundaryBottom                        = -1000;
    m_InforAlpha                            = 0.0;
//    m_AutoZoomMaxX                          = std::numeric_limits<double>::min();
//    m_AutoZoomMinX                          = std::numeric_limits<double>::max();
//    m_AutoZoomMaxY                          = std::numeric_limits<double>::min();
//    m_AutoZoomMinY                          = std::numeric_limits<double>::max();
    m_AutoZoomMaxX                          = MIN_VALUE;
    m_AutoZoomMinX                          = MAX_VALUE;
    m_AutoZoomMaxY                          = MIN_VALUE;
    m_AutoZoomMinY                          = MAX_VALUE;
    m_BoundaryLeftDefault                   = -1000;
    m_BoundaryRightDefault                  = 1000;
    m_BoundaryBottomDefault                 = -1000;
    m_BoundaryTopDefault                    = 1000;
    m_RestrictionLeft                       = -1000;
    m_RestrictionRight                      = 1000;
    m_RestrictionTop                        = 1000;
    m_RestrictionBot                        = -1000;
    m_MinXSpan                              = 1.0;
    m_MinYSpan                              = 1.0;

    m_GridLabelFont.setFamily( "Calibri" );
    m_GridLabelFont.setWeight( 30 );
    m_GridLabelFont.setPixelSize( 15 );

    m_AutoZoomType                          = AutoZoom_Default;

    m_InfoType                              = MsgType_None;

    m_UpdateInterval                        = 100;
    m_AutoZoomInterval                      = 1000;
    m_DecimalRoundNumber                    = 2;
}

// /////////////////////// PUBLIC

int VChart_Base::UpdateInterval() const
{
    return m_UpdateInterval;
}

/////////////////////////

void VChart_Base::setUpdateInterval(int UpdateInterval)
{
    m_UpdateInterval = UpdateInterval;
}

/////////////////////////

QColor VChart_Base::BackColor() const
{
    return m_BackColor;
}

/////////////////////////

void VChart_Base::setBackColor(const QColor &BackColor)
{
    m_BackColor = BackColor;
}

/////////////////////////

int VChart_Base::DecimalRoundNumber() const
{
    return m_DecimalRoundNumber;
}

/////////////////////////

void VChart_Base::setDecimalRoundNumber(int DecimalRoundNumber)
{
    m_DecimalRoundNumber = DecimalRoundNumber;
}

/////////////////////////

bool VChart_Base::ShowMouseAnnot() const
{
    return m_ShowMouseAnnot;
}

/////////////////////////

void VChart_Base::setShowMouseAnnot(bool ShowMouseAnnot)
{
    m_ShowMouseAnnot = ShowMouseAnnot;
}

/////////////////////////

QString VChart_Base::Title() const
{
    return m_Title;
}

/////////////////////////

void VChart_Base::setTitle(const QString &Title)
{
    m_Title = Title;
}

/////////////////////////

QString VChart_Base::XScale() const
{
    return m_XScale;
}

/////////////////////////

void VChart_Base::setXScale(const QString &XScale)
{
    m_XScale = XScale;
}

/////////////////////////

QString VChart_Base::YScale() const
{
    return m_YScale;
}

/////////////////////////

void VChart_Base::setYScale(const QString &YScale)
{
    m_YScale = YScale;
}

/////////////////////////

void VChart_Base::AdjustAsceptRatio()
{
    double ratio = (double)width() / (double)height();
//    double OldScopeWidth = m_BoundaryRight - m_BoundaryLeft;
    double OldScopeHeight = m_BoundaryTop - m_BoundaryBottom;

    double NewScopeWidth = OldScopeHeight * ratio;
    m_BoundaryLeft = -NewScopeWidth / 2.0;
    m_BoundaryRight = NewScopeWidth / 2.0;

    setBoundaries();
}

/////////////////////////

Enum_AutoZoomType VChart_Base::AutoZoomType() const
{
    return m_AutoZoomType;
}

/////////////////////////

void VChart_Base::setAutoZoomType(const Enum_AutoZoomType &AutoZoomType)
{
    m_AutoZoomType = AutoZoomType;
}

/////////////////////////

Enum_ZoomType VChart_Base::ZoomType() const
{
    return m_ZoomType;
}

/////////////////////////

void VChart_Base::setZoomType(const Enum_ZoomType &ZoomType)
{
    m_ZoomType = ZoomType;
}

/////////////////////////

void VChart_Base::SetDefaultBoundaries(double left, double right, double bottom, double top)
{
    m_BoundaryLeftDefault = left;
    m_BoundaryRightDefault = right;
    m_BoundaryTopDefault = top;
    m_BoundaryBottomDefault = bottom;

    m_BoundaryLeft = m_BoundaryLeftDefault;
    m_BoundaryRight = m_BoundaryRightDefault;
    m_BoundaryBottom = m_BoundaryBottomDefault;
    m_BoundaryTop = m_BoundaryTopDefault;
}

/////////////////////////

void VChart_Base::SetRestrictions(bool LeftEn, double Left, bool RightEn, double Right, bool BotEn, double Bot, bool TopEn, double Top)
{
    m_RestrictionLeftEn = LeftEn;
    m_RestrictionLeft = Left;
    m_RestrictionRightEn = RightEn;
    m_RestrictionRight = Right;
    m_RestrictionBotEn = BotEn;
    m_RestrictionBot = Bot;
    m_RestrictionTopEn = TopEn;
    m_RestrictionTop = Top;
}

// /////////////////////// PROTECTED

void VChart_Base::initializeGL()
{
    makeCurrent();
    initializeOpenGLFunctions();
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable( GL_COLOR_BUFFER_BIT );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
//    glDepthMask(GL_TRUE);
//    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 10.0f);
}

/////////////////////////

void VChart_Base::resizeGL(int w, int h)
{
    makeCurrent();

    glViewport( 0, 0, w, h );
    setBoundaries( );

    update();
}

/////////////////////////

void VChart_Base::mouseMoveEvent(QMouseEvent *e)
{
    m_LastMousePos = e->pos();

    if( m_IsMouseRightBtnPressed )
    {
        QPointF diff = mouseToScopeRatio( m_LastMousePos - m_MousePanBasePos );

        m_BoundaryLeft      -= diff.x();
        m_BoundaryRight     -= diff.x();
        m_BoundaryBottom    += diff.y();
        m_BoundaryTop       += diff.y();

        if(m_RestrictionLeftEn)
        {
            if( m_BoundaryLeft < m_RestrictionLeft && diff.x() > 0 )
            {
                m_BoundaryLeft      += diff.x();
                m_BoundaryRight     += diff.x();
            }
        }

        if(m_RestrictionRightEn)
        {
            if( m_BoundaryRight > m_RestrictionRight && diff.x() < 0 )
            {
                m_BoundaryLeft      += diff.x();
                m_BoundaryRight     += diff.x();
            }
        }

        if(m_RestrictionBotEn)
        {
            if( m_BoundaryBottom < m_RestrictionBot && diff.y() < 0 )
            {
                m_BoundaryBottom    -= diff.y();
                m_BoundaryTop       -= diff.y();
            }
        }

        if(m_RestrictionTopEn)
        {
            if( m_BoundaryTop > m_RestrictionTop && diff.y() > 0 )
            {
                m_BoundaryBottom    -= diff.y();
                m_BoundaryTop       -= diff.y();
            }
        }

        setBoundaries();
        m_MousePanBasePos = e->pos();
    }

    TryUpdate();
}

/////////////////////////

void VChart_Base::mousePressEvent(QMouseEvent *e)
{
    m_MouseBasePos = e->pos();
    if( e->buttons() == Qt::LeftButton )
    {
        m_IsMouseLeftBtnPressed = true;
    }
    else if( e->buttons() == Qt::RightButton )
    {
        m_MousePanBasePos = e->pos();
        m_IsMouseRightBtnPressed = true;
    }
}

/////////////////////////

void VChart_Base::mouseReleaseEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        m_IsMouseLeftBtnPressed = false;
        QPointF pos1 = mouseToScopeCoor( m_LastMousePos );
        QPointF pos2 = mouseToScopeCoor( m_MouseBasePos );

        if( m_TrackClick )
        {
            m_TrackClick = false;
            emit SgTrackedClick( pos1 );
        }
        if( qAbs(pos1.x() - pos2.x()) < (0.01 * qAbs(m_BoundaryRight - m_BoundaryLeft) ) ||
            qAbs(pos1.y() - pos2.y()) < (0.01 * qAbs(m_BoundaryTop - m_BoundaryBottom)))
            return;

        if( m_ZoomType == ZoomType_Square || m_ZoomType == ZoomType_WheelAndSquare )
        {
            double newLeft      = qMin( pos1.x(), pos2.x() );
            double newRight     = qMax( pos1.x(), pos2.x() );
            double newBottom    = qMin( pos1.y(), pos2.y() );
            double newTop       = qMax( pos1.y(), pos2.y() );

            double XSpan = newRight - newLeft;
            double YSpan = newTop - newBottom;

            if( XSpan >= m_MinXSpan )
            {
                m_BoundaryLeft = newLeft;
                m_BoundaryRight = newRight;
            }
            else
            {
                m_BoundaryLeft = newLeft;
                m_BoundaryRight = m_BoundaryLeft + m_MinXSpan;
            }

            if( YSpan >= m_MinYSpan )
            {
                m_BoundaryBottom = newBottom;
                m_BoundaryTop = newTop;
            }
            else
            {
                m_BoundaryBottom = newBottom;
                m_BoundaryTop = m_BoundaryBottom + m_MinYSpan;
            }

            setBoundaries();
        }
    }
    else if( e->button() == Qt::RightButton )
    {
        m_IsMouseRightBtnPressed = false;
    }
}

/////////////////////////

void VChart_Base::enterEvent(QEvent *)
{
    m_IsMouseInside = true;

    m_InforAlpha = 1.0;
}

/////////////////////////

void VChart_Base::leaveEvent(QEvent *)
{
    m_IsMouseInside = false;

    ForceUpdate();
}

/////////////////////////

void VChart_Base::mouseDoubleClickEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        if( m_AutoZoomType == AutoZoom_Default )
        {
            setBoundaries(m_BoundaryLeftDefault, m_BoundaryRightDefault, m_BoundaryBottomDefault, m_BoundaryTopDefault);
            if( m_ScopeMode == SMode_Polar )
                resizeGL( width(), height() );
        }
        else if( m_AutoZoomType == AutoZoom_Calculated )
        {
            setBoundaries( m_AutoZoomMinX, m_AutoZoomMaxX, m_AutoZoomMinY, m_AutoZoomMaxY );
        }
    }
    else if( e->button() == Qt::RightButton )
    {

    }
}

/////////////////////////

void VChart_Base::wheelEvent(QWheelEvent *e)
{
    if( m_ZoomType == ZoomType_MouseWheel || m_ZoomType == ZoomType_WheelAndSquare )
    {
        if( e->delta() > 0 )
        {
            QPointF PreZoomMouseCoor = mouseToScopeCoor( QPointF( e->pos().x(), e->pos().y() ) );

            m_BoundaryLeft      = 0.9 * m_BoundaryLeft;
            m_BoundaryRight     = 0.9 * m_BoundaryRight;
            m_BoundaryBottom    = 0.9 * m_BoundaryBottom;
            m_BoundaryTop       = 0.9 * m_BoundaryTop;

            m_BoundaryLeft      += (PreZoomMouseCoor.x() * 0.1);
            m_BoundaryRight     += (PreZoomMouseCoor.x() * 0.1);
            m_BoundaryBottom    += (PreZoomMouseCoor.y() * 0.1);
            m_BoundaryTop       += (PreZoomMouseCoor.y() * 0.1);
        }
        else
        {
            QPointF PreZoomMouseCoor = mouseToScopeCoor( QPointF( e->pos().x(), e->pos().y() ) );

            m_BoundaryLeft      = 1.1 * m_BoundaryLeft;
            m_BoundaryRight     = 1.1 * m_BoundaryRight;
            m_BoundaryBottom    = 1.1 * m_BoundaryBottom;
            m_BoundaryTop       = 1.1 * m_BoundaryTop;

            m_BoundaryLeft      -= (PreZoomMouseCoor.x() * 0.1);
            m_BoundaryRight     -= (PreZoomMouseCoor.x() * 0.1);
            m_BoundaryBottom    -= (PreZoomMouseCoor.y() * 0.1);
            m_BoundaryTop       -= (PreZoomMouseCoor.y() * 0.1);
        }

        CheckRestrictions();

        resizeGL( width(), height() );
    }
}

/////////////////////////

void VChart_Base::setBoundaries()
{
    makeCurrent();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( m_BoundaryLeft, m_BoundaryRight, m_BoundaryBottom , m_BoundaryTop, 0, MAX_DEPTH );
    glMatrixMode( GL_MODELVIEW);

    TryUpdate();
}

/////////////////////////

void VChart_Base::setBoundaries(double left, double right, double bottom, double top)
{
    if( right - left < 0.00001 )
    {
        m_BoundaryLeft = left - 0.5;
        m_BoundaryRight = left + 0.5;
    }
    else
    {
        m_BoundaryLeft = left;
        m_BoundaryRight = right;
    }

    if( top - bottom < 0.00001 )
    {
        m_BoundaryBottom = bottom - 0.5;
        m_BoundaryTop = bottom + 0.5;
    }
    else
    {
        m_BoundaryBottom = bottom;
        m_BoundaryTop = top;
    }
    setBoundaries();
}

/////////////////////////

void VChart_Base::TryUpdate()
{
    if( m_RenderETimer.elapsed() > m_UpdateInterval )
    {
        m_RenderETimer.restart();
        updateGL();
    }

    if( m_AutoZoomETimer.elapsed() > m_AutoZoomInterval && ( m_AutoZoomType == AutoZoom_PeriodicCalculated || m_AutoZoomType == AutoZoom_Calculated ) )
    {
        m_AutoZoomETimer.restart();
        if( m_AutoZoomMaxX  != std::numeric_limits<double>::min() &&
            m_AutoZoomMinX  != std::numeric_limits<double>::max() &&
            m_AutoZoomMaxY  != std::numeric_limits<double>::min() &&
            m_AutoZoomMinY  != std::numeric_limits<double>::max() )
        {
            if( m_AutoZoomType == AutoZoom_PeriodicCalculated )
            {
                setBoundaries( m_AutoZoomMinX, m_AutoZoomMaxX, m_AutoZoomMinY, m_AutoZoomMaxY );
            }
        }

        m_AutoZoomMaxX                          = MIN_VALUE;
        m_AutoZoomMinX                          = MAX_VALUE;
        m_AutoZoomMaxY                          = MIN_VALUE;
        m_AutoZoomMinY                          = MAX_VALUE;
    }
}

void VChart_Base::Clear()
{
    m_AutoZoomMaxX                          = std::numeric_limits<double>::min();
    m_AutoZoomMinX                          = std::numeric_limits<double>::max();
    m_AutoZoomMaxY                          = std::numeric_limits<double>::min();
    m_AutoZoomMinY                          = std::numeric_limits<double>::max();
}

double VChart_Base::MinYSpan() const
{
    return m_MinYSpan;
}

void VChart_Base::setMinYSpan(double MinYSpan)
{
    m_MinYSpan = MinYSpan;
}

double VChart_Base::MinXSpan() const
{
    return m_MinXSpan;
}

void VChart_Base::setMinXSpan(double MinXSpan)
{
    m_MinXSpan = MinXSpan;
}

int VChart_Base::AutoZoomInterval() const
{
    return m_AutoZoomInterval;
}

void VChart_Base::setAutoZoomInterval(int AutoZoomInterval)
{
    m_AutoZoomInterval = AutoZoomInterval;
}

MsgType VChart_Base::InfoType() const
{
    return m_InfoType;
}

void VChart_Base::setInfoType(const MsgType &InfoType)
{
    m_InfoType = InfoType;
}

/////////////////////////

void VChart_Base::TrackMyClick()
{
    m_TrackClick = true;
}

QColor VChart_Base::GridColor() const
{
    return m_GridColor;
}

void VChart_Base::setGridColor(const QColor &GridColor)
{
    m_GridColor = GridColor;
}

QColor VChart_Base::GridLabelColor() const
{
    return m_GridLabelColor;
}

void VChart_Base::setGridLabelColor(const QColor &GridLabelColor)
{
    m_GridLabelColor = GridLabelColor;
}

QFont VChart_Base::GridLabelFont() const
{
    return m_GridLabelFont;
}

void VChart_Base::setGridLabelFont(const QFont &GridLabelFont)
{
    m_GridLabelFont = GridLabelFont;
}

/////////////////////////

void VChart_Base::ForceUpdate()
{
    updateGL();
}

/////////////////////////

void VChart_Base::CheckRestrictions()
{
    bool Update = false;

    if( m_RestrictionLeftEn )
    {
        if( m_BoundaryLeft < m_RestrictionLeft )
        {
            m_BoundaryLeft = m_RestrictionLeft;
            Update = true;
        }
    }

    if( m_RestrictionRightEn )
    {
        if( m_BoundaryRight > m_RestrictionRight )
        {
            m_BoundaryRight = m_RestrictionRight;
            Update = true;
        }
    }

    if( m_RestrictionBotEn )
    {
        if( m_BoundaryBottom < m_RestrictionBot )
        {
            m_BoundaryBottom = m_RestrictionBot;
            Update = true;
        }
    }

    if( m_RestrictionTopEn )
    {
        if( m_BoundaryTop > m_RestrictionTop )
        {
            m_BoundaryTop = m_RestrictionTop;
            Update = true;
        }
    }

    if(Update)
        setBoundaries();
}

/////////////////////////

void VChart_Base::DoBackGrnPaitings()
{
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    QColor ClearColor = m_BackColor;
    glClearColor( ClearColor.redF(), ClearColor.greenF(), ClearColor.blueF(), ClearColor.alphaF() );

    glClear( GL_COLOR_BUFFER_BIT );
    glClear( GL_DEPTH_BUFFER_BIT );

    double horStep = ( m_BoundaryRight - m_BoundaryLeft ) / (HOR_GRID_CNT+1);
    double verStep = ( m_BoundaryTop - m_BoundaryBottom ) / (VER_GRID_CNT+1);

    if(m_ShowGridLines)
    {
        glLineStipple(1, 0x5555);
        glEnable(GL_LINE_STIPPLE);
        glColor4d( m_GridColor.redF(), m_GridColor.greenF(), m_GridColor.blueF(), 0.5 );

        for( int i = 1; i < HOR_GRID_CNT+ 1; i++ )
        {
            glBegin(GL_LINES);
            glVertex3d(m_BoundaryLeft + horStep * i, m_BoundaryBottom, 0);
            glVertex3d(m_BoundaryLeft + horStep * i, m_BoundaryTop, 0);
            glEnd();
        }

        for( int i = 1; i < VER_GRID_CNT + 1; i++ )
        {
            glBegin(GL_LINES);
            glVertex3d(m_BoundaryLeft  , m_BoundaryBottom + verStep * i, 0);
            glVertex3d(m_BoundaryRight , m_BoundaryBottom + verStep * i, 0);
            glEnd();
        }
        glDisable(GL_LINE_STIPPLE);
    }
    if(m_ShowGridLabels)
    {
        glColor3d( m_GridLabelColor.redF(), m_GridLabelColor.greenF(), m_GridLabelColor.blueF() );
        QPointF posRatio = mouseToScopeRatio(QPointF(5, 10));
        QFont font = m_GridLabelFont;
        for( int i = 1; i < HOR_GRID_CNT+ 1; i++ )
        {
            QPointF lPos = ScopeToMouseCoor(QPointF(m_BoundaryLeft + horStep*i, m_BoundaryTop - posRatio.y()));
            renderText( lPos.x(),
                        lPos.y(),
                        QString::number( m_BoundaryLeft + horStep*i,'F', m_DecimalRoundNumber),
                        font);
        }

        for( int i = 1; i < VER_GRID_CNT+ 1; i++ )
        {
            QPointF lPos = ScopeToMouseCoor(QPointF(m_BoundaryLeft + posRatio.x(), m_BoundaryBottom + verStep*i));
            renderText( lPos.x(),
                        lPos.y(),
                        QString::number(m_BoundaryBottom + verStep*i, 'F', m_DecimalRoundNumber),
                        font);
        }
    }
}

/////////////////////////

void VChart_Base::DoForeGrnPaitings()
{
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

    if( m_InforAlpha > 0 )
    {
        if( m_InfoType == MsgType_Title )
        {
            glColor4d( 1.0, 1.0, 1.0, m_InforAlpha );
            QFont font;
            font.setPixelSize( 30 );
            font.setBold( true );
            QFontMetrics *fm = new QFontMetrics( font );
            int len = fm->width( m_Title );
            renderText( width() / 2 - len / 2, 50, m_Title, font );
        }
        else if( m_InfoType == MsgType_Msg )
        {
            glColor4d( 1.0, 0.3, 0.0, m_InforAlpha );
            QFont font;
            font.setPixelSize( 30 );
            font.setBold( true );
            QFontMetrics *fm = new QFontMetrics( font );
            int len = fm->width( m_Message );
            renderText( width() / 2 - len / 2, 50, m_Message, font );
        }

        m_InforAlpha -= 0.1;
    }
}

/////////////////////////

QPointF VChart_Base::mouseToScopeCoor(QPointF p)
{
    double w = width();
    double h = height();

    double dBoundHor = m_BoundaryRight - m_BoundaryLeft;
    double dBoundVer = m_BoundaryTop - m_BoundaryBottom;

    double x = dBoundHor * p.x() / w + m_BoundaryLeft;
    double dy = height() - p.y();
    double y = (dBoundVer * dy / h + m_BoundaryBottom );

    return QPointF(x, y);
}

/////////////////////////

QPointF VChart_Base::ScopeToMouseCoor(QPointF p)
{
    double w = width();
    double h = height();

    double dBoundHor = m_BoundaryRight - m_BoundaryLeft;
    double dBoundVer = m_BoundaryTop - m_BoundaryBottom;

    double x = (p.x() - m_BoundaryLeft)*w / dBoundHor;
    double y = (p.y() - m_BoundaryBottom)*h / dBoundVer;

    return QPointF(x, y);
}

/////////////////////////

QPointF VChart_Base::mouseToScopeRatio(QPointF p)
{
    double w = width();
    double h = height();

    double dBoundHor = m_BoundaryRight - m_BoundaryLeft;
    double dBoundVer = m_BoundaryTop - m_BoundaryBottom;

    double x = p.x() * dBoundHor / w;
    double y = p.y() * dBoundVer / h;

    return QPointF(x, y);
}

/////////////////////////

QPointF VChart_Base::ScopeToMouseRatio(QPointF p)
{
    double w = width();
    double h = height();

    double dBoundHor = m_BoundaryRight - m_BoundaryLeft;
    double dBoundVer = m_BoundaryTop - m_BoundaryBottom;

    double x = p.x() * w / dBoundHor;
    double y = p.y() * h / dBoundVer;

    return QPointF(x, y);
}
