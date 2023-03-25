#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currentemployee.h"
#include "loadingunloadinginput.h"
#include "shippingcontainergrid.h"
#include "manifest/manifest.h"
#include "logfile/logfile.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

enum ProblemType
{
    LOAD_UNLOAD,
    BALANCING
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ShippingContainerGrid *currInputGrid;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ship *currShip;
    LogFile *currLogFile;

private slots:

    void on_btnEnter_clicked();

    void on_backButtonPS_clicked();

    void on_buttonImport_clicked();

    void on_buttonStartProblem_clicked();

    void on_backButtonLU_clicked();

    void on_btnInputType_clicked();

    void on_btnAddContainer_clicked();

    void on_buttonStartLoadingUnloading_clicked();

    void on_backButtonOperation_clicked();

    void on_cbLogFileResponse_currentIndexChanged(int index);

    void on_buttonEnterApp_clicked();

private:
    Ui::MainWindow *ui;
    currentEmployee currOperator;
    QString currManifestPath;
    ProblemType currProblem;
    LoadingUnloadingInput *currLoadingUnloading;
};
#endif // MAINWINDOW_H
