#ifndef SCANERSETUPWINDOW_H
#define SCANERSETUPWINDOW_H

#include <QDialog>
#include <QVector3D>
#include "scaner.h"
namespace Ui {
class ScanerSetupWindow;
}

class ScanerSetupWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ScanerSetupWindow(Scaner *scaner,QWidget *parent = nullptr);
    ~ScanerSetupWindow();

private slots:
    void on_OKButton_clicked();
private:
    Scaner *sc;
    Ui::ScanerSetupWindow *ui;
};

#endif // SCANERSETUPWINDOW_H
