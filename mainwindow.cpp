#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

#define MD_NO_SELECTION 0xFFFF
#define NO_OF_MODES 4

using namespace std;

using signal_data = pair<double, TimedPointDuration>;

struct modtype
{
    int                     mode_no;
    const char              name[128];
    function<signal_data()>  f ;
} modes[NO_OF_MODES] =

{ {1, "JT-65A", []() {
    return (signal_data(2.6917*((int)((double)rand()/RAND_MAX*64) + 2),
                       chrono::milliseconds(372)));
    }
  },
  {2, "JT-65B", []() {
   return (signal_data(2.6917*((int)((double)rand()/RAND_MAX*64) + 2)*2,
                      chrono::milliseconds(372)));
   }
  },
  {3, "JT-65C", []() {
   return (signal_data(2.6917*((int)((double)rand()/RAND_MAX*64) + 2)*4,
                      chrono::milliseconds(372)));
   }
  },
  {4, "RTTY", []() {
    return (signal_data(170*(int)((double)rand()/RAND_MAX*2),
                       chrono::milliseconds(244)));
    }
  }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load antenna icon. Credit: <div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from
    // <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a> is licensed by
    // <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
    QPixmap iconWhat(QString("support.png"));

    // Load question mark icon. Credit: <div>Icons made by <a href="http://www.freepik.com" title="Freepik">Freepik</a> from
    // <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a> is licensed by
    // <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0" target="_blank">CC 3.0 BY</a></div>
    QPixmap iconAntenna(QString("antenna_icon.png"));

    ui->comboModeSel->insertItem(0,QIcon(iconWhat),QString("Select Emission Mode"),QVariant((unsigned short)MD_NO_SELECTION));
    for (modtype& m : modes)
        ui->comboModeSel->insertItem(m.mode_no,QIcon(iconAntenna),QString(m.name),
                                     QVariant((unsigned short)m.mode_no));

    if (!pGraphDialog)
        pGraphDialog = new GraphDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pGraphDialog;
    if (pm)
        delete pm;
}

void MainWindow::on_pushSimulate_clicked()
{
    // Get selection from drop-down list.
    int sel = ui->comboModeSel->currentIndex();

    if ((sel == 0) || (sel == -1))
        return; // No item selected or combo box empty/invalid.

    QListWidget*& plist = ui->listWidget;
    plist->clear();

    int offset = sel - 1;

    MarkovChain<SignalAtom, float> mc;

    signal_data prev_data(0.0L, TimedPointDuration(0));

    for (int i =0; i < 100; i++)
    {
        signal_data&& dat = modes[offset].f();
        signal_data diff(dat.first-prev_data.first, dat.second);
        QString liststr("(%1 Hz, %2 us)");
        plist->addItem(liststr.arg(diff.first).arg(dat.second.count()));
        mc.GoToState(SignalAtom(diff.first, dat.second, 0.005));
        prev_data = dat;
    }

    /*for (int i =0; i < 32768; i++)
    mc.GoToState((int)((double)rand()/RAND_MAX*64));
    */
    if (states.size())
        states.clear();

    size_t dim = mc.GetStates(states);
    QStringList labels;
    for (auto& state : states) {
        char s[128];
        labels.push_back(QString(state.GetValueString(s)));
    }
    QTableWidget*& tw = ui->tableWidget;

    tw->clearContents();

    if (dim > tw->rowCount())
        tw->setRowCount(dim);
    if (dim > tw->columnCount())
        tw->setColumnCount(dim);

    tw->setHorizontalHeaderLabels(labels);
    tw->setVerticalHeaderLabels(labels);

    if (pm)
        delete pm;
    mc.GetTransitionMatrix(states, pm);

    int rh = 44; // Based on current UI geometry.
    //int wperchar = 20, edge = 10;

    for (size_t r = 0; r < dim; r++)
    {
        tw->setRowHeight(r, rh);
        for (size_t c = 0; c < dim; c++)
        {
            QString qs;
            qs.setNum((*pm)(r,c),'g',4);
            //int colw = max<int>(qs.size(), 4) * wperchar + edge;
            tw->setColumnWidth(c, max<int>(tw->columnWidth(c), 90)); // colw));
            tw->setItem(r, c, new QTableWidgetItem(qs));
        }
    }

    pGraphDialog->SetBounds(&(states.front()), &(states.back()));
    pGraphDialog->SetData(pm, &states);
}

void MainWindow::on_pushShowGraph_clicked()
{
    pGraphDialog->show();
}
