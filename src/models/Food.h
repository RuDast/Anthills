#ifndef FOOD_H
#define FOOD_H

enum class FoodState {
    free, // свободна
    wait, // ждет муравья
    going, // ее относят
    on_sklad // на складе
};


class Food {
public:
    Food();
private:
    bool is_taken = false;
    unsigned weight ;
    float x,y;
    FoodState state = FoodState::free;
    bool is_alive = true;
public:
    void print() const;
    float getX() const;
    float getY() const;
    FoodState getState() const;
    void setState(FoodState state);

    bool isAlive() const;
    void terminate();
};



#endif //FOOD_H