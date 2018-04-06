#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "markovchain.h"
#include "signalatom.h"
#include <vector>
#include <tuple>
#include <QWidget>

// Probability Density Function of Normal distribution. Used in RGB colour scale function
struct N
{
    const   double TwoPi = 2*3.14159265;
            char    str[128];
    double  var1;
    double  var2;
            N(double v1, double v2) : var1(v1), var2(v2) {}
    float   operator () (double x) {
              //return exp(-(pow((x-mean),2)/2*pow(var,2)))/sqrt(TwoPi*pow(var,2));
                return (x > var1 && x <= var2) ? 1.0 : 0.0;
            }
    char*   tostr(double d) { sprintf(str, "%2.5f", d); return str; }
    char*   tostr() { sprintf(str, "%1.4f to %1.4f", var1, var2); return str; }
};

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit    GraphWidget(QWidget *parent = nullptr);
                ~GraphWidget();
    void        paintEvent(QPaintEvent *e);

    void        SetData(Matrix<float>* pma, vector<SignalAtom>* pstat) { pm=pma; pstates=pstat; }
    void        SetBounds(SignalAtom * pLow, SignalAtom* pHigh) { psaLow=pLow; psaHigh=pHigh; }
    void        SetRGBVariance(int slider_pos) { miRGBFactor = slider_pos; update(); }

signals:
    void        SetFields(const char* one, const char* two, const char* three);

public slots:

private:
    Matrix<float>* pm = nullptr;
    vector<SignalAtom>* pstates = nullptr;
    SignalAtom *psaLow = nullptr, *psaHigh = nullptr;
    int miRGBFactor = 1;
};

#endif // GRAPHWIDGET_H
