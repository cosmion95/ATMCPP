#ifndef TRANZACTIIWINDOW_H
#define TRANZACTIIWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "cont.h"

namespace Ui {
class TranzactiiWindow;
}

class TranzactiiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TranzactiiWindow(Cont *cont, QWidget *parent = 0);
    ~TranzactiiWindow();

private slots:
    void on_backButon_clicked();

private:
    Ui::TranzactiiWindow *ui;
    Cont* cont;
};

#endif // TRANZACTIIWINDOW_H
