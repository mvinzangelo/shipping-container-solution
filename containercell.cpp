#include "containercell.h"

ContainerCell::ContainerCell(QWidget *parent) : QPushButton(parent)
{
    setFixedHeight(80);
    setFixedWidth(80);
    QColor cellColor = Qt::white;
    QColor hoverColor = Qt::red;
    QString cs1=QString("QPushButton {"
                   "background-color: %1;"
                   "color: rgb(0, 0, 0);"
                 "}"
                 "QPushButton:hover {"
                     "background-color: %2;"
                 "}").arg(cellColor.name(), hoverColor.name());
    setStyleSheet(cs1);
}
