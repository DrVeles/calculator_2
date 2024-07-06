CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17
CC_TEST_FLAGS = -lgtest --coverage 

all: install

install: uninstall
	@cmake -B build "view/Calculator_1" 
	@make -C build Calculator_1
	@cp -R build/Calculator_1.app ../
	@rm -rf ./build/
	@echo "======================================"
	@echo "==> INSTALLED ../Calculator_1.app  <=="
	@echo "======================================"

uninstall: clean
	-@rm -rf build/ ../Calculator_1.app/
	@echo "======================================"
	@echo "===========> UNINSTALLED <============"
	@echo "======================================"

clean: 
	-@rm -rf *.out *.gcno *.gcda *.dSYM/ *.o ../*.tar ./report *info

dvi:
	open ./../README.md

dist: clean
	@mkdir -p SmartCalc_v2.0
	@mkdir -p SmartCalc_v2.0/src
	@cp -r ./* SmartCalc_v2.0/src
	@cp ../README.md SmartCalc_v2.0/
	@tar -cf SmartCalc_v2.0.tar SmartCalc_v2.0 
	@rm -rf SmartCalc_v2.0/
	@mv ./SmartCalc_v2.0.tar ../. 
	@echo "======================================"
	@echo "===========> DIST READY <============="
	@echo "======================================"

test: clean google_format
	$(CC) $(CC_FLAGS) ./tests/tests.cpp ./model/model.cpp -o a.out $(CC_TEST_FLAGS)
	./a.out

gcov_report: test
	@lcov -t "Tests" -o tests.info -c -d . --ignore-errors inconsistent >/dev/null 2>&1
	@lcov -e tests.info '*.cpp' -o tests.info >/dev/null 2>&1
	@genhtml -o report tests.info >/dev/null 2>&1
	open ./report/index.html

leaks: test
	CK_FORK=no leaks -atExit -q -- ./a.out

google_format:
	-@clang-format -style=Google -i */*.h */*.cpp 
	@echo "===========> FORMATTED <============"
