#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currentemployee.h"
#include "loadingunloadinginput.h"
#include "shippingcontainergrid.h"
#include "manifest/manifest.h"
#include "logfile/logfile.h"
#include "atomicmove.h"
#include "balance/balance.h"
#include "node/Node.h"

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
    ShippingContainerGrid *currShipGrid;
    ShippingContainerGrid *currBufferGrid;
    std::vector<AtomicMove *> currOperationsList;
    int minToCompleteCurrJob = 0;
    int currOperationIndex = 0;
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

    void on_buttonAddComment_clicked();

    void generateBalanceOperationsList();

    void generateLoadingUnloadingOperationsList();

    void updateOperationsScreen(int index);

    void on_buttonNextMove_clicked();

    void on_btnLogOut_clicked();

private:
    Ui::MainWindow *ui;
    currentEmployee currOperator;
    QString currManifestPath;
    ProblemType currProblem;
    LoadingUnloadingInput *currLoadingUnloading;
};
#endif // MAINWINDOW_H
