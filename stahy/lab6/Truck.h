#ifndef TRUCK_H
#define TRUCK_H

#include "Transport.h"

class Truck: public Transport
{
public:
    Truck(const char*, int, int);
    void setCapacity(int);
    void show();

protected:
    int capacity;
};

#endif // TRUCK_H
