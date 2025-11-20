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
    // Має містити {1,2}, {3,4}, {5,6}
    stats_union.print();

    // Тест Перетину (Intersection)
    std::cout << "\nTesting Intersection (stats1 * stats2)...\n";
    ArrayStatistic stats_intersect = stats1 * stats2;
    // Має містити *тільки* {1,2}
    stats_intersect.print();
}


int main() {
    // std::cout << "--- Start of testing the C++ project ---\n\n";
    //
    // ArrayStatistic stats;
    //
    // std::cout << "Created object. Initial state:\n";
    // stats.print();
    //
    // printf("\nAdding arr1 {1.5, 2.5, 3.0}...\n");
    // stats.addArray({1.5, 2.5, 3.0});
    // stats.print();
    //
    // printf("\nAdding arr2 {10.0, 20.0}...\n");
    // stats.addArray({10.0, 20.0});
    // stats.print();
    //
    // printf("\nTesting helper functions for Array [1]...\n");
    // // Ми не реалізували ці методи в .h файлі, тому додамо їх.
    // // Але ми реалізували getMean/getVariance як приватні,
    // // тому ми не можемо їх викликати тут.
    // // Ми протестуємо їх пізніше через публічні статистичні методи.
    //
    // std::cout << "\n--- Testing complete (Step 1) ---\n";
    // return 0;



    // std::cout << "--- Start of testing the C++ project (Step 2: Deletion) ---\n\n";
    //
    // ArrayStatistic stats;
    // stats.addArray({1.0, 2.0, 3.0, 4.0, 5.0});
    // stats.addArray({10.0, 20.0, 30.0});
    // stats.addArray({100.0, 200.0});
    //
    // std::cout << "Initial state:\n";
    // stats.print();
    //
    // // Тест deleteElement
    // // Видалимо "3.0" (індекс 2) з масиву [0]
    // std::cout << "\nTesting deleteElement(0, 2)...\n";
    // stats.deleteElement(0, 2);
    // stats.print();
    // // Масив [0] має стати: 1.0 2.0 4.0 5.0
    //
    // // Тест deleteArray
    // // Видалимо середній масив [1] ({10.0, 20.0, 30.0})
    // std::cout << "\nTesting deleteArray(1)...\n";
    // stats.deleteArray(1);
    // stats.print();
    // // Масив {100.0, 200.0} має "піднятися" на індекс 1
    //
    // std::cout << "\n--- Testing complete (Step 2) ---\n";
    // return 0;



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

    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ ОПЕРАТОРІВ +++
    test_set_operations();
    pause_console();

    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (Spearman) +++
    std::cout << "\n\n--- Testing Statistics (Spearman) ---\n";
    // Перевіримо на даних, які ми завантажили з меню
    if (stats.getNumArrays() >= 2) {
        std::cout << "Calculating Spearman for loaded arrays [0] and [1]...\n";
        double rho_loaded = stats.getSpearman(0, 1);
        std::cout << "Spearman's Rho (loaded data): " << rho_loaded << "\n";
    }

    // Ідеальні дані для тесту
    ArrayStatistic stats_stat;
    stats_stat.addArray({1.0, 2.0, 3.0, 4.0, 5.0}); // Ідеально відсортований
    stats_stat.addArray({2.0, 4.0, 6.0, 8.0, 10.0}); // Теж ідеально відсортований
    stats_stat.addArray({5.0, 4.0, 3.0, 2.0, 1.0}); // Зворотний порядок

    std::cout << "\nCalculating Spearman for test data (X vs Y)...\n";
    double rho_XY = stats_stat.getSpearman(0, 1);
    std::cout << "Spearman's Rho (X, Y): " << rho_XY << "\n"; // Має бути 1.0

    std::cout << "\nCalculating Spearman for test data (X vs Z)...\n";
    double rho_XZ = stats_stat.getSpearman(0, 2);
    std::cout << "Spearman's Rho (X, Z): " << rho_XZ << "\n"; // Має бути -1.0

    pause_console();


    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ (F-test, t-test, Z-test) +++
    std::cout << "\n\n--- Testing Statistics (Fisher, t-test, Z-test) ---\n";

    // Тест для Фішера (F-test)
    ArrayStatistic stats_ftest;
    stats_ftest.addArray({10.0, 10.1, 10.0, 9.9, 10.0}); // Малий розкид
    stats_ftest.addArray({5.0, 10.0, 15.0, 2.0, 20.0}); // Великий розкид

    std::cout << "Calculating Fisher F-test for low_var vs high_var...\n";
    double f_value = stats_ftest.getFisherTest(0, 1);
    std::cout << "Fisher F-value: " << f_value << "\n"; // Має бути > 10000

    // Тест для t-test / Z-test
    ArrayStatistic stats_ttest;
    stats_ttest.addArray({10, 11, 12, 10, 11}); // mean = 10.8
    stats_ttest.addArray({13, 14, 12, 13, 14}); // mean = 13.2

    std::cout << "\nCalculating t-test (small samples)...\n";
    double t_val = stats_ttest.getTTestSmall(0, 1);
    std::cout << "t-value: " << t_val << "\n"; // Має бути від'ємним

    std::cout << "\nCalculating Z-test (using same small samples)...\n";
    double z_val = stats_ttest.getZTestLarge(0, 1);
    std::cout << "Z-value: " << z_val << "\n"; // Має бути схожим на t-value

    pause_console();


    // +++ ФІНАЛЬНИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (Wilcoxon) +++
    std::cout << "\n\n--- Testing Statistics (Wilcoxon/Wilson U-test) ---\n";

    ArrayStatistic stats_wilcox;
    stats_wilcox.addArray({1, 2, 3}); // Група 1 (низькі ранги)
    stats_wilcox.addArray({10, 11, 12}); // Група 2 (високі ранги)

    std::cout << "Calculating U-test (perfect separation)...\n";
    // Очікувана U-статистика = 0
    double u_val_1 = stats_wilcox.getWilsonTest(0, 1);
    std::cout << "U-value (perfect separation): " << u_val_1 << "\n"; // Має бути 0.0

    // Дві вибірки, що перемішані
    ArrayStatistic stats_wilcox_2;
    stats_wilcox_2.addArray({1, 10, 12}); // G1
    stats_wilcox_2.addArray({2, 3, 11}); // G2

    std::cout << "\nCalculating U-test (mixed samples)...\n";
    // Сорт: {1(G1), 2(G2), 3(G2), 10(G1), 11(G2), 12(G1)}
    // Ранги G1: 1, 4, 6. Сума = 11.
    // U1 = 11 - (3*4)/2 = 11 - 6 = 5
    double u_val_2 = stats_wilcox_2.getWilsonTest(0, 1);
    std::cout << "U-value (mixed samples): " << u_val_2 << "\n"; // Має бути 5.0

    pause_console();

    // +++ ТЕСТУВАННЯ addElement та deleteElementByValue +++
    std::cout << "\n\n--- Testing addElement & deleteElementByValue ---\n";
    if (stats.getNumArrays() > 0) {
        std::cout << "Before addElement:\n";
        stats.print();

        std::cout << "\nAdding 99.9 to array[0]...\n";
        stats.addElement(0, 99.9);
        stats.print(); // Масив [0] має стати довшим

        std::cout << "\nTesting deleteElementByValue (looking for 100.0)...\n";
        // (Припускаючи, що ми завантажили з файлу, де є 100.0)
        stats.deleteElementByValue(100.0);
        stats.print();

        std::cout << "\nTesting deleteElementByValue (looking for 99.9)...\n";
        stats.deleteElementByValue(99.9);
        stats.print(); // Масив [0] має зменшитись
    }

    pause_console();

    // +++ ТЕСТ deleteArrayByValue +++
    std::cout << "\nTesting deleteArrayByValue (looking for {7.0, 8.0, 9.0, 10.0})...\n";
    // (Припускаючи, що ми завантажили з файлу .dat)
    stats.deleteArrayByValue({7.0, 8.0, 9.0, 10.0});
    stats.print(); // Масив {7.0...} має зникнути

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
