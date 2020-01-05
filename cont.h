#ifndef CONT_H
#define CONT_H

#include <moneda.h>
#include <client.h>
#include <QDate>

class Cont
{
public:
    Cont(int id, Moneda* tip, float disponibil, QDate dataDeschidere, Client *client);
    Cont(int id, Moneda* tip, float disponibil, QDate dataDeschidere);
    Moneda *getTip() const;

    float getDisponibil() const;

    int getId() const;

    void setDisponibil(float value);

    Client *getClient() const;

private:
    int id;
    Moneda* tip;
    float disponibil;
    QDate dataDeschidere;
    Client* client;
};

#endif // CONT_H
