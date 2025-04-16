#ifndef NOTIFICATIONLISTENER_H
#define NOTIFICATIONLISTENER_H

class Anthill;
class Ant;


class NotificationListener {
public:
    virtual ~NotificationListener();
    virtual void onFoodPickupFailed(const Ant& ant);
    virtual void attacked_an_ant(float x, float y);
    virtual void attacked_an_anthill();
    virtual void connectAnthill(Anthill* anthill);
    // TODO добавить остальные методы для уведомлений
};



#endif //NOTIFICATIONLISTENER_H
