#include <QtGui>
#include <QtCore>
#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{

}

GraphWidget::~GraphWidget()
{
}

/*void GraphWidget::SetFields(char *one, char *two, char *three)
{
}*/

void GraphWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), Qt::white);
    //p.setPen(Qt::NoPen);

    if (!pm || !pstates || !psaLow || !psaHigh)
        return; // Add exception handling here.
    QRect circ_rect(0, 0, 20, 20);

    double range = psaHigh->GetFreq() - psaLow->GetFreq();

    double x_per_range = size().width() / range;

    auto&& scale_to_xy = [&, this] (SignalAtom& atom) -> int {
        return (int)((atom.GetFreq() - psaLow->GetFreq()) * x_per_range);
    };

    SizeInfo s = pm->Dimensions();
    if (s.first)
    {
        QColor col(0,0,0);
        double&& factor = miRGBFactor+1;
        N Nblue(0, factor/100*0.4+0.1),
                Ngreen(factor/100*0.4+0.1, factor/100*0.7+0.1),
                Nred(factor/100*0.7+0.1, 1);
        SetFields(Nred.tostr(), Ngreen.tostr(), Nblue.tostr());
        QBrush br(col);
        size_t r = 0;
        for (SignalAtom& rowatom : *pstates)
        {
            size_t c = 0;
            for (SignalAtom& colatom : *pstates)
            {
                if ((*pm)(r,c))
                {
                    circ_rect.moveTo(scale_to_xy(rowatom), scale_to_xy(colatom));
                    float& d = (*pm)(r,c);
                    col.setRgb(Nred(d)*255.0, Ngreen(d)*255.0, Nblue(d)*255.0);
                    br.setColor(col);
                    p.setBrush(br);
                    p.drawEllipse(circ_rect);
                }
                c++;
            }
            r++;
        }
    }
}
