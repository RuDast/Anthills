#ifndef ROLE_H
#define ROLE_H


class Role {
public:
    virtual ~Role() = default;

private:
    virtual void work() = 0;

public:
    virtual void print();
    virtual bool isCleaner();
    virtual bool isNone();
};


#endif //ROLE_H
