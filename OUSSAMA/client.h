#ifndef Client_H
#define Client_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Client
{
    long tel;
        QString nom,prenom,cin,adresse,mail;

public:
    Client();
    Client(QString,long,QString,QString,QString,QString);
    QString getcin(){return cin;}
    void setcin(QString cin){this->cin=cin;}
    void settel(long tel){this->tel=tel;}
    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    void setadresse(QString adresse){this->adresse=adresse;}
    void setmail(QString mail){this->mail=mail;}
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
        QSqlQueryModel *tricroissant();



    bool ajouter();
    QSqlQueryModel * afficher();


    bool supprimer(QString);
    bool modifier();
    bool testmail(QString);
    bool testnumber(QString);
    bool testCin(QString);




    ~Client(){}


};

#endif // Client_H
