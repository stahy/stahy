#include "Truck.h"

Truck::Truck(const char* n, int y, int c)
{
    strcpy(name, n);
    year = y;
    capacity = c;
}

void Truck::setCapacity(int c)
{
    capacity = c;
}

int Truck::getCapacity()
{
    return capacity;
}

void Truck::loadCargo()
{
    cout << "Truck " << name << " is loading cargo (capacity: " << capacity << " tons)" << endl;
}

void Truck::show()
{
    cout << "Name: " << name << "  Year: " << year << "  Capacity: " << capacity << endl;
}
