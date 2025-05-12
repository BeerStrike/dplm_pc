#ifndef SCANVISUALIZATORWIDGET_H
#define SCANVISUALIZATORWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "ScanVisualization/scanvisualizationwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "scancontroller.h"
class ScanVisualizatorWidget : public QWidget
{
    Q_OBJECT
private:
    ScanVisualizationWidget *scv;
    QSlider *yawSlider;
    QSlider *pitchSlider;
    QSlider *zoomSlider;
    QLabel *yawSliderLabel;
    QLabel *pitchSliderLabel;
    QLabel *zoomSliderLabel;
    QVBoxLayout *yawSliderLayout;
    QVBoxLayout *zoomSliderLayout;
    QVBoxLayout *pitchSliderLayout;
    QHBoxLayout *layout;
private slots:
    void on_zoomSlider_sliderMoved(int position);
    void on_yawSlider_sliderMoved(int position);
    void on_pitchSlider_sliderMoved(int position);
    void on_newScanData();
public:
    explicit ScanVisualizatorWidget(ScanController *sc,QWidget *parent = nullptr);
signals:
};

#endif // SCANVISUALIZATORWIDGET_H
