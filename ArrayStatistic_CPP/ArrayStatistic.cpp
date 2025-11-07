/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Файл реалізації C++ класу ArrayStatistic.
 */

#include "ArrayStatistic.h"
#include <iostream>
#include <fstream>  // Для std::ofstream / std::ifstream
#include <string>
#include <vector>
#include <algorithm> // Для std::sort
#include <numeric>   // Для std::iota (корисно для індексів)
#include <cmath>     // Для std::isnan, pow

ArrayStatistic::ArrayStatistic() {
    // Конструктор за замовчуванням.
    // m_arrays (який є std::vector) автоматично
    // ініціалізується як порожній. Нічого робити не треба!
}

/**
 * Виводить вміст класу на консоль.
 */
void ArrayStatistic::print() const {
    // .size() - це C++ аналог нашого 'num_arrays'
    std::cout << "--- ArrayStatistic (C++) ---\n";
    std::cout << "Number of arrays: " << m_arrays.size() << "\n";

    // Цикл "for-each" - елегантний спосіб C++
    int i = 0;
    for (const auto& array : m_arrays) {
        std::cout << "  Array [" << i << "] (size " << array.size() << "): ";

        for (double val : array) {
            std::cout << val << " ";
        }
        std::cout << "\n";
        i++;
    }
    std::cout << "----------------------------\n";
}


void ArrayStatistic::addArray(const std::vector<double>& new_array) {
    // .push_back() - це C++ аналог 'add_array' з realloc.
    // Вектор сам подбає про виділення пам'яті та розширення.
    m_arrays.push_back(new_array);
}


/**
 * Допоміжний метод: перевіряє, чи присутній вектор у m_arrays.
 */
bool ArrayStatistic::isArrayPresent(const std::vector<double>& arr) const {
    // Проходимо по кожному існуючому вектору
    for (const auto& existing_arr : m_arrays) {
        // std::vector автоматично вміє порівнювати себе (через ==)
        // Він перевіряє і розмір, і всі елементи.
        if (arr == existing_arr) {
            return true;
        }
    }
    return false;
}

// Допоміжні функції для статистики (поки що "заглушки") ---
double ArrayStatistic::getMean(int arr_idx) const {
    if (arr_idx < 0 || arr_idx >= m_arrays.size() || m_arrays[arr_idx].empty()) {
        return 0.0;
    }
    double sum = 0.0;
    for (double val : m_arrays[arr_idx]) {
        sum += val;
    }
    return sum / m_arrays[arr_idx].size();
}


double ArrayStatistic::getVariance(int arr_idx) const {
    if (arr_idx < 0 || arr_idx >= m_arrays.size() || m_arrays[arr_idx].size() <= 1) {
        return 0.0;
    }
    double mean = getMean(arr_idx);
    double sum_sq_diff = 0.0;
    for (double val : m_arrays[arr_idx]) {
        double diff = val - mean;
        sum_sq_diff += (diff * diff);
    }
    return sum_sq_diff / (m_arrays[arr_idx].size() - 1);
}

void ArrayStatistic::deleteElement(int array_index, int element_index) {
    // Перевірка індексу масиву
    if (array_index < 0 || array_index >= m_arrays.size()) {
        std::cerr << "Error (deleteElement): Invalid array_index " << array_index << "\n";
        return;
    }

    // Перевірка індексу елемента
    if (element_index < 0 || element_index >= m_arrays[array_index].size()) {
        std::cerr << "Error (deleteElement): Invalid element_index " << element_index << "\n";
        return;
    }

    // Видалення
    // m_arrays[array_index] - це std::vector<double>
    // .begin() - це ітератор (вказівник) на початок
    // .erase() - зсуває всі елементи за вас.
    m_arrays[array_index].erase(m_arrays[array_index].begin() + element_index);
}

void ArrayStatistic::deleteArray(int array_index) {
    // Перевірка індексу масиву
    if (array_index < 0 || array_index >= m_arrays.size()) {
        std::cerr << "Error (deleteArray): Invalid array_index " << array_index << "\n";
        return;
    }

    //  Видалення
    // .erase() для зовнішнього вектора (вектора векторів)
    m_arrays.erase(m_arrays.begin() + array_index);
}


size_t ArrayStatistic::getNumArrays() const {
    return m_arrays.size();
}

size_t ArrayStatistic::getArraySize(int array_index) const {
    if (array_index < 0 || array_index >= m_arrays.size()) {
        return 0; //
    }
    return m_arrays[array_index].size();
}

bool ArrayStatistic::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return false;
    }

    int num_arrays_to_load;
    // Зчитуємо загальну кількість
    file >> num_arrays_to_load;

    if (file.fail()) {
        std::cerr << "Error: Could not read total number of arrays from file.\n";
        file.close();
        return false;
    }

    // Очищуємо поточні дані (якщо вони були)
    m_arrays.clear();


    for (int i = 0; i < num_arrays_to_load; i++) {
        int current_size;
        // Зчитуємо розмір
        file >> current_size;

        if (current_size < 0) continue; // Пропускаємо некоректний розмір

        // Створюємо тимчасовий вектор
        std::vector<double> temp_array;

        // Зчитуємо елементи
        for (int j = 0; j < current_size; j++) {
            double element;
            file >> element;
            temp_array.push_back(element);
        }

        // Додаємо зчитаний вектор у клас
        m_arrays.push_back(temp_array);
    }

    file.close();
    return true;
}


bool ArrayStatistic::saveToFile(const std::string& filename) const {
    // Відкриваємо файл для запису (output file stream)
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing\n";
        return false;
    }

    // Записуємо кількість (використовуємо .size())
    file << m_arrays.size() << "\n";

    // Цикл по кожному вектору (C++ for-each)
    for (const auto& array : m_arrays) {
        // Записуємо розмір
        file << array.size() << "\n";

        // Записуємо елементи
        for (double val : array) {
            file << val << " ";
        }
        file << "\n"; // Новий рядок для наступного масиву
    }

    file.close();
    std::cout << "Data successfully saved to " << filename << "\n";
    return true;
}


void ArrayStatistic::readFromConsole() {
    int num_arrays_to_load;
    std::cout << "Enter the total number of arrays you want to create: ";
    std::cin >> num_arrays_to_load;

    m_arrays.clear();

    for (int i = 0; i < num_arrays_to_load; i++) {
        int current_size;
        std::cout << "--- Array " << i << " ---\n";
        std::cout << "Enter size for array " << i << ": ";
        std::cin >> current_size;

        if (current_size <= 0) {
            std::cout << "Invalid size, skipping array " << i << ".\n";
            continue;
        }

        std::vector<double> temp_array;
        std::cout << "Enter " << current_size << " elements (separated by space): ";

        for (int j = 0; j < current_size; j++) {
            double element;
            std::cin >> element;
            temp_array.push_back(element);
        }

        // Додаємо в клас
        m_arrays.push_back(temp_array);
    }
    std::cout << "--- Console input finished ---\n";
}

ArrayStatistic ArrayStatistic::operator+(const ArrayStatistic& other) const {
    ArrayStatistic result;

    // Копіюємо всі масиви з 'this' (вони унікальні в межах 'this')
    result.m_arrays = this->m_arrays;

    // Додаємо масиви з 'other', якщо їх ще немає
    for (const auto& other_array : other.m_arrays) {
        if (!result.isArrayPresent(other_array)) {
            // Цього масиву ще немає, додаємо
            result.m_arrays.push_back(other_array);
        }
    }
    return result;
}


ArrayStatistic ArrayStatistic::operator*(const ArrayStatistic& other) const {
    ArrayStatistic result;

    // Цикл по 'this'
    for (const auto& this_array : this->m_arrays) {
        // Перевіряємо, чи є цей масив у 'other'
        // (Ми викликаємо isArrayPresent для об'єкта 'other')
        if (other.isArrayPresent(this_array)) {
            // Збіг! Додаємо цей масив у result
            result.m_arrays.push_back(this_array);
        }
    }
    return result;
}



void get_ranks_cpp(const std::vector<double>& arr, std::vector<double>& ranks_out) {
    int n = arr.size();
    ranks_out.resize(n); // Встановлюємо розмір вихідного вектора

    // Створюємо вектор індексів (0, 1, 2, ... n-1)
    std::vector<int> indices(n);
    std::iota(indices.begin(), indices.end(), 0); // Заповнює вектор: 0, 1, 2...

    // Використовуємо C++ лямбда-функцію для порівняння
    std::sort(indices.begin(), indices.end(), [&](int i, int j) {
        return arr[i] < arr[j];
    });

    // Записуємо ранги
    // (Спрощена обробка однакових рангів)
    for (int i = 0; i < n; ++i) {
        // індекс [i] - це ранг
        // indices[i] - це оригінальна позиція
        ranks_out[indices[i]] = (double)(i + 1);
    }
}


double ArrayStatistic::getSpearman(int arr_idx1, int arr_idx2) const {
    // Валідація
    if (arr_idx1 < 0 || arr_idx1 >= m_arrays.size() ||
        arr_idx2 < 0 || arr_idx2 >= m_arrays.size()) {
        std::cerr << "Error (Spearman): Invalid array index.\n";
        return std::nan(""); // C++ версія NAN
    }

    // Перевірка розміру
    if (m_arrays[arr_idx1].size() != m_arrays[arr_idx2].size()) {
        std::cerr << "Error (Spearman): Arrays must have the same size.\n";
        return std::nan("");
    }

    int n = m_arrays[arr_idx1].size();
    if (n <= 1) {
        std::cerr << "Error (Spearman): Need at least 2 data points.\n";
        return std::nan("");
    }

    // Отримуємо ранги
    std::vector<double> ranks1, ranks2;
    get_ranks_cpp(m_arrays[arr_idx1], ranks1);
    get_ranks_cpp(m_arrays[arr_idx2], ranks2);

    // Обчислюємо суму квадратів різниць
    double sum_d_squared = 0.0;
    for (int i = 0; i < n; i++) {
        double d = ranks1[i] - ranks2[i];
        sum_d_squared += (d * d);
    }

    // Формула
    double n_cubed_minus_n = (double)n * n * n - n;
    double rho = 1.0 - (6.0 * sum_d_squared) / n_cubed_minus_n;

    return rho;
}


/**
 * Перевірка гіпотези про рівність дисперсій (критерій Фішера-Снедекера).
 */
double ArrayStatistic::getFisherTest(int arr_idx1, int arr_idx2) const {
    // 1. Валідація
    if (arr_idx1 < 0 || arr_idx1 >= m_arrays.size() ||
        arr_idx2 < 0 || arr_idx2 >= m_arrays.size()) {
        std::cerr << "Error (Fisher): Invalid array index.\n";
        return std::nan("");
    }

    int size1 = m_arrays[arr_idx1].size();
    int size2 = m_arrays[arr_idx2].size();

    if (size1 <= 1 || size2 <= 1) {
        std::cerr << "Error (Fisher): Need at least 2 data points per array.\n";
        return std::nan("");
    }

    // 2. Обчислюємо дисперсії (викликаємо приватні методи)
    double var1 = getVariance(arr_idx1);
    double var2 = getVariance(arr_idx2);

    if (var2 == 0.0) {
        std::cerr << "Error (Fisher): Division by zero (variance of array 2 is 0).\n";
        return std::nan("");
    }

    // 3. F-статистика (більшу ділимо на меншу)
    if (var1 > var2) {
        return var1 / var2;
    } else {
        return var2 / var1;
    }
}

/**
 * Перевірка гіпотези про рівність середніх (t-критерій Стьюдента, малі вибірки).
 */
double ArrayStatistic::getTTestSmall(int arr_idx1, int arr_idx2) const {
    // Валідація
    if (arr_idx1 < 0 || arr_idx1 >= m_arrays.size() ||
        arr_idx2 < 0 || arr_idx2 >= m_arrays.size()) {
        std::cerr << "Error (t-test): Invalid array index.\n";
        return std::nan("");
    }

    int n1 = m_arrays[arr_idx1].size();
    int n2 = m_arrays[arr_idx2].size();

    if (n1 <= 1 || n2 <= 1) {
        std::cerr << "Error (t-test): Need at least 2 data points per array.\n";
        return std::nan("");
    }

    // Обчислюємо середні та дисперсії
    double mean1 = getMean(arr_idx1);
    double var1 = getVariance(arr_idx1);
    double mean2 = getMean(arr_idx2);
    double var2 = getVariance(arr_idx2);

    // Об'єднана дисперсія
    double sp_squared = ((n1 - 1) * var1 + (n2 - 1) * var2) / (n1 + n2 - 2);

    // t-статистика
    double t_value = (mean1 - mean2) / (std::sqrt(sp_squared * (1.0/n1 + 1.0/n2)));

    return t_value;
}

/**
 * Перевірка гіпотези про рівність середніх (Z-критерій, великі вибірки).
 */
double ArrayStatistic::getZTestLarge(int arr_idx1, int arr_idx2) const {
    // Валідація
    if (arr_idx1 < 0 || arr_idx1 >= m_arrays.size() ||
        arr_idx2 < 0 || arr_idx2 >= m_arrays.size()) {
        std::cerr << "Error (Z-test): Invalid array index.\n";
        return std::nan("");
    }

    int n1 = m_arrays[arr_idx1].size();
    int n2 = m_arrays[arr_idx2].size();

    if (n1 == 0 || n2 == 0) {
        std::cerr << "Error (Z-test): Arrays cannot be empty.\n";
        return std::nan("");
    }

    // Обчислюємо середні та дисперсії
    double mean1 = getMean(arr_idx1);
    double var1 = getVariance(arr_idx1);
    double mean2 = getMean(arr_idx2);
    double var2 = getVariance(arr_idx2);

    // Z-статистика
    double z_value = (mean1 - mean2) / std::sqrt( (var1 / n1) + (var2 / n2) );

    return z_value;
}


/**
 * Перевірка гіпотези (критерій Вілкоксона/Манна-Уітні).
 */
double ArrayStatistic::getWilsonTest(int arr_idx1, int arr_idx2) const {
    // Валідація
    if (arr_idx1 < 0 || arr_idx1 >= m_arrays.size() ||
        arr_idx2 < 0 || arr_idx2 >= m_arrays.size()) {
        std::cerr << "Error (Wilcoxon): Invalid array index.\n";
        return std::nan("");
    }

    int n1 = m_arrays[arr_idx1].size();
    int n2 = m_arrays[arr_idx2].size();

    if (n1 == 0 || n2 == 0) {
        std::cerr << "Error (Wilcoxon): Arrays cannot be empty.\n";
        return std::nan("");
    }

    const auto& arr1 = m_arrays[arr_idx1];
    const auto& arr2 = m_arrays[arr_idx2];

    // Створюємо допоміжну структуру (тільки для цього методу)
    struct WilcoxonData {
        double value;
        int group; // 1 = arr1, 2 = arr2
    };

    int n_total = n1 + n2;
    std::vector<WilcoxonData> combined;
    combined.reserve(n_total); // Оптимізація: виділяємо пам'ять одразу

    // Копіюємо з першого масиву
    for (double val : arr1) {
        combined.push_back({val, 1});
    }
    // Копіюємо з другого масиву
    for (double val : arr2) {
        combined.push_back({val, 2});
    }

    // Сортуємо об'єднаний вектор (використовуємо лямбду)
    std::sort(combined.begin(), combined.end(), [](const WilcoxonData& a, const WilcoxonData& b) {
        return a.value < b.value;
    });

    // Обчислюємо суму рангів для першої групи
    double rank_sum_1 = 0.0;
    for (int i = 0; i < n_total; i++) {
        if (combined[i].group == 1) {
            rank_sum_1 += (i + 1); // Ранг = позиція + 1
        }
    }

    // Обчислюємо U-статистику
    // U1 = R1 - (n1 * (n1 + 1)) / 2
    double u_statistic = rank_sum_1 - ((double)n1 * (n1 + 1)) / 2.0;

    return u_statistic;
}