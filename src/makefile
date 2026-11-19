CC:=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -Wpedantic
LDFLAGS=-lncurses

BUILD_DIR:=build
TETRIS_DIR=brick_game/tetris
MENU_SRC=gui/cli/menu.c 
MENU_TARGET=$(BUILD_DIR)/menu

all: install

install: menu tetris

uninstall:
	rm -rf $(BUILD_DIR)

tetris:
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C $(TETRIS_DIR) tetris DEFFLAGS=-DMAIN_TETRIS
	mv $(TETRIS_DIR)/$(BUILD_DIR)/tetris $(BUILD_DIR)

menu: $(MENU_TARGET)

$(MENU_TARGET): $(MENU_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run-tetris: tetris
	./$(BUILD_DIR)/tetris

run-menu: menu
	./$(BUILD_DIR)/menu

clean: uninstall
	$(MAKE) -C $(TETRIS_DIR) clean

.PHONY: all tetris menu run-tetris run-menu clean