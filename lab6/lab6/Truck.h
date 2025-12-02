#ifndef TRUCK_H
#define TRUCK_H

#include "Transport.h"

class Truck: public Transport
{
public:
    Truck(const char*, int, int);
    void setCapacity(int);
    int getCapacity(); // Геттер для грузоподъемности
    void show();
    void loadCargo(); // Собственный метод класса Truck

protected:
    int capacity;
};

#endif // TRUCK_H
