#include "cont.h"

Cont::Cont(int id, Moneda* tip, float disponibil, QDate dataDeschidere, Client *client)
{
    this->id = id;
    this->tip = tip;
    this->disponibil = disponibil;
    this->dataDeschidere = dataDeschidere;
    this->client = client;
}

Cont::Cont(int id, Moneda* tip, float disponibil, QDate dataDeschidere)
{
    this->id = id;
    this->tip = tip;
    this->disponibil = disponibil;
    this->dataDeschidere = dataDeschidere;
}

Moneda *Cont::getTip() const
{
    return tip;
}

float Cont::getDisponibil() const
{
    return disponibil;
}

int Cont::getId() const
{
    return id;
}

void Cont::setDisponibil(float value)
{
    disponibil = value;
}

Client *Cont::getClient() const
{
    return client;
}
