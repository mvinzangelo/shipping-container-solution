#include "mainwindow.h"
#include "shippingcontainergrid.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

void onCellPressed(int i, int j)
{
    // Do stuff with i and j here
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // UNCOMMENT TO START AT BEGINNING
    //ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
    ui->cbProblemType->addItems({"Loading / Unloading", "Balancing"});
    ShippingContainerGrid* grid = new ShippingContainerGrid();
    ui->gridContainer->addWidget(grid);
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
              QDir::currentPath(),
              "Text files (*.txt)");
    if( !manifestPath.isNull() )
        {
          // display the name of the file
          QStringList pathSplit = manifestPath.split("/");
          ui->textBrowser->setText(pathSplit.at(pathSplit.size()-1));
          currManifestPath = manifestPath;
        }
}


void MainWindow::on_buttonStartProblem_clicked()
{
    switch(ui->cbProblemType->currentIndex()) {
        case 0:
            currProblem = LOAD_UNLOAD;
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
