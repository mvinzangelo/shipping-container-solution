#include "shippingcontainergrid.h"
#include "qgridlayout.h"
#include "qpushbutton.h"
#include "containercell.h"
#include <QLabel>

ShippingContainerGrid::ShippingContainerGrid(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSizeConstraint(QLayout::SetFixedSize);

    for (int i = 0; i < columns + 1; i++)
    {
        for (int j = 0; j < rows + 1; j++)
        {
            if (i != 0 && j != rows)
            {
                QPushButton *cell = new ContainerCell(this);
                grid->addWidget(cell, j, i);

                // Set size text etc. for each button

                connect(cell, &QPushButton::clicked, [=]()
                        {
                            onCellPressed(rows - j, i); // Call the function which uses i and j here
                        });
            }
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
    qInfo() << i << j;
}
