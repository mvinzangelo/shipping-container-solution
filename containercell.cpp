#include "containercell.h"

ContainerCell::ContainerCell(QWidget *parent) : QPushButton(parent)
{
    setFixedHeight(80);
    setFixedWidth(80);
    cellColor = Qt::white;
    QColor hoverColor = Qt::red;
    QString cs1 = QString("QPushButton {"
                          "background-color: %1;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: %2;"
                          "}")
                      .arg(cellColor.name(), hoverColor.name());
    setStyleSheet(cs1);
}

void ContainerCell::updateInputType(int inputType)
{
    switch (inputType)
    {
    case 0:
        hoverColor = Qt::transparent;
        break;
    case 1:
        hoverColor = Qt::red;
        break;
    }
}
