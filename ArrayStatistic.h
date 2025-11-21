/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Заголовочний файл для C++ класу ArrayStatistic.
 * Описує клас для зберігання масиву масивів (std::vector<std::vector<double>>)
 * та методи для роботи з ним.
 */

#ifndef ARRAYSTATISTIC_CPP_H
#define ARRAYSTATISTIC_CPP_H

#include <vector>
#include <string>
#include <iostream>

class ArrayStatistic {
private:
    // "Масив масивів" реалізований як вектор векторів
    std::vector<std::vector<double>> m_arrays;
    bool isArrayPresent(const std::vector<double>& arr) const;
    double getMean(int arr_idx) const;
    double getVariance(int arr_idx) const;

public:
    ArrayStatistic(); // Конструктор за замовчуванням
    // Деструктор не потрібен, std::vector сам звільнить пам'ять

    /**
     * Виводить вміст класу на консоль.
     */
    void print() const;

    /**
     * Записує вміст класу у текстовий файл.
     * @param filename Ім'я файлу.
     * @return true у разі успіху, false у разі помилки.
     */
    bool saveToFile(const std::string& filename) const;

    /**
     * Зчитує дані зі текстового файлу у клас.
     * @param filename Ім'я файлу.
     * @return true у разі успіху, false у разі помилки.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * Зчитує дані для класу з консолі (інтерактивний режим).
     */
    void readFromConsole();

    /**
     * Додає один елемент в кінець вказаного масиву.
     * @param array_index Індекс масиву, куди додавати.
     * @param element Значення елемента.
     */
    void addElement(int array_index, double element);

    /**
     * Додає цілий новий масив (вектор) у клас.
     * @param new_array Вектор елементів для додавання.
     */
    void addArray(const std::vector<double>& new_array);

    /**
     * Додає всі масиви з іншого об'єкта (other) в цей.
     * (Використовується для операції об'єднання).
     * @param other Об'єкт-джерело.
     */
    void merge(const ArrayStatistic& other);

    /**
     * Видаляє елемент за індексом з вказаного масиву.
     * @param array_index Індекс масиву.
     * @param element_index Індекс елемента для видалення.
     */
    void deleteElement(int array_index, int element_index);

    /**
     * Видаляє цілий масив з класу за його індексом.
     * @param array_index Індекс масиву для видалення.
     */
    void deleteArray(int array_index);

    /**
     * Видаляє *перше* знайдене входження елемента (за значенням) з усіх масивів.
     * @param value Значення, яке треба знайти та видалити.
     * @return true якщо видалено, false якщо не знайдено.
     */
    bool deleteElementByValue(double value);

    /**
     * Видаляє *перший* знайдений масив, який повністю ідентичний array_to_delete.
     * @param array_to_delete Вектор, який ми шукаємо.
     * @return true якщо видалено, false якщо не знайдено.
     */
    bool deleteArrayByValue(const std::vector<double>& array_to_delete);

    /**
     * Отримує кількість масивів у структурі.
     */
    size_t getNumArrays() const;

    /**
     * Отримує розмір конкретного масиву.
     */
    size_t getArraySize(int array_index) const;

    /**
     * Операція "Додавання" (Об'єднання).
     * Створює новий об'єкт, що містить всі масиви з this та other,
     * уникаючи дублікатів.
     * @param other Правий операнд.
     * @return Новий об'єкт з результатом об'єднання.
     */
    ArrayStatistic operator+(const ArrayStatistic& other) const;

    /**
     * Операція "Множення" (Перетин).
     * Створює новий об'єкт, що містить тільки ті масиви,
     * які ідентичні в this та other.
     * @param other Правий операнд.
     * @return Новий об'єкт з результатом перетину.
     */
    ArrayStatistic operator*(const ArrayStatistic& other) const;

    /**
     * Обчислює коефіцієнт рангової кореляції Спірмена для двох масивів.
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Значення коефіцієнта Спірмена.
     */
    double getSpearman(int arr_idx1, int arr_idx2) const;

    /**
     * Перевірка гіпотези про рівність дисперсій (критерій Фішера-Снедекера).
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Розраховане F-значення.
     */
    double getFisherTest(int arr_idx1, int arr_idx2) const;

    /**
     * Перевірка гіпотези про рівність середніх (для малих незалежних вибірок).
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Розраховане t-значення.
     */
    double getTTestSmall(int arr_idx1, int arr_idx2) const;

    /**
     * Перевірка гіпотези про рівність середніх (для великих незалежних вибірок).
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Розраховане Z-значення.
     */
    double getZTestLarge(int arr_idx1, int arr_idx2) const;

    /**
     * Перевірка гіпотези (критерій Вілсона/Вілкоксона).
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Розраховане значення критерію.
     */
    double getWilsonTest(int arr_idx1, int arr_idx2) const;
};

#endif //ARRAYSTATISTIC_CPP_H