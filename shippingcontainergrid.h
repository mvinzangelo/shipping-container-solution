#ifndef SHIPPINGCONTAINERGRID_H
#define SHIPPINGCONTAINERGRID_H

#include <QWidget>
#include "qgridlayout.h"
#include "qpushbutton.h"
#include "containercell.h"
#include <QLabel>
#include <vector>

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr);
    void onCellPressed(int i, int j);
    int columns = 12;
    int rows = 8;
    int inputMode = 0;
    ContainerCell *cellWidgets[8][12];

signals:

private slots:
    void
    updateInputMode(int newMode);

private:
    void setHoverColor(QColor newHoverColor);
};

#endif // SHIPPINGCONTAINERGRID_H
