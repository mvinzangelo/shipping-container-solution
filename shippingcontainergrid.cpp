#include "shippingcontainergrid.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include "containercell.h"

ShippingContainerGrid::ShippingContainerGrid(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout * grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(0,0,0,0);
    grid->setSizeConstraint(QLayout::SetFixedSize);

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            QPushButton * cell = new ContainerCell(this);
            grid->addWidget(cell, j, i);

            // Set size text etc. for each button

            connect(cell, &QPushButton::clicked, [=](){
                onCellPressed(i, j);     // Call the function which uses i and j here
            });
        }
    }
}
void ShippingContainerGrid::onCellPressed(int i, int j)
{
    // Do stuff with i and j here
    qInfo() << i << j;
}

