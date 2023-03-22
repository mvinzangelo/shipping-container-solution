#ifndef SHIPPINGCONTAINERGRID_H
#define SHIPPINGCONTAINERGRID_H

#include <QWidget>

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr);
    void onCellPressed(int i, int j);

signals:

};

#endif // SHIPPINGCONTAINERGRID_H
