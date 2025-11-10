#include <string>

class DVD_RW {
public:
    DVD_RW();
    DVD_RW(bool diskIn, std::string type, std::string mode, std::string speed);
    ~DVD_RW();

    void insertDisk(std::string type); // Вставить диск с типом
    void ejectDisk();                  // Извлечь диск
    void openTray();                   // Открыть лоток
    void closeTray();                  // Закрыть лоток
    void startRead();                  // Начать чтение
    void startWrite();                 // Начать запись
    void formatDisk();                 // Форматировать

    // Геттеры для демонстрации состояния
    std::string getState();

private:
    bool diskInserted;
    std::string diskType; // Blank, ReadOnly, Rewritable, None
    std::string mode;     // Standby, Reading, Writing, Formatting
    std::string speed;    // Low, Medium, High
    bool trayOpen;
};
