#include "shippingcontainergrid.h"
#include "qgridlayout.h"
#include "qpushbutton.h"

ShippingContainerGrid::ShippingContainerGrid(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout * grid = new QGridLayout(this);

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            QPushButton * button = new QPushButton(this);
            grid->addWidget(button, j, i);

            // Set size text etc. for each button

            connect(button, &QPushButton::clicked, [=](){
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

