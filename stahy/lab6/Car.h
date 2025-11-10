#ifndef CAR_H
#define CAR_H

#include "Transport.h"

class Car: public Transport
{
public:
    Car(const char*, int, int);
    void setSeats(int);
    void show();

protected:
    int seats;
};

#endif // CAR_H
