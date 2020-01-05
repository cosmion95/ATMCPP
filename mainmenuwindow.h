#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "client.h"

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(Client* client, QWidget *parent = 0);
    ~MainMenuWindow();

private slots:
    void on_alegeButon_clicked();

    void on_logoutButon_clicked();

private:
    Ui::MainMenuWindow *ui;
    Client* client;

};

#endif // MAINMENUWINDOW_H
