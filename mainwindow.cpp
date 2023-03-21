#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
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

