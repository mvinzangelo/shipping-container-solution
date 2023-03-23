#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currentemployee.h"
#include "loadingunloadinginput.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ProblemType {
    LOAD_UNLOAD, BALANCING
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnEnter_clicked();

    void on_backButtonPS_clicked();

    void on_buttonImport_clicked();

    void on_buttonStartProblem_clicked();

    void on_backButtonLU_clicked();

private:
    Ui::MainWindow *ui;
    currentEmployee currOperator;
    QString currManifestPath;
    ProblemType currProblem;
    LoadingUnloadingInput *currLoadingUnloading;

};
#endif // MAINWINDOW_H
