# Makefile для ArrayStatistic_CPP
CXX = g++
CXXFLAGS = -Wall -g -std=c++17

# Ціль за замовчуванням
all: test_app_cpp

# Як зібрати C++ тест
test_app_cpp: ArrayStatistic.cpp ArrayStatistic_test.cpp
	$(CXX) $(CXXFLAGS) -o test_app_cpp ArrayStatistic.cpp ArrayStatistic_test.cpp -lm

# Поки що не додаємо cross_test, щоб не ускладнювати

clean:
	rm -f *.o test_app_cpp