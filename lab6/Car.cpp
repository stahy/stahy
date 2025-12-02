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

int Car::getSeats()
{
    return seats;
}

void Car::honk()
{
    cout << "Car " << name << " honks: Beep-beep!" << endl;
}

void Car::show()
{
    cout << "Name: " << name << "  Year: " << year << "  Seats: " << seats << endl;
}
