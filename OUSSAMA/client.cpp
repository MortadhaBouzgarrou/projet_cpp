#include "client.h"
#include<QSqlQuery>
#include<QString>
#include<QVariant>

Client::Client()
{
    cin="";
    tel=00;
    nom="";
    prenom="";
    adresse="";
    mail="";


}

Client::Client(QString cin,long tel,QString nom,QString prenom,QString adresse,QString mail)
{
this->cin=cin;
this->tel=tel;
this->nom=nom;
this->prenom=prenom;
this->adresse=adresse;
this->mail=mail;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString res1=QString::number(tel);
          query.prepare("INSERT INTO Client (cin,tel, nom, prenom,mail,adresse) "
                        "VALUES (:cin, :tel, :nom, :prenom, :mail, :adresse)");
          query.bindValue(":cin", cin);
          query.bindValue(":tel", res1);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":mail", mail);

          return  query.exec();
}

QSqlQueryModel * Client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    return model;
}


bool Client::supprimer(QString cin)
{

    QSqlQuery query;
    query.prepare("Delete from Client where CIN = :cin ");
    query.bindValue(":cin", cin);
    return    query.exec();

}




bool Client::modifier(){
    QSqlQuery query;
    QString res1=QString::number(tel);
    query.prepare("update Client set CIN=:cin,TEL=:tel,NOM=:nom ,PRENOM=:prenom,ADRESSE=:adresse,MAIL=:mail  where CIN = :cin");
    query.bindValue(":cin", cin);
    query.bindValue(":tel", res1);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail", mail);
    return query.exec();
}

bool Client::testmail(QString mail){
    int test=0;
    for(int i = 0; i < mail.size(); i++) {
if(mail[i]=="@")
{test++;

}}
    for(int i = 0; i < mail.size(); i++) {
if((test==1)&&(mail[i]=="."))
{if(mail.size()>i+1)
    return true;
}}
return false;}
bool Client::testnumber(QString number){


    if(number.size()==8)
        return true;
    return false;



}

bool Client::testCin(QString cin){
    if(cin.size()!=8)
    return false;

    for(int i = 0; i < cin.size(); i++) {


    if (!(cin[i] >= '0' && cin[i] <= '9'))
        return false;

}
    return true;


}

QSqlQueryModel *Client::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM CLIENT " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));

    return model;
}



QSqlQueryModel * Client::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM CLIENT ORDER BY NOM ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    return model;
}
QSqlQueryModel * Client::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM CLIENT ORDER BY NOM DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telephone"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    return model;
}








