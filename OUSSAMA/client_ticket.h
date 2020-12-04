#ifndef Client_ticket_H
#define Client_ticket_H
#include "ticket.h"
#include "client.h"
#include "notification.h"



#include <QMainWindow>

namespace Ui {
class Client_ticket;
}

class Client_ticket : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client_ticket(QWidget *parent = nullptr);
    ~Client_ticket();

private slots:





    void on_pb_ajouter_c_clicked();

    void on_pb_modifier_c_clicked();

    void on_pb_supprimer_c_clicked();

    void on_Client_affichage_activated(const QModelIndex &index);


    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_ajouter_clicked();


    void on_Ticket_affichage_activated(const QModelIndex &index);

    void on_recherche_client_textChanged();

    void on_recherche_ticket_textChanged();

    void on_tri_croissant_Client_clicked();

    void on_tri_deccroissant_Client_clicked();

    void on_tri_croissant_ticket_clicked();

    void on_tri_deccroissant_ticket_clicked();


    void on_stat_ticket_clicked();

    void on_pdf_client_clicked();

    void on_sendBtn_3_clicked();
    void mailSent(QString);


private:
    Ui::Client_ticket *ui;
    Ticket tmp_Ticket;
    Client tmp_Client;
    Notification N;
    void refresh();


};

#endif // Client_ticket_H
