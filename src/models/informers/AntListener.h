#ifndef ANTLISTENER_H
#define ANTLISTENER_H

class Ant;


class AntListener {
public:
    virtual ~AntListener() = default;

    virtual void on_change_role(const Ant &ant) = 0;
};


#endif //ANTLISTENER_H
