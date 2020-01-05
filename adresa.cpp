#include "adresa.h"

Adresa::Adresa(int id, QString tara, QString judet, QString localitate, QString numar, QString codPostal, QString strada)
{
    this->id = id;
    this->tara = tara;
    this->judet = judet;
    this->localitate = localitate;
    this->numar = numar;
    this->codPostal = codPostal;
    this->strada = strada;
}

Adresa::Adresa(){}

QString Adresa::getTara() const
{
    return tara;
}

QString Adresa::getJudet() const
{
    return judet;
}

QString Adresa::getLocalitate() const
{
    return localitate;
}

QString Adresa::getNumar() const
{
    return numar;
}

QString Adresa::getCodPostal() const
{
    return codPostal;
}

QString Adresa::getStrada() const
{
    return strada;
}
