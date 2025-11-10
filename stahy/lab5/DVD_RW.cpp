#include "DVD_RW.h"
#include <string>
#include <iostream>

// Конструкторы
DVD_RW::DVD_RW() {
    diskInserted = false;
    diskType = "Отсутствует";
    mode = "Ожидание";
    speed = "Низкая";
    trayOpen = false;
}

DVD_RW::DVD_RW(bool diskIn, std::string type, std::string mode, std::string speed) {
    diskInserted = diskIn;
    diskType = type;
    this->mode = mode;
    this->speed = speed;
    trayOpen = false;
}

DVD_RW::~DVD_RW() {}

// Открыть лоток
void DVD_RW::openTray() {
    if (!trayOpen && mode == "Ожидание") {
        trayOpen = true;
        std::cout << "Лоток открыт." << std::endl;
    } else if (trayOpen) {
        std::cout << "Лоток уже открыт." << std::endl;
    } else {
        std::cout << "Невозможно открыть лоток во время: " << mode << std::endl;
    }
}

// Закрыть лоток
void DVD_RW::closeTray() {
    if (trayOpen) {
        trayOpen = false;
        std::cout << "Лоток закрыт." << std::endl;
    } else {
        std::cout << "Лоток уже закрыт." << std::endl;
    }
}

// Вставить диск
void DVD_RW::insertDisk(std::string type) {
    if (!trayOpen) {
        std::cout << "Ошибка: Сначала откройте лоток!" << std::endl;
        return;
    }
    if (diskInserted) {
        std::cout << "Ошибка: Диск уже вставлен!" << std::endl;
        return;
    }
    
    if (type == "Blank") diskType = "Чистый";
    else if (type == "ReadOnly") diskType = "Только чтение";
    else if (type == "Rewritable") diskType = "Перезаписываемый";
    else diskType = type;
    
    diskInserted = true;
    mode = "Ожидание";
    speed = "Низкая";
    std::cout << "Диск вставлен: " << diskType << std::endl;
}

// Извлечь диск
void DVD_RW::ejectDisk() {
    if (!trayOpen) {
        std::cout << "Ошибка: Сначала откройте лоток!" << std::endl;
        return;
    }
    if (!diskInserted) {
        std::cout << "Ошибка: Диск не вставлен!" << std::endl;
        return;
    }
    
    diskType = "Отсутствует";
    diskInserted = false;
    mode = "Ожидание";
    speed = "Низкая";
    std::cout << "Диск извлечен." << std::endl;
}

// Начать чтение
void DVD_RW::startRead() {
    if (trayOpen) {
        std::cout << "Ошибка: Закройте лоток!" << std::endl;
        return;
    }
    if (!diskInserted) {
        std::cout << "Ошибка: Диск не вставлен!" << std::endl;
        return;
    }
    if (diskType != "Только чтение" && diskType != "Перезаписываемый") {
        std::cout << "Ошибка: Невозможно читать с диска типа '" << diskType << "'!" << std::endl;
        return;
    }
    
    mode = "Чтение";
    speed = "Средняя";
    std::cout << "Начато чтение диска." << std::endl;
}

// Начать запись
void DVD_RW::startWrite() {
    if (trayOpen) {
        std::cout << "Ошибка: Закройте лоток!" << std::endl;
        return;
    }
    if (!diskInserted) {
        std::cout << "Ошибка: Диск не вставлен!" << std::endl;
        return;
    }
    if (diskType != "Чистый") {
        std::cout << "Ошибка: Можно записывать только на чистые диски!" << std::endl;
        return;
    }
    
    mode = "Запись";
    diskType = "Перезаписываемый";
    speed = "Высокая";
    std::cout << "Начата запись на диск." << std::endl;
}

// Форматировать диск
void DVD_RW::formatDisk() {
    if (trayOpen) {
        std::cout << "Ошибка: Закройте лоток!" << std::endl;
        return;
    }
    if (!diskInserted) {
        std::cout << "Ошибка: Диск не вставлен!" << std::endl;
        return;
    }
    if (diskType != "Перезаписываемый") {
        std::cout << "Ошибка: Можно форматировать только перезаписываемые диски!" << std::endl;
        return;
    }
    
    mode = "Форматирование";
    speed = "Высокая";
    std::cout << "Начато форматирование диска." << std::endl;
}

// Получить состояние
std::string DVD_RW::getState() {
    std::string state = "Лоток: " + std::string(trayOpen ? "Открыт" : "Закрыт") + "\n";
    state += "Диск вставлен: " + std::string(diskInserted ? "Да" : "Нет") + "\n";
    state += "Тип: " + diskType + "\n";
    state += "Режим: " + mode + "\n";
    state += "Скорость: " + speed + "\n";
    return state;
}
