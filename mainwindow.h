#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct user {
    QString firstName;
    QString lastName;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnEnter_clicked();

private:
    Ui::MainWindow *ui;
    user currentEmploye;
};
#endif // MAINWINDOW_H
