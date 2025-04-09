#ifndef SCANERUARTSETUPWINDOW_H
#define SCANERUARTSETUPWINDOW_H

#include <QDialog>
#include <QSerialPort>
namespace Ui {
class ScanerUARTSetupWindow;
}

class ScanerUARTSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerUARTSetupWindow(QWidget *parent = nullptr);
    ~ScanerUARTSetupWindow();

private slots:
    void on_connectBtn_clicked();

    void on_saveBtn_clicked();

    void on_UARTRecive();
private:
    QSerialPort *port;
    QByteArray jsonStr;
    int bracketCounter;
    Ui::ScanerUARTSetupWindow *ui;
};

#endif // SCANERUARTSETUPWINDOW_H
