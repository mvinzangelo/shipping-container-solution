#ifndef SHIPPINGCONTAINERGRID_H
#define SHIPPINGCONTAINERGRID_H

#include <QWidget>

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr);
    void onCellPressed(int i, int j);
    int columns = 12;
    int rows = 8;
    int inputMode = 0;

signals:

private slots:
    void updateInputMode(int newMode);

private:
    // void setHoverColor(Q)
};

#endif // SHIPPINGCONTAINERGRID_H
