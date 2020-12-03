#include "pub_promo.h"
#include "ui_pub_promo.h"
#include "publicite.h"
#include<QMessageBox>
#include <QComboBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPrinter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include "smtp.h"
#include"QSortFilterProxyModel"


QT_CHARTS_USE_NAMESPACE
Pub_Promo::Pub_Promo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Pub_Promo)
{
ui->setupUi(this);

refresh();


}
void Pub_Promo::refresh(){
    ui->Publicite_affichage->setModel(tmp_publicite.afficher());
    ui->Promotion_affichage->setModel(tmp_promotion.afficher());

}

Pub_Promo::~Pub_Promo()
{
    delete ui;
}

QString Pub_Promo::ConvertirTime(){
    QTime duree =ui->lineEdit_datec->time();
    QString h1=QString((duree.toString()[0]));
    QString h2=QString((duree.toString()[1]));
    QString m1=QString((duree.toString()[3]));
    QString m2=QString((duree.toString()[4]));
    QString heure=h1.append(h2);
    heure=heure.append(":");
    heure=heure.append(m1);
    heure=heure.append(m2);
return heure;
}
//Crud Publicite
void Pub_Promo::on_pb_ajouter_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString nom= ui->lineEdit_nom->text();
    int prix= ui->lineEdit_prix->text().toInt();
    QString duree=ConvertirTime();
    QString id_p= ui->lineEdit_idp->text();
  Publicite e(id,nom,prix,duree,id_p);



  if (ui->lineEdit_id->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (ui->lineEdit_nom->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
  else if (ui->lineEdit_prix->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prix!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else if (ui->lineEdit_idp->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }








  else{

  bool test=e.ajouter();
  if(test)
{

     refresh();
            N.notification_ajoutPublicite();

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Publicite"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}}
void Pub_Promo::on_pb_supprimer_clicked()
{

    if(ui->Publicite_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir une Publicite du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),0)).toInt();
        Publicite pub(ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),0)).toInt(),ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),1)).toString(),ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),2)).toInt(),ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),3)).toString(),ui->Publicite_affichage->model()->data(ui->Publicite_affichage->model()->index(ui->Publicite_affichage->currentIndex().row(),4)).toString());



            QString str = " Vous voulez vraiment supprimer \n la publicite :";
                              int ret = QMessageBox::question(this, tr("Publicite"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (pub.supprimer(id)){
                                       N.notification_supprimerPublicite();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Publicite non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}
}
void Pub_Promo::on_modifier_3_clicked()
{

        int id=ui->lineEdit_id1->text().toInt();
        int prix = ui->lineEdit_prix1->text().toInt();
        QString nom = ui->lineEdit_nom1->text();
        QString duree = ui->lineEdit_duree1->text();
        QString id_p= ui->lineEdit_idp1->text();
        Publicite pub (id,nom,prix,duree,id_p);



        if (ui->lineEdit_id1->text().isEmpty())
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }

          else if (ui->lineEdit_nom1->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }
        else if (ui->lineEdit_prix1->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prix!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
        else if (ui->lineEdit_idp1->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP id produit!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
        else if (ui->lineEdit_duree1->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP DUREE!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }








        else{






        bool test=pub.modifier();
        if(test)
        {



           N.notification_modifierPublicite();
                refresh();


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer Publicite"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        ui->lineEdit_id1->clear();
        ui->lineEdit_nom1->clear();
        ui->lineEdit_prix1->clear();
        ui->lineEdit_duree1->clear();
        ui->lineEdit_idp1->clear();





}}
void Pub_Promo::on_Publicite_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Publicite_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM PUBLICITE WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id1->setText(query.value(0).toString());
                ui->lineEdit_nom1->setText(query.value(1).toString());
                ui->lineEdit_prix1->setText(query.value(2).toString());
                ui->lineEdit_duree1->setText(query.value(3).toString());
                ui->lineEdit_idp1->setText(query.value(4).toString());


            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }
}
//Fin Crud Publicite



//Crud Promotion

void Pub_Promo::on_pb_ajouter_pr_clicked()
{
    QString id = ui->lineEdit_id_pr->text();
    QString nom= ui->lineEdit_nom_pr->text();
    int pourc= ui->lineEdit_pourc->text().toInt();
    QDate datee =ui->dateEdit->date();
    QString id_p= ui->lineEdit_idp_pr->text();
  Promotion p(id,nom,pourc,datee,id_p);

  if (ui->lineEdit_id_pr->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (ui->lineEdit_nom_pr->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Nom!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
          else if (ui->lineEdit_idp_pr->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ID PRODUIT!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }

  else if ((p.test_pourc(pourc)==false)||(ui->lineEdit_pourc->text().isEmpty()))
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Pourcentage!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }






  else{
  bool test=p.ajouter();
  if(test)
{

    refresh();
    N.notification_ajoutPromotion();
QMessageBox::information(nullptr, QObject::tr("Ajouter une Promotion"),
                  QObject::tr("Promotion ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une Promotion"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}

void Pub_Promo::on_pb_modifier_pr_clicked()
{
    QString id = ui->lineEdit_id_pr1->text();
    QString nom= ui->lineEdit_nom_pr1->text();
    int pourc= ui->lineEdit_pourc1->text().toInt();
    QDate datee =ui->dateEdit1->date();
    QString id_p= ui->lineEdit_idp_pr1->text();

    Promotion p (id,nom,pourc,datee,id_p);


    if (ui->lineEdit_id_pr1->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }

      else if (ui->lineEdit_nom_pr1->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Nom!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }
            else if (ui->lineEdit_idp_pr1->text().isEmpty())
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP ID PRODUIT!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }
    else if ((p.test_pourc(pourc)==false)||(ui->lineEdit_pourc->text().isEmpty()))
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Pourcentage!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }






    else{




    bool test=p.modifier();
    if(test)
    {



        N.notification_modifierPromotion();
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Modifier une Promotion"),
                          QObject::tr("Promotion modifiee.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Promotion"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->lineEdit_id_pr1->clear();
    ui->lineEdit_nom_pr1->clear();
    ui->lineEdit_pourc1->clear();
    ui->lineEdit_idp1->clear();

}}

void Pub_Promo::on_pb_supprimer_pr_clicked()
{
    if(ui->Promotion_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir une Promotion du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   int id=ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),0)).toInt();
        Promotion p(ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),0)).toString(),ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),1)).toString(),ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),2)).toInt(),ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),3)).toDate(),ui->Promotion_affichage->model()->data(ui->Promotion_affichage->model()->index(ui->Promotion_affichage->currentIndex().row(),4)).toString());



            QString str = " Vous voulez vraiment supprimer \n la Promotion :";
                              int ret = QMessageBox::question(this, tr("Promotion"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (p.supprimer(id)){
                                       N.notification_supprimerPromotion();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Promotion non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}

}

void Pub_Promo::on_Promotion_affichage_activated(const QModelIndex &index)
{
    QString id=ui->Promotion_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM PROMOTION WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id_pr1->setText(query.value(0).toString());
                ui->lineEdit_nom_pr1->setText(query.value(1).toString());
                ui->lineEdit_pourc1->setText(query.value(2).toString());
                ui->lineEdit_idp_pr1->setText(query.value(4).toString());


            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }

}


//Fin Crud Promotion


void Pub_Promo::on_recherche_Promotion_textChanged()
{
    if(ui->recherche_Promotion->text()!="")
        {        QString b=ui->comboBox_recherche_Promotion->currentText();
                QString a=ui->recherche_Promotion->text();
                ui->Promotion_affichage->setModel(tmp_promotion.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Promotion_affichage->setModel(tmp_promotion.afficher());

}

void Pub_Promo::on_recherche_Publicite_textChanged()
{
    if(ui->recherche_Publicite->text()!="")
        {        QString b=ui->comboBox_recherche_Publicite->currentText();
                QString a=ui->recherche_Publicite->text();
                ui->Publicite_affichage->setModel(tmp_publicite.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
            }
             else
             ui->Publicite_affichage->setModel(tmp_publicite.afficher());

}

void Pub_Promo::on_tri_croissant_promotion_clicked()
{
    ui->Promotion_affichage->setModel(tmp_promotion.tricroissant());

}

void Pub_Promo::on_tri_deccroissant_promotion_clicked()
{
    ui->Promotion_affichage->setModel(tmp_promotion.trideccroissant());

}

void Pub_Promo::on_tri_croissant_publicite_clicked()
{
    ui->Publicite_affichage->setModel(tmp_publicite.tricroissant());

}

void Pub_Promo::on_tri_deccroissant_publicite_clicked()
{
    ui->Publicite_affichage->setModel(tmp_publicite.trideccroissant());

}

void Pub_Promo::on_stat_promotion_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                    model->setQuery("select * from PROMOTION where POURCENTAGE < 10 ");
                    float salaire=model->rowCount();
                    model->setQuery("select * from PROMOTION where POURCENTAGE  between 10 and 50 ");
                    float salairee=model->rowCount();
                    model->setQuery("select * from PROMOTION where POURCENTAGE>50 ");
                    float salaireee=model->rowCount();
                    float total=salaire+salairee+salaireee;
                    QString a=QString("moins de 10% "+QString::number((salaire*100)/total,'f',2)+"%" );
                    QString b=QString("entre 10% et 50%  "+QString::number((salairee*100)/total,'f',2)+"%" );
                    QString c=QString("+50%"+QString::number((salaireee*100)/total,'f',2)+"%" );
                    QPieSeries *series = new QPieSeries();
                    series->append(a,salaire);
                    series->append(b,salairee);
                    series->append(c,salaireee);
            if (salaire!=0)
            {QPieSlice *slice = series->slices().at(0);
             slice->setLabelVisible();
             slice->setPen(QPen());}
            if ( salairee!=0)
            {
                     // Add label, explode and define brush for 2nd slice
                     QPieSlice *slice1 = series->slices().at(1);
                     //slice1->setExploded();
                     slice1->setLabelVisible();
            }
            if(salaireee!=0)
            {
                     // Add labels to rest of slices
                     QPieSlice *slice2 = series->slices().at(2);
                     //slice1->setExploded();
                     slice2->setLabelVisible();
            }
                    // Create the chart widget
                    QChart *chart = new QChart();
                    // Add data to chart with title and hide legend
                    chart->addSeries(series);
                    chart->setTitle("Pourcentage Par Pourcentage de promotion :Nombre Des Promotions "+ QString::number(total));
                    chart->legend()->hide();
                    // Used to display the chart
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->resize(1000,500);
                    chartView->show();
}

void Pub_Promo::on_stat_publicite_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                    model->setQuery("select * from PUBLICITE where PRIX < 100 ");
                    float salaire=model->rowCount();
                    model->setQuery("select * from PUBLICITE where PRIX  between 100 and 500 ");
                    float salairee=model->rowCount();
                    model->setQuery("select * from PUBLICITE where PRIX>500 ");
                    float salaireee=model->rowCount();
                    float total=salaire+salairee+salaireee;
                    QString a=QString("moins de 100 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
                    QString b=QString("entre 100 et 500 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
                    QString c=QString("+500 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
                    QPieSeries *series = new QPieSeries();
                    series->append(a,salaire);
                    series->append(b,salairee);
                    series->append(c,salaireee);
            if (salaire!=0)
            {QPieSlice *slice = series->slices().at(0);
             slice->setLabelVisible();
             slice->setPen(QPen());}
            if ( salairee!=0)
            {
                     // Add label, explode and define brush for 2nd slice
                     QPieSlice *slice1 = series->slices().at(1);
                     //slice1->setExploded();
                     slice1->setLabelVisible();
            }
            if(salaireee!=0)
            {
                     // Add labels to rest of slices
                     QPieSlice *slice2 = series->slices().at(2);
                     //slice1->setExploded();
                     slice2->setLabelVisible();
            }
                    // Create the chart widget
                    QChart *chart = new QChart();
                    // Add data to chart with title and hide legend
                    chart->addSeries(series);
                    chart->setTitle("Pourcentage Par Prix :Nombre Des PUBLICITE "+ QString::number(total));
                    chart->legend()->hide();
                    // Used to display the chart
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->resize(1000,500);
                    chartView->show();
}

void Pub_Promo::on_pdf_publicite_clicked()
{
    QPdfWriter pdf("C:/Users/SeifBS/Desktop/PdfPublicite.pdf");
                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::blue);
                      painter.setFont(QFont("Arial", 30));
                      painter.drawText(2300,1200,"Liste Des Publicite");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 50));
                     // painter.drawText(1100,2000,afficheDC);
                      painter.drawRect(1500,200,7300,2600);
                      //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(300,3300,"ID");
                      painter.drawText(2300,3300,"NOM");
                      painter.drawText(4300,3300,"PRIX");
                      painter.drawText(6300,3300,"DUREE");
                      painter.drawText(8000,3300,"IDP");



                      QSqlQuery query;
                      query.prepare("select * from PUBLICITE");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2300,i,query.value(1).toString());
                          painter.drawText(4300,i,query.value(2).toString());
                          painter.drawText(6300,i,query.value(3).toString());
                          painter.drawText(8000,i,query.value(4).toString());



                         i = i +500;
                      }
                      int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                          if (reponse == QMessageBox::Yes)
                          {
                              QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/SeifBS/Desktop/PdfPublicite.pdf"));

                              painter.end();
                          }
                          if (reponse == QMessageBox::No)
                          {
                               painter.end();
                          }
}




void Pub_Promo::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Publicite();
}

void Pub_Promo::on_send_mail_clicked()
{

    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

       smtp->sendMail("farmeresprit414@gmail.com","seifeddine.bensalah@gmail.com",ui->subject->text(),ui->msg->toPlainText());
}




