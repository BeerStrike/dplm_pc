#ifndef SCANERSETUPWINDOW_H
#define SCANERSETUPWINDOW_H

#include <QDialog>

namespace Ui {
class ScanerSetupWindow;
}

class ScanerSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerSetupWindow(QWidget *parent = nullptr);
    ~ScanerSetupWindow();

private:
    Ui::ScanerSetupWindow *ui;
};

#endif // SCANERSETUPWINDOW_H
