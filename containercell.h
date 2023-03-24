#ifndef CONTAINERCELL_H
#define CONTAINERCELL_H

#include <QPushButton>

class ContainerCell : public QPushButton
{
public:
    ContainerCell(QWidget *parent = nullptr, QColor cellColor = Qt::white);
    QColor cellColor;
    QColor hoverColor = Qt::red;
    QString currStyleSheet;
    void updateInputType(int inputType);

private:
    void updateStyleSheet();
};

#endif // CONTAINERCELL_H
