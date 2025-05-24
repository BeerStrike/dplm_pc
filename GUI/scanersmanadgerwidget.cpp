#include "scanersmanadgerwidget.h"
#include "Forms/scanersetupwindow.h"
#include "Forms/scaneraddwindow.h"

ScanersManadgerWidget::ScanersManadgerWidget(ScanController *sc,int pcPort,int scanersPort,QWidget *parent)
    : QWidget{parent},scCtrl(sc)
{
    layout=new QVBoxLayout(this);
    scanerAddBtn=new QPushButton(this);
    scanerDeleteBtn=new QPushButton(this);
    scanerFindBtn=new QPushButton(this);
    scanerSetupBtn=new QPushButton(this);
    scanPauseBtn=new QPushButton(this);
    scanContinueBtn=new QPushButton(this);
    scanerAddBtn->setText("Добавить сканер");
    scanerDeleteBtn->setText("Удалить сканер");
    scanerFindBtn->setText("Поиск сканеров в сети");
    scanerSetupBtn->setText("Настроить сканер");
    scanPauseBtn->setText("Приостановить сканирование");
    scanContinueBtn->setText("Возобновить сканирование");
    scanersList=new QListWidget(this);
    scanersListLabel=new QLabel(this);
    scanersListLabel->setText("Cписок сканеров:");
    layout->addWidget(scanersListLabel);
    layout->addWidget(scanersList);
    layout->addWidget(scanerFindBtn);
    layout->addWidget(scanerAddBtn);
    layout->addWidget(scanerSetupBtn);
    layout->addWidget(scanerDeleteBtn);
    layout->addWidget(scanPauseBtn);
    layout->addWidget(scanContinueBtn);
    connect(scanerAddBtn,SIGNAL(clicked()),this,SLOT(on_scanerAddBtn_clicked()));
    connect(scanerDeleteBtn,SIGNAL(clicked()),this,SLOT(on_scanerDeleteBtn_clicked()));
    connect(scanerFindBtn,SIGNAL(clicked()),this,SLOT(on_scanerFindBtn_clicked()));
    connect(scanerSetupBtn,SIGNAL(clicked()),this,SLOT(on_scanerSetupBtn_clicked()));
    connect(scanPauseBtn,SIGNAL(clicked()),this,SLOT(on_scanPauseBtn_clicked()));
    connect(scanContinueBtn,SIGNAL(clicked()),this,SLOT(on_scanContinueBtn_clicked()));

    udpsrv=new UdpServer(pcPort,scanersPort,this);
    connect(udpsrv,SIGNAL(findScaner(QHostAddress,int)),this,SLOT(on_findScaner(QHostAddress,int)));
    scanersList->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);
}

void ScanersManadgerWidget::setPorts(int pcPort,int scanersPort)
{
    udpsrv->restart(pcPort);
    udpsrv->setScanersPort(scanersPort);
}

void ScanersManadgerWidget::clearList()
{
    sm.clear();
    scanersList->clear();
}


void ScanersManadgerWidget::addScaner(QHostAddress IP, int port)
{
    int i=0;
    for(;i<scCtrl->getScanersNum();i++)
        if(scCtrl->getScaner(i)->getIP()==IP){
            break;
        }
    if(i==scCtrl->getScanersNum()){
        Scaner *sc=scCtrl->addScaner(IP,port);
        connect(sc,SIGNAL(statusChanged(Scaner *)),this,SLOT(on_scanerStatusChanged(Scaner *)));
        QListWidgetItem * iw=new QListWidgetItem(scanersList);
        iw->setText(sc->getName()+": нет соединения");
        scanersList->addItem(iw);
        sm.insert(sc,iw);
    }
}

void ScanersManadgerWidget::on_scanerAddBtn_clicked()
{
    ScanerAddWindow *w=new ScanerAddWindow(scCtrl,this);
    w->exec();
    Scaner *sc=w->getScaner();
    if(sc==nullptr)
        return;
    connect(sc,SIGNAL(statusChanged(Scaner *)),this,SLOT(on_scanerStatusChanged(Scaner *)));
    QListWidgetItem * iw=new QListWidgetItem(scanersList);
    iw->setText(sc->getName()+": нет соединения");
    scanersList->addItem(iw);
    sm.insert(sc,iw);
    delete w;
}


void ScanersManadgerWidget::on_scanerSetupBtn_clicked()
{
    if(scanersList->currentItem()){
        ScanerSetupWindow* w=new ScanerSetupWindow(sm.key(scanersList->currentItem()),this);
        w->exec();
        delete w;
    }
}

void ScanersManadgerWidget::on_scanerDeleteBtn_clicked()
{
    if(scanersList->currentItem()){
        int row=scanersList->currentRow();
        scCtrl->removeScaner(sm.key(scanersList->currentItem()));
        sm.remove(sm.key(scanersList->currentItem()));
        delete scanersList->takeItem(row);
        scanersList->clearSelection();
    }
}


void ScanersManadgerWidget::on_scanerFindBtn_clicked()
{
    udpsrv->searchScaners();
}

void ScanersManadgerWidget::on_scanPauseBtn_clicked()
{
    scCtrl->pauseScan();
}

void ScanersManadgerWidget::on_scanContinueBtn_clicked()
{
    scCtrl->continueScan();
}

ScanersManadgerWidget::~ScanersManadgerWidget(){
    delete udpsrv;
}

void ScanersManadgerWidget::on_scanerStatusChanged(Scaner * sc)
{
    QString statusText;
    switch (sc->getStatus()){
    case Scaner::unconfigured:
        statusText="нет конфигурации";
        break;
    case Scaner::working:
        statusText="работает";
        break;
    case Scaner::not_connected:
        statusText="нет соединения";
        break;
    case Scaner::connected:
        statusText="соединено";
        break;
    case Scaner::pause:
        statusText="приостановлен";
        break;
    }
    sm[sc]->setText(sc->getName()+": "+statusText);
}


void ScanersManadgerWidget::on_findScaner(QHostAddress IP,int port)
{
   addScaner(IP,port);
}
