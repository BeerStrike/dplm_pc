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
#include "scanvisualization.h"

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

    void on_UDPRecive();

    void on_scanerFindTimerTimeout();

    void on_scanerList_itemClicked(QListWidgetItem *item);

    void on_reciveScanResult(float x,float z,float h);
private:
    Ui::MainWindow *ui;
    ScanVisualization *scv;
    QSettings *settings;
    QUdpSocket *udpSocket;
    QTimer *scanerFindTimer;
    std::vector<Scaner *> scaners;

};
#endif // MAINWINDOW_H
