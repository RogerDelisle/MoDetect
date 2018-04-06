#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signalatom.h"
#include "markovchain.h"
#include "graphdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushSimulate_clicked();

    void on_pushShowGraph_clicked();

private:
    Ui::MainWindow *ui;
    GraphDialog*    pGraphDialog = nullptr;
    Matrix<float>*  pm = nullptr;
    vector<SignalAtom> states;
};

#endif // MAINWINDOW_H
