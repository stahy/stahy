#include "Transport.h"

Transport::Transport(): year(0)
{
    strcpy(name, "Noname");
}

void Transport::show()
{
    cout << "Name: " << name << "  Year: " << year << endl;
}

int Transport::getYear()
{
    return year;
}

void Transport::setName(const char* n)
{
    strcpy(name, n);
}

void Transport::setYear(int y)
{
    year = y;
}
