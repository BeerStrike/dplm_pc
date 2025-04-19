#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QCloseEvent>
#include <QSettings>
#include <QTimer>
#include <QUdpSocket>
#include <scaner.h>
#include <vector>
#include "visualization/scanvisualizationwidget.h"
#include "udpserver.h"
#include "room.h"
#include <QMap>
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
    void on_zoomSlider_sliderMoved(int position);

    void on_yawSlider_sliderMoved(int position);

    void on_pitchSlider_sliderMoved(int position);

    void on_networkSettingsBtn_triggered();

    void on_roonParametersConfigBtn_triggered();

    void on_addScanerBtn_clicked();

    void on_setupScanerBtn_clicked();

    void on_deleteScanerBtn_clicked();

    void on_findScanerBtn_clicked();

    void on_scanerSetupUART_triggered();

    void on_findScaner(QHostAddress IP);

    void on_scanerStatusChanged(Scaner *sc);
private:
    Room *room;
    UdpServer *udpsrv;
    Ui::MainWindow *ui;
    ScanVisualizationWidget *scv;
    QMap<Scaner *,QListWidgetItem *> sm;
    QSettings *settings;
    std::vector<Scaner *> scaners;

};
#endif // MAINWINDOW_H
