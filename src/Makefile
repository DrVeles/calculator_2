CC = g++
CC_FLAGS = -Wall -Wextra -Werror -std=c++17
# CC_TEST_FLAGS = -lgtest --coverage 

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

dvi:
	$(OPEN_COMAND) ../README.md

clean: 
	-@rm -rf a.out

# rt: clean test

leaks: test
	CK_FORK=no leaks -atExit -q -- ./tests/test_all 

google_format:
	-@clang-format -style=Google -i */*.h */*.cpp
	@echo "===========> FORMATTED <============"
