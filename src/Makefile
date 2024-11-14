CC = c++ --coverage 
CFLAGS = -Wall -Werror -Wextra -std=c++17

all:clean
	c++ $(FLAGS) main.cpp s21_matrix_oop.cpp -o test -g -std=c++17

s21_matrix_oop.a:clean
	$(CC) $(CFLAGS) -c s21_matrix_oop.cpp
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm s21_matrix_oop.o

test:clean
	$(CC) $(CFLAGS) s21_matrix_test.cpp s21_matrix_oop.cpp  -pthread -lgmock -lgmock_main -lgtest_main -lgtest -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib -o s21_matrix_test 
	./s21_matrix_test

gcov_report:test
	lcov  --no-external --capture --directory  . --output-file s21_matrix.info
	genhtml -o report s21_matrix.info
	open report/index.html

clean:
	rm -rf  test *.o *.a s21_matrix_test
	rm -rf *.gcda *.gcno *.info report htmlcov
