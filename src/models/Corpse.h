#ifndef CORPSE_H
#define CORPSE_H


enum class CorpseState { free, wait, going, on_trash };

class Corpse {
public:
    Corpse(float x, float y)
        : x(x), y(y), state(CorpseState::free), alive(true) {}

    float getX() const { return x; }
    float getY() const { return y; }

    CorpseState getState() const { return state; }
    void setState(CorpseState s) { state = s; }

    bool isAlive() const { return alive; }
    void terminate() { alive = false; }

private:
    float x, y;
    CorpseState state;
    bool alive;
};



#endif //CORPSE_H
