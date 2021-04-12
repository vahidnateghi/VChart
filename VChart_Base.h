#ifndef VCHART_BASE_H
#define VCHART_BASE_H

#include <QWidget>
#include <QGLWidget>
#include <QOpenGLFunctions_3_0>
#include <QMouseEvent>
#include <QEvent>
#include <QWheelEvent>
#include <QPointF>
#include <QElapsedTimer>
#include <QTimer>
#include "VChartDefines.h"
#include "Channels/Channel_Base.h"

#define MAX_VALUE 999999999999999999
#define MIN_VALUE -999999999999999999
#define MAX_DEPTH 10.0

class VChart_Base : public QGLWidget, protected QOpenGLFunctions_3_0
{
    Q_OBJECT
public:
    explicit VChart_Base(QWidget *parent = nullptr);

    int UpdateInterval() const;
    void setUpdateInterval(int UpdateInterval);

    QColor BackColor() const;
    void setBackColor(const QColor &BackColor);

    int DecimalRoundNumber() const;
    void setDecimalRoundNumber(int DecimalRoundNumber);

    bool ShowMouseAnnot() const;
    void setShowMouseAnnot(bool ShowMouseAnnot);

    QString Title() const;
    void setTitle(const QString &Title);

    QString XScale() const;
    void setXScale(const QString &XScale);

    QString YScale() const;
    void setYScale(const QString &YScale);

    void AdjustAsceptRatio();

    Enum_AutoZoomType AutoZoomType() const;
    void setAutoZoomType(const Enum_AutoZoomType &AutoZoomType);

    Enum_ZoomType ZoomType() const;
    void setZoomType(const Enum_ZoomType &ZoomType);

    void                    SetDefaultBoundaries(double left, double right, double bottom, double top);
    void                    SetRestrictions(bool LeftEn, double Left,
                                            bool RightEn, double Right,
                                            bool BotEn, double Bot,
                                            bool TopEn, double Top);

    void                    TryUpdate();
    virtual void            Clear();

    double MinYSpan() const;
    void setMinYSpan(double MinYSpan);

    double MinXSpan() const;
    void setMinXSpan(double MinXSpan);

    int AutoZoomInterval() const;
    void setAutoZoomInterval(int AutoZoomInterval);

    MsgType InfoType() const;
    void setInfoType(const MsgType &InfoType);

    void TrackMyClick();

    QColor GridColor() const;
    void setGridColor(const QColor &GridColor);

    QColor GridLabelColor() const;
    void setGridLabelColor(const QColor &GridLabelColor);

    QFont GridLabelFont() const;
    void setGridLabelFont(const QFont &GridLabelFont);

    bool ShowGridLines() const;
    void setShowGridLines(bool ShowGridLines);

    bool ShowGridLabels() const;
    void setShowGridLabels(bool ShowGridLabels);

    int InfoMaxAgeMS() const;
    void setInfoMaxAgeMS(int InfoMaxAgeMS);

protected:
    QElapsedTimer           m_RenderETimer;
    QElapsedTimer           m_AutoZoomETimer;
    bool                    m_IsMouseRightBtnPressed;
    bool                    m_IsMouseLeftBtnPressed;
    bool                    m_IsMouseInside;
    bool                    m_ShowInfo;
    bool                    m_ShowGridLines;
    bool                    m_ShowGridLabels;
    bool                    m_ShowMouseAnnot;
    bool                    m_RestrictionLeftEn;
    bool                    m_RestrictionRightEn;
    bool                    m_RestrictionTopEn;
    bool                    m_RestrictionBotEn;
    QPointF                 m_LastMousePos;
    QPointF                 m_MousePanBasePos;
    QPointF                 m_MouseBasePos;
    double                  m_BoundaryLeft;
    double                  m_BoundaryRight;
    double                  m_BoundaryBottom;
    double                  m_BoundaryTop;
    double                  m_BoundaryLeftDefault;
    double                  m_BoundaryRightDefault;
    double                  m_BoundaryBottomDefault;
    double                  m_BoundaryTopDefault;
    double                  m_RestrictionLeft;
    double                  m_RestrictionRight;
    double                  m_RestrictionTop;
    double                  m_RestrictionBot;
    double                  m_AutoZoomMaxX;
    double                  m_AutoZoomMinX;
    double                  m_AutoZoomMaxY;
    double                  m_AutoZoomMinY;
    double                  m_InforAlpha;
    int                     m_InfoMaxAgeMS;
    QTimer*                 m_MsgTimer;
    double                  m_MinXSpan;
    double                  m_MinYSpan;
    MsgType                 m_InfoType;
    int                     m_UpdateInterval;
    int                     m_AutoZoomInterval;
    int                     m_DecimalRoundNumber;
    QColor                  m_BackColor;
    QColor                  m_GridColor;
    QColor                  m_GridLabelColor;
    QFont                   m_GridLabelFont;
    QString                 m_Title;
    QString                 m_XScale;
    QString                 m_YScale;
    QString                 m_Message;
    QVector<Channel_Base *> m_Channels;
    Enum_AutoZoomType       m_AutoZoomType;
    Enum_ZoomType           m_ZoomType;
    bool                    m_TrackClick;
    ScopeMode               m_ScopeMode;


    virtual void            initializeGL();
    void                    resizeGL(int w, int h);
    void                    mouseMoveEvent(QMouseEvent *);
    void                    mousePressEvent(QMouseEvent *);
    void                    mouseReleaseEvent(QMouseEvent *);
    void                    enterEvent(QEvent *);
    void                    leaveEvent(QEvent *);
    void                    mouseDoubleClickEvent(QMouseEvent *);
    void                    wheelEvent(QWheelEvent *);

    void                    setBoundaries();
    void                    setBoundaries(double left, double right, double bottom, double top);
    void                    ForceUpdate();
    void                    CheckRestrictions();

    virtual void                    DoBackGrnPaitings();
    virtual void                    DoForeGrnPaitings();

    QPointF                 mouseToScopeCoor(QPointF);
    QPointF                 ScopeToMouseCoor(QPointF);
    QPointF                 mouseToScopeRatio(QPointF);
    QPointF                 ScopeToMouseRatio(QPointF);

private slots:
    void                    SltPrMsgTimerTimeout();

signals:
    void SgTrackedClick(QPointF);

};

#endif // VCHART_BASE_H
