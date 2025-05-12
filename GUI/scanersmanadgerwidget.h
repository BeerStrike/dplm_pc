#ifndef SCANERSMANADGERWIDGET_H
#define SCANERSMANADGERWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QVector>
#include <QMap>
#include "udpserver.h"
#include "scaner.h"
#include "room.h"
#include "combinatedheightmap.h"
#include "scancontroller.h"
class ScanersManadgerWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *scanerFindBtn;
    QPushButton *scanerAddBtn;
    QPushButton *scanerDeleteBtn;
    QPushButton *scanerSetupBtn;
    QListWidget *scanersList;
    QLabel *scanersListLabel;
    QVBoxLayout *layout;
    UdpServer *udpsrv;
    QMap<Scaner *,QListWidgetItem *> sm;
    ScanController *scCtrl;
    void addScaner(QHostAddress IP,int port);
private slots:
    void on_scanerAddBtn_clicked();
    void on_scanerSetupBtn_clicked();
    void on_scanerDeleteBtn_clicked();
    void on_scanerFindBtn_clicked();
    void on_findScaner(QHostAddress IP,int port);
public slots:
    void on_scanerStatusChanged(Scaner *sc);
public:
    explicit ScanersManadgerWidget(ScanController *sc,int pcPort,int scanersPort,QWidget *parent = nullptr);
    void setPorts(int pcPort,int scanersPort);
    void clearList();
    ~ScanersManadgerWidget();
signals:
    void newData();
};

#endif // SCANERSMANADGERWIDGET_H
