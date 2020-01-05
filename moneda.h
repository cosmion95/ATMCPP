#ifndef MONEDA_H
#define MONEDA_H

#include <QString>

class Moneda
{
public:
    Moneda();
    Moneda(QString cod);
    Moneda(QString cod, QString denumire);

    QString getCod() const;

    QString getDenumire() const;

private:
    QString cod, denumire;
};

#endif // MONEDA_H
