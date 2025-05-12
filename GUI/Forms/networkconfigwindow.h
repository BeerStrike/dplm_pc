#ifndef NETWORKCONFIGWINDOW_H
#define NETWORKCONFIGWINDOW_H

#include <QDialog>
#include <QSettings>
namespace Ui {
class NetworkConfigWindow;
}

class NetworkConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkConfigWindow(QSettings *stngs,QWidget *parent = nullptr);
    ~NetworkConfigWindow();
private slots:
    void on_OKButton_clicked();

private:
    QSettings *settings;
    Ui::NetworkConfigWindow *ui;
};

#endif // NETWORKCONFIGWINDOW_H
