#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

void onCellPressed(int i, int j)
{
    // Do stuff with i and j here
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // UNCOMMENT TO START AT BEGINNING
    ui->stackedWidget->setCurrentWidget(ui->screenLogFile);
    ui->cbProblemType->addItems({"Loading / Unloading", "Balancing"});
    currLogFile = new LogFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnEnter_clicked()
{
    if (currOperator.getFirstName() != "" || currOperator.getLastName() != "")
    {
        std::string fullName = currOperator.getFirstName().toStdString() + " " + currOperator.getLastName().toStdString();
        currLogFile->logEmployeeCheckOut(fullName);
    }
    currOperator.setFirstName(ui->lineFirstName->text());
    currOperator.setLastName(ui->lineLastName->text());
    ui->stackedWidget->setCurrentWidget(ui->screenSetUp);
    std::string fullName = ui->lineFirstName->text().toStdString() + " " + ui->lineLastName->text().toStdString();
    currLogFile->logEmployeeCheckIn(fullName);
    qInfo() << QString::fromStdString(fullName);
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
    currLogFile->logManifestOpen(*currShip);
    // change screen based off of problem type
    if (ui->cbProblemType->currentIndex() == 0)
    {
        if (currInputGrid)
        {

            delete currInputGrid;
        }
        // initialize input grid
        ShippingContainerGrid *inputGrid = new ShippingContainerGrid(nullptr, currShip);
        currInputGrid = inputGrid;
        inputGrid->loadingCollection = ui->loadingContents;
        // add grid to the input screen
        ui->gridContainer->addWidget(inputGrid, 0, 1);
        currProblem = LOAD_UNLOAD;
        ui->stackedWidget->setCurrentWidget(ui->screenInput);
        currLoadingUnloading = new LoadingUnloadingInput();
    }
    // if balancing problem
    else
    {
        // initialize input grid
        if (currShipGrid && currBufferGrid)
        {
            delete currShipGrid;
            delete currBufferGrid;
        }
        ShippingContainerGrid *shipGrid = new ShippingContainerGrid(nullptr, currShip);
        ShippingContainerGrid *bufferGrid = new ShippingContainerGrid(nullptr, currShip, 24, 4, shipGrid->colorMap);
        currShipGrid = shipGrid;
        currBufferGrid = bufferGrid;
        currProblem = BALANCING;
        // add grid to the input screen
        ui->operationGrid->addWidget(shipGrid, 0, 1, Qt::AlignLeft);
        ui->operationGrid->addWidget(bufferGrid, 1, 0, 1, 2, Qt::AlignHCenter);
        // alert user generating
        QMessageBox *msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("");
        msgbox->setText("Generating operations list...");
        msgbox->open();
        // TODO: CALL AI
        generateBalanceOperationsList();
        ui->stackedWidget->setCurrentWidget(ui->screenOperation);
        // alert user done generating
        msgbox->open();
        msgbox->setText("Generating operations complete.");
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
                { 
                    for (unsigned x = 0; x < currInputGrid->loadContainers.size(); x++) {
                        if (currInputGrid->loadContainers.at(x)->name == nameText->text().toStdString()) {
                            currInputGrid->loadContainers.erase(currInputGrid->loadContainers.begin() + x);
                            break;
                        }
                    }
                    delete container; });
        // add to layout
        layout->addWidget(nameText);
        layout->addWidget(weightText);
        layout->addWidget(deleteButton);
        // add to actual gui container
        ui->loadingContents->layout()->addWidget(container);
    }
    // reset ui elements
    ui->lineContainerName->clear();
    ui->lineContainerWeight->setValue(1);
    ui->spinBoxQuantity->setValue(1);
}

void MainWindow::on_buttonStartLoadingUnloading_clicked()
{
    if (currShipGrid && currBufferGrid)
    {
        delete currShipGrid;
        delete currBufferGrid;
    }
    ShippingContainerGrid *shipGrid = new ShippingContainerGrid(nullptr, currShip, 12, 8, currInputGrid->colorMap);
    ShippingContainerGrid *bufferGrid = new ShippingContainerGrid(nullptr, currShip, 24, 4, shipGrid->colorMap);
    currShipGrid = shipGrid;
    currBufferGrid = bufferGrid;
    // add grid to the input screen
    ui->operationGrid->addWidget(shipGrid, 0, 1, Qt::AlignLeft);
    ui->operationGrid->addWidget(bufferGrid, 1, 0, 1, 2, Qt::AlignHCenter);
    QMessageBox *msgbox = new QMessageBox(this);
    // alert user that it's generating
    msgbox->setWindowTitle("");
    msgbox->setText("Generating operations list...");
    msgbox->open();
    // TODO: CALL AI
    generateLoadingUnloadingOperationsList();
    ui->stackedWidget->setCurrentWidget(ui->screenOperation);
    // alert user done generating
    msgbox->open();
    msgbox->setText("Generating operations complete.");
}

void MainWindow::on_backButtonOperation_clicked()
{
    if (currProblem == LOAD_UNLOAD)
    {
        ui->stackedWidget->setCurrentWidget(ui->screenInput);
    }
    else if (currProblem == BALANCING)
    {
        ui->stackedWidget->setCurrentWidget(ui->screenSetUp);
    }
}

void MainWindow::on_cbLogFileResponse_currentIndexChanged(int index)
{
    if (index == 0)
    {
        ui->labelLogFileYear->setEnabled(true);
        ui->lineLogFileYear->setEnabled(true);
    }
    else
    {
        ui->labelLogFileYear->setEnabled(false);
        ui->lineLogFileYear->setEnabled(false);
    }
}

void MainWindow::on_buttonEnterApp_clicked()
{
    if (ui->cbLogFileResponse->currentIndex() == 1)
    {
        currLogFile->initLogFile(0, 2002);
    }
    else
    {
        currLogFile->initLogFile(1, ui->lineLogFileYear->text().toInt());
    }
    ui->stackedWidget->setCurrentWidget(ui->screenSignIn);
}

void MainWindow::on_buttonAddComment_clicked()
{
    std::string comment = ui->txtComment->toPlainText().toStdString();
    currLogFile->getOperatorMessage(comment);
    ui->txtComment->clear();
}

// TODO: CALL AI FUNCTIONS
void MainWindow::generateBalanceOperationsList()
{
    // TODO: CALL SYKLER
    // call function and set currOperationsList
    // calculate time to completion
    updateOperationsScreen(0);
}
void MainWindow::generateLoadingUnloadingOperationsList()
{
    // TODO: CALL CHAD
    // call function and set currOperationsList
    // calculate time to completion
}

void MainWindow::updateOperationsScreen(int index)
{
    AtomicMove *currMove = currOperationsList.at(index);
    currBufferGrid->renderNewShip(currMove->shipState);
    currShipGrid->renderNewShip(currMove->shipState);
    // set minutes left
    QString minutesLeftString;
    if (index == 0)
    {
        minutesLeftString = QString("%1 minutes left").arg(QString::number(minToCompleteCurrJob));
    }
    else
    {
        minToCompleteCurrJob -= currOperationsList.at(index - 1)->timeToMove;
        minutesLeftString = QString("%1 minutes left").arg(QString::number(minToCompleteCurrJob));
    }
    ui->labelMinutesLeft->setText(minutesLeftString);
    // set current move
    QString currentMove = QString("Current move: %1 to %2").arg(QString::fromStdString(currOperationsList.at(index)->containerToMove), QString::fromStdString(currOperationsList.at(index)->locationToMove));
    ui->labelCurrentMove->setText(currentMove);
    // set steps string
    QString currentSteps = QString("Step %1 of %2").arg(QString::number(index + 1), QString::number(currOperationsList.size()));
    ui->labelSteps->setText(currentSteps);
}
void MainWindow::on_buttonNextMove_clicked()
{

}

