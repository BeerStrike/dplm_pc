#ifndef SCANERADDWINDOW_H
#define SCANERADDWINDOW_H

#include <QDialog>
#include <QUdpSocket>

namespace Ui {
class ScanerAddWindow;
}

class ScanerAddWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ScanerAddWindow(QUdpSocket *sct,QWidget *parent = nullptr);
    ~ScanerAddWindow();
    QHostAddress getIP();
    int getPort();
    bool isSuccess();
private slots:
    void on_connectBtn_clicked();

private:
    QHostAddress ip;
    int port;
    bool success;
    QUdpSocket *udpSocket;
    Ui::ScanerAddWindow *ui;
};

#endif // SCANERADDWINDOW_H
