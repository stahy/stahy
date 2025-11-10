#include "Transport.h"
#include "Car.h"
#include "Truck.h"

using namespace std;

int main()
{
    Car c1("Lada", 2020, 5);
    Car c2("Toyota", 2018, 4);
    Truck t1("Kamaz", 2021, 10);
    Truck t2("MAN", 2019, 15);

    Transport* ts[4];
    ts[0] = &c1;
    ts[1] = &c2;
    ts[2] = &t1;
    ts[3] = &t2;

    // Отображение всех объектов
    for (int i = 0; i < 4; i++)
        ts[i]->show();

    // Изменение свойства по номеру
    ts[0]->setYear(2022);

    // Вычисление количества авто, выпущенных после заданного года
    int year_check = 2019;
    int count = 0;
    for (int i = 0; i < 4; i++)
        if (ts[i]->getYear() > year_check)
            count++;

    cout << "Transport released after " << year_check << ": " << count << endl;

    return 0;
}
