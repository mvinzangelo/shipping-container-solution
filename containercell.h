#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>
#include "manifest/manifest.h"
#include <QTimer>

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent, Container *currContainer, std::map<std::string, QColor> *colorMap);
    QColor cellColor = Qt::white;
    QColor hoverColor = Qt::red;
    QString currStyleSheet;
    Container *currContainer;
    bool isBeingUnloaded = false;
    std::map<std::string, QColor> *currColorMap;

    void toggleIsBeingUnloaded();
    void updateInputType(int inputType);
    void renderNewContainer(Container *newContainer);
    void flashColor(QColor newColor);

private:
    void updateStyleSheet();
};

#endif // CONTAINERCELL_H
