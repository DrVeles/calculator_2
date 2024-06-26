CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17
# CC_TEST_FLAGS = -lgtest --coverage 

#  all, install, uninstall, clean, dvi, dist, tests

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
	@echo "===========> UNINSATLLED <============"
	@echo "======================================"

clean: 
	-@rm -rf a.out

dvi:
	$(OPEN_COMAND) ../README.md

dist: clean
# 	@mkdir SmartCalc_v1.0
# 	@mkdir SmartCalc_v1.0/src
# 	@cp -r front functions tests Makefile s21_calc_controller.* SmartCalc_v1.0/src/
# 	@cp ../README.md SmartCalc_v1.0/
# 	@tar -cf SmartCalc_v1.0.tar SmartCalc_v1.0 
# 	@rm -rf SmartCalc_v1.0/

test: clean google_format
	$(CC) $(CC_FLAGS) ./model/model.cpp -o a.out
	./a.out

leaks: test
	CK_FORK=no leaks -atExit -q -- ./a.out

google_format:
	-@clang-format -style=Google -i */*.h */*.cpp
	@echo "===========> FORMATTED <============"
