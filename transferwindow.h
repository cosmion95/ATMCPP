#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "cont.h"

namespace Ui {
class TransferWindow;
}

class TransferWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TransferWindow(Cont *cont, QWidget *parent = 0);
    ~TransferWindow();

private slots:
    void on_acceptButon_clicked();

    void on_renuntaButon_clicked();

private:
    Ui::TransferWindow *ui;
    Cont* cont;
};

#endif // TRANSFERWINDOW_H
