#include "client_ticket.h"
#include "ui_client_ticket.h"
#include "smtp.h"

#include <QMessageBox>
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
#include"QSortFilterProxyModel"


QT_CHARTS_USE_NAMESPACE
Client_ticket::Client_ticket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client_ticket)
{
ui->setupUi(this);

refresh();



}

void Client_ticket::refresh(){
    ui->Ticket_affichage->setModel(tmp_Ticket.afficher());
    ui->Client_affichage->setModel(tmp_Client.afficher());
    ui->comboBox_idc->setModel(tmp_Client.afficher());
    ui->comboBox_idc1->setModel(tmp_Client.afficher());
    ui->Client_affichage_2->setModel(tmp_Client.afficher());
    ui->Ticket_affichage1->setModel(tmp_Ticket.afficher());



}

Client_ticket::~Client_ticket()
{
    delete ui;
}



//Crud Tickets
void Client_ticket::on_pb_ajouter_clicked()
{
    QString id= ui->lineEdit_id->text();
    QString idc=ui->comboBox_idc->currentText();

    int prix= ui->lineEdit_prix->text().toInt();
    QDate datee = ui->dateEdit->date();
  Ticket t(id,idc,prix,datee);



  if (ui->lineEdit_id->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }

  else if (ui->lineEdit_prix->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRIX!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else{



  bool test=t.ajouter();
  if(test)
{
refresh();
N.notification_ajoutTicket();
QMessageBox::information(nullptr, QObject::tr("Ajouter un Ticket"),
                  QObject::tr("Ticket ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Ticket"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}}


void Client_ticket::on_pb_supprimer_clicked()
{
    if(ui->Ticket_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir un Ticket du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   QString id=ui->Ticket_affichage->model()->data(ui->Ticket_affichage->model()->index(ui->Ticket_affichage->currentIndex().row(),0)).toString();
        Ticket t(ui->Ticket_affichage->model()->data(ui->Ticket_affichage->model()->index(ui->Ticket_affichage->currentIndex().row(),0)).toString(),ui->Ticket_affichage->model()->data(ui->Ticket_affichage->model()->index(ui->Ticket_affichage->currentIndex().row(),1)).toString(),ui->Ticket_affichage->model()->data(ui->Ticket_affichage->model()->index(ui->Ticket_affichage->currentIndex().row(),2)).toInt(),ui->Ticket_affichage->model()->data(ui->Ticket_affichage->model()->index(ui->Ticket_affichage->currentIndex().row(),3)).toDate());



            QString str = " Vous voulez vraiment supprimer \n le Ticket :";
                              int ret = QMessageBox::question(this, tr("Ticket"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (t.supprimer(id)){
                                       N.notification_supprimerTicket();
                                            refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Ticket non trouvé "), QMessageBox::Cancel);
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

void Client_ticket::on_pb_modifier_clicked()
{

    QString id= ui->lineEdit_id1->text();
    QString idc=ui->comboBox_idc1->currentText();
    int prix= ui->lineEdit_prix1->text().toInt();
    QDate datee = ui->dateEdit1->date();







  Ticket t(id,idc,prix,datee);


    QSqlQuery query;

    if (ui->lineEdit_id1->text().isEmpty())
       {

           QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
           QMessageBox::critical(0, qApp->tr("Ajout"),

                           qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

       }

    else if (ui->lineEdit_prix1->text().isEmpty())
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRIX!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
    else{








    bool test=t.modifier();
    if(test)
    {



       N.notification_modifierTicket();
            refresh();
        QMessageBox::information(nullptr, QObject::tr("Modifier un Ticket"),
                          QObject::tr("Ticket modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Ticket"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->lineEdit_id1->clear();
    ui->lineEdit_prix1->clear();


}
}

void Client_ticket::on_Ticket_affichage_activated(const QModelIndex &index)
{

    QString id=ui->Ticket_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM TICKET WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id1->setText(query.value(0).toString());
                ui->lineEdit_prix1->setText(query.value(2).toString());





            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }


}






//Fin Crud Tickets


//Crud Clients










void Client_ticket::on_pb_ajouter_c_clicked()
{
    QString cin= ui->lineEdit_cin->text();
    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString mail = ui->lineEdit_mail->text();
    QString adresse = ui->lineEdit_adresse->text();
    long tel= ui->lineEdit_tel->text().toLong();
  Client c(cin,tel,nom,prenom,adresse,mail);

   if (c.testCin(ui->lineEdit_cin->text())==false)
     {

         QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP CIN!!!!") ;
         QMessageBox::critical(0, qApp->tr("Ajout"),

                         qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

     }
            else if (ui->lineEdit_nom->text().isEmpty())
             {

                 QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NOM!!!!") ;
                 QMessageBox::critical(0, qApp->tr("Ajout"),

                                 qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

             }
              else if (ui->lineEdit_prenom->text().isEmpty())
               {

                   QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
                   QMessageBox::critical(0, qApp->tr("Ajout"),

                                   qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

               }
          else if (ui->lineEdit_adresse->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }

        else if (c.testmail(ui->lineEdit_mail->text())==false)
               {

                   QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP MAIL!!!!") ;
                   QMessageBox::critical(0, qApp->tr("Ajout"),

                                   qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

               }
          else if (c.testnumber(ui->lineEdit_tel->text())==false)
                 {

                     QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NUMERO !!!!") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                 }





    else {
      bool test=c.ajouter();
  if(test)
{
      N.notification_ajoutClient();
refresh();
QMessageBox::information(nullptr, QObject::tr("Ajouter un Client"),
                  QObject::tr("Client ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un Client"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}






void Client_ticket::on_pb_modifier_c_clicked()
{
    QString cin= ui->lineEdit_cin1->text();
    QString nom= ui->lineEdit_nom1->text();
    QString prenom= ui->lineEdit_prenom1->text();
    QString mail = ui->lineEdit_mail1->text();
    QString adresse = ui->lineEdit_adresse1->text();
    long tel= ui->lineEdit_tel1->text().toLong();
  Client c(cin,tel,nom,prenom,adresse,mail);


    QSqlQuery query;
    if (c.testCin(ui->lineEdit_cin1->text())==false)
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP CIN!!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
             else if (ui->lineEdit_nom1->text().isEmpty())
              {

                  QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NOM!!!!") ;
                  QMessageBox::critical(0, qApp->tr("Ajout"),

                                  qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

              }
               else if (ui->lineEdit_prenom1->text().isEmpty())
                {

                    QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
                    QMessageBox::critical(0, qApp->tr("Ajout"),

                                    qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                }
           else if (ui->lineEdit_adresse1->text().isEmpty())
            {

                QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP PRENOM!!!!") ;
                QMessageBox::critical(0, qApp->tr("Ajout"),

                                qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

            }

         else if (c.testmail(ui->lineEdit_mail1->text())==false)
                {

                    QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP MAIL!!!!") ;
                    QMessageBox::critical(0, qApp->tr("Ajout"),

                                    qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                }
           else if (c.testnumber(ui->lineEdit_tel1->text())==false)
                  {

                      QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP NUMERO !!!!") ;
                      QMessageBox::critical(0, qApp->tr("Ajout"),

                                      qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

                  }





     else {

    bool test=c.modifier();
    if(test)
    {



       N.notification_modifierClient();
refresh();
        QMessageBox::information(nullptr, QObject::tr("Modifier un Client"),
                          QObject::tr("Client modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer Client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->lineEdit_cin1->clear();
    ui->lineEdit_nom1->clear();
    ui->lineEdit_prenom1->clear();
    ui->lineEdit_mail1->clear();
    ui->lineEdit_adresse1->clear();
    ui->lineEdit_tel1->clear();

}}

void Client_ticket::on_pb_supprimer_c_clicked()
{
    if(ui->Client_affichage->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir un Client du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {   QString id=ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),0)).toString();
        Client c(ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),0)).toString(),ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),1)).toULongLong(),ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),2)).toString(),ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),3)).toString(),ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),4)).toString(),ui->Client_affichage->model()->data(ui->Client_affichage->model()->index(ui->Client_affichage->currentIndex().row(),5)).toString());



            QString str = " Vous voulez vraiment supprimer \n le Client :";
                              int ret = QMessageBox::question(this, tr("Client"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (c.supprimer(id)){
                                       N.notification_supprimerClient();
                                    refresh();

                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Client non trouvé "), QMessageBox::Cancel);
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

void Client_ticket::on_Client_affichage_activated(const QModelIndex &index)
{

    QString cin=ui->Client_affichage->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM CLIENT WHERE CIN='"+cin+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_cin1->setText(query.value(0).toString());
                ui->lineEdit_tel1->setText(query.value(1).toString());
                ui->lineEdit_nom1->setText(query.value(2).toString());

                ui->lineEdit_prenom1->setText(query.value(3).toString());
                ui->lineEdit_mail1->setText(query.value(4).toString());
                ui->lineEdit_adresse1->setText(query.value(5).toString());




            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }

}
//Fin Crud Commandes





void Client_ticket::on_recherche_client_textChanged()
{
    if(ui->recherche_client->text()!="")
    {        QString b=ui->comboBox_recherche_client->currentText();
            QString a=ui->recherche_client->text();
            ui->Client_affichage->setModel(tmp_Client.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
        }
         else
         ui->Client_affichage->setModel(tmp_Client.afficher());
}

void Client_ticket::on_recherche_ticket_textChanged()
{
    if(ui->recherche_ticket->text()!="")
    {        QString b=ui->comboBox_recherche_ticket->currentText();
            QString a=ui->recherche_ticket->text();
            ui->Ticket_affichage->setModel(tmp_Ticket.displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
        }
         else
         ui->Ticket_affichage->setModel(tmp_Ticket.afficher());
}

void Client_ticket::on_tri_croissant_Client_clicked()
{
    ui->Client_affichage->setModel(tmp_Client.tricroissant());

}

void Client_ticket::on_tri_deccroissant_Client_clicked()
{
    ui->Client_affichage->setModel(tmp_Client.trideccroissant());

}

void Client_ticket::on_tri_croissant_ticket_clicked()
{
    ui->Ticket_affichage->setModel(tmp_Ticket.tricroissant());

}

void Client_ticket::on_tri_deccroissant_ticket_clicked()
{
    ui->Ticket_affichage->setModel(tmp_Ticket.trideccroissant());

}



void Client_ticket::on_stat_ticket_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                    model->setQuery("select * from TICKET where PRIX < 5 ");
                    float salaire=model->rowCount();
                    model->setQuery("select * from TICKET where PRIX  between 5 and 10 ");
                    float salairee=model->rowCount();
                    model->setQuery("select * from TICKET where PRIX>10 ");
                    float salaireee=model->rowCount();
                    float total=salaire+salairee+salaireee;
                    QString a=QString("moins de 5 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
                    QString b=QString("entre 5 et 10 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
                    QString c=QString("+10 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
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
                    chart->setTitle("Pourcentage Par Prix :Nombre Des Tickets "+ QString::number(total));
                    chart->legend()->hide();
                    // Used to display the chart
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    chartView->resize(1000,500);
                    chartView->show();
    }


void Client_ticket::on_pdf_client_clicked()
{
    QPdfWriter pdf("C:/Users/SeifBS/Desktop/PdfClients.pdf");
                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::blue);
                      painter.setFont(QFont("Arial", 30));
                      painter.drawText(2300,1200,"Liste Des Clients");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 50));
                     // painter.drawText(1100,2000,afficheDC);
                      painter.drawRect(1500,200,7300,2600);
                      //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(300,3300,"CIN");
                      painter.drawText(1633,3300,"TEL");
                      painter.drawText(2966,3300,"NOM");
                      painter.drawText(4299,3300,"PRENOM");
                      painter.drawText(5632,3300,"MAIL");
                      painter.drawText(6965,3300,"ADRESSE");


                      QSqlQuery query;
                      query.prepare("select * from CLIENT");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(1633,i,query.value(1).toString());
                          painter.drawText(2966,i,query.value(2).toString());
                          painter.drawText(4299,i,query.value(3).toString());
                          painter.drawText(5632,i,query.value(4).toString());
                          painter.drawText(6965,i,query.value(5).toString());



                         i = i +500;
                      }
                      int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                          if (reponse == QMessageBox::Yes)
                          {
                              QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/SeifBS/Desktop/PdfClients.pdf"));

                              painter.end();
                          }
                          if (reponse == QMessageBox::No)
                          {
                               painter.end();
                          }
}

void Client_ticket::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_Ticket();
}

void Client_ticket::on_sendBtn_3_clicked()
{
    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
          connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

          smtp->sendMail("farmeresprit414@gmail.com",ui->rcpt->text(),ui->subject->text(),ui->msg->toPlainText());
}
