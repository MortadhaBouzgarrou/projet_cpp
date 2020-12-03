#ifndef Publicite_H
#define Publicite_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QTime>

class Publicite
{public:
    Publicite();
    Publicite(int,QString,int,QString,QString);
    QString get_nom();
    int get_prix();
    int get_id();
    QString get_id_p();

    QString get_duree();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *displayClause(QString cls);
    QSqlQueryModel *trideccroissant();
    QSqlQueryModel *tricroissant();




private:
    QString nom;
    int id,prix;
    QString duree,id_p;
};

#endif // Publicite_H
