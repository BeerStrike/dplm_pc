#ifndef ROOMPARAMETERSINPUTFORM_H
#define ROOMPARAMETERSINPUTFORM_H

#include <QDialog>
#include <QSettings>
#include "room.h"
namespace Ui {
class RoomParametersInputForm;
}

class RoomParametersInputForm : public QDialog
{
    Q_OBJECT

public:
    explicit RoomParametersInputForm(QSettings *stngs,QWidget *parent = nullptr);
    Room *getRoom();
    ~RoomParametersInputForm();

private slots:
    void on_saveBtn_clicked();
    void on_loadBtn_clicked();
private:
    Ui::RoomParametersInputForm *ui;
    Room *room;
    QSettings *settings;
};

#endif // ROOMPARAMETERSINPUTFORM_H
