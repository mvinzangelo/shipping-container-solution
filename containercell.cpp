#include "containercell.h"

ContainerCell::ContainerCell(QWidget *parent) : QPushButton(parent)
{
    setFixedHeight(80);
    setFixedWidth(80);
    cellColor = Qt::white;
    hoverColor = Qt::red;
    currStyleSheet = QString("QPushButton {"
                             "background-color: %1;"
                             "}")
                         .arg(cellColor.name());
    setStyleSheet(currStyleSheet);
}

void ContainerCell::updateInputType(int inputType)
{
    switch (inputType)
    {
    // loading mode
    case 0:
        currStyleSheet = QString("QPushButton {"
                                 "background-color: %1;"
                                 "}")
                             .arg(cellColor.name());
        setStyleSheet(currStyleSheet);
        break;
    // unloading mode
    case 1:
        setStyleSheet("");
        currStyleSheet = QString("QPushButton {"
                                 "background-color: %1;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: %2;"
                                 "}")
                             .arg(cellColor.name(), hoverColor.name());
        setStyleSheet(currStyleSheet);
        break;
    }
}

void ContainerCell::updateStyleSheet()
{
    currStyleSheet = QString("QPushButton {"
                             "background-color: %1;"
                             "}"
                             "QPushButton:hover {"
                             "background-color: %2;"
                             "}")
                         .arg(cellColor.name(), hoverColor.name());
    setStyleSheet(currStyleSheet);
}