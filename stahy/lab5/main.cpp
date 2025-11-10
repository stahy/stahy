#include <iostream>
#include "DVD_RW.h"

int main() {
    int work = 1, command;
    DVD_RW drive;

    while (work) {
        std::cout << "Введите команду:\n";
        std::cout << "1 - Вставить диск\n2 - Извлечь диск\n3 - Открыть лоток\n4 - Закрыть лоток\n5 - Начать чтение\n6 - Начать запись\n7 - Форматировать диск\n8 - Показать состояние\n0 - Выход\n";
        std::cin >> command ;
        std::cout << "";
        switch (command) {
            case 1: {
                std::cout << "Введите тип диска (Blank/ReadOnly/Rewritable): ";
                std::string type;
                std::cin >> type;
                drive.insertDisk(type);
                break;
            }
            case 2: drive.ejectDisk(); break;
            case 3: drive.openTray(); break;
            case 4: drive.closeTray(); break;
            case 5: drive.startRead(); break;
            case 6: drive.startWrite(); break;
            case 7: drive.formatDisk(); break;
            case 8: std::cout << drive.getState() << std::endl; break;
            case 0: work = 0; break;
        }
    }
    return 0;
}
