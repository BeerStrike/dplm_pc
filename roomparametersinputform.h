#ifndef ROOMPARAMETERSINPUTFORM_H
#define ROOMPARAMETERSINPUTFORM_H

#include <QDialog>

namespace Ui {
class RoomParametersInputForm;
}

class RoomParametersInputForm : public QDialog
{
    Q_OBJECT

public:
    explicit RoomParametersInputForm(QWidget *parent = nullptr);
    float getW();
    float getL();
    float getH();
    float getXStep();
    float getZStep();
    ~RoomParametersInputForm();

private slots:
    void on_OKBtn_clicked();

private:
    Ui::RoomParametersInputForm *ui;
};

#endif // ROOMPARAMETERSINPUTFORM_H
