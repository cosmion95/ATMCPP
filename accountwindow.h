#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "cont.h"

namespace Ui {
class AccountWindow;
}

class AccountWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AccountWindow(Cont* cont, QString msg = "", QWidget *parent = 0);
    ~AccountWindow();

private slots:
    void on_extragereButon_clicked();

    void on_depunereButon_clicked();

    void on_transferButon_clicked();

    void on_backButon_clicked();

    void on_transButon_clicked();

private:
    Ui::AccountWindow *ui;
    Cont* cont;
};

#endif // ACCOUNTWINDOW_H
