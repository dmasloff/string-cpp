build: test_simple test_simple_opt test_ubsan

test_simple: tests/string_test.cpp src/string.h
	clang++ -std=c++20 -gdwarf-4 -O0 -Wall -Wextra -Werror -o ./test_simple tests/string_test.cpp src/string.cpp

test_simple_opt: tests/string_test.cpp src/string.h
	clang++ -std=c++20 -O2 -Wall -Wextra -Werror -o ./test_simple_opt tests/string_test.cpp src/string.cpp

test_ubsan: tests/string_test.cpp src/string.h
	clang++ -std=c++20 -g -O0 -Wall -Wextra -Werror -fsanitize=undefined -o ./test_ubsan tests/string_test.cpp src/string.cpp

info:
	clang++ --version
	valgrind --version

run: build
	@echo 'Run tests (simple)'
	time ./test_simple
	@echo 'Run tests (simple_opt)'
	time ./test_simple_opt
	@echo 'Run tests (ubsan)'
	time ./test_ubsan
	@echo 'Run tests (valgrind)'
	time valgrind --leak-check=yes ./test_simple

test: info run
	@echo 'Great job!'

clean:
	rm test_simple test_simple_opt test_ubsan
	rm -rf test_simple.dSYM test_ubsan.dSYM