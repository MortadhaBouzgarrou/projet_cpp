#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>
Notification::Notification()
{

}

void Notification::notification_ajoutClient()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Clients ","Nouveau Client ajouté ",QSystemTrayIcon::Information,15000);
}
void Notification::notification_ajoutTicket()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Tickets ","Nouveau Ticket ajouté ",QSystemTrayIcon::Information,15000);
}
void Notification::notification_supprimerClient(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Clients ","Client Supprimé",QSystemTrayIcon::Information,15000);
}
void Notification::notification_supprimerTicket(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Tickets ","Un Ticket est supprimé",QSystemTrayIcon::Information,15000);

}
void Notification::notification_modifierTicket(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Tickets ","Un Ticket est modifié",QSystemTrayIcon::Information,15000);

}
void Notification::notification_modifierClient(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Clients ","Un Client est modifié",QSystemTrayIcon::Information,15000);

}
void Notification::mail_Ticket(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("","Votre Mail est envoyé :)",QSystemTrayIcon::Information,15000);

}



