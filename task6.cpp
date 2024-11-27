#include <iostream>
#include <string>

using namespace std;

struct RomanNumeral {
    int value;            // Значение римского символа
    const char* symbol;   // Римский символ
};

struct HashNode {
    RomanNumeral numeral;
    HashNode* next;
};

class HashTable {
private:
    HashNode* table[13]; // Массив указателей на узлы

public:
    // Конструктор
    HashTable() {
        // Инициализация таблицы
        for (int i = 0; i < 13; ++i) {
            table[i] = nullptr;
        }
        // Заполнение таблицы
        insert(4000, "MMMM"); // 4000
        insert(3000, "MMM");
        insert(2000, "MM");
        insert(1000, "M");
        insert(900, "CM");
        insert(500, "D");
        insert(400, "CD");
        insert(100, "C");
        insert(90, "XC");
        insert(50, "L");
        insert(40, "XL");
        insert(10, "X");
        insert(9, "IX");
        insert(5, "V");
        insert(4, "IV");
        insert(1, "I");
    }

    // Метод для вставки узла в хэш-таблицу
    void insert(int value, const char* symbol) {
        int index = value % 13; // Хэш-функция
        HashNode* newNode = new HashNode{{value, symbol}, nullptr};

        if (table[index] == nullptr) {
            table[index] = newNode; // Если индекс свободен, добавляем новый узел
        } else {
            // Если индекс занят, добавляем узел в конец цепочки
            HashNode* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode; // Добавление в конец цепочки
        }
    }

    // Метод для получения римского символа по его значению
    const char* getSymbol(int value) {
        int index = value % 13; // Хэш-функция
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->numeral.value == value) {
                return current->numeral.symbol; // Если найдено, возвращаем символ
            }
            current = current->next; // Переходим к следующему узлу
        }
        return nullptr; // Если не найдено
    }

    // Деструктор для освобождения памяти
    ~HashTable() {
        for (int i = 0; i < 13; ++i) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }
};

string intToRoman(int num, HashTable& hashTable) {
    string result;

    // Проходим по хэш-таблице
    for (int value : {4000, 3000, 2000, 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}) {
        while (num >= value) {
            result += hashTable.getSymbol(value); // Добавляем римский символ
            num -= value;                         // Уменьшаем число
        }
    }
    return result;
}

int main() {
    int number;
    cout << "Введите целое число (1-5252): ";
    cin >> number;

    if (number <= 0 || number > 5252) {
        cout << "Пожалуйста, введите число в диапазоне от 1 до 5252." << endl;
        return 1;
    }

    HashTable hashTable; // Создаем экземпляр хэш-таблицы
    string roman = intToRoman(number, hashTable);
    cout << "Римская цифра: " << roman << endl;

    return 0;
}