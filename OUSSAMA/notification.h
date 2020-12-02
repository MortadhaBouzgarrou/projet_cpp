#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSystemTrayIcon>
#include<QString>
class Notification
{
public:
    Notification();
    void notification_ajoutClient();
    void notification_ajoutTicket();
    void notification_supprimerClient();
    void notification_supprimerTicket();
    void notification_modifierClient();
    void notification_modifierTicket();
    void mail_Ticket();






};

#endif // NOTIFICATION_H
