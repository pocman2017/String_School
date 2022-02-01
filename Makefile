CFLAGS=-Wall -Werror -Wextra -std=c11
LIBS=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
OBJECTS= s21_string.o
SOURSES= s21_string.c
all: main

main: clean s21_string.a test gcov_report

s21_string.a: 
	gcc -c $(SOURSES) 
	@ar rcs s21_string.a $(OBJECTS)

test: s21_string.a unit_tests

unit_tests:
	gcc -c unit_tests.c  -o unit_tests.o
	gcc unit_tests.o s21_string.a  -lcheck -o unit_tests
	./unit_tests

gcov_report: s21_string.a
	gcc $(GCOV) unit_tests.c  -lcheck $(SOURSES) -o GcovReport
	./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*

clean:
	@rm -rf unit_tests ./*.o ./*.a ./a.out ./GcovReport ./*.gc* ./report ./*.info

rebuild: clean all

cpplint:
	cp -f ../materials/linters/CPPLINT.cfg ./CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c ../src/*.c
	python3 ../materials/linters/cpplint.py --extensions=c ../src/*.h

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem *.c