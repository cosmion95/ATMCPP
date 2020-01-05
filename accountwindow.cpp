#include "accountwindow.h"
#include "ui_accountwindow.h"

#include "depunereextragerewindow.h"
#include "tranzactiiwindow.h"
#include "transferwindow.h"
#include "mainmenuwindow.h"

AccountWindow::AccountWindow(Cont* cont, QString msg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AccountWindow)
{
    ui->setupUi(this);
    this->cont = cont;
    QString contString = "Contul " + QString::number(cont->getId()) + ", moneda: " + cont->getTip()->getCod();
    QString disponibilString = "Disponibil: " + QString::number(cont->getDisponibil());

    ui->contLabel->setText(contString);
    ui->balanceLabel->setText(disponibilString);

    ui->msgLabel->setStyleSheet("QLabel {color : green; }");
    ui->msgLabel->setText(msg);

    //interoghez baza de date sa vad daca am tranzactii noi
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
    QSqlQuery sql;
    sql.prepare("select count(*) from tranzactii where (dinC = :idCont or inC = :idCont) and vazut = 'N'");
    sql.bindValue(":idCont", cont->getId());
    sql.exec();
    while (sql.next()) {
        if (sql.value(0).toInt() > 0){
            //anunt userul ca are tranzactii pe care nu le-a vazut
            QString msgTranz = "Aveti " + sql.value(0).toString() + " tranzactii noi.";
            ui->notifTransLabel->setStyleSheet("QLabel {color : green; }");
            ui->notifTransLabel->setText(msgTranz);
        }
    }

}

AccountWindow::~AccountWindow()
{
    delete ui;
}

void AccountWindow::on_extragereButon_clicked()
{
    //deschid fereastra de depunere/extragere cu parametru de cont si tip operatie
    DepunereExtragereWindow *depExtWin = new DepunereExtragereWindow(cont, 0);
    depExtWin->show();
    this->hide();
}

void AccountWindow::on_depunereButon_clicked()
{
    //deschid fereastra de depunere/extragere cu parametru de cont si tip operatie
    DepunereExtragereWindow *depExtWin = new DepunereExtragereWindow(cont, 1);
    depExtWin->show();
    this->hide();
}

void AccountWindow::on_transferButon_clicked()
{
    //deschid fereastra de transfer intre conturi
    TransferWindow *transfWin = new TransferWindow(cont);
    transfWin->show();
    this->hide();
}

void AccountWindow::on_backButon_clicked()
{
    MainMenuWindow *mainWin = new MainMenuWindow(cont->getClient());
    mainWin->show();
    this->hide();
}

void AccountWindow::on_transButon_clicked()
{
    //deschid un window cu lista de tranzactii in care a fost implicat acest cont
    TranzactiiWindow *transWin = new TranzactiiWindow(cont);
    transWin->show();
    this->hide();

}
