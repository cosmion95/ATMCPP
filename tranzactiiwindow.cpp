#include "tranzactiiwindow.h"
#include "ui_tranzactiiwindow.h"

#include "accountwindow.h"

TranzactiiWindow::TranzactiiWindow(Cont *cont, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TranzactiiWindow)
{
    ui->setupUi(this);
    this->cont = cont;

    //obtin lista de tranzactii asociate contului
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
    QSqlQuery sql;
    sql.prepare("select * from tranzactii where dinC = :idCont or inC = :idCont order by data desc");
    sql.bindValue(":idCont", cont->getId());
    sql.exec();
    while (sql.next()) {
        //adaug tranzactia in lista afisata pe ecran ca si string
        QString descriereTranzactie = "";
        //verific ce tip de tranzactie este
        if (sql.value(3).toString() == "TRANSFER"){
            descriereTranzactie = sql.value(3).toString() + " -- " + sql.value(4).toString() + " " + cont->getTip()->getCod() +  " in contul " + sql.value(2).toString() + ". Data operatie: " + sql.value(5).toString() + ". Mesaj: " + sql.value(6).toString();
        }
        else {
            descriereTranzactie = sql.value(3).toString() + " -- " + sql.value(4).toString() + " " + cont->getTip()->getCod() + ". Data: " + sql.value(5).toString();
        }
        ui->listaTranzactii->addItem(descriereTranzactie);
    }

    //setez toate tranzactiile ca fiind vazute in momentul intrarii pe pagina
    sql.prepare("update tranzactii set vazut='D' where dinC = :idCont");
    sql.bindValue(":idCont", cont->getId());
    sql.exec();
}

TranzactiiWindow::~TranzactiiWindow()
{
    delete ui;
}

void TranzactiiWindow::on_backButon_clicked()
{
    AccountWindow *accWin = new AccountWindow(cont);
    accWin->show();
    this->hide();
}
