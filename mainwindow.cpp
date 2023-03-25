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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnter_clicked()
{
    currOperator.setFirstName(ui->lineFirstName->text());
    currOperator.setLastName(ui->lineLastName->text());
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
    // call constructor for ship with manifest path
    std::string shipPath = currManifestPath.toStdString();
    currShip = new Ship(shipPath);
    // initialize input grid
    ShippingContainerGrid *inputGrid = new ShippingContainerGrid(nullptr, currShip);
    currInputGrid = inputGrid;
    inputGrid->loadingCollection = ui->loadingContents;
    // add grid to the input screen
    ui->gridContainer->addWidget(inputGrid, 0, 1);
    // change screen based off of problem type
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
    if (currInputGrid->currInputType == LOADING)
    {
        currInputGrid->currInputType = UNLOADING;
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
        currInputGrid->currInputType = LOADING;
        ui->btnInputType->setStyleSheet("background: #3657ff");
        ui->btnInputType->setText("Loading");
        if (currInputGrid)
        {
            currInputGrid->updateInputMode(0);
        }
        ui->loadInput->setEnabled(true);
    }
}

void MainWindow::on_btnAddContainer_clicked()
{
    // add new color to the color map
    if (!(*currInputGrid->colorMap).count(ui->lineContainerName->text().toStdString()))
    {
        (*currInputGrid->colorMap)[ui->lineContainerName->text().toStdString()] = QColor::fromRgb(QRandomGenerator::global()->generate());
    }
    // create new container for quantity and push into vector
    for (auto i = 0; i < ui->spinBoxQuantity->value(); i++)
    {
        std::string containerName = ui->lineContainerName->text().toStdString();
        int containerWeight = ui->lineContainerWeight->text().toInt();
        Container *containerToLoad = new Container(-1, -1, containerWeight, containerName);
        currInputGrid->loadContainers.push_back(containerToLoad);
        // update loading contents
        // create widget
        QWidget *container = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(container);
        container->setFixedHeight(120);
        QColor widgetColor = (*currInputGrid->colorMap)[ui->lineContainerName->text().toStdString()];
        QString styleSheet = QString("background: %1").arg(widgetColor.name());
        container->setStyleSheet(styleSheet);
        // create labels
        QLabel *nameText = new QLabel();
        QLabel *weightText = new QLabel();
        // set font of labels
        QFont font = QFont(weightText->font());
        font.setPointSize(14);
        nameText->setText(ui->lineContainerName->text());
        weightText->setText(ui->lineContainerWeight->text());
        nameText->setFont(font);
        weightText->setFont(font);
        // create remove button;
        QPushButton *deleteButton = new QPushButton();
        deleteButton->setText("Delete");
        deleteButton->setFont(font);
        deleteButton->setMaximumWidth(80);
        deleteButton->setMaximumHeight(30);
        connect(deleteButton, &QPushButton::clicked, [=]()
                { delete container;;});
        // add to layout
        layout->addWidget(nameText);
        layout->addWidget(weightText);
        layout->addWidget(deleteButton);
        // add to actual gui container
        ui->loadingContents->layout()->addWidget(container);
    }
    // reset ui elements
    ui->lineContainerName->clear();
    ui->lineContainerWeight->clear();
    ui->spinBoxQuantity->setValue(1);
}
