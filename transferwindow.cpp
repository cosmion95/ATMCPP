#include "transferwindow.h"
#include "ui_transferwindow.h"
#include "accountwindow.h"

TransferWindow::TransferWindow(Cont *cont, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TransferWindow)
{
    ui->setupUi(this);
    this->cont = cont;

    QString contString = "Contul " + QString::number(cont->getId()) + ", moneda: " + cont->getTip()->getCod();
    QString disponibilString = "Disponibil: " + QString::number(cont->getDisponibil());

    ui->contLabel->setText(contString);
    ui->disponibilLabel->setText(disponibilString);

    //fortez utilizatorul sa introduca numai cifre ca si valoare, fara sa depaseasca numarul de cifre pe care il are in cont
    ui->valoareEdit->setValidator( new QIntValidator(0, (int)cont->getDisponibil()*10, this) );
    ui->inContEdit->setValidator(new QIntValidator(0, 1000, this));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
}

TransferWindow::~TransferWindow()
{
    delete ui;
}

void TransferWindow::on_acceptButon_clicked()
{
    //verific daca contul cautat este acelasi cu contul curent
    if (cont->getId() == ui->inContEdit->text().toInt()){
        //afisez mesaj de eroare
        ui->infoLabel->setStyleSheet("QLabel {color : red; }");
        ui->infoLabel->setText("Eroare. Nu puteti efectua transferuri intre acelasi cont");
    }
    else{
        //verific daca valoarea introdusa este mai mica decat disponibilul in cont
        //asta este valoarea introdusa, care trebuie scazuta din contul curent
        float valoare = ui->valoareEdit->text().toFloat();
        //calculez dobanda la 1%
        float dobanda = valoare * 0.01;
        if (valoare+dobanda > cont->getDisponibil()){
            //eroare, fonduri insuficiente
            //afisez mesaj de eroare
            ui->infoLabel->setStyleSheet("QLabel {color : red; }");
            ui->infoLabel->setText("Eroare. Fonduri insuficiente.");
        }
        else{
            bool checkCont = false;

            Cont *contDest;

            int inCont = ui->inContEdit->text().toInt();

            //momentan functioneaza numai cu 2 nume introduse
            QString numeBeneficiar = ui->numeEdit->text();
            QString num1 = numeBeneficiar.simplified().split(" ")[0];
            QString num2 = numeBeneficiar.simplified().split(" ")[1];

            //verific daca id-ul contului si numele corespund vreunui cont din db
            QSqlQuery sql;
            sql.prepare("select conturi.* from conturi, clienti where conturi.client = clienti.id and conturi.id = :idCont and upper(clienti.nume) in (:num1, :num2) and upper(clienti.prenume) in (:num1, :num2)");
            sql.bindValue(":idCont", inCont);
            sql.bindValue(":num1", num1.toUpper());
            sql.bindValue(":num2", num2.toUpper());
            sql.exec();
            while (sql.next()) {
                if (sql.value(0).toInt() == inCont){
                    //exista contul cu combinatia de nume si id
                    checkCont = true;
                    //formez obiectul de tip Cont
                    Moneda* m = new Moneda(sql.value(2).toString());
                    QDate data = QDate::fromString(sql.value(4).toString(),"dd/MM/yyyy");
                    contDest = new Cont(inCont, m, sql.value(3).toFloat(), data);
                }
            }

            if (checkCont){
                float valoareDeAdaugat = valoare;
                //daca monedele sunt diferite
                //obtin cursul valutar
                if (cont->getTip()->getCod() != contDest->getTip()->getCod()){
                    sql.prepare("select * from curs_schimb where (m1 = :curM or m1 = :destM) and (m2 = :curM or m2 = :destM)");
                    sql.bindValue(":curM", cont->getTip()->getCod());
                    sql.bindValue(":destM", contDest->getTip()->getCod());
                    sql.exec();
                    while (sql.next()) {
                        //daca moneda mea e M1, atunci inmultesc, altfel impart
                        if (sql.value(0).toString() == cont->getTip()->getCod()){
                            valoareDeAdaugat = valoare * sql.value(2).toFloat();
                        }
                        else{
                            valoareDeAdaugat = valoare / sql.value(2).toFloat();
                        }
                    }
                }

                //TODO: de adaugat operatia in tranzactii

                //scad disponibilul din contul meu in db si in interfata
                sql.prepare("update conturi set disponibil = :newDisponibil where id = :idCont");
                sql.bindValue(":newDisponibil", cont->getDisponibil() - valoare);
                sql.bindValue(":idCont", cont->getId());
                sql.exec();
                cont->setDisponibil(cont->getDisponibil() - valoare);

                //adaug in contul tinta numai in db
                sql.prepare("update conturi set disponibil = :newDisponibil where id = :idCont");
                sql.bindValue(":newDisponibil", contDest->getDisponibil() + valoareDeAdaugat);
                sql.bindValue(":idCont", contDest->getId());
                sql.exec();

                //inregistrez o noua tranzactie
                QDateTime sysdate = QDateTime::currentDateTime();
                float valoare = ui->valoareEdit->text().toFloat();
                sql.prepare("INSERT INTO tranzactii(dinC,inC,tip_tranzactie,valoare,data,mesaj) VALUES(:dinC,:inC,:tipTranz,:valoare,:data,:mesaj)");
                sql.bindValue(":dinC", cont->getId());
                sql.bindValue(":inC", ui->inContEdit->text().toInt());
                sql.bindValue(":tipTranz", "TRANSFER");
                sql.bindValue(":valoare", valoare);
                sql.bindValue(":data", sysdate.toString("MM/dd/yyyy"));
                sql.bindValue(":mesaj", ui->mesajEdit->text());
                sql.exec();

                //ma introc in fereastra initiala cu mesaj de succes
                AccountWindow *accountWindow = new AccountWindow(cont, "Transfer efectuat cu succes.");
                accountWindow->show();
                this->hide();

                delete contDest;

            }
            else {
                //nu s-a gasit contul cautat
                //afisez mesaj de eroare
                ui->infoLabel->setStyleSheet("QLabel {color : red; }");
                ui->infoLabel->setText("Eroare. Nu am gasit contul cautat.");
            }
        }
    }

}

void TransferWindow::on_renuntaButon_clicked()
{
    //ma intorc inapoi
    AccountWindow *accountWindow = new AccountWindow(cont, "");
    accountWindow->show();
    this->hide();
}
