#ifndef SHIPPINGCONTAINERGRID_H
#define SHIPPINGCONTAINERGRID_H

#include "containercell.h"
#include <QWidget>
#include "qgridlayout.h"
#include "qpushbutton.h"
#include <QLabel>
#include <vector>
#include "manifest/manifest.h"
#include <map>
#include <QRandomGenerator>

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr, Ship *currShip = nullptr);
    void onCellPressed(int i, int j);
    int columns = 12;
    int rows = 8;
    int inputMode = 0;
    std::map<std::string, QColor> colorMap = {{"NAN", Qt::gray}, {"UNUSED", Qt::white}};
    ContainerCell *cellWidgets[8][12];
    std::vector<ContainerCell *> containersToLoad;
    std::vector<ContainerCell *> containersToUnload;
    void updateInputMode(int newMode);
    void updateManifestGUI();

signals:

private:
    void setHoverColor(QColor newHoverColor);
};

#endif // SHIPPINGCONTAINERGRID_H
