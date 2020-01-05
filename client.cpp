#include "client.h"

Client::Client(int id, QString nume, QString prenume, QString username, bool juridica, QDate dataInregistrare, Adresa* adresa)
{
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->username = username;
    this->juridica = juridica;
    this->dataInregistrare = dataInregistrare;
    this->adresa = adresa;
}

QString Client::getNume() const
{
    return nume;
}

void Client::setNume(const QString &value)
{
    nume = value;
}

QString Client::getPrenume() const
{
    return prenume;
}

void Client::setPrenume(const QString &value)
{
    prenume = value;
}

QString Client::getUsername() const
{
    return username;
}

void Client::setUsername(const QString &value)
{
    username = value;
}

bool Client::getJuridica() const
{
    return juridica;
}

void Client::setJuridica(bool value)
{
    juridica = value;
}

QDate Client::getDataInregistrare() const
{
    return dataInregistrare;
}

int Client::getId() const
{
    return id;
}

void Client::setDataInregistrare(const QDate &value)
{
    dataInregistrare = value;
}

//QLinkedList<Cont> Client::getListaConturi() const
//{
//    return listaConturi;
//}

//void Client::setListaConturi(const QLinkedList<Cont> &value)
//{
//    listaConturi = value;
//}
