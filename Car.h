#ifndef CAR_H
#define CAR_H

#include "Transport.h"

class Car: public Transport
{
public:
    Car(const char*, int, int);
    void setSeats(int);
    int getSeats(); // Геттер для количества мест
    void show();
    void honk(); // Собственный метод класса Car

protected:
    int seats;
};

#endif // CAR_H
