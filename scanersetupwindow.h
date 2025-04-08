#ifndef SCANERSETUPWINDOW_H
#define SCANERSETUPWINDOW_H

#include <QDialog>
#include <QVector3D>

namespace Ui {
class ScanerSetupWindow;
}

class ScanerSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerSetupWindow(QWidget *parent = nullptr);
    QVector3D getScanerPos();
    ~ScanerSetupWindow();

private slots:
    void on_OKButton_clicked();

private:
    Ui::ScanerSetupWindow *ui;
};

#endif // SCANERSETUPWINDOW_H
