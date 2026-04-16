#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

int run_test(string name, string input, string expected);
string run_program(string input);

int main() {
    int failed = 0;

    cout << "=== Запуск тестов для проверки латинского квадрата ===" << endl;
    cout << endl;

    // Тест 1: Правильный латинский квадрат 3x3
    failed += run_test(
        "Тест 1: Латинский квадрат 3x3 (корректный)",
        "3\n1 2 3\n2 3 1\n3 1 2\n",
        "ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 2: Правильный латинский квадрат 2x2
    failed += run_test(
        "Тест 2: Латинский квадрат 2x2 (корректный)",
        "2\n1 2\n2 1\n",
        "ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 3: Неправильный квадрат (повтор в строке)
    failed += run_test(
        "Тест 3: Латинский квадрат 3x3 (повтор в строке 2)",
        "3\n1 2 3\n2 2 1\n3 1 2\n",
        "НЕ ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 4: Неправильный квадрат (повтор в столбце)
    failed += run_test(
        "Тест 4: Латинский квадрат 3x3 (повтор в столбце 1)",
        "3\n1 2 3\n2 3 1\n1 3 2\n",
        "НЕ ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 5: Неправильный квадрат (число вне диапазона)
    failed += run_test(
        "Тест 5: Латинский квадрат 3x3 (число 4 вне диапазона)",
        "3\n1 2 3\n2 4 1\n3 1 2\n",
        "НЕ ЯВЛЯЕТСЯ латинским квадратом"
        );

    // Тест 6: Правильный латинский квадрат 4x4
    failed += run_test(
        "Тест 6: Латинский квадрат 4x4 (корректный)",
        "4\n1 2 3 4\n2 1 4 3\n3 4 1 2\n4 3 2 1\n",
        "ЯВЛЯЕТСЯ латинским квадратом"
        );

    cout << "\n=== Результаты тестов ===" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;

    if (failed == 0) {
        cout << "✅ Все тесты пройдены успешно!" << endl;
        return 0;
    } else {
        cout << "❌ Провалено тестов: " << failed << endl;
        return 1;
    }
}

string run_program(string input) {
    string command = "echo \"" + input + "\" | ../usr/bin/latin-checker";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw runtime_error("popen failed");
    }

    char buffer[4096];
    string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    return result;
}

int run_test(string name, string input, string expected) {
    string output = run_program(input);

    if (output.find(expected) != string::npos) {
        cout << "✅ " << name << " - ПРОЙДЕН" << endl;
        return 0;
    } else {
        cout << "❌ " << name << " - ПРОВАЛЕН" << endl;
        cout << "   Ожидалось: \"" << expected << "\"" << endl;

        // Показываем первые 200 символов
        string short_output = output.substr(0, 200);
        cout << "   Получено: \"" << short_output << "\"" << endl;
        return 1;
    }
}
