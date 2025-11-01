# Makefile для ArrayStatistic_C
CC = gcc
CFLAGS = -Wall -g # -Wall (попередження) та -g (дебаг)

# Ціль за замовчуванням (що збирати, коли натиснете "Run")
all: test_app

# Як зібрати test_app
test_app: ArrayStatistic.c ArrayStatistic_test.c
	$(CC) $(CFLAGS) -o test_app ArrayStatistic.c ArrayStatistic_test.c -lm

# Правило для очищення (видалення)
clean:
	rm -f *.o test_app