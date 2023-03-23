#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent = nullptr);
private:
    QColor cellColor;
    QColor hoverColor;
};

#endif // CONTAINERCELL_H
