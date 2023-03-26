#include "shippingcontainergrid.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include <QLabel>
#include <QTimer>

ShippingContainerGrid::ShippingContainerGrid(QWidget *parent, Ship *currShip, int columns, int rows, std::map<std::string, QColor> *argColorMap)
    : QWidget{parent}
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSizeConstraint(QLayout::SetFixedSize);
    this->colorMap = argColorMap;
    this->columns = columns;
    this->rows = rows;
    animationTimer = new QTimer(this);
    animationTimer->setInterval(500);
    connect(animationTimer, &QTimer::timeout, [=]()
            { animateMovement(); });
    animationTimer->start();
    if (columns == 24 && rows == 4)
    {
        currSubject = BUFFER;
    }

    for (int i = 0; i < columns + 1; i++)
    {
        for (int j = 0; j < rows + 1; j++)
        {
            if (i != 0 && j != rows)
            {
                ContainerCell *cell;
                // ship case
                if (currSubject == SHIP)
                {
                    // is a container
                    if (!colorMap->count(currShip->bay[rows - j - 1][i - 1].name))
                    {
                        (*colorMap)[currShip->bay[rows - j - 1][i - 1].name] = QColor::fromRgb(QRandomGenerator::global()->generate());
                    }
                    cell = new ContainerCell(this, &currShip->bay[rows - j - 1][i - 1], colorMap);
                    grid->addWidget(cell, j, i);
                    cellWidgets[rows - j - 1][i - 1] = cell;
                    connect(cell, &QPushButton::clicked, [=]()
                            { onCellPressed(rows - j, i); });
                }
                // buffer case
                else
                {
                    if (!colorMap->count(currShip->buffer[rows - j - 1][i - 1].name))
                    {
                        (*colorMap)[currShip->buffer[rows - j - 1][i - 1].name] = QColor::fromRgb(QRandomGenerator::global()->generate());
                    }
                    cell = new ContainerCell(this, &currShip->buffer[rows - j - 1][i - 1], colorMap);
                    bufCellWidgets[rows - j - 1][i - 1] = cell;
                    grid->addWidget(cell, j, i);
                }
            }
            // labels on the left hand side
            else if (i == 0 && j != rows)
            {
                QLabel *label = new QLabel(this);
                QString str;
                QFont font = label->font();
                font.setPointSize(14);
                label->setFont(font);
                label->setAlignment(Qt::AlignCenter);
                label->setText(str.setNum(rows - j));
                grid->addWidget(label, j, i);
            }
            // labels on the bottom
            else if (i != 0 && j == rows)
            {
                QLabel *label = new QLabel(this);
                QString str;
                QFont font = label->font();
                font.setPointSize(14);
                label->setFont(font);
                label->setAlignment(Qt::AlignCenter);
                label->setText(str.setNum(i));
                grid->addWidget(label, j, i);
            }
        }
    }
}
void ShippingContainerGrid::onCellPressed(int i, int j)
{
    // Do stuff with i and j here
    if (currInputType == UNLOADING)
    {
        // cell is already being unloaded
        if (cellWidgets[i - 1][j - 1]->isBeingUnloaded)
        {
            for (unsigned x = 0; x < unloadContainers.size(); x++)
            {
                // remove that element from the vector
                if (unloadContainers.at(x)->name == cellWidgets[i - 1][j - 1]->currContainer->name)
                {
                    unloadContainers.erase(unloadContainers.begin() + x);
                }
            }
        }
        // cell is now being unloaded
        else
        {
            unloadContainers.push_back(cellWidgets[i - 1][j - 1]->currContainer);
        }
        // toggle cell to be unloaded
        cellWidgets[i - 1][j - 1]->toggleIsBeingUnloaded();
        qInfo() << QString::number(i - 1) << QString::number(j - 1);
    }
}

void ShippingContainerGrid::updateInputMode(int newMode)
{
    for (unsigned i = 0; i < rows; i++)
    {
        for (unsigned j = 0; j < columns; j++)
        {
            cellWidgets[i][j]->updateInputType(newMode);
        }
    }
    return;
}

void ShippingContainerGrid::renderNewShip(Ship *newShip)
{
    qInfo() << "SHIP NAME" << QString::fromStdString(newShip->manifestName);
    for (unsigned i = 0; i < columns; i++)
    {
        for (unsigned j = 0; j < rows; j++)
        {
            // render new buffer
            if (currSubject == BUFFER)
            {
                qInfo() << "RENDERING BUFFER AT" << QString::number(rows - j - 1) << QString::number(i);
                qInfo() << "CONTAINER NAME: " << QString::fromStdString(newShip->bay[rows - j - 1][i].name);
                // TODO: FIXME
                bufCellWidgets[rows - j - 1][i]->renderNewContainer(&(newShip->buffer[rows - j - 1][i]));
            }
            // render new ship
            else if (currSubject == SHIP)
            {
                qInfo() << "RENDERING SHIP AT" << QString::number(rows - j - 1) << QString::number(i);
                // TODO: FIXME
                qInfo() << "CONTAINER NAME: " << QString::fromStdString(newShip->bay[rows - j - 1][i].name);
                cellWidgets[rows - j - 1][i]->renderNewContainer(&(newShip->bay[rows - j - 1][i]));
            }
        }
    }
}

void ShippingContainerGrid::animateMovement()
{
    // do nothing if not set to animate
    if (curr_i < -2 && curr_j < -2)
    {
        return;
    }
    qInfo() << "CALL ANIMATE MOVEMENT";
    qInfo() << "curr_i: " << QString::number(curr_i);
    qInfo() << "curr_j: " << QString::number(curr_j);
    qInfo() << "target_i: " << QString::number(target_i);
    qInfo() << "target_j: " << QString::number(target_j);
    if (curr_i != target_i)
    {
        if (currSubject == SHIP)
        {
            cellWidgets[curr_i][curr_j]->flashColor(cellWidgets[start_i][start_j]->cellColor);
            if (curr_i < target_i)
            {
                curr_i++;
            }
            else
            {
                curr_i--;
            }
        }
    }
    else if (curr_j != target_j)
    {
        if (currSubject == SHIP)
        {
            cellWidgets[curr_i][curr_j]->flashColor(cellWidgets[start_i][start_j]->cellColor);
            if (curr_j < target_j)
            {
                curr_j++;
            }
            else
            {
                curr_j--;
            }
        }
    }
    else if (curr_i == target_i && curr_j == target_j)
    {
        curr_i = start_i;
        curr_j = start_j;
    }
}

void ShippingContainerGrid::setTargetAndStartContainers(int start_i, int start_j, int target_i, int target_j)
{
    if (start_i == -1 && start_j == -1)
    {
        this->start_i = 0;
        this->start_j = 7;
        this->curr_i = 0;
        this->curr_j = 7;
    }
    else
    {
        this->start_i = start_i;
        this->start_j = start_j;
        this->curr_i = start_i;
        this->curr_j = start_j;
    }
    if (target_i == -1 && target_j == -1)
    {
        this->target_i = 7;
        this->target_j = 0;
    }
    else
    {
        this->target_i = target_i;
        this->target_j = target_j;
    }
}