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

enum SUBJECT
{
    SHIP,
    BUFFER
};

class ShippingContainerGrid : public QWidget
{
    Q_OBJECT
public:
    explicit ShippingContainerGrid(QWidget *parent = nullptr, Ship *currShip = nullptr, int columns = 12, int rows = 8, std::map<std::string, QColor> *colorMap = new std::map<std::string, QColor>({{"NAN", Qt::gray}, {"UNUSED", Qt::white}}));
    void onCellPressed(int i, int j);
    int columns = 12;
    int rows = 8;
    INPUT_TYPE currInputType = LOADING;
    QWidget *loadingCollection;
    SUBJECT currSubject = SHIP;
    int curr_i = -1;
    int curr_j = -1;
    int start_i = -1;
    int start_j = -1;
    int target_i = -1;
    int target_j = -1;
    std::vector<Container *> loadContainers;
    std::vector<QWidget *> loadContainersWidgets;
    std::vector<Container *> unloadContainers;
    std::map<std::string, QColor> *colorMap;
    ContainerCell *cellWidgets[8][12];
    ContainerCell *bufCellWidgets[8][12];
    QTimer *animationTimer;
    void updateInputMode(int newMode);
    void updateManifestGUI();
    void renderNewShip(Ship *newShip);
    void animateMovement();

signals:

private:
};

#endif // SHIPPINGCONTAINERGRID_H
