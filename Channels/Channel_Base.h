#ifndef CHANNEL_BASE_H
#define CHANNEL_BASE_H

#include <QObject>
#include "VChartDefines.h"

class Channel_Base : public QObject
{
    Q_OBJECT
public:
    explicit Channel_Base(QObject *parent = nullptr);

    void setIsVisible(bool IsVisible);
    void setTitle(const QString &Title);
    void setShowLabels(bool ShowLabels);

    QString Title() const;
    bool IsVisible() const;
    bool ShowLabels() const;

    virtual void PrepToRemove(){ }

    QColor PointColor() const;
    void setPointColor(const QColor &PointColor);

    QColor LineColor() const;
    void setLineColor(const QColor &LineColor);

private:
    bool m_IsVisible;
    bool m_ShowLabels;
    QString m_Title;
    QColor  m_PointColor;
    QColor m_LineColor;
};

#endif // CHANNEL_BASE_H
