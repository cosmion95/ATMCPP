#include "moneda.h"

Moneda::Moneda(QString cod, QString denumire)
{
    this->cod = cod;
    this->denumire = denumire;
}

Moneda::Moneda(QString cod)
{
    this->cod = cod;
}

Moneda::Moneda(){}

QString Moneda::getCod() const
{
    return cod;
}

QString Moneda::getDenumire() const
{
    return denumire;
}
