#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent = nullptr);
    QColor cellColor;
    QColor hoverColor;
    QString currStyleSheet;
    void updateInputType(int inputType);

private:
    void updateStyleSheet();
};

#endif // CONTAINERCELL_H
