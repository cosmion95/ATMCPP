#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"
#include "accountwindow.h"
#include "mainwindow.h"

#include "cont.h"
#include "moneda.h"

MainMenuWindow::MainMenuWindow(Client* client, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
    this->client = client;

    QString numeComplet = client->getNume() + " " + client->getPrenume() + ", bine ai revenit.";
    ui->numePrenumeLabel->setText(numeComplet);

    //obtin lista de conturi din db pe baza clientului
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
    QSqlQuery sql;
    sql.prepare("select * from conturi where client = :idClient");
    sql.bindValue(":idClient", client->getId());
    sql.exec();
    while (sql.next()) {
        //adaug contul in lista afisata pe ecran ca si string
        QString descriereCont = sql.value(0).toString() + " - " + sql.value(2).toString() + ", disponibil: " + sql.value(3).toString();
        ui->listaConturi->addItem(descriereCont);
    }
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}

void MainMenuWindow::on_alegeButon_clicked()
{
    //obtin contul ales din lista, extrag id-ul din string
    QString contString = ui->listaConturi->currentItem()->text();
    QString idContString = contString.simplified().split(" ")[0];

    int idCont = idContString.toInt();

    //obtin restul campurilor din db pentru a forma obiectul de tip CONT
    Cont* cont;
    QSqlQuery sql;
    sql.prepare("select * from conturi where id = :idCont");
    sql.bindValue(":idCont", idCont);
    sql.exec();
    while (sql.next()) {
        Moneda* m = new Moneda(sql.value(2).toString());
        QDate data = QDate::fromString(sql.value(4).toString(),"dd/MM/yyyy");
        cont = new Cont(idCont, m, sql.value(3).toFloat(), data, client);
    }

    //afisez noua fereastra si ascund fereastra curenta
    AccountWindow *accountWindow = new AccountWindow(cont,"");
    accountWindow->show();
    this->hide();

}

void MainMenuWindow::on_logoutButon_clicked()
{
    //inchid conexiunea la db si deschid fereastra anterioara
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
    this->hide();
}
