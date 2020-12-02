#include "ticket.h"
#include <QDebug>
#include "connexion.h"
Ticket::Ticket()
{
id="";
idc="";
prix=0;
}
Ticket::Ticket(QString id,QString idc,int prix,QDate datee)
{
  this->id=id;
  this->idc=idc;
    this->prix=prix;
  this->datee=datee;

}
QString Ticket::get_id(){return id;}

QString Ticket::get_idc(){return  idc;}

QDate Ticket::get_datee(){return  datee;}
int Ticket::get_prix(){return prix;}



bool Ticket::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO TICKET (ID,IDC,PRIX,DATEE) "
                    "VALUES (:id, :idc, :prix, :datee)");
query.bindValue(":id", id);
query.bindValue(":idc",idc);
query.bindValue(":prix",prix);
query.bindValue(":datee",datee);



return    query.exec();
}

QSqlQueryModel * Ticket::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from TICKET");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Client"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));


    return model;
}

bool Ticket::supprimer(QString id)
{
QSqlQuery query;
query.prepare("Delete from TICKET where ID = :id ");
query.bindValue(":id", id);
return    query.exec();
}

bool Ticket::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE TICKET SET ID=:id,IDC=:idc,PRIX=:prix,DATEE=:datee WHERE ID=:id");
    query.bindValue(":id", id);
    query.bindValue(":idc",idc);
    query.bindValue(":prix",prix);
    query.bindValue(":datee",datee);


 return query.exec();
}

QSqlQueryModel *Ticket::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM TICKET " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Client"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));

    return model;
}



QSqlQueryModel * Ticket::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM TICKET ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Client"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
    return model;
}
QSqlQueryModel * Ticket::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM TICKET ORDER BY PRIX DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_Client"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
    return model;
}




