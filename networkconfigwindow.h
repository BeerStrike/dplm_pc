#ifndef NETWORKCONFIGWINDOW_H
#define NETWORKCONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class NetworkConfigWindow;
}

class NetworkConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkConfigWindow(QWidget *parent = nullptr);
    ~NetworkConfigWindow();
    int getPCPort();
    int getScanerPort();
private slots:
    void on_OKButton_clicked();

private:
    Ui::NetworkConfigWindow *ui;
};

#endif // NETWORKCONFIGWINDOW_H
