#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnEnter_clicked()
{
    currentEmploye.firstName = ui->lineFirstName->text();
    currentEmploye.lastName = ui->lineLastName->text();
    qInfo() << currentEmploye.firstName << currentEmploye.lastName;
}

