#include "containercell.h"

ContainerCell::ContainerCell(QWidget *parent, Container *currContainer, std::map<std::string, QColor> &colorMap) : QPushButton(parent)
{
    setFixedHeight(80);
    setFixedWidth(80);
    setDisabled(true);
    setAttribute(Qt::WA_TranslucentBackground);
    this->currContainer = currContainer;
    if (currContainer != nullptr)
    {
        // if the container has
        if (currContainer->isContainer())
        {
            setText(QString::fromStdString(currContainer->name));
            setToolTip(QString::fromStdString(currContainer->name));
        }
    }
    cellColor = colorMap[currContainer->name];
    currStyleSheet = QString("QPushButton {"
                             "background-color: %1;"
                             "}"
                             "QPushButton:disabled {"
                             "color: black"
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
                                 "}"
                                 "QPushButton:disabled {"
                                 "color: black"
                                 "}")
                             .arg(cellColor.name());
        setStyleSheet(currStyleSheet);
        setDisabled(true);
        break;
    // unloading mode
    case 1:
        setStyleSheet("");
        if (currContainer->isContainer())
        {
            currStyleSheet = QString("QPushButton {"
                                     "background-color: %1;"
                                     "}"
                                     "QPushButton:hover {"
                                     "background-color: %2;"
                                     "}")
                                 .arg(cellColor.name(), hoverColor.name());
            setStyleSheet(currStyleSheet);
            setDisabled(false);
        }
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