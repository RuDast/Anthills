#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H
#include "NotificationListener.h"
#include "../Anthill.h"


class NotificationManager : public NotificationListener {
public:
    ~NotificationManager() override;

    void onFoodPickupFailed(const Ant &ant) override;

    void attacked_an_ant(float x, float y) override;

    void attacked_an_anthill() override;

    void connectAnthill(Anthill* anthill) override;

private:
    Anthill* anthill_ = nullptr;
};



#endif //NOTIFICATIONMANAGER_H
