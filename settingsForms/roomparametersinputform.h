#ifndef ROOMPARAMETERSINPUTFORM_H
#define ROOMPARAMETERSINPUTFORM_H

#include <QDialog>
#include <QSettings>
namespace Ui {
class RoomParametersInputForm;
}

class RoomParametersInputForm : public QDialog
{
    Q_OBJECT

public:
    explicit RoomParametersInputForm(QSettings *stngs,QWidget *parent = nullptr);
    ~RoomParametersInputForm();

private slots:
    void on_OKBtn_clicked();

private:
    QSettings *settings;
    Ui::RoomParametersInputForm *ui;
};

#endif // ROOMPARAMETERSINPUTFORM_H
