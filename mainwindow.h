#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "currentemployee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnEnter_clicked();

    void on_backButtonPS_clicked();

    void on_buttonImport_clicked();

private:
    Ui::MainWindow *ui;
    currentEmployee currOperator;
};
#endif // MAINWINDOW_H
