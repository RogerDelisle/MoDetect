#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include "graphwidget.h"
#include "signalatom.h"
#include "markovchain.h"
#include <QDialog>

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit    GraphDialog(QWidget *parent = 0);
                ~GraphDialog();
    void        SetData(Matrix<float>* pma, vector<SignalAtom>* pstat)
                    { if (mrpGraphWidget) mrpGraphWidget->SetData(pma,pstat); }
    void        SetBounds(SignalAtom * pLow, SignalAtom* pHigh);

public slots:
    void        show();
    void        SetFields(const char *one, const char *two, const char *three);

private slots:
    void on_sliderRGBVar_sliderMoved(int position);

private:
    Ui::GraphDialog *ui;
    GraphWidget*&    mrpGraphWidget;
    SignalAtom *psaLow = nullptr, *psaHigh = nullptr;
};

#endif // GRAPHDIALOG_H
