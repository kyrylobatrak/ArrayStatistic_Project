/*
 * Завдання: 25. ArrayStatistic
 * Група: 2 year of compmath
 * Прізвище: Batrak
 *
 * Опис:
 * Файл реалізації C-структури ArrayStatistic.
 * Містить логіку керування пам'яттю та базові операції.
 */

#include "ArrayStatistic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Для memcpy
#include <stdbool.h>
#include <math.h>

bool are_arrays_equal(const double* arr1, int size1, const double* arr2, int size2);
bool is_array_present(const ArrayStatistic* stats, const double* arr, int size);

ArrayStatistic create_statistic(int initial_capacity) {
    ArrayStatistic stats;

    if (initial_capacity <= 0) {
        initial_capacity = 2; // Початкова ємність за замовчуванням
    }

    stats.num_arrays = 0;
    stats.capacity = initial_capacity;

    // Виділяємо пам'ять для "масиву покажчиків"
    stats.arrays = (double**)malloc(stats.capacity * sizeof(double*));
    // Виділяємо пам'ять для "масиву розмірів"
    stats.sizes = (int*)malloc(stats.capacity * sizeof(int));

    if (stats.arrays == NULL || stats.sizes == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory (create_statistic)\n");
        // У разі помилки повертаємо "порожню" структуру
        stats.arrays = NULL;
        stats.sizes = NULL;
        stats.capacity = 0;
    }

    return stats;
}

void free_statistic(ArrayStatistic* stats) {
    if (stats == NULL || stats->arrays == NULL) {
        return; // Нічого звільняти
    }

    // Спочатку звільняємо кожен під-масив (кожен рядок)
    for (int i = 0; i < stats->num_arrays; i++) {
        free(stats->arrays[i]);
    }

    // Тепер звільняємо "масив покажчиків" (стовпець)
    free(stats->arrays);
    // І звільняємо "масив розмірів"
    free(stats->sizes);

    // Обнуляємо, щоб уникнути "висячих покажчиків"
    stats->arrays = NULL;
    stats->sizes = NULL;
    stats->num_arrays = 0;
    stats->capacity = 0;
}
void print_statistic(const ArrayStatistic* stats) {
    if (stats == NULL || stats->arrays == NULL) {
        printf("The structure is empty or not initialized.\n");
        return;
    }

    printf("--- ArrayStatistic (C) ---\n");
    printf("Number of arrays: %d (Capacity: %d)\n", stats->num_arrays, stats->capacity);

    // Цикл по кожному масиву (рядку)
    for (int i = 0; i < stats->num_arrays; i++) {
        printf("  Array [%d] (size %d): ", i, stats->sizes[i]);

        // Цикл по кожному елементу всередині масиву
        for (int j = 0; j < stats->sizes[i]; j++) {
            printf("%.2f ", stats->arrays[i][j]);
        }
        printf("\n"); // Новий рядок для наступного масиву
    }
    printf("----------------------------\n");
}

void add_array(ArrayStatistic* stats, const double* new_array, int size) {
    // Перевірка на заповненість: Чи потрібно розширювати?
    if (stats->num_arrays >= stats->capacity) {
        // Ємність вичерпана. Подвоюємо її.
        int new_capacity = stats->capacity * 2;

        double** new_arrays_ptr = (double**)realloc(stats->arrays, new_capacity * sizeof(double*));
        int* new_sizes_ptr = (int*)realloc(stats->sizes, new_capacity * sizeof(int));

        if (new_arrays_ptr == NULL || new_sizes_ptr == NULL) {
            fprintf(stderr, "Error: Failed to expand memory (realloc)\n");
            return; // Не додаємо масив, якщо не вистачило пам'яті
        }

        stats->arrays = new_arrays_ptr;
        stats->sizes = new_sizes_ptr;
        stats->capacity = new_capacity;
        printf("!!! Capacity increased to %d !!!\n", new_capacity);
    }

    // Виділяємо пам'ять для *копії* нового масиву
    // Ми не можемо просто зберегти `new_array`, бо він може бути тимчасовим!
    double* array_copy = (double*)malloc(size * sizeof(double));
    if (array_copy == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new array\n");
        return;
    }

    memcpy(array_copy, new_array, size * sizeof(double));

    stats->arrays[stats->num_arrays] = array_copy;
    stats->sizes[stats->num_arrays] = size;
    stats->num_arrays++; // Збільшуємо лічильник масивів
}

void delete_element(ArrayStatistic* stats, int array_index, int element_index) {
    // Перевірка коректності індексів
    if (stats == NULL || array_index < 0 || array_index >= stats->num_arrays) {
        fprintf(stderr, "Error (delete_element): Invalid array_index %d\n", array_index);
        return;
    }
    if (element_index < 0 || element_index >= stats->sizes[array_index]) {
        fprintf(stderr, "Error (delete_element): Invalid element_index %d\n", element_index);
        return;
    }

    // Якщо це останній елемент, просто зменшуємо розмір
    if (element_index == stats->sizes[array_index] - 1) {
        stats->sizes[array_index]--;
        // Можна також зробити realloc, щоб зменшити пам'ять, але поки не будемо
        return;
    }



    // Логіка зсуву:
    // [1.0] [2.0] [3.0] [4.0] -- видаляємо [1] (2.0)
    // [1.0] [3.0] [4.0] [4.0] -- після зсуву
    //
    // Ми "насуваємо" всі елементи справа від element_index на одну позицію вліво.



    // Адреса елемента, який треба видалити
    double* target_array = stats->arrays[array_index];

    // Кількість байт для переміщення
    int elements_to_move = stats->sizes[array_index] - element_index - 1;
    size_t bytes_to_move = elements_to_move * sizeof(double);

    // Адреса джерела (звідки копіюємо)
    void* source = (void*)(&target_array[element_index + 1]);
    // Адреса призначення (куди копіюємо)
    void* destination = (void*)(&target_array[element_index]);

    memmove(destination, source, bytes_to_move); //memmove (а не memcpy), тому що це безпечна функція для "зсуву" блоків пам'яті, які перекриваються (overlapping).

    stats->sizes[array_index]--;
}


void delete_array(ArrayStatistic* stats, int array_index) {
    if (stats == NULL || array_index < 0 || array_index >= stats->num_arrays) {
        fprintf(stderr, "Error (delete_array): Invalid array_index %d\n", array_index);
        return;
    }

    free(stats->arrays[array_index]);



    // Зсуваємо всі покажчики у `stats->arrays` на 1 позицію вліво,
    // починаючи з `array_index`.
    //
    // [ptr0] [ptr1] [ptr2] [ptr3] -- видаляємо [1]
    // [ptr0] [ptr2] [ptr3] [ptr3] -- після зсуву



    int elements_to_move = stats->num_arrays - array_index - 1;

    if (elements_to_move > 0) {
        // Зсуваємо масив покажчиків
        memmove(
            (void*)(&stats->arrays[array_index]), // Куди
            (void*)(&stats->arrays[array_index + 1]), // Звідки
            elements_to_move * sizeof(double*) // Скільки
        );

        // Зсуваємо масив розмірів
        memmove(
            (void*)(&stats->sizes[array_index]), // Куди
            (void*)(&stats->sizes[array_index + 1]), // Звідки
            elements_to_move * sizeof(int) // Скільки
        );
    }

    stats->num_arrays--;
}

/**
 * Додає один елемент в кінець вказаного масиву.
 */
void add_element(ArrayStatistic* stats, int array_index, double element) {
    // 1. Перевірка індексу
    if (stats == NULL || array_index < 0 || array_index >= stats->num_arrays) {
        fprintf(stderr, "Error (add_element): Invalid array_index %d\n", array_index);
        return;
    }

    // 2. Отримуємо поточний розмір та вказівник
    int current_size = stats->sizes[array_index];
    double* target_array = stats->arrays[array_index];

    // 3. Розширюємо цей конкретний масив на 1
    double* new_array_ptr = (double*)realloc(target_array, (current_size + 1) * sizeof(double));

    if (new_array_ptr == NULL) {
        fprintf(stderr, "Error (add_element): realloc failed.\n");
        return; // Не можемо додати елемент
    }

    // 4. Додаємо новий елемент в кінець
    new_array_ptr[current_size] = element;

    // 5. Оновлюємо вказівник та розмір у структурі
    stats->arrays[array_index] = new_array_ptr;
    stats->sizes[array_index] = current_size + 1;
}


/**
 * Видаляє *перше* знайдене входження елемента (за значенням) з усіх масивів.
 */
int delete_element_by_value(ArrayStatistic* stats, double value) {
    if (stats == NULL) return -1;

    // Використовуємо DBL_EPSILON для порівняння чисел з плаваючою комою
    // (A == B) -> (fabs(A - B) < DBL_EPSILON)
    // Потрібно #include <float.h> або <math.h> для DBL_EPSILON

    // Зовнішній цикл: по масивах
    for (int i = 0; i < stats->num_arrays; i++) {
        // Внутрішній цикл: по елементах
        for (int j = 0; j < stats->sizes[i]; j++) {
            if (fabs(stats->arrays[i][j] - value) < 1e-9) {
                printf("Found value %f at array[%d] index[%d]. Deleting...\n", value, i, j);
                delete_element(stats, i, j);
                return 0; // Успіх, видалили перше входження
            }
        }
    }

    printf("Value %f not found.\n", value);
    return -1; // Не знайдено
}

/**
 * Видаляє *перший* знайдений масив, який повністю ідентичний array_to_delete.
 */
int delete_array_by_value(ArrayStatistic* stats, const double* array_to_delete, int size) {
    if (stats == NULL) return -1;

    // Цикл по всіх масивах у структурі
    for (int i = 0; i < stats->num_arrays; i++) {
        // Використовуємо нашу існуючу допоміжну функцію
        if (are_arrays_equal(stats->arrays[i], stats->sizes[i], array_to_delete, size)) {
            // Знайшли! Викликаємо нашу існуючу функцію видалення за індексом
            printf("Found matching array at index [%d]. Deleting...\n", i);
            delete_array(stats, i);
            return 0; // Успіх
        }
    }

    printf("Array not found.\n");
    return -1; // Не знайдено
}

/**
 * Зчитує дані зі текстового файлу у структуру.
 * Формат файлу:
 * Рядок 1: <N> (загальна кількість масивів)
 * Рядок 2: <size1> (розмір першого масиву)
 * Рядок 3: <el1> <el2> ... (елементи першого масиву)
 * Рядок 4: <size2>
 * ...
 */



int load_from_file(ArrayStatistic* stats, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return -1; // Помилка
    }

    int num_arrays_to_load;
    // Зчитуємо загальну кількість масивів
    if (fscanf(file, "%d", &num_arrays_to_load) != 1) {
        fprintf(stderr, "Error: Could not read total number of arrays from file.\n");
        fclose(file);
        return -1;
    }

    printf("File %s opened. Loading %d arrays...\n", filename, num_arrays_to_load);

    // Цикл N разів
    for (int i = 0; i < num_arrays_to_load; i++) {
        int current_size;
        // Зчитуємо розмір поточного масиву
        if (fscanf(file, "%d", &current_size) != 1) {
            fprintf(stderr, "Error: Could not read size for array %d.\n", i);
            break; // Виходимо з циклу, якщо формат файлу пошкоджено
        }

        // Виділяємо тимчасовий буфер для елементів
        double* temp_array = (double*)malloc(current_size * sizeof(double));
        if (temp_array == NULL) {
            fprintf(stderr, "Error: Could not allocate memory for temp_array.\n");
            break;
        }

        // Зчитуємо елементи у тимчасовий буфер
        for (int j = 0; j < current_size; j++) {
            if (fscanf(file, "%lf", &temp_array[j]) != 1) { // %lf - long float (для double)
                fprintf(stderr, "Error: Could not read element %d for array %d.\n", j, i);
                // Помилка, але ми все одно збережемо те, що встигли прочитати
                current_size = j; // Зберігаємо частково прочитаний масив
                break;
            }
        }

        // Додаємо зчитаний масив у нашу структуру
        // (add_array створить *копію* temp_array)
        add_array(stats, temp_array, current_size);

        free(temp_array);
    }

    fclose(file);
    return 0;
}




int save_to_file(const ArrayStatistic* stats, const char* filename) {
    // "w" - означає "write" (писати). Файл буде створено або ПЕРЕЗАПИСАНО.
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s for writing\n", filename);
        return -1;
    }

    // Записуємо загальну кількість масивів
    fprintf(file, "%d\n", stats->num_arrays);

    // Цикл по кожному масиву
    for (int i = 0; i < stats->num_arrays; i++) {
        // Записуємо розмір поточного масиву
        fprintf(file, "%d\n", stats->sizes[i]);

        // Записуємо всі елементи в один рядок
        for (int j = 0; j < stats->sizes[i]; j++) {
            fprintf(file, "%f ", stats->arrays[i][j]);
        }
        fprintf(file, "\n"); // Новий рядок для наступного масиву
    }

    fclose(file);
    printf("Data successfully saved to %s\n", filename);
    return 0;
}


void read_from_console(ArrayStatistic* stats) {
    int num_arrays_to_load;
    printf("Enter the total number of arrays you want to create: ");
    scanf("%d", &num_arrays_to_load);

    for (int i = 0; i < num_arrays_to_load; i++) {
        int current_size;
        printf("--- Array %d ---\n", i);
        printf("Enter size for array %d: ", i);
        scanf("%d", &current_size);

        if (current_size <= 0) {
            printf("Invalid size, skipping array %d.\n", i);
            continue; // Пропускаємо цю ітерацію циклу
        }

        // Виділяємо тимчасовий буфер
        double* temp_array = (double*)malloc(current_size * sizeof(double));
        if (temp_array == NULL) {
            fprintf(stderr, "Error: Could not allocate memory for temp_array.\n");
            break;
        }

        // Зчитуємо елементи
        printf("Enter %d elements (separated by space): ", current_size);
        for (int j = 0; j < current_size; j++) {
            scanf("%lf", &temp_array[j]); //
        }

        // Додаємо в структуру (яка зробить копію)
        add_array(stats, temp_array, current_size);


        free(temp_array);
    }
    printf("--- Console input finished ---\n");
}



    bool are_arrays_equal(const double* arr1, int size1, const double* arr2, int size2) {
        if (size1 != size2) {
            return false; // Розміри різні
        }

        // memcmp - побайтово порівнює два блоки пам'яті.
        // Повертає 0, якщо вони повністю однакові.
        if (memcmp(arr1, arr2, size1 * sizeof(double)) == 0) {
            return true;
        }

        return false;
    }


    bool is_array_present(const ArrayStatistic* stats, const double* arr, int size) {
        for (int i = 0; i < stats->num_arrays; i++) {
            if (are_arrays_equal(stats->arrays[i], stats->sizes[i], arr, size)) {
                return true;
            }
        }
        return false;
    }


    void merge_structures(ArrayStatistic* dest, const ArrayStatistic* src) {
        for (int i = 0; i < src->num_arrays; i++) {
            add_array(dest, src->arrays[i], src->sizes[i]);
        }
    }

    /**
     * Операція "Додавання" (Об'єднання).
     * Створює нову структуру, що містить всі масиви з s1 та s2,
     * УНИКАЮЧИ дублікатів.
     */
    ArrayStatistic union_structures(const ArrayStatistic* s1, const ArrayStatistic* s2) {
        ArrayStatistic result = create_statistic(s1->num_arrays + s2->num_arrays);

        // Копіюємо всі масиви з s1 (вони гарантовано унікальні)
        merge_structures(&result, s1);

        // Копіюємо масиви з s2, *тільки якщо* їх ще немає в result
        for (int i = 0; i < s2->num_arrays; i++) {
            if (!is_array_present(&result, s2->arrays[i], s2->sizes[i])) {
                // Цього масиву ще немає, додаємо
                add_array(&result, s2->arrays[i], s2->sizes[i]);
            }
        }

        return result;
    }

    /**
     * Операція "Множення" (Перетин).
     * Створює нову структуру, що містить тільки ті масиви,
     * які ідентичні в обох структурах (s1 та s2).
     */
    ArrayStatistic intersection(const ArrayStatistic* s1, const ArrayStatistic* s2) {
    // Створюємо нову структуру (ємність = менша з двох)
    int capacity = (s1->num_arrays < s2->num_arrays) ? s1->num_arrays : s2->num_arrays;
    ArrayStatistic result = create_statistic(capacity);

    // Цикл по s1
    for (int i = 0; i < s1->num_arrays; i++) {
        // Шукаємо, чи є цей масив у s2
        if (is_array_present(s2, s1->arrays[i], s1->sizes[i])) {
            // Збіг! Додаємо цей масив у result
            add_array(&result, s1->arrays[i], s1->sizes[i]);
        }
    }

    return result;
}

        // --- Допоміжні функції для Спірмена ---

    /**
     * Допоміжна структура для зберігання значення та його початкового індексу
     * Потрібна для визначення рангів.
     */
    typedef struct {
        double value;
        int index;
    } RankData;

    /**
     * Функція порівняння для qsort (для RankData)
     * Сортує за полем 'value'.
     */
    int compare_rank_data(const void* a, const void* b) {
        RankData* rdA = (RankData*)a;
        RankData* rdB = (RankData*)b;
        if (rdA->value < rdB->value) return -1;
        if (rdA->value > rdB->value) return 1;
        return 0;
    }

    void get_ranks(const double* arr, int size, double* ranks_out) {
        // Створюємо масив пар (значення, індекс)
        RankData* ranked_data = (RankData*)malloc(size * sizeof(RankData));
        for (int i = 0; i < size; i++) {
            ranked_data[i].value = arr[i];
            ranked_data[i].index = i;
        }

        // Сортуємо цей масив за значеннями
        qsort(ranked_data, size, sizeof(RankData), compare_rank_data);

        // Записуємо ранги.
        // Ранг - це позиція у відсортованому масиві.
        // (Обробка однакових рангів (ties) тут спрощена)
        for (int i = 0; i < size; i++) {
            // ranked_data[i].index -- це початковий індекс елемента
            // (i + 1) -- це його ранг
            ranks_out[ranked_data[i].index] = (double)(i + 1);
        }

        free(ranked_data);
    }


    double calculate_spearman(const ArrayStatistic* stats, int arr_idx1, int arr_idx2) {
        // Валідація індексів
        if (arr_idx1 < 0 || arr_idx1 >= stats->num_arrays ||
            arr_idx2 < 0 || arr_idx2 >= stats->num_arrays) {
            fprintf(stderr, "Error (Spearman): Invalid array index.\n");
            return NAN; // NAN (Not-a-Number) з math.h
            }

        int size1 = stats->sizes[arr_idx1];
        int size2 = stats->sizes[arr_idx2];

        // Спірмен вимагає, щоб масиви були однакового розміру
        if (size1 != size2) {
            fprintf(stderr, "Error (Spearman): Arrays must have the same size. (%d != %d)\n", size1, size2);
            return NAN;
        }

        int n = size1;
        if (n <= 1) {
            fprintf(stderr, "Error (Spearman): Need at least 2 data points.\n");
            return NAN;
        }

        // Отримуємо вказівники на дані
        const double* arr1 = stats->arrays[arr_idx1];
        const double* arr2 = stats->arrays[arr_idx2];

        // Виділяємо пам'ять для рангів
        double* ranks1 = (double*)malloc(n * sizeof(double));
        double* ranks2 = (double*)malloc(n * sizeof(double));

        // Обчислюємо ранги
        get_ranks(arr1, n, ranks1);
        get_ranks(arr2, n, ranks2);

        // 6. Обчислюємо коефіцієнт за формулою
        // rho = 1 - (6 * sum(d_i^2)) / (n * (n^2 - 1))
        // d_i = ranks1[i] - ranks2[i]

        double sum_d_squared = 0.0;
        for (int i = 0; i < n; i++) {
            double d = ranks1[i] - ranks2[i];
            sum_d_squared += (d * d);
        }


        free(ranks1);
        free(ranks2);

        double n_cubed_minus_n = (double)n * n * n - n;

        double rho = 1.0 - (6.0 * sum_d_squared) / n_cubed_minus_n;

        return rho;
    }

    // --- Допоміжні функції для F-тесту та t-тесту ---


    double get_mean(const double* arr, int size) {
        if (size == 0) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum / size;
    }

    /**
     * Допоміжна функція: обчислює вибіркову дисперсію масиву.
     * Дисперсія - це міра "розкиду" значень навколо середнього.
     */
    double get_variance(const double* arr, int size) {
        if (size <= 1) return 0.0; // Дисперсію неможливо обчислити для 1 елемента

        double mean = get_mean(arr, size);
        double sum_sq_diff = 0.0;

        // Сума квадратів різниць: (x_i - mean)^2
        for (int i = 0; i < size; i++) {
            double diff = arr[i] - mean;
            sum_sq_diff += (diff * diff);
        }

        // Ділимо на (n - 1) для *вибіркової* (незміщеної) дисперсії
        return sum_sq_diff / (size - 1);
    }


    /**
     * Перевірка гіпотези про рівність дисперсій (критерій Фішера-Снедекера).
     * @param stats Вказівник на структуру.
     * @param arr_idx1 Індекс першого масиву.
     * @param arr_idx2 Індекс другого масиву.
     * @return Розраховане F-значення.
     */
    double calculate_fisher_test(const ArrayStatistic* stats, int arr_idx1, int arr_idx2) {
        // Валідація індексів
        if (arr_idx1 < 0 || arr_idx1 >= stats->num_arrays ||
            arr_idx2 < 0 || arr_idx2 >= stats->num_arrays) {
            fprintf(stderr, "Error (Fisher): Invalid array index.\n");
            return NAN;
            }

        int size1 = stats->sizes[arr_idx1];
        int size2 = stats->sizes[arr_idx2];

        if (size1 <= 1 || size2 <= 1) {
            fprintf(stderr, "Error (Fisher): Need at least 2 data points per array.\n");
            return NAN;
        }

        // Обчислюємо дисперсії
        double var1 = get_variance(stats->arrays[arr_idx1], size1);
        double var2 = get_variance(stats->arrays[arr_idx2], size2);

        if (var2 == 0.0) {
            fprintf(stderr, "Error (Fisher): Division by zero (variance of array 2 is 0).\n");
            return NAN;
        }

        // Обчислюємо F-статистику
        // Зазвичай, більшу дисперсію ділять на меншу.
        if (var1 > var2) {
            return var1 / var2;
        } else {
            return var2 / var1;
        }
    }

     /**
     * Перевірка гіпотези про рівність середніх (t-критерій Стьюдента).
     * Використовується для МАЛИХ незалежних вибірок (n < 30).
     * (Тут реалізовано варіант з припущенням про рівність дисперсій)
     * @return Розраховане t-значення.
     */
    double calculate_t_test_small(const ArrayStatistic* stats, int arr_idx1, int arr_idx2) {
        // Валідація
        if (arr_idx1 < 0 || arr_idx1 >= stats->num_arrays ||
            arr_idx2 < 0 || arr_idx2 >= stats->num_arrays) {
            fprintf(stderr, "Error (t-test): Invalid array index.\n");
            return NAN;
        }

        int n1 = stats->sizes[arr_idx1];
        int n2 = stats->sizes[arr_idx2];

        if (n1 <= 1 || n2 <= 1) {
            fprintf(stderr, "Error (t-test): Need at least 2 data points per array.\n");
            return NAN;
        }

        // Обчислюємо середні та дисперсії
        double mean1 = get_mean(stats->arrays[arr_idx1], n1);
        double var1 = get_variance(stats->arrays[arr_idx1], n1);

        double mean2 = get_mean(stats->arrays[arr_idx2], n2);
        double var2 = get_variance(stats->arrays[arr_idx2], n2);

        // Обчислюємо "об'єднану" дисперсію (pooled variance)
        double sp_squared = ((n1 - 1) * var1 + (n2 - 1) * var2) / (n1 + n2 - 2);

        // Обчислюємо t-статистику
        double t_value = (mean1 - mean2) / (sqrt(sp_squared * (1.0/n1 + 1.0/n2)));

        return t_value;
    }

    /**
     * Перевірка гіпотези про рівність середніх (Z-критерій).
     * Використовується для ВЕЛИКИХ незалежних вибірок (n >= 30).
     * @return Розраховане Z-значення.
     */
    double calculate_z_test_large(const ArrayStatistic* stats, int arr_idx1, int arr_idx2) {
        // Валідація
        if (arr_idx1 < 0 || arr_idx1 >= stats->num_arrays ||
            arr_idx2 < 0 || arr_idx2 >= stats->num_arrays) {
            fprintf(stderr, "Error (Z-test): Invalid array index.\n");
            return NAN;
            }

        int n1 = stats->sizes[arr_idx1];
        int n2 = stats->sizes[arr_idx2];

        if (n1 == 0 || n2 == 0) {
            fprintf(stderr, "Error (Z-test): Arrays cannot be empty.\n");
            return NAN;
        }

        // Обчислюємо середні та дисперсії
        double mean1 = get_mean(stats->arrays[arr_idx1], n1);
        double var1 = get_variance(stats->arrays[arr_idx1], n1); // s1^2

        double mean2 = get_mean(stats->arrays[arr_idx2], n2);
        double var2 = get_variance(stats->arrays[arr_idx2], n2); // s2^2

        // Обчислюємо Z-статистику
        // Z = (mean1 - mean2) / sqrt( (var1/n1) + (var2/n2) )
        double z_value = (mean1 - mean2) / sqrt( (var1 / n1) + (var2 / n2) );

        return z_value;
    }

    // --- Допоміжні функції для критерію Вілкоксона (Вілсона) ---

    /**
     * Допоміжна структура для зберігання значення та групи (з якого масиву воно)
     */
    typedef struct {
        double value;
        int group; // 1 = з arr1, 2 = з arr2
    } WilcoxonData;

    /**
     * Функція порівняння для qsort (для WilcoxonData)
     * Сортує за полем 'value'.
     */
    int compare_wilcoxon_data(const void* a, const void* b) {
        WilcoxonData* wdA = (WilcoxonData*)a;
        WilcoxonData* wdB = (WilcoxonData*)b;
        if (wdA->value < wdB->value) return -1;
        if (wdA->value > wdB->value) return 1;
        return 0;
    }

    /**
     * Перевірка гіпотези (критерій Вілкоксона/Манна-Уітні).
     * Це непараметричний тест для перевірки рівності розподілів.
     * @return Розраховане значення U-статистики.
     */
    double calculate_wilson_test(const ArrayStatistic* stats, int arr_idx1, int arr_idx2) {
        // Валідація
        if (arr_idx1 < 0 || arr_idx1 >= stats->num_arrays ||
            arr_idx2 < 0 || arr_idx2 >= stats->num_arrays) {
            fprintf(stderr, "Error (Wilcoxon): Invalid array index.\n");
            return NAN;
        }

        int n1 = stats->sizes[arr_idx1];
        int n2 = stats->sizes[arr_idx2];

        if (n1 == 0 || n2 == 0) {
            fprintf(stderr, "Error (Wilcoxon): Arrays cannot be empty.\n");
            return NAN;
        }

        const double* arr1 = stats->arrays[arr_idx1];
        const double* arr2 = stats->arrays[arr_idx2];

        int n_total = n1 + n2;

        // Створюємо об'єднаний масив
        WilcoxonData* combined = (WilcoxonData*)malloc(n_total * sizeof(WilcoxonData));
        if (combined == NULL) {
             fprintf(stderr, "Error (Wilcoxon): Failed to allocate memory.\n");
             return NAN;
        }

        // Копіюємо дані з першого масиву (група 1)
        for (int i = 0; i < n1; i++) {
            combined[i].value = arr1[i];
            combined[i].group = 1;
        }
        // Копіюємо дані з другого масиву (група 2)
        for (int i = 0; i < n2; i++) {
            combined[n1 + i].value = arr2[i];
            combined[n1 + i].group = 2;
        }

        // Сортуємо об'єднаний масив за значеннями
        qsort(combined, n_total, sizeof(WilcoxonData), compare_wilcoxon_data);

        // Обчислюємо суму рангів для першої групи
        // (Тут спрощена обробка однакових рангів, ми просто беремо їхній індекс)
        double rank_sum_1 = 0.0;
        for (int i = 0; i < n_total; i++) {
            if (combined[i].group == 1) {
                rank_sum_1 += (i + 1); // Ранг = позиція + 1
            }
        }

        free(combined);

        // Обчислюємо U-статистику для першої групи
        // U1 = R1 - (n1 * (n1 + 1)) / 2
        double u_statistic = rank_sum_1 - ((double)n1 * (n1 + 1)) / 2.0;

        return u_statistic;
}