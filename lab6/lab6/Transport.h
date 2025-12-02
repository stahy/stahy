#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string.h>
using namespace std;

class Transport
{
public:
    Transport();
    virtual ~Transport();
    virtual void show();
    int getYear();
    void setName(const char*);
    void setYear(int);

protected:
    char name[30];
    int year;
};

#endif // TRANSPORT_H
