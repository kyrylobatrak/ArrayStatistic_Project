/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Заголовочний файл для C-структури ArrayStatistic.
 * Описує структуру для зберігання масиву масивів (double)
 * та прототипи функцій для роботи з нею.
 */

#ifndef ARRAYSTATISTIC_C_H
#define ARRAYSTATISTIC_C_H

#include <stdio.h> // Для FILE*
#include <stdlib.h> // Для size_t


typedef struct {
    double** arrays;     // Динамічний масив покажчиків на масиви
    int* sizes;          // Масив, що зберігає розміри кожного під-масиву
    int num_arrays;      // Поточна кількість масивів
    int capacity;        // Загальна виділена ємність
} ArrayStatistic;


/**
 * Створює та ініціалізує новий екземпляр ArrayStatistic.
 * @param initial_capacity Початкова ємність.
 * @return Нова структура.
 */
ArrayStatistic create_statistic(int initial_capacity);

/**
 * Звільняє всю пам'ять, виділену для структури.
 * @param stats Вказівник на структуру.
 */
void free_statistic(ArrayStatistic* stats);

/**
 * Виводить вміст структури на консоль.
 * @param stats Вказівник на структуру.
 */
void print_statistic(const ArrayStatistic* stats);

/**
 * Записує вміст структури у текстовий файл.
 * @param stats Вказівник на структуру.
 * @param filename Ім'я файлу.
 * @return 0 у разі успіху, -1 у разі помилки.
 */
int save_to_file(const ArrayStatistic* stats, const char* filename);

/**
 * Зчитує дані зі текстового файлу у структуру.
 * @param stats Вказівник на структуру.
 * @param filename Ім'я файлу.
 * @return 0 у разі успіху, -1 у разі помилки.
 */
int load_from_file(ArrayStatistic* stats, const char* filename);

/**
 * Зчитує дані для структури з консолі (інтерактивний режим).
 * @param stats Вказівник на структуру.
 */
void read_from_console(ArrayStatistic* stats);

/**
 * Додає один елемент в кінець вказаного масиву.
 * @param stats Вказівник на структуру.
 * @param array_index Індекс масиву, куди додавати.
 * @param element Значення елемента.
 */
void add_element(ArrayStatistic* stats, int array_index, double element);

/**
 * Додає цілий новий масив у структуру.
 * @param stats Вказівник на структуру.
 * @param new_array Масив елементів для додавання.
 * @param size Розмір нового масиву.
 */
void add_array(ArrayStatistic* stats, const double* new_array, int size);

/**
 * Додає всі масиви з однієї структури (src) в іншу (dest).
 * (Використовується для операції об'єднання).
 * @param dest Структура-приймач.
 * @param src Структура-джерело.
 */
void merge_structures(ArrayStatistic* dest, const ArrayStatistic* src);

/**
 * Видаляє елемент за індексом з вказаного масиву.
 * @param stats Вказівник на структуру.
 * @param array_index Індекс масиву.
 * @param element_index Індекс елемента для видалення.
 */
void delete_element(ArrayStatistic* stats, int array_index, int element_index);

/**
 * Видаляє цілий масив зі структури за його індексом.
 * @param stats Вказівник на структуру.
 * @param array_index Індекс масиву для видалення.
 */
void delete_array(ArrayStatistic* stats, int array_index);

/**
 * Видаляє *перше* знайдене входження елемента (за значенням) з усіх масивів.
 * @param stats Вказівник на структуру.
 * @param value Значення, яке треба знайти та видалити.
 * @return 0 якщо видалено, -1 якщо не знайдено.
 */
int delete_element_by_value(ArrayStatistic* stats, double value);

/**
 * Видаляє *перший* знайдений масив, який повністю ідентичний array_to_delete.
 * @param stats Вказівник на структуру.
 * @param array_to_delete Масив, який ми шукаємо.
 * @param size Розмір масиву, який ми шукаємо.
 * @return 0 якщо видалено, -1 якщо не знайдено.
 */
int delete_array_by_value(ArrayStatistic* stats, const double* array_to_delete, int size);

/**
 * Операція "Множення" (Перетин).
 * Створює нову структуру, що містить тільки ті масиви,
 * які ідентичні в обох структурах (s1 та s2).
 * @param s1 Перша структура.
 * @param s2 Друга структура.
 * @return Нова структура з результатом перетину.
 */
ArrayStatistic intersection(const ArrayStatistic* s1, const ArrayStatistic* s2);

/**
 * Операція "Додавання" (Об'єднання).
 * Створює нову структуру, що містить всі масиви з s1 та s2,
 * уникаючи дублікатів.
 * @param s1 Перша структура.
 * @param s2 Друга структура.
 * @return Нова структура з результатом об'єднання.
 */
ArrayStatistic union_structures(const ArrayStatistic* s1, const ArrayStatistic* s2);

/**
 * Обчислює коефіцієнт рангової кореляції Спірмена для двох масивів.
 * @param stats Вказівник на структуру.
 * @param arr_idx1 Індекс першого масиву.
 * @param arr_idx2 Індекс другого масиву.
 * @return Значення коефіцієнта Спірмена.
 */
double calculate_spearman(const ArrayStatistic* stats, int arr_idx1, int arr_idx2);

/**
 * Перевірка гіпотези про рівність дисперсій (критерій Фішера-Снедекера).
 * @param stats Вказівник на структуру.
 * @param arr_idx1 Індекс першого масиву.
 * @param arr_idx2 Індекс другого масиву.
 * @return Розраховане F-значення.
 */
double calculate_fisher_test(const ArrayStatistic* stats, int arr_idx1, int arr_idx2);

/**
 * Перевірка гіпотези про рівність середніх (для малих незалежних вибірок).
 * @param stats Вказівник на структуру.
 * @param arr_idx1 Індекс першого масиву.
 * @param arr_idx2 Індекс другого масиву.
 * @return Розраховане t-значення.
 */
double calculate_t_test_small(const ArrayStatistic* stats, int arr_idx1, int arr_idx2);

/**
 * Перевірка гіпотези про рівність середніх (для великих незалежних вибірок).
 * @param stats Вказівник на структуру.
 * @param arr_idx1 Індекс першого масиву.
 * @param arr_idx2 Індекс другого масиву.
 * @return Розраховане Z-значення.
 */
double calculate_z_test_large(const ArrayStatistic* stats, int arr_idx1, int arr_idx2);

/**
 * Перевірка гіпотези (критерій Вілсона/Вілкоксона).
 * @param stats Вказівник на структуру.
 * @param arr_idx1 Індекс першого масиву.
 * @param arr_idx2 Індекс другого масиву.
 * @return Розраховане значення критерію.
 */
double calculate_wilson_test(const ArrayStatistic* stats, int arr_idx1, int arr_idx2);


#endif //ARRAYSTATISTIC_C_H