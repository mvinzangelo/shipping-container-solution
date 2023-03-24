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
#include "loadingunloadinginput.h"

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr, Ship *currShip = nullptr);
    void onCellPressed(int i, int j);
    int columns = 12;
    int rows = 8;
    INPUT_TYPE currInputType = LOADING;
    QWidget *loadingCollection;
    std::vector<Container *> loadContainers;
    std::vector<Container *> unloadContainers;
    std::map<std::string, QColor> *colorMap = new std::map<std::string, QColor>({{"NAN", Qt::gray}, {"UNUSED", Qt::white}});
    ContainerCell *cellWidgets[8][12];
    void updateInputMode(int newMode);
    void updateManifestGUI();

signals:

private:
};

#endif // SHIPPINGCONTAINERGRID_H
