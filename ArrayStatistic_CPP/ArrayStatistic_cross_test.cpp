/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * КРОС-ТЕСТ: Порівняння C та C++ реалізацій.
 */

#include <iostream>
#include <cmath>
#include "ArrayStatistic.h" // C++ клас (залишається глобальним)



// 1. "Ховаємо" C-версію у простір імен 'C_Version'
namespace C_Version {
    extern "C" {
        #include "../ArrayStatistic_C/ArrayStatistic.h"
    }
}


// Допоміжна функція для порівняння
bool are_equal(double d1, double d2) {
    if (std::isnan(d1) && std::isnan(d2)) {
        return true;
    }
    return std::abs(d1 - d2) < 1e-9;
}

// Макрос для тестування
#define RUN_TEST(name, c_val, cpp_val) \
    std::cout << "Testing " << name << "... "; \
    if (are_equal(c_val, cpp_val)) { \
        std::cout << "PASSED\n"; \
    } else { \
        std::cout << "FAILED! (C: " << c_val << " vs C++: " << cpp_val << ")\n"; \
    }


int main() {
    std::cout << "--- Cross-Test (C vs C++) ---\n";

    // Створюємо об'єкти
    ArrayStatistic cpp_stats; // C++ клас

    // Використовуємо 'C_Version::' для доступу до C-структури та функцій
    C_Version::ArrayStatistic c_stats = C_Version::create_statistic(5);

    // 2. Завантажуємо ІДЕНТИЧНІ дані
    const char* data_file = "ArrayStatistic_test.dat";

    if (!cpp_stats.loadFromFile(data_file)) {
        std::cerr << "Failed to load C++ data. Aborting.\n";
        return 1;
    }

    if (C_Version::load_from_file(&c_stats, data_file) != 0) {
        std::cerr << "Failed to load C data. Aborting.\n";
        return 1;
    }

    std::cout << "Data loaded into C and C++ models successfully.\n";

    // 3. Запускаємо тести (використовуємо C_Version:: для всіх C-функцій)

    RUN_TEST("Spearman (diff size)",
             C_Version::calculate_spearman(&c_stats, 0, 1),
             cpp_stats.getSpearman(0, 1));

    RUN_TEST("Fisher F-test (0, 2)",
             C_Version::calculate_fisher_test(&c_stats, 0, 2),
             cpp_stats.getFisherTest(0, 2));

    RUN_TEST("t-test (0, 2)",
             C_Version::calculate_t_test_small(&c_stats, 0, 2),
             cpp_stats.getTTestSmall(0, 2));

    RUN_TEST("Z-test (0, 2)",
             C_Version::calculate_z_test_large(&c_stats, 0, 2),
             cpp_stats.getZTestLarge(0, 2));

    RUN_TEST("Wilcoxon U-test (0, 2)",
             C_Version::calculate_wilson_test(&c_stats, 0, 2),
             cpp_stats.getWilsonTest(0, 2));

    // 4. Очищення
    C_Version::free_statistic(&c_stats);

    std::cout << "--- Cross-Test Finished ---\n";
    return 0;

}
