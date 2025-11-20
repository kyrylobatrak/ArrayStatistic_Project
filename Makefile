CXX = g++
CC = gcc
CXXFLAGS = -Wall -g -std=c++17
CFLAGS = -Wall -g

# --- ВАЖЛИВО: Шлях до C-проекту ---
# (Переконайтеся, що він правильний)
C_PROJECT_DIR = ../ArrayStatistic_C

# Об'єктні файли C-проекту, які нам потрібні
C_OBJS = $(C_PROJECT_DIR)/ArrayStatistic.o


# Ціль за замовчуванням
all: test_app_cpp

# --- Збірка C++ тесту ---
test_app_cpp: ArrayStatistic.o ArrayStatistic_test.o
	$(CXX) $(CXXFLAGS) -o test_app_cpp ArrayStatistic.o ArrayStatistic_test.o -lm

ArrayStatistic.o: ArrayStatistic.cpp ArrayStatistic.h
	$(CXX) $(CXXFLAGS) -c ArrayStatistic.cpp -o ArrayStatistic.o

ArrayStatistic_test.o: ArrayStatistic_test.cpp ArrayStatistic.h
	$(CXX) $(CXXFLAGS) -c ArrayStatistic_test.cpp -o ArrayStatistic_test.o


# --- НОВА ЦІЛЬ: Збірка КРОС-ТЕСТУ ---
cross_test: ArrayStatistic_cross_test.o ArrayStatistic.o $(C_OBJS)
	$(CXX) $(CXXFLAGS) -o cross_test_app ArrayStatistic_cross_test.o ArrayStatistic.o $(C_OBJS) -lm

ArrayStatistic_cross_test.o: ArrayStatistic_cross_test.cpp ArrayStatistic.h
	$(CXX) $(CXXFLAGS) -c ArrayStatistic_cross_test.cpp -o ArrayStatistic_cross_test.o

# --- Правило для C-файлу ---
# Як зібрати .o з C-проекту, якщо він змінився
$(C_OBJS): $(C_PROJECT_DIR)/ArrayStatistic.c $(C_PROJECT_DIR)/ArrayStatistic.h
	$(CC) $(CFLAGS) -c $(C_PROJECT_DIR)/ArrayStatistic.c -o $(C_PROJECT_DIR)/ArrayStatistic.o


clean:
	rm -f *.o test_app_cpp cross_test_app results_CPP.txt
	# Також очищуємо C-проект
	rm -f $(C_PROJECT_DIR)/*.o