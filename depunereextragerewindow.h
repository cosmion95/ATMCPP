#ifndef DEPUNEREEXTRAGEREWINDOW_H
#define DEPUNEREEXTRAGEREWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include "cont.h"

namespace Ui {
class DepunereExtragereWindow;
}

class DepunereExtragereWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DepunereExtragereWindow(Cont* cont, int tip, QWidget *parent = 0);
    ~DepunereExtragereWindow();
    float extragere();
    void setDisponibil(float newDisponibil, QString tipTranzactie);

private slots:
    void on_acceptButon_clicked();

    void on_renuntaButon_clicked();

private:
    Ui::DepunereExtragereWindow *ui;
    Cont* cont;
    int tip;
};

#endif // DEPUNEREEXTRAGEREWINDOW_H
