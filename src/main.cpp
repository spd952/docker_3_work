#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

// Функция для ввода числа с проверкой диапазона от 1 до 100
int inputNumber(const string& prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число от 1 до 100." << endl;
        }
        else if (number < 1 || number > 100) {
            cout << "Ошибка! Число должно быть от 1 до 100." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }
    }
}

// Функция для ввода матрицы с клавиатуры
void inputMatrixInteractive(int** matrix, int size, const string& name) {
    cout << "\nВведите элементы матрицы " << name << " (" << size << "x" << size << "):" << endl;
    cout << "Числа должны быть целыми от 1 до " << size << " (для латинского квадрата)." << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            string prompt = "Элемент [" + to_string(i + 1) + "][" + to_string(j + 1) + "]: ";
            matrix[i][j] = inputNumber(prompt);
        }
    }
}

// Функция для вывода матрицы на экран
void printMatrix(int** matrix, int size, const string& name) {
    cout << "\nМатрица " << name << " (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(4) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для проверки, является ли матрица латинским квадратом
bool isLatinSquare(int** matrix, int size) {
    // Проверка строк
    for (int i = 0; i < size; i++) {
        bool* seen = new bool[size + 1]();

        for (int j = 0; j < size; j++) {
            int val = matrix[i][j];
            if (val < 1 || val > size) {
                delete[] seen;
                return false;
            }
            if (seen[val]) {
                delete[] seen;
                return false;
            }
            seen[val] = true;
        }
        delete[] seen;
    }

    // Проверка столбцов
    for (int j = 0; j < size; j++) {
        bool* seen = new bool[size + 1]();

        for (int i = 0; i < size; i++) {
            int val = matrix[i][j];
            if (val < 1 || val > size) {
                delete[] seen;
                return false;
            }
            if (seen[val]) {
                delete[] seen;
                return false;
            }
            seen[val] = true;
        }
        delete[] seen;
    }

    return true;
}

// Функция для проверки и вывода результата
void checkLatinSquare(int** matrix, int size, const string& name) {
    cout << "\n=== Проверка матрицы " << name << " ===" << endl;
    printMatrix(matrix, size, name);

    if (isLatinSquare(matrix, size)) {
        cout << "\nРезультат: Матрица " << name << " ЯВЛЯЕТСЯ латинским квадратом!" << endl;
        cout << "Каждая строка и каждый столбец содержат все числа от 1 до " << size << "." << endl;
    } else {
        cout << "\nРезультат: Матрица " << name << " НЕ ЯВЛЯЕТСЯ латинским квадратом." << endl;
        cout << "Условие нарушено (число вне диапазона 1.." << size
             << " или есть повторения в строке/столбце)." << endl;
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    // Режим 1: Чтение из pipe или перенаправления (для тестов)
    if (!isatty(STDIN_FILENO)) {
        int size;
        cin >> size;

        if (size < 1 || size > 100) {
            cerr << "Ошибка: размер должен быть от 1 до 100" << endl;
            return 1;
        }

        // Создание матрицы
        int** matrix = new int*[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }

        // Чтение матрицы
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> matrix[i][j];
            }
        }

        // Проверка
        checkLatinSquare(matrix, size, "M");

        // Освобождение памяти
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;

        return 0;
    }

    // Режим 2: Интерактивный режим
    cout << "=== Программа проверки латинского квадрата ===" << endl;
    cout << "Латинский квадрат порядка n — это матрица n x n," << endl;
    cout << "в которой каждая строка и каждый столбец содержат все числа от 1 до n." << endl;

    int size;
    cout << "\nВведите порядок матрицы n (от 1 до 100): ";
    size = inputNumber("n = ");

    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }

    inputMatrixInteractive(matrix, size, "M");
    checkLatinSquare(matrix, size, "M");

    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    cout << "\nПрограмма завершена." << endl;
    return 0;
}
