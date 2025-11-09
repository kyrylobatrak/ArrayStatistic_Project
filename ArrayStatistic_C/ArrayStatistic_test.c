/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Тестовий файл (головний) для C-проекту.
 * Перевіряє роботу базових функцій: create, add, print, free.
 */

#include "ArrayStatistic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Для system
#include <stdbool.h>


// Ця функція потрібна при пункті "--- Welcome to ArrayStatistic (C) Test Program ---" !!!!!

// Допоміжна функція, щоб потримати консоль (для Windows)
void pause_console() {
    printf("\nPress Enter to continue...");
    // Очищуємо буфер вводу
    while (getchar() != '\n');
    getchar(); // Чекаємо на Enter
}

// Нова функція для тестування операцій
void test_set_operations() {
    printf("\n\n--- Testing Union (+) and Intersection (*) ---\n");
    // Створюємо два набори даних
    ArrayStatistic stats1 = create_statistic(5);
    ArrayStatistic stats2 = create_statistic(5);

    double arrA[] = {1.0, 2.0}; // Спільний
    double arrB[] = {3.0, 4.0}; // Тільки в s1
    double arrC[] = {5.0, 6.0}; // Тільки в s2

    add_array(&stats1, arrA, 2);
    add_array(&stats1, arrB, 2);

    add_array(&stats2, arrA, 2); // Спільний
    add_array(&stats2, arrC, 2);

    printf("Stats1:\n");
    print_statistic(&stats1);
    printf("Stats2:\n");
    print_statistic(&stats2);

    // Тест Об'єднання (Union)
    printf("\nTesting Union (s1 + s2)...\n");
    ArrayStatistic stats_union = union_structures(&stats1, &stats2);
    // Має містити {1,2}, {3,4}, {5,6}
    print_statistic(&stats_union);

    // Тест Перетину (Intersection)
    printf("\nTesting Intersection (s1 * s2)...\n");
    ArrayStatistic stats_intersect = intersection(&stats1, &stats2);
    // Має містити *тільки* {1,2}
    print_statistic(&stats_intersect);

    // 4. Очищення
    free_statistic(&stats1);
    free_statistic(&stats2);
    free_statistic(&stats_union);
    free_statistic(&stats_intersect);
}



int main() {
//     printf("--- Start of testing the C-project ---\n\n");
//
//     // Створюємо структуру з маленькою початковою ємністю (2),
//     // щоб перевірити логіку розширення (realloc)
//     ArrayStatistic stats = create_statistic(2);
//     printf("A structure has been created. Initial state:\n");
//     print_statistic(&stats); // Викликаємо print для порожньої структури
//
//     // Тестові дані
//     double arr1[] = {1.5, 2.5, 3.0};
//     double arr2[] = {10.0, 20.0};
//     double arr3[] = {7.7, 8.8, 9.9, 10.1};
//
//     // Додаємо перший масив
//     printf("\nAdd arr1...\n");
//     add_array(&stats, arr1, 3);
//     print_statistic(&stats);
//
//     // 4. Додаємо другий масив
//     printf("\nAdd arr2...\n");
//     add_array(&stats, arr2, 2);
//     print_statistic(&stats);
//
//     // Додаємо третій масив
//     // Тут має спрацювати realloc!
//     printf("\nAdd arr3 (enlargement must work)...\n");
//     add_array(&stats, arr3, 4);
//     print_statistic(&stats); // Має бути 3 масиви, ємність 4.
//
//
//
//     printf("\nMemory release...\n");
//     free_statistic(&stats);
//     print_statistic(&stats); // Перевіряємо, що структура порожня
//
//     printf("\n--- Testing complete ---\n");
//     return 0;
//




    // printf("--- Start of testing the C-project (Step 2: Deletion) ---\n\n");
    //
    // ArrayStatistic stats = create_statistic(2);
    //
    // // Тестові дані
    // double arr1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    // double arr2[] = {10.0, 20.0};
    // double arr3[] = {7.7, 8.8, 9.9};
    //
    // add_array(&stats, arr1, 5);
    // add_array(&stats, arr2, 2);
    // add_array(&stats, arr3, 3);
    //
    // printf("Initial state (before deletions):\n");
    // print_statistic(&stats);
    //
    // // Тест `delete_element`
    // // Видалимо елемент "3.0" (індекс 2) з масиву 0
    // printf("\nTesting delete_element(stats, 0, 2)...\n");
    // delete_element(&stats, 0, 2);
    // print_statistic(&stats);
    //
    // // Тест `delete_array`
    // // Видалимо середній масив (індекс 1, тобто {10.0, 20.0})
    // printf("\nTesting delete_array(stats, 1)...\n");
    // delete_array(&stats, 1);
    // print_statistic(&stats);
    //
    // // Тест `delete_element` на іншому масиві
    // // Видалимо елемент "8.8" (індекс 1) з нового масиву 1
    // printf("\nTesting delete_element(stats, 1, 1)...\n");
    // delete_element(&stats, 1, 1);
    // print_statistic(&stats);
    //
    //
    //
    // printf("\nMemory release...\n");
    // free_statistic(&stats);
    // print_statistic(&stats); // Перевіряємо, що структура порожня
    //
    // printf("\n--- Testing complete ---\n");
    // return 0;



    // printf("--- Start of testing the C-project (Step 3: File Loading) ---\n\n");
    //
    // ArrayStatistic stats_from_file = create_statistic(2);
    //
    // // Викликаємо нашу нову функцію
    // printf("Attempting to load data from 'ArrayStatistic_test.dat'...\n");
    // int result = load_from_file(&stats_from_file, "ArrayStatistic_test.dat");
    //
    // if (result == 0) {
    //     printf("\nFile loaded successfully. Current state:\n");
    // } else {
    //     printf("\nFile loading failed.\n");
    // }
    //
    // // Друкуємо те, що завантажили
    // // (навіть якщо завантажилося частково, подивимось)
    // print_statistic(&stats_from_file);
    // // Вивід має відповідати вмісту .dat файлу!
    //
    // // Тестуємо, чи можна з нею працювати (наприклад, видалити щось)
    // printf("\nTesting deletion on loaded data (deleting array 0)...\n");
    // delete_array(&stats_from_file, 0);
    // print_statistic(&stats_from_file);
    //
    //
    //
    // printf("\nMemory release...\n");
    // free_statistic(&stats_from_file);
    // print_statistic(&stats_from_file);
    //
    // printf("\n--- Testing complete ---\n");
    // return 0;


    // ОБОВ'ЯЗКОВО ПОТРІБНА РОЗКОМЕНТУВАТИ ДОПОМІЖНУ ФУНКЦІЮ !!!!!
    printf("--- Welcome to ArrayStatistic (C) Test Program ---\n");

    ArrayStatistic stats = create_statistic(5);
    int choice = 0;

    printf("How do you want to load data?\n");
    printf("  1: Load from file (ArrayStatistic_test.dat)\n");
    printf("  2: Enter data manually (from console)\n");
    printf("Your choice: ");
    scanf("%d", &choice);


    switch (choice) {
        case 1:
            printf("Loading from file...\n");
            if (load_from_file(&stats, "ArrayStatistic_test.dat") == 0) {
                printf("File loaded successfully.\n");
            } else {
                fprintf(stderr, "File loading failed.\n");
            }
            break;
        case 2:
            printf("Loading from console...\n");
            read_from_console(&stats);
            break;
        default:
            printf("Invalid choice. Starting with an empty structure.\n");
            break;
    }

    printf("\n--- Current data state: ---\n");
    print_statistic(&stats);
    pause_console();

    // --- Блок тестування операцій ---
    // Тепер, коли у нас є дані (з файлу чи консолі),
    // ми можемо їх протестувати

    if (stats.num_arrays > 0) {
        printf("\n--- Testing Deletion ---\n");
        printf("Testing delete_element(stats, 0, 0) (deleting first element of first array)...\n");
        delete_element(&stats, 0, 0);
        print_statistic(&stats);
    }

    if (stats.num_arrays > 1) {
        printf("\nTesting delete_array(stats, 1) (deleting second array)...\n");
        delete_array(&stats, 1);
        print_statistic(&stats);
    }

    pause_console();





    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ ОПЕРАЦІЙ +++
    // Цей тест запускається окремо і не залежить від меню
    test_set_operations();
    pause_console();





    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ +++
    printf("\n\n--- Testing Statistics (Spearman) ---\n");
    // Перевіримо на даних, які ми завантажили з меню
    if (stats.num_arrays >= 2) {
        printf("Calculating Spearman for loaded arrays [0] and [1]...\n");
        // Ми не можемо гарантувати, що їх розміри збігаються,
        // тому функція має сама обробити помилку.
        double rho_loaded = calculate_spearman(&stats, 0, 1);
        printf("Spearman's Rho (loaded data): %f\n", rho_loaded); // Виведе 'nan', якщо розміри різні
    } else {
        printf("Not enough arrays in loaded data to test Spearman.\n");
    }

    // Ідеальні дані для тесту
    ArrayStatistic stats_stat = create_statistic(2);
    double arrX[] = {1.0, 2.0, 3.0, 4.0, 5.0}; // Ідеально відсортований
    double arrY[] = {2.0, 4.0, 6.0, 8.0, 10.0}; // Теж ідеально відсортований
    double arrZ[] = {5.0, 4.0, 3.0, 2.0, 1.0}; // Зворотний порядок

    add_array(&stats_stat, arrX, 5);
    add_array(&stats_stat, arrY, 5);
    add_array(&stats_stat, arrZ, 5);

    printf("\nCalculating Spearman for test data (X vs Y)...\n");
    double rho_XY = calculate_spearman(&stats_stat, 0, 1);
    printf("Spearman's Rho (X, Y): %f\n", rho_XY); // Має бути 1.0 (ідеальна пряма кореляція)

    printf("\nCalculating Spearman for test data (X vs Z)...\n");
    double rho_XZ = calculate_spearman(&stats_stat, 0, 2);
    printf("Spearman's Rho (X, Z): %f\n", rho_XZ); // Має бути -1.0 (ідеальна зворотна кореляція)

    free_statistic(&stats_stat);
    pause_console();





    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (F-TEST) +++
    printf("\n\n--- Testing Statistics (Fisher F-test) ---\n");

    // Створимо дані для тесту
    ArrayStatistic stats_ftest = create_statistic(2);
    // Масив з малим розкидом
    double arr_low_var[] = {10.0, 10.1, 10.0, 9.9, 10.0};
    // Масив з великим розкидом
    double arr_high_var[] = {5.0, 10.0, 15.0, 2.0, 20.0};

    add_array(&stats_ftest, arr_low_var, 5);
    add_array(&stats_ftest, arr_high_var, 5);

    printf("Calculating Fisher F-test for low_var vs high_var...\n");

    double f_value = calculate_fisher_test(&stats_ftest, 0, 1);

    printf("\nFisher F-value: %f\n", f_value); // Має бути (var_high / var_low)

    free_statistic(&stats_ftest);
    pause_console();




    // +++ НОВИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (t-test / Z-test) +++
    printf("\n\n--- Testing Statistics (t-test & Z-test) ---\n");

    // Дані для тесту
    ArrayStatistic stats_ttest = create_statistic(2);

    // Дві "малі" вибірки.
    // arrT1 має бути "трохи" меншим за arrT2
    double arrT1[] = {10, 11, 12, 10, 11}; // mean = 10.8
    double arrT2[] = {13, 14, 12, 13, 14}; // mean = 13.2

    add_array(&stats_ttest, arrT1, 5);
    add_array(&stats_ttest, arrT2, 5);

    printf("Calculating t-test (small samples)...\n");
    double t_val = calculate_t_test_small(&stats_ttest, 0, 1);
    printf("t-value: %f\n", t_val); // Має бути від'ємним, оскільки mean1 < mean2

    // Z-тест зазвичай використовує ті ж дані (якщо n > 30),
    // але ми можемо викликати його і на малих, щоб перевірити формулу.
    // Значення Z і t будуть дуже близькі.
    printf("\nCalculating Z-test (using same small samples)...\n");
    double z_val = calculate_z_test_large(&stats_ttest, 0, 1);
    printf("Z-value: %f\n", z_val);

    free_statistic(&stats_ttest);
    pause_console();




    // +++ ФІНАЛЬНИЙ БЛОК ТЕСТУВАННЯ СТАТИСТИКИ (Wilcoxon) +++
    printf("\n\n--- Testing Statistics (Wilcoxon/Wilson U-test) ---\n");

    ArrayStatistic stats_wilcox = create_statistic(2);

    // Дві вибірки, що чітко розділені
    double arrW1[] = {1, 2, 3}; // Група 1 (низькі ранги)
    double arrW2[] = {10, 11, 12}; // Група 2 (високі ранги)

    add_array(&stats_wilcox, arrW1, 3);
    add_array(&stats_wilcox, arrW2, 3);

    printf("Calculating U-test (perfect separation)...\n");
    // Очікувані ранги (1, 2, 3, 4, 5, 6)
    // Сума рангів для G1 = 1+2+3 = 6
    // n1 = 3. U1 = 6 - (3*(3+1))/2 = 6 - 6 = 0
    double u_val_1 = calculate_wilson_test(&stats_wilcox, 0, 1);
    printf("U-value (perfect separation): %f\n", u_val_1); // Має бути 0.0

    // Дві вибірки, що перемішані
    ArrayStatistic stats_wilcox_2 = create_statistic(2);
    double arrW3[] = {1, 10, 12}; //
    double arrW4[] = {2, 3, 11}; //
    add_array(&stats_wilcox_2, arrW3, 3);
    add_array(&stats_wilcox_2, arrW4, 3);

    printf("\nCalculating U-test (mixed samples)...\n");
    // Сортований список: {1(G1), 2(G2), 3(G2), 10(G1), 11(G2), 12(G1)}
    // Ранги:             1      2      3      4       5       6
    // Сума рангів для G1 = 1 + 4 + 6 = 11
    // n1 = 3. U1 = 11 - (3*(3+1))/2 = 11 - 6 = 5
    double u_val_2 = calculate_wilson_test(&stats_wilcox_2, 0, 1);
    printf("U-value (mixed samples): %f\n", u_val_2); // Має бути 5.0

    free_statistic(&stats_wilcox);
    free_statistic(&stats_wilcox_2);
    pause_console();

    // +++ ТЕСТУВАННЯ add_element та delete_by_value +++
    printf("\n\n--- Testing add_element & delete_by_value ---\n");
    if (stats.num_arrays > 0) {
        printf("Before add_element:\n");
        print_statistic(&stats);

        printf("\nAdding 99.9 to array[0]...\n");
        add_element(&stats, 0, 99.9);
        print_statistic(&stats); // Масив [0] має стати довшим на 1 елемент

        printf("\nTesting delete_by_value (looking for 100.0)...\n");
        // (Припускаючи, що ми завантажили з файлу, де є 100.0)
        delete_element_by_value(&stats, 100.0);
        print_statistic(&stats);

        printf("\nTesting delete_by_value (looking for 99.9)...\n");
        delete_element_by_value(&stats, 99.9);
        print_statistic(&stats); // Масив [0] має зменшитись
    }

    pause_console();

    // +++ ТЕСТ delete_array_by_value +++
    printf("\nTesting delete_array_by_value (looking for {7.0, 8.0, 9.0, 10.0})...\n");
    // (Припускаючи, що ми завантажили з файлу .dat)
    double arr_to_find[] = {7.0, 8.0, 9.0, 10.0};
    delete_array_by_value(&stats, arr_to_find, 4);
    print_statistic(&stats); // Масив {7.0...} має зникнути

    pause_console();

    // --- Блок збереження ---
    printf("\n--- Testing Save ---\n");
    printf("Saving current state to 'results_C.txt'...\n");
    if (save_to_file(&stats, "results_C.txt") == 0) {

        printf("Data saved. Now loading it back into a NEW structure for verification...\n");
        ArrayStatistic stats_verify = create_statistic(2);
        load_from_file(&stats_verify, "results_C.txt");
        printf("Data loaded from 'results_C.txt':\n");
        print_statistic(&stats_verify);
        free_statistic(&stats_verify);
    } else {
        fprintf(stderr, "Failed to save data.\n");
    }


    printf("\n--- Final Cleanup ---\n");
    free_statistic(&stats);
    printf("Test program finished.\n");

    return 0;

}