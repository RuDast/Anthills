#ifndef FOOD_H
#define FOOD_H



class Food {
public:
    Food();
private:
    unsigned weight ;
    float x,y;
    //TODO добавить подписчиков
public:
    void print() const;
    float getX() const;
    float getY() const;

};



#endif //FOOD_H