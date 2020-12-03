#include "publicite.h"
#include <QDebug>
#include "connexion.h"
Publicite::Publicite()
{
id=0;
nom="";
prix=0;
duree="";
}
Publicite::Publicite(int id,QString nom,int prix,QString duree,QString id_p)
{
  this->id=id;
  this->nom=nom;
  this->prix=prix;
  this->duree=duree;
  this->id_p=id_p;

}
QString Publicite::get_nom(){return  nom;}
int Publicite::get_prix(){return prix;}
int Publicite::get_id(){return  id;}
QString Publicite::get_duree(){return  duree;}
QString Publicite::get_id_p(){return  id_p;}



bool Publicite::ajouter()
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("INSERT INTO PUBLICITE (ID, NOM, PRIX,DUREE,ID_P) "
                    "VALUES (:id, :nom, :prix,:duree,:id_p)");
query.bindValue(":id", res);
query.bindValue(":nom", nom);
query.bindValue(":prix", prix);
query.bindValue(":duree", duree);
query.bindValue(":id_p", id_p);



return    query.exec();
}

QSqlQueryModel * Publicite::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PUBLICITE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));


    return model;
}

bool Publicite::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from PUBLICITE where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

bool Publicite::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE PUBLICITE SET ID=:id, NOM=:nom,PRIX=:prix,DUREE=:duree,ID_P=:id_p WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prix",prix);
    query.bindValue(":duree",duree);
    query.bindValue(":id_p", id_p);



 return query.exec();
}

QSqlQueryModel *Publicite::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM Publicite " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}



QSqlQueryModel * Publicite::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM PUBLICITE ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}
QSqlQueryModel * Publicite::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM PUBLICITE ORDER BY PRIX DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prix"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_p"));

    return model;
}
