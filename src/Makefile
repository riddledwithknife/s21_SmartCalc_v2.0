CC = gcc
CFLAGS = -std=c++17 -lstdc++ -pedantic -Wall -Werror -Wextra
TEST_FLAGS = -lgtest
MODEL_FILES = $(wildcard Model/*.cc)
CONTROLLER_FILES = $(wildcard Controller/*.cc)
TEST_FILES = $(wildcard Tests/*.cc)

all:
	$(MAKE) clean
	$(MAKE) install

install:
	mkdir SmartCalc
	cd SmartCalc && cmake ..
	cd SmartCalc && make

uninstall:
	rm -rf SmartCalc

launch:
	open SmartCalc/SmartCalc.app

dvi:
	open documentation.md

dist:
	 tar -cf SmartCalc.tar SmartCalc

build_test:
	cd Tests && mkdir -p build
	cd Tests/build && cmake -DCMAKE_BUILD_TYPE=Debug ..
	cd Tests/build && make

test: build_test
	cd Tests/build && ctest -VV

gcov_report:
	$(CC) $(CFLAGS) $(TEST_FILES) $(MODEL_FILES) -coverage $(TEST_FLAGS) -o gcovreport
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info
	rm -rf *.a *.info *.gcda *.gcno gcovreport

style:
	 clang-format -style=Google -i Model/*.cc Model/*.h View/FinanceWindow/*.cc View/FinanceWindow/*.h View/MainWindow/*.cc View/MainWindow/*.h Controller/*.cc Controller/*.h Tests/*.cc

clean:
	 rm -rf SmartCalc
	 rm -rf Tests/build