#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>
#include "manifest/manifest.h"

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent, Container *currContainer, std::map<std::string, QColor> &colorMap);
    QColor cellColor = Qt::white;
    QColor hoverColor = Qt::red;
    QString currStyleSheet;
    void updateInputType(int inputType);

private:
    void updateStyleSheet();
};

#endif // CONTAINERCELL_H
