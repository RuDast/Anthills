#include "NotificationManager.h"
#include <iostream>

NotificationManager::~NotificationManager() = default;

void NotificationManager::onFoodPickupFailed(const Ant &ant) {
    // TODO Этот менеджер должен управлять всем тем, что происходит в муравейнике после уведомлений
    std::cout << "Вызываем муравьев на помощь для сбора еды" << std::endl;
}

void NotificationManager::attacked_an_ant(float x, float y) {
    std::cout << "Нападение на муравья, нужна помощь" << std::endl;
}

void NotificationManager::attacked_an_anthill() {
    std::cout << "Нападение на муравейник, план сигма!" << std::endl;
}

void NotificationManager::connectAnthill(Anthill *anthill) {
    anthill_ = anthill;
}
