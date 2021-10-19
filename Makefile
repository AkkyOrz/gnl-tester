
all: exec_1 exec_42 exec_10M exec_INTMAX

build_1:
	cmake -S . -B build -D BUFFER_SIZE=1 && cmake --build build
build_42:
	cmake -S . -B build -D BUFFER_SIZE=42 && cmake --build build
build_INTMAX:
	cmake -S . -B build -D BUFFER_SIZE=2147483647 && cmake --build build
build_10M:
	cmake -S . -B build -D BUFFER_SIZE=10000000 && cmake --build build

exec_1: build_1
	./build/main < files/alternate_line_nl_with_nl
exec_42: build_42
	./build/main < files/alternate_line_nl_with_nl
exec_INTMAX: build_INTMAX
	./build/main < files/alternate_line_nl_with_nl
exec_10M: build_10M
	./build/main < files/alternate_line_nl_with_nl

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all ./build/main < files/alternate_line_nl_with_nl
