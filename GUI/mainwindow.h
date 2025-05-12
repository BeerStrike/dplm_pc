#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "GUI/scanersmanadgerwidget.h"
#include "GUI/scanvisualizatorwidget.h"
#include "scancontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_networkSettingsBtn_triggered();
    void on_roonParametersConfigBtn_triggered();
    void on_scanerSetupUART_triggered();
private:
    ScanersManadgerWidget *smng;
    ScanVisualizatorWidget *scv;
    ScanController *scCtrl;
    Ui::MainWindow *ui;
    QSettings *settings;

};
#endif // MAINWINDOW_H
