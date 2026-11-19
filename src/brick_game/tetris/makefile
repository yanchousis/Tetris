CC:=gcc
CFLAGS:=-I inc -I ../../api -std=c11 -Wall -Werror -Wextra -Wpedantic
DEF_FLAGS=
LDFLAGS=-lncurses
LDFLAGS_CHECK=-lcheck
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

TARGET:=tetris
BUILD_DIR:=build

OBJS_SRC:=out/backend.o out/fsm.o out/figures.o
OBJS_FRONT:=out/frontend.o

OBJS_SRC_TEST:=tests/out/fsm.o tests/out/backend.o tests/out/figures.o
OBJS_TEST:=tests/out/test.o tests/out/test_figures.o tests/out/test_backend.o tests/out/test_fsm.o

OBJS_SRC_GCOV:=gcov_report/out/fsm.o gcov_report/out/backend.o gcov_report/out/figures.o
OBJS_TEST_GCOV:=gcov_report/out/test.o gcov_report/out/test_figures.o gcov_report/out/test_backend.o gcov_report/out/test_fsm.o

UNAME_S:=$(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LDFLAGS_CHECK+=-lm -lsubunit
endif

all: install

install: $(OBJS_SRC) $(OBJS_FRONT)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)
	mv $(TARGET) $(BUILD_DIR)/

out/%.o: src/%.c
	$(CC) $(CFLAGS) $(DEF_FLAGS) -c $< -o $@

out/frontend.o: ../../gui/cli/frontend.c
	$(CC) $(CFLAGS) -c $< -o $@

uninstall:
	rm -rf $(BUILD_DIR)

clean: uninstall
	rm -rf out/*.o tests/out/* gcov_report *.gz 

dvi:
	open diagramm/diagramm_of_ka.pdf

dist: $(OBJS_SRC)
	mkdir -p tetris
	ar rcs tetris/tetris.a $(OBJS_SRC)
	ranlib tetris/tetris.a
	cp -r src inc ../../gui tests makefile tetris/
	tar czf tetris-1.0.tar.gz tetris/
	rm -rf tetris

test: $(OBJS_SRC_TEST) $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ -o tests/out/test $(LDFLAGS_CHECK) $(LDFLAGS) 
	./tests/out/test

tests/out/%.o: src/%.c
	$(CC) $(CFLAGS) $(DEF_FLAGS) -c $< -o $@

tests/out/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS_CHECK)

gcov_report: $(OBJS_SRC_GCOV) $(OBJS_TEST_GCOV)
	mkdir -p gcov_report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $^ -o tests/out/test $(LDFLAGS_CHECK) $(LDFLAGS) 
	./tests/out/test
	lcov -t "stest" -o gcov_report/test.info -c -d gcov_report/
	genhtml -o gcov_report/report gcov_report/test.info

gcov_report/out/%.o: src/%.c
	mkdir -p gcov_report/out
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(DEF_FLAGS) -c $< -o $@

gcov_report/out/%.o: tests/%.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@ $(LDFLAGS_CHECK)

.PHONY: all install uninstall clean dvi dist test gcov_report