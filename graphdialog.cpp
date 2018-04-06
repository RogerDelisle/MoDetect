#include "signalatom.h"
#include "markovchain.h"
#include "graphdialog.h"
#include "ui_graphdialog.h"

#include <iostream>

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog), mrpGraphWidget(ui->widget)
{
    ui->setupUi(this);

    ui->labelOne->setStyleSheet("QLabel { color : red; }");
    ui->labelTwo->setStyleSheet("QLabel { color : green; }");
    ui->labelThree->setStyleSheet("QLabel { color : blue; }");

    connect(mrpGraphWidget, &GraphWidget::SetFields, this, &GraphDialog::SetFields);

}

GraphDialog::~GraphDialog()
{
    delete ui;
    if (psaLow)
        delete psaLow;
    if (psaHigh)
        delete psaHigh;
}

void GraphDialog::SetBounds(SignalAtom *pLow, SignalAtom *pHigh)
{
    if ((!pLow && !psaLow) || (!pHigh && !psaHigh))
        return; // Fails silently for now.

    if (psaLow)
        delete psaLow;
    if (psaHigh)
        delete psaHigh;

    psaLow = new SignalAtom(*pLow);
    psaHigh = new SignalAtom(*pHigh);

    char minstr[128];
    char maxstr[128];

    char* prMaxStr = psaHigh->GetValueString(maxstr);
    ui->labelScaleMin->setText(psaLow->GetValueString(minstr));
    ui->labelScaleMaxX->setText(prMaxStr);
    ui->labelScaleMaxY->setText(prMaxStr);

    if (mrpGraphWidget)
        mrpGraphWidget->SetBounds(psaLow,psaHigh);
}

void GraphDialog::show() // May not need to override this in the end.
{
    QDialog::show();
}

void GraphDialog::SetFields(const char *one, const char *two, const char *three)
{
    ui->labelOne->setText(one);
    ui->labelTwo->setText(two);
    ui->labelThree->setText(three);
}

void GraphDialog::on_sliderRGBVar_sliderMoved(int position)
{
    if (mrpGraphWidget)
        mrpGraphWidget->SetRGBVariance(position);
}
