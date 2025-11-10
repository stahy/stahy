#include <iostream>
#include <fstream>

using namespace std;

// структура Сотрудника
struct Employee {
    int id;
    char fullName[50];
    char position[30];
    int age;
    float salary;
    int experience;
};

// Загрузить данные из файла
Employee* loadFromFile(const char* filename, int& size) {
    ifstream fin(filename);
    if (!fin) {
        cout << "Файл не найден!" << endl;
        size = 0;
        return nullptr;
    }
    fin >> size;
    fin.get();

    Employee* employees = new Employee[size];
    for (int i = 0; i < size; i++) {
        fin >> employees[i].id;
        fin.get();
        fin.getline(employees[i].fullName, 50);
        fin.getline(employees[i].position, 30);
        fin >> employees[i].age >> employees[i].salary >> employees[i].experience;
        fin.get();
    }
    fin.close();
    return employees;
}

// Сохранить данные в файл
void saveToFile(const char* filename, Employee* employees, int size) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }
    fout << size << endl;
    for (int i = 0; i < size; i++) {
        fout << employees[i].id << "\n"
             << employees[i].fullName << "\n"
             << employees[i].position << "\n"
             << employees[i].age << " "
             << employees[i].salary << " "
             << employees[i].experience << "\n";
    }
    fout.close();
}

// Печать таблицы сотрудников
void printTable(Employee* employees, int size) {
    printf(" ID   | %-25s | %-20s | Возраст |  Зарплата  | Стаж\n", "ФИО", "Должность");
    printf("--------------------------------------------------------------------------\n");
    
    for (int i = 0; i < size; i++) {
        printf("%4d | %-25s | %-20s | %7d | %10.2f | %4d\n",
            employees[i].id,
            employees[i].fullName,
            employees[i].position,
            employees[i].age,
            employees[i].salary,
            employees[i].experience
        );
    }
}

// Редактировать сотрудника по ID
void editEmployee(Employee* employees, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (employees[i].id == id) {
            cout << "Редактирование сотрудника с ID=" << id << endl;
            cout << "Введите новое ФИО: ";
            cin.get();
            cin.getline(employees[i].fullName, 50);
            cout << "Введите новую должность: ";
            cin.getline(employees[i].position, 30);
            cout << "Введите новый возраст: ";
            cin >> employees[i].age;
            cout << "Введите новую зарплату: ";
            cin >> employees[i].salary;
            cout << "Введите новый стаж: ";
            cin >> employees[i].experience;
            return;
        }
    }
    cout << "Сотрудник с таким ID не найден." << endl;
}

// Вычислить среднюю зарплату
float averageSalary(Employee* employees, int size) {
    if (size == 0) return 0.0f;
    float sum = 0;
    for (int i = 0; i < size; i++) sum += employees[i].salary;
    return sum / size;
}

int main() {
    Employee* employees = nullptr;
    int size = 0;
    int choice;
    char filename[50];
    char saveFilename[50];

    do {
        cout << "\nМеню:\n"
             << "1. Загрузить данные из файла\n"
             << "2. Просмотреть данные\n"
             << "3. Редактировать данные по ID\n"
             << "4. Вычислить среднюю зарплату\n"
             << "5. Сохранить данные в новый файл\n"
             << "0. Выход\n"
             << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите имя входного файла: ";
            cin >> filename;
            if (employees) {
                delete[] employees;
                employees = nullptr;
                size = 0;
            }
            employees = loadFromFile(filename, size);
            break;
        case 2:
            if (employees && size > 0)
                printTable(employees, size);
            else
                cout << "Данные не загружены." << endl;
            break;
        case 3:
            if (employees && size > 0) {
                int id;
                cout << "Введите ID сотрудника для редактирования: ";
                cin >> id;
                editEmployee(employees, size, id);
            } else {
                cout << "Данные не загружены." << endl;
            }
            break;
        case 4:
            if (employees && size > 0) {
                cout << "Средняя зарплата: " << averageSalary(employees, size) << endl;
            } else {
                cout << "Данные не загружены." << endl;
            }
            break;
        case 5:
            if (employees && size > 0) {
                cout << "Введите имя файла для сохранения: ";
                cin >> saveFilename;
                saveToFile(saveFilename, employees, size);
                cout << "Данные сохранены." << endl;
            } else {
                cout << "Данные не загружены." << endl;
            }
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор." << endl;
        }
    } while (choice != 0);

    if (employees) delete[] employees;

    return 0;
}

//       g++ main.cpp -o main - компиляция
//       ./main (macOS/Linux) || main.exe (Windows) - запуск программы