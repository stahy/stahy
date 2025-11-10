#include "Car.h"

Car::Car(const char* n, int y, int s)
{
    strcpy(name, n);
    year = y;
    seats = s;
}

void Car::setSeats(int s)
{
    seats = s;
}

void Car::show()
{
    cout << "Name: " << name << "  Year: " << year << "  Seats: " << seats << endl;
}
