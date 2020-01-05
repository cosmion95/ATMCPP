#ifndef ADRESA_H
#define ADRESA_H

#include <QString>

class Adresa
{
public:
    Adresa();
    Adresa(int id, QString tara, QString judet, QString localitate, QString numar, QString codPostal, QString strada);
    QString getTara() const;

    QString getJudet() const;

    QString getLocalitate() const;

    QString getNumar() const;

    QString getCodPostal() const;

    QString getStrada() const;

private:
    int id;
    QString tara, judet, localitate, numar, codPostal, strada;
};

#endif // ADRESA_H
