#include "scanvisualizatorwidget.h"

ScanVisualizatorWidget::ScanVisualizatorWidget(ScanController *sc,QWidget *parent)
    : QWidget{parent}
{
    scv=new ScanVisualizationWidget(sc,this);
    scv->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    yawSlider=new QSlider(this);
    pitchSlider=new QSlider(this);
    zoomSlider=new QSlider(this);
    yawSlider->setOrientation(Qt::Vertical);
    pitchSlider->setOrientation(Qt::Horizontal);
    zoomSlider->setOrientation(Qt::Vertical);
    connect(yawSlider,SIGNAL(sliderMoved(int)),this,SLOT(on_yawSlider_sliderMoved(int)));
    connect(pitchSlider,SIGNAL(sliderMoved(int)),this,SLOT(on_pitchSlider_sliderMoved(int)));
    connect(zoomSlider,SIGNAL(sliderMoved(int)),this,SLOT(on_zoomSlider_sliderMoved(int)));
    yawSliderLabel=new QLabel(this);
    pitchSliderLabel=new QLabel(this);
    zoomSliderLabel=new QLabel(this);
    yawSliderLabel->setText("Поворот по вертикали");
    pitchSliderLabel->setText("Поворот по горизонтали");
    zoomSliderLabel->setText("Приближение");
    yawSliderLayout=new QVBoxLayout();
    pitchSliderLayout=new QVBoxLayout();
    zoomSliderLayout=new QVBoxLayout();
    yawSliderLayout->addWidget(yawSlider);
    yawSliderLayout->addWidget(yawSliderLabel);
    pitchSliderLayout->addWidget(scv);
    pitchSliderLayout->addWidget(pitchSlider);
    pitchSliderLayout->addWidget(pitchSliderLabel);
    zoomSliderLayout->addWidget(zoomSlider);
    zoomSliderLayout->addWidget(zoomSliderLabel);
    layout=new QHBoxLayout(this);
    layout->addItem(zoomSliderLayout);
    layout->addItem(pitchSliderLayout);
    layout->addItem(yawSliderLayout);
}


void ScanVisualizatorWidget::on_zoomSlider_sliderMoved(int position)
{
    scv->setZoom(position);
}


void ScanVisualizatorWidget::on_yawSlider_sliderMoved(int position)
{
    scv->setCamYaw((position-50)/50.0*90.0);
}


void ScanVisualizatorWidget::on_pitchSlider_sliderMoved(int position)
{
    scv->setCamPitch((position-50)/50.0*180.0);
}

void ScanVisualizatorWidget::on_newScanData()
{
    scv->repaint();
}


