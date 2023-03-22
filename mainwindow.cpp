#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
    ui->cbProblemType->addItems({"Loading / Unloading", "Balancing"});
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

