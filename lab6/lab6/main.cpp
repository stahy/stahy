#include "Transport.h"
#include "Car.h"
#include "Truck.h"
#include <iostream>

using namespace std;

void showMenu() {
    cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ТРАНСПОРТОМ ===" << endl;
    cout << "1. Показать все объекты" << endl;
    cout << "2. Изменить свойство по номеру" << endl;
    cout << "3. Вычислить количество транспорта после заданного года" << endl;
    cout << "4. Вызвать собственные методы классов" << endl;
    cout << "0. Выход" << endl;
    cout << "Введите команду: ";
}

void showAllObjects(Transport* ts[], int size) {
    cout << "\n=== ВСЕ ОБЪЕКТЫ ===" << endl;
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] ";
        ts[i]->show();
    }
}

void changeProperty(Transport* ts[], int size) {
    cout << "\nВведите номер объекта (0-" << size-1 << "): ";
    int index;
    cin >> index;
    
    if (index < 0 || index >= size) {
        cout << "Неверный номер объекта!" << endl;
        return;
    }
    
    cout << "Что изменить?" << endl;
    cout << "1. Название" << endl;
    cout << "2. Год выпуска" << endl;
    
    // Определяем тип объекта для дополнительных свойств
    Car* car = dynamic_cast<Car*>(ts[index]);
    Truck* truck = dynamic_cast<Truck*>(ts[index]);
    
    if (car) {
        cout << "3. Количество мест" << endl;
    } else if (truck) {
        cout << "3. Грузоподъемность" << endl;
    }
    
    cout << "Выберите: ";
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1: {
            cout << "Введите новое название: ";
            char newName[30];
            cin >> newName;
            ts[index]->setName(newName);
            cout << "Название изменено!" << endl;
            break;
        }
        case 2: {
            cout << "Введите новый год: ";
            int newYear;
            cin >> newYear;
            ts[index]->setYear(newYear);
            cout << "Год изменен!" << endl;
            break;
        }
        case 3: {
            if (car) {
                cout << "Введите новое количество мест: ";
                int seats;
                cin >> seats;
                car->setSeats(seats);
                cout << "Количество мест изменено!" << endl;
            } else if (truck) {
                cout << "Введите новую грузоподъемность: ";
                int capacity;
                cin >> capacity;
                truck->setCapacity(capacity);
                cout << "Грузоподъемность изменена!" << endl;
            }
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
    }
}

void calculateAfterYear(Transport* ts[], int size) {
    cout << "\nВведите год для сравнения: ";
    int year_check;
    cin >> year_check;
    
    int count = 0;
    cout << "\nТранспорт выпущенный после " << year_check << " года:" << endl;
    for (int i = 0; i < size; i++) {
        if (ts[i]->getYear() > year_check) {
            cout << "[" << i << "] ";
            ts[i]->show();
            count++;
        }
    }
    cout << "Всего найдено: " << count << " объектов" << endl;
}

void callSpecificMethods(Transport* ts[], int size) {
    cout << "\n=== СОБСТВЕННЫЕ МЕТОДЫ КЛАССОВ ===" << endl;
    for (int i = 0; i < size; i++) {
        Car* car = dynamic_cast<Car*>(ts[i]);
        Truck* truck = dynamic_cast<Truck*>(ts[i]);
        
        if (car) {
            car->honk();
        } else if (truck) {
            truck->loadCargo();
        }
    }
}

int main()
{
    // Создание объектов
    Car c1("Lada", 2020, 5);
    Car c2("Toyota", 2018, 4);
    Truck t1("Kamaz", 2021, 10);
    Truck t2("MAN", 2019, 15);

    // Массив указателей на базовый класс
    const int SIZE = 4;
    Transport* ts[SIZE];
    ts[0] = &c1;
    ts[1] = &c2;
    ts[2] = &t1;
    ts[3] = &t2;

    int choice;
    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                showAllObjects(ts, SIZE);
                break;
            case 2:
                changeProperty(ts, SIZE);
                showAllObjects(ts, SIZE);
                break;
            case 3:
                calculateAfterYear(ts, SIZE);
                showAllObjects(ts, SIZE);
                break;
            case 4:
                callSpecificMethods(ts, SIZE);
                showAllObjects(ts, SIZE);
                break;
            case 0:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверная команда!" << endl;
        }
    } while (choice != 0);

    return 0;
}

//                 g++ -o main main.cpp Transport.cpp Car.cpp Truck.cpp 