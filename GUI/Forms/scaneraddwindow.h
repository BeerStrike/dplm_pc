#ifndef SCANERADDWINDOW_H
#define SCANERADDWINDOW_H

#include <QDialog>
#include <QUdpSocket>
#include "scancontroller.h"
namespace Ui {
class ScanerAddWindow;
}

class ScanerAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerAddWindow(ScanController *sc,QWidget *parent = nullptr);
    Scaner *getScaner();
    ~ScanerAddWindow();

private slots:
    void on_connectBtn_clicked();

private:
    ScanController *scCtrl;
    Scaner *scaner;
    Ui::ScanerAddWindow *ui;
};

#endif // SCANERADDWINDOW_H
