/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Тестовий файл (головний) для C++ проекту.
 */
#include <iostream>
#include "ArrayStatistic.h"

// Допоміжна функція, щоб потримати консоль
void pause_console() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(); // Ігноруємо попередній '\n'
    std::cin.get();    // Чекаємо на Enter
}

// Нова функція для тестування операцій
void test_set_operations() {
    std::cout << "\n\n--- Testing Union (+) and Intersection (*) ---\n";
    // Створюємо два набори даних
    ArrayStatistic stats1;
    ArrayStatistic stats2;

    // Використовуємо { } для створення std::vector "на льоту"
    stats1.addArray({1.0, 2.0}); // Спільний
    stats1.addArray({3.0, 4.0}); // Тільки в s1

    stats2.addArray({1.0, 2.0}); // Спільний
    stats2.addArray({5.0, 6.0}); // Тільки в s2

    std::cout << "Stats1:\n";
    stats1.print();
    std::cout << "Stats2:\n";
    stats2.print();

    // Тест Об'єднання (Union)
    std::cout << "\nTesting Union (stats1 + stats2)...\n";
    ArrayStatistic stats_union = stats1 + stats2;
    stats_union.print();

    // Тест Перетину (Intersection)
    std::cout << "\nTesting Intersection (stats1 * stats2)...\n";
    ArrayStatistic stats_intersect = stats1 * stats2;
    stats_intersect.print();
}

int main() {
    std::cout << "--- Welcome to ArrayStatistic (C++) Test Program ---\n";

    ArrayStatistic stats;
    int choice = 0;

    std::cout << "How do you want to load data?\n";
    std::cout << "  1: Load from file (ArrayStatistic_test.dat)\n";
    std::cout << "  2: Enter data manually (from console)\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    // --- Блок завантаження даних ---
    switch (choice) {
        case 1:
            std::cout << "Loading from file...\n";
            if (stats.loadFromFile("ArrayStatistic_test.dat")) {
                std::cout << "File loaded successfully.\n";
            } else {
                std::cerr << "File loading failed.\n";
            }
            break;
        case 2:
            std::cout << "Loading from console...\n";
            stats.readFromConsole();
            break;
        default:
            std::cout << "Invalid choice. Starting with an empty structure.\n";
            break;
    }

    std::cout << "\n--- Current data state: ---\n";
    stats.print();
    pause_console();

    // --- Блок тестування операцій ---
    if (stats.getNumArrays() > 0) {
        std::cout << "\n--- Testing Deletion ---\n";
        std::cout << "Testing deleteElement(0, 0)...\n";
        stats.deleteElement(0, 0);
        stats.print();
    }

    pause_console();

    // +++ БЛОК ТЕСТУВАННЯ ОПЕРАТОРІВ +++
    test_set_operations();
    pause_console();

    // +++ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (Spearman) +++
    std::cout << "\n\n--- Testing Statistics (Spearman) ---\n";
    if (stats.getNumArrays() >= 2) {
        std::cout << "Calculating Spearman for loaded arrays [0] and [1]...\n";
        double rho_loaded = stats.getSpearman(0, 1);
        std::cout << "Spearman's Rho (loaded data): " << rho_loaded << "\n";
    }

    ArrayStatistic stats_stat;
    stats_stat.addArray({1.0, 2.0, 3.0, 4.0, 5.0});
    stats_stat.addArray({2.0, 4.0, 6.0, 8.0, 10.0});
    stats_stat.addArray({5.0, 4.0, 3.0, 2.0, 1.0});

    std::cout << "\nCalculating Spearman for test data (X vs Y)...\n";
    double rho_XY = stats_stat.getSpearman(0, 1);
    std::cout << "Spearman's Rho (X, Y): " << rho_XY << "\n";

    std::cout << "\nCalculating Spearman for test data (X vs Z)...\n";
    double rho_XZ = stats_stat.getSpearman(0, 2);
    std::cout << "Spearman's Rho (X, Z): " << rho_XZ << "\n";

    pause_console();

    // +++ БЛОК ТЕСТУВАННЯ (F-test, t-test, Z-test) +++
    std::cout << "\n\n--- Testing Statistics (Fisher, t-test, Z-test) ---\n";

    ArrayStatistic stats_ftest;
    stats_ftest.addArray({10.0, 10.1, 10.0, 9.9, 10.0});
    stats_ftest.addArray({5.0, 10.0, 15.0, 2.0, 20.0});

    std::cout << "Calculating Fisher F-test for low_var vs high_var...\n";
    double f_value = stats_ftest.getFisherTest(0, 1);
    std::cout << "Fisher F-value: " << f_value << "\n";

    ArrayStatistic stats_ttest;
    stats_ttest.addArray({10, 11, 12, 10, 11});
    stats_ttest.addArray({13, 14, 12, 13, 14});

    std::cout << "\nCalculating t-test (small samples)...\n";
    double t_val = stats_ttest.getTTestSmall(0, 1);
    std::cout << "t-value: " << t_val << "\n";

    std::cout << "\nCalculating Z-test (using same small samples)...\n";
    double z_val = stats_ttest.getZTestLarge(0, 1);
    std::cout << "Z-value: " << z_val << "\n";

    pause_console();

    // +++ ФІНАЛЬНИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (Wilcoxon) +++
    std::cout << "\n\n--- Testing Statistics (Wilcoxon/Wilson U-test) ---\n";

    ArrayStatistic stats_wilcox;
    stats_wilcox.addArray({1, 2, 3});
    stats_wilcox.addArray({10, 11, 12});

    std::cout << "Calculating U-test (perfect separation)...\n";
    double u_val_1 = stats_wilcox.getWilsonTest(0, 1);
    std::cout << "U-value (perfect separation): " << u_val_1 << "\n";

    ArrayStatistic stats_wilcox_2;
    stats_wilcox_2.addArray({1, 10, 12});
    stats_wilcox_2.addArray({2, 3, 11});

    std::cout << "\nCalculating U-test (mixed samples)...\n";
    double u_val_2 = stats_wilcox_2.getWilsonTest(0, 1);
    std::cout << "U-value (mixed samples): " << u_val_2 << "\n";

    pause_console();

    // +++ ТЕСТУВАННЯ addElement та deleteElementByValue +++
    std::cout << "\n\n--- Testing addElement & deleteElementByValue ---\n";
    if (stats.getNumArrays() > 0) {
        std::cout << "Before addElement:\n";
        stats.print();

        std::cout << "\nAdding 99.9 to array[0]...\n";
        stats.addElement(0, 99.9);
        stats.print();

        std::cout << "\nTesting deleteElementByValue (looking for 100.0)...\n";
        stats.deleteElementByValue(100.0);
        stats.print();

        std::cout << "\nTesting deleteElementByValue (looking for 99.9)...\n";
        stats.deleteElementByValue(99.9);
        stats.print();
    }

    pause_console();

    // +++ ТЕСТ deleteArrayByValue +++
    std::cout << "\nTesting deleteArrayByValue (looking for {7.0, 8.0, 9.0, 10.0})...\n";
    stats.deleteArrayByValue({7.0, 8.0, 9.0, 10.0});
    stats.print();

    pause_console();

    // --- Блок збереження ---
    std::cout << "\n--- Testing Save ---\n";
    std::cout << "Saving current (menu-loaded) state to 'results_CPP.txt'...\n";
    if (stats.saveToFile("results_CPP.txt")) {
        std::cout << "Data saved. Now loading it back into a NEW object for verification...\n";
        ArrayStatistic stats_verify;
        stats_verify.loadFromFile("results_CPP.txt");
        std::cout << "Data loaded from 'results_CPP.txt':\n";
        stats_verify.print();
    } else {
        std::cerr << "Failed to save data.\n";
    }

    std::cout << "\n--- Test program finished ---\n";
    return 0;

}
