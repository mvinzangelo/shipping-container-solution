#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent = nullptr);
    QColor cellColor;
    QColor hoverColor;
public slots:
    void updateInputType(int inputType);

private:
};

#endif // CONTAINERCELL_H
