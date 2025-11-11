# ArrayStatistic: C & C++ Statistical Analysis Library

![Language](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![Language](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white)
![Build](https://img.shields.io/badge/Build-Makefile-brightgreen)

This project is a parallel C and C++ implementation of a data structure for storing and analyzing arrays of arrays (vectors of vectors), as per Task #25 of the CppPracticum course.

It provides two modules:
* **`ArrayStatistic_C`**: A C implementation using manual memory management (`malloc`, `realloc`, `free`) and pointer arithmetic.
* **`ArrayStatistic_CPP`**: A modern C++ implementation using an object-oriented approach and STL containers (`std::vector`), which automates memory management (RAII).

The entire project is built using `Makefile` and includes a comprehensive cross-test to verify that both C and C++ modules produce **identical** statistical results, ensuring logical consistency.

## 🚀 Features

This library implements a complete set of data management and statistical analysis functions.

### Data Management
* **CRUD Operations**: Create, read, and destroy the array-of-arrays structure.
* **Add**: Add an entire array, or add a single element to a specific array.
* **Delete (by Index)**: Delete an entire array or a specific element by its index.
* **Delete (by Value)**: Delete an entire array or a specific element by its value.

### Set Operations
* **Union (`operator+` in C++)**: Merges two `ArrayStatistic` structures, ensuring no duplicate arrays are added.
* **Intersection (`operator*` in C++)**: Creates a new `ArrayStatistic` structure containing only the arrays that are present in *both* original structures.

### 📊 Statistical Analysis
The core feature is the ability to run statistical tests on any two arrays within the structure:
* **Spearman's Rank Correlation Coefficient**
* **Fisher-Snedecor F-test** (for equality of variances)
* **Student's t-test** (for equality of means, small samples)
* **Z-test** (for equality of means, large samples)
* **Wilcoxon (Mann-Whitney U) test** (non-parametric test for equality of distributions)

---

## 📁 Project Structure

The repository is organized into two main projects, as required by the assignment.

ArrayStatistic_Project/ ├── .gitignore ├── ArrayStatistic_C/ │ ├── ArrayStatistic.c │ ├── ArrayStatistic.h │ ├── ArrayStatistic_test.c │ ├── ArrayStatistic_test.dat │ ├── Makefile │ └── results_C.txt ├── ArrayStatistic_CPP/ │ ├── ArrayStatistic.cpp │ ├── ArrayStatistic.h │ ├── ArrayStatistic_test.cpp │ ├── ArrayStatistic_cross_test.cpp │ ├── ArrayStatistic_test.dat │ ├── Makefile │ └── results_CPP.txt └── README.md


---

## 🛠️ Getting Started

### Prerequisites
* A C/C++ compiler (e.g., `gcc`/`g++` via MinGW or Linux build-essentials)
* `make`
* `git`

### Installation & Building

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/mecchmatProjects/CppPracticum.git](https://github.com/mecchmatProjects/CppPracticum.git)
    cd CppPracticum
    ```
    *(Note: Assumes you cloned the main course repository)*

2.  **Build the C Project:**
    ```bash
    cd ArrayStatistic_C
    make
    ```
    This will create the `test_app` (or `test_app.exe`) executable.

3.  **Build the C++ Project:**
    ```bash
    cd ../ArrayStatistic_CPP
    make
    ```
    This will create the `test_app_cpp` (or `test_app_cpp.exe`) executable.

### Running the Test Applications

Each test program provides an interactive menu to either load data from `ArrayStatistic_test.dat` or enter it manually. All tests defined in the task are run sequentially.

* **Run C Test:**
    ```bash
    # (While in ArrayStatistic_C)
    ./test_app
    ```

* **Run C++ Test:**
    ```bash
    # (While in ArrayStatistic_CPP)
    ./test_app_cpp
    ```

---

## ✅ Cross-Testing (Verification)

The most important test is the `cross_test`, which proves that the C and C++ implementations are logically identical. It builds **both** `ArrayStatistic.c` and `ArrayStatistic.cpp` into a single program.

1.  **Navigate** to the C++ project directory:
    ```bash
    cd ArrayStatistic_CPP
    ```

2.  **Build** the cross-test target specified in the `Makefile`:
    ```bash
    make cross_test
    ```
    This creates the `cross_test_app` (or `cross_test_app.exe`) executable.

3.  **Run** the cross-test:
    ```bash
    ./cross_test_app
    ```

#### Expected Output
You should see the following output, confirming that all statistical functions return the same values for both modules:

--- Cross-Test (C vs C++) --- File ArrayStatistic_test.dat opened. Loading 3 arrays... Data loaded into C and C++ models successfully. Testing Spearman (diff size)... PASSED Testing Fisher F-test (0, 2)... PASSED Testing t-test (0, 2)... PASSED Testing Z-test (0, 2)... PASSED Testing Wilcoxon U-test (0, 2)... PASSED --- Cross-Test Finished ---

*(Note: The `Error (Spearman): Arrays must have the same size.` message is expected, as the test correctly verifies that both modules return `NAN` for invalid data).*

---

## 👨‍💻 Author

* **Batrak K.V.**
* *Group: Computer Mathematics, 2nd Year*
