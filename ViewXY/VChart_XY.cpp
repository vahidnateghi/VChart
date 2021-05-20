#include "VChart_XY.h"

VChart_XY::VChart_XY(QWidget *parent) : VChart_Base(parent)
{
}

void VChart_XY::AddChannel(QString Title, QColor PointColor, QColor LineColor, double PointSize, double LineSize, bool ShowPoints)
{
    Channel_Line* Chnl = new Channel_Line();

    Chnl->setTitle( Title );
    Chnl->setPointColor( PointColor );
    Chnl->setLineColor( LineColor );
    Chnl->setPointSize( PointSize );
    Chnl->setLineSize( LineSize );
    Chnl->setShowPoints( ShowPoints );

    m_Channels.append( Chnl );
}

void VChart_XY::Clear()
{
    VChart_Base::Clear();

    for(int i = 0; i < m_Channels.count(); i++)
    {
        Channel_Line *tChnls = (Channel_Line*)m_Channels.at(i);
        tChnls->Points()->clear();
    }
}

