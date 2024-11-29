#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

class AssociativeArray {
private:
    std::map<int, std::string> data; // Основний контейнер для збереження асоціацій
    int CodeError = 0;              // Змінна для збереження коду помилки

public:
    // Додавання асоціації
    void addPair(int number, const std::string& text) {
        data[number] = text;
    }

    // Перевантаження оператора []
    const std::string& operator[](int number) {
        if (data.find(number) != data.end()) {
            CodeError = 0; // Помилка відсутня
            return data[number];
        } else {
            CodeError = -1; // Помилка: елемент не знайдено
            static const std::string error = "Не знайдено";
            return error;
        }
    }

    // Перевантаження операції ()
    const std::string& operator()(int number) {
        return (*this)[number]; // Використовуємо вже реалізований оператор []
    }

    // Повернення коду помилки
    int getCodeError() const {
        return CodeError;
    }

    // Дружня операція введення
    friend std::istream& operator>>(std::istream& in, AssociativeArray& array) {
        int number;
        std::string text;
        std::cout << "Введіть число та його текстове представлення (наприклад, '1 один'): ";
        in >> number >> text;
        array.addPair(number, text);
        return in;
    }

    // Дружня операція виведення
    friend std::ostream& operator<<(std::ostream& out, const AssociativeArray& array) {
        for (const auto& [number, text] : array.data) {
            out << number << " -> " << text << "\n";
        }
        return out;
    }
};

// Функція для створення набору асоціативних сутностей
AssociativeArray createAssociativeArray() {
    AssociativeArray array;
    array.addPair(1, "один");
    array.addPair(10, "десять");
    array.addPair(100, "сто");
    return array;
}

int main() {
    // Створення об'єкта асоціативного масиву
    AssociativeArray array = createAssociativeArray();

    // Виведення вмісту
    std::cout << "Ініціальний асоціативний масив:\n" << array;

    // Перевірка операторів [] та ()
    std::cout << "Значення за ключем 10: " << array[10] << "\n";
    
    // Додавання нових значень через ввід
    std::cin >> array;

    // Повторний вивід вмісту
    std::cout << "\nОновлений асоціативний масив:\n" << array;

    return 0;
}
