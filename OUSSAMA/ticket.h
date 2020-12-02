#ifndef Ticket_H
#define Ticket_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QDate>

class Ticket
{public:
    Ticket();
    Ticket(QString,QString,int,QDate);
    QString get_id();
    QString get_idc();
    int get_prix();

    QDate get_datee();
    ;
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
        QSqlQueryModel *tricroissant();


private:
    QString idc,id;
    int prix;
    QDate datee;

};

#endif // Ticket_H
