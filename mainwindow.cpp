#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

void onCellPressed(int i, int j)
{
    // Do stuff with i and j here
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // UNCOMMENT TO START AT BEGINNING
    // ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
    ui->cbProblemType->addItems({"Loading / Unloading", "Balancing"});
    ShippingContainerGrid *inputGrid = new ShippingContainerGrid();
    ui->gridContainer->addWidget(inputGrid, 0, 1);
    currInputGrid = inputGrid;
    for(int i = 0; i < 20; i++) {
    QPushButton * temp = new QPushButton();
    ui->loadingContents->layout()->addWidget(temp);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnter_clicked()
{
    currOperator.setFirstName(ui->lineFirstName->text());
    currOperator.setLastName(ui->lineLastName->text());
    qInfo() << currOperator.getFirstName() << currOperator.getLastName();
    ui->stackedWidget->setCurrentWidget(ui->screenSetUp);
}

void MainWindow::on_backButtonPS_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
}

void MainWindow::on_buttonImport_clicked()
{
    QString manifestPath = QFileDialog::getOpenFileName(
        this,
        "Open Document",
        QDir::homePath(),
        "Text files (*.txt)");
    if (!manifestPath.isNull())
    {
        // display the name of the file
        QStringList pathSplit = manifestPath.split("/");
        ui->textBrowser->setText(pathSplit.at(pathSplit.size() - 1));
        currManifestPath = manifestPath;
    }
}

void MainWindow::on_buttonStartProblem_clicked()
{
    switch (ui->cbProblemType->currentIndex())
    {
    case 0:
        currProblem = LOAD_UNLOAD;
        ui->stackedWidget->setCurrentWidget(ui->screenInput);
        currLoadingUnloading = new LoadingUnloadingInput();
        break;
    case 1:
        currProblem = BALANCING;
        break;
    }
}

void MainWindow::on_backButtonLU_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->screenSetUp);
}

void MainWindow::on_btnInputType_clicked()
{
    // loading -> unloading
    if (currLoadingUnloading->currInputType == LOADING)
    {
        currLoadingUnloading->currInputType = UNLOADING;
        ui->btnInputType->setText("Unloading");
        ui->btnInputType->setStyleSheet("background: rgb(255, 0, 0)");
        if (currInputGrid)
        {
            currInputGrid->updateInputMode(1);
        }
        ui->loadInput->setEnabled(false);
    }
    // unloading -> loading
    else
    {
        currLoadingUnloading->currInputType = LOADING;
        ui->btnInputType->setStyleSheet("background: #3657ff");
        ui->btnInputType->setText("Loading");
        if (currInputGrid)
        {
            currInputGrid->updateInputMode(0);
        }
        ui->loadInput->setEnabled(true);
    }
}
