#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    int id;
    string fullName;
    string position;
    int age;
    float salary;
    int experience;

public:
    // Конструктор по умолчанию
    Employee() {
        id = 0;
        fullName = "None";
        position = "None";
        age = 0;
        salary = 0.0f;
        experience = 0;
    }

    // Конструктор с параметрами
    Employee(int _id, string _fullName, string _position, int _age, float _salary, int _experience) {
        id = _id;
        fullName = _fullName;
        position = _position;
        age = _age;
        salary = _salary;
        experience = _experience;
    }

    // Методы для редактирования и получения свойств
    int getId() const { return id; }
    void setId(int val) { id = val; }

    string getFullName() const { return fullName; }
    void setFullName(string val) { fullName = val; }

    string getPosition() const { return position; }
    void setPosition(string val) { position = val; }

    int getAge() const { return age; }
    void setAge(int val) { age = val; }

    float getSalary() const { return salary; }
    void setSalary(float val) { salary = val; }

    int getExperience() const { return experience; }
    void setExperience(int val) { experience = val; }

    // Метод для вывода информации об объекте
    void print() const {
        cout
            << id << " | "
            << fullName << " | "
            << position << " | "
            << age << " | "
            << salary << " | "
            << experience << endl;
    }
};

void printTable(Employee* arr, int size) {
    printf(" ID   | %-25s | %-20s | Возраст |  Зарплата  | Стаж\n", "ФИО", "Должность");
    printf("--------------------------------------------------------------------------\n");
    
for (int i = 0; i < size; i++) {
    printf("%4d | %-25s | %-20s | %7d | %10.2f | %4d\n",
        arr[i].getId(),
        arr[i].getFullName().c_str(),
        arr[i].getPosition().c_str(),
        arr[i].getAge(),
        arr[i].getSalary(),
        arr[i].getExperience()
    );
  }
}

int main() {
    const int size = 3;
    // Исходные тестовые данные, как в первой работе
    Employee arr[size] = {
        Employee(1001, "Иванов Иван Иванович", "Разработчик", 28, 75000.5, 5),
        Employee(1002, "Петрова Мария Сергеевна", "Бухгалтер", 33, 62000.0, 10),
        Employee(1003, "Сидоров Алексей Петрович", "Тестировщик", 25, 51000.75, 2)
    };

    int menu = -1;
    while (menu != 0) {
        cout << "\nМеню:\n";
        cout << "1. Посмотреть всю таблицу\n";
        cout << "2. Редактировать сотрудника\n";
        cout << "3. Средняя зарплата\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> menu;

        if (menu == 1) {
            printTable(arr, size);
        } else if (menu == 2) {
            int idx;
            cout << "Введите индекс (0..2) сотрудника: ";
            cin >> idx;
            if (idx >= 0 && idx < size) {
                string newName, newPos;
                int newAge, newExp;
                float newSal;
                cout << "Введите новое ФИО: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Введите новую должность: ";
                getline(cin, newPos);
                cout << "Введите возраст: ";
                cin >> newAge;
                cout << "Введите зарплату: ";
                cin >> newSal;
                cout << "Введите стаж: ";
                cin >> newExp;
                arr[idx].setFullName(newName);
                arr[idx].setPosition(newPos);
                arr[idx].setAge(newAge);
                arr[idx].setSalary(newSal);
                arr[idx].setExperience(newExp);
            } else {
                cout << "Некорректный индекс." << endl;
            }
        } else if (menu == 3) {
            float sum = 0.0;
            for (int i = 0; i < size; i++) sum += arr[i].getSalary();
            cout << "Средняя зарплата: " << (sum / size) << endl;
        } else if (menu == 0) {
            cout << "Выход." << endl;
        } else {
            cout << "Некорректный выбор!" << endl;
        }
    }
    return 0;
}
