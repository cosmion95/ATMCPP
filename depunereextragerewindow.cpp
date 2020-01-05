#include "depunereextragerewindow.h"
#include "ui_depunereextragerewindow.h"
#include "accountwindow.h"

DepunereExtragereWindow::DepunereExtragereWindow(Cont *cont, int tip, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DepunereExtragereWindow)
{
    ui->setupUi(this);
    this->cont = cont;
    this->tip = tip;
    //construiesc etichetele
    QString contString = "Contul " + QString::number(cont->getId()) + ", moneda: " + cont->getTip()->getCod();
    QString disponibilString = "Disponibil: " + QString::number(cont->getDisponibil());
    QString tipOperatie = "";
    if (tip == 0) {
        tipOperatie = "Extragere";
    }
    else {
        tipOperatie = "Depunere";
    }

    //setez etichetele
    ui->titluLabel->setText(tipOperatie);
    ui->contLabel->setText(contString);
    ui->disponibilLabel->setText(disponibilString);

    //fortez utilizatorul sa introduca numai cifre ca si valoare, fara sa depaseasca numarul de cifre pe care il are in cont
    ui->valoareEdit->setValidator( new QIntValidator(0, (int)cont->getDisponibil()*10, this) );

    //conexiunea la db
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("new_db.sqlite");
    if(!db.open()){
        qInfo()<<"eroare la conectarea la db";
    }
    else {
        qInfo()<<"conectat la db";
    }
}

DepunereExtragereWindow::~DepunereExtragereWindow()
{
    delete ui;
}

void DepunereExtragereWindow::on_acceptButon_clicked()
{
    //verific care este tipul de operatie care trebuie efectuat si apelez procedura
    if (tip == 0){
        //efectuez o extragere
        float newDisponibil = extragere();
        //verific daca noua valoare e diferita de cea existenta
        if (newDisponibil < cont->getDisponibil()){
            //setez noua valoare in db si in interfata
            setDisponibil(newDisponibil, "EXTRAGERE");

            //ma intorc in pagina anterioara
            AccountWindow *accountWindow = new AccountWindow(cont, "Extragere efectuata cu succes.");
            accountWindow->show();
            this->hide();
        }
        else {
            //afisez mesaj de eroare
            ui->msgLabel->setStyleSheet("QLabel {color : red; }");
            ui->msgLabel->setText("Eroare. Fonduri insuficiente.");
        }

    }
    else {
        //efectuez o depunere
        float valoare = ui->valoareEdit->text().toFloat();
        if (valoare > 0){
            valoare += cont->getDisponibil();
            //setez noua valoare in db si interfata
            setDisponibil(valoare, "DEPUNERE");

            //ma intorc in pagina anterioara
            AccountWindow *accountWindow = new AccountWindow(cont, "Depunere efectuata cu succes.");
            accountWindow->show();
            this->hide();
        }
        else {
            //afisez mesaj de eroare
            ui->msgLabel->setStyleSheet("QLabel {color : red; }");
            ui->msgLabel->setText("Eroare. Valoarea introdusa trebuie sa fie mai mare decat 0.");
        }
    }
}

void DepunereExtragereWindow::setDisponibil(float newDisponibil, QString tipTranzactie){
    //setez noua valoare in db
    QSqlQuery sql;
    sql.prepare("update conturi set disponibil = :newDisponibil where id = :idCont");
    sql.bindValue(":newDisponibil", newDisponibil);
    sql.bindValue(":idCont", cont->getId());
    sql.exec();

    //inregistrez o noua tranzactie
    QDateTime sysdate = QDateTime::currentDateTime();
    float valoare = ui->valoareEdit->text().toFloat();
    sql.prepare("INSERT INTO tranzactii(dinC,tip_tranzactie,valoare,data) VALUES(:dinC,:tipTranz,:valoare,:data)");
    sql.bindValue(":dinC", cont->getId());
    sql.bindValue(":tipTranz", tipTranzactie);
    sql.bindValue(":valoare", valoare);
    sql.bindValue(":data", sysdate.toString("MM/dd/yyyy"));
    sql.exec();

    //setez noua valoare si in interfata
    cont->setDisponibil(newDisponibil);
}

float DepunereExtragereWindow::extragere(){
    //verific daca valoarea introdusa este mai mica decat disponibilul in cont
    float valoare = ui->valoareEdit->text().toFloat();
    //calculez dobanda la 1%
    float dobanda = valoare * 0.01;
    if (valoare+dobanda > cont->getDisponibil()){
        //eroare, fonduri insuficiente
        return cont->getDisponibil();
    }
    else {
        float newDisponibil = cont->getDisponibil() - (valoare+dobanda);
        return newDisponibil;
    }
}


void DepunereExtragereWindow::on_renuntaButon_clicked()
{
    //ma intorc in pagina anterioara
    AccountWindow *accountWindow = new AccountWindow(cont, "");
    accountWindow->show();
    this->hide();
}
