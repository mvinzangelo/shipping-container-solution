#include "shippingcontainergrid.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include <QLabel>

ShippingContainerGrid::ShippingContainerGrid(QWidget *parent, Ship *currShip, int columns, int rows, std::map<std::string, QColor> *argColorMap)
    : QWidget{parent}
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSizeConstraint(QLayout::SetFixedSize);
    this->colorMap = argColorMap;
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
    for (unsigned i = 0; i < columns; i++)
    {
        for (unsigned j = 0; j < rows; j++)
        {
            // render new buffer
            if (currSubject == BUFFER)
            {
                bufCellWidgets[rows - j][i]->renderNewContainer(&(newShip->buffer[rows - j][i]));
            }
            // render new ship
            else
            {
                cellWidgets[rows - j][i]->renderNewContainer(&(newShip->bay[rows - j][i]));
            }
        }
    }
}
