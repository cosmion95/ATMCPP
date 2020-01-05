#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenuwindow.h"

#include "adresa.h"
#include "client.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
    connect(ui->userInput, SIGNAL(textChanged()), this, SLOT(checkLineEdits()));
    connect(ui->passInput, SIGNAL(textChanged()), this, SLOT(checkLineEdits()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

//verifica daca au fost completate campurile de user si parola pentru activarea butonului de login
void MainWindow::checkLineEdits()
{
    qInfo()<<"apel check line edits";
    bool ok = !ui->userInput->text().isEmpty() && !ui->passInput->text().isEmpty();
    ui->loginButton->setEnabled(ok);
}

void MainWindow::on_loginButton_clicked()
{
    QString user, password;
    user = ui->userInput->text();
    password = ui->passInput->text();
    QSqlQuery sql;
    sql.prepare("select count(*) from clienti where username = :name and password = :pass");
    sql.bindValue(":name", user);
    sql.bindValue(":pass", password);
    sql.exec();
    while (sql.next()) {
        int returnValue = sql.value(0).toInt();
        if (returnValue > 0){
            //login cu succes
            //obtin informatiile despre utilizatorul conectat pana reusesc sa formez obiectul
            sql.prepare("select * from clienti where username = :name and password = :pass");
            sql.bindValue(":name", user);
            sql.bindValue(":pass", password);

            //campuri necesare pentru client
            int id;
            QString nume, prenume;
            QString juridicaString;
            bool juridica;
            //QDate dataInregistrare;
            QString dataInreg;
            int idAdresa;

            sql.exec();
            while (sql.next()) {
                id = sql.value(0).toInt();
                nume = sql.value(1).toString();
                prenume = sql.value(2).toString();
                juridicaString = sql.value(5).toString();
                dataInreg = sql.value(6).toString();
                idAdresa = sql.value(7).toInt();
            }

            //tratez campul pentru persoana juridica
            if (juridicaString == "N"){
                juridica = false;
            }
            else {
                juridica = true;
            }

            //obtin datele pentru obiectul de adresa
            Adresa* adresa;
            sql.prepare("select * from adrese where id = :idAdr");
            sql.bindValue(":idAdr", idAdresa);
            sql.exec();
            while (sql.next()) {
                adresa = new Adresa(idAdresa, sql.value(1).toString(), sql.value(2).toString(), sql.value(3).toString(), sql.value(4).toString(), sql.value(5).toString(), sql.value(6).toString());
            }

            //convertesc data din string in date
            QDate data = QDate::fromString(dataInreg,"dd/MM/yyyy");

            //formez clientul
            Client* client = new Client(id, nume, prenume, user, juridica, data, adresa);


            qInfo()<<id << " " << nume << " " << prenume << " " << juridicaString << ' ' << idAdresa << " " << dataInreg;

            //deschid fereastra cu meniul principal si cu userul curent -- obiectul de client creat
            MainMenuWindow *mainMenu = new MainMenuWindow(client);
            mainMenu->show();
            this->hide();

            db.close();
        }
        else {
            //login failed
            //anunt userul ca ceva nu e ok
            ui->loginResult->setStyleSheet("QLabel {color : red; }");
            ui->loginResult->setText("User sau parola incorecte.");
        }
    }
}
