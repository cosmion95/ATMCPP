#ifndef CLIENT_H
#define CLIENT_H

#include <QDate>
#include <QString>
#include <adresa.h>
#include <QLinkedList>

class Client
{
public:
    Client(int id, QString nume, QString prenume, QString username, bool juridica, QDate dataInregistrare, Adresa* adresa);
    QString getNume() const;
    void setNume(const QString &value);

    QString getPrenume() const;
    void setPrenume(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

    bool getJuridica() const;
    void setJuridica(bool value);

    QDate getDataInregistrare() const;
    void setDataInregistrare(const QDate &value);

    int getId() const;

    //QLinkedList<Cont> getListaConturi() const;
    //void setListaConturi(const QLinkedList<Cont> &value);

private:
    int id;
    QString nume;
    QString prenume;
    QString username;
    bool juridica;
    QDate dataInregistrare;
    Adresa* adresa;
    //QLinkedList<Cont> listaConturi;

};

#endif // CLIENT_H
