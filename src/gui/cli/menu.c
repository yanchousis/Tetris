#include "menu.h"

int main() {
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  cbreak();
  noecho();
  timeout(500);

  menu();

  endwin();
  return 0;
}

void menu() {
  const Game_t games[] = {{"Tetris", "tetris", "./brick_game/tetris/"}};
  const int games_count = sizeof(games) / sizeof(games[0]);

  int selected = 0;
  int break_flag = 0;

  while (!break_flag) {
    mvprintw(2, 2, "Welcome to the Brickgame menu");
    mvprintw(3, 2, "Choose the game: ");
    mvprintw(4 + games_count + 2, 2, "Enter: select");
    mvprintw(4 + games_count + 3, 2, "I: install");
    mvprintw(4 + games_count + 4, 2, "R: run");
    mvprintw(4 + games_count + 5, 2, "Q: quit");
    refresh();

    for (int i = 0; i < games_count; ++i) {
      if (i == selected) attron(A_REVERSE);

      char status[64];
      if (game_installed(games[i].executable)) {
        snprintf(status, sizeof(status), "%s (installed)", games[i].name);
      } else {
        snprintf(status, sizeof(status), "%s (not installed)", games[i].name);
      }
      mvprintw(5 + i, 2, "%s", status);

      if (i == selected) attroff(A_REVERSE);
    }

    int ch = 0;
    ch = GET_USER_INPUT;

    switch (ch) {
      case KEY_UP:
        if (selected > 0) --selected;

        break;
      case KEY_DOWN:
        if (selected < games_count - 1) ++selected;

        break;
      case '\n':
      case 'r':
      case 'R':
        if (game_installed(games[selected].executable)) {
          run_game(games[selected].executable);
        } else {
          clear();
          mvprintw(selected + 5, 30, "Game not install");
          refresh();
        }

        break;
      case 'i':
      case 'I':
        if (!game_installed(games[selected].executable)) {
          install_game(&games[selected], selected);
        } else {
          clear();
          mvprintw(selected + 5, 30, "Game already installed");
          refresh();
        }
        break;
      case 'q':
      case 'Q':
        break_flag = 1;
        break;
      default:
        break;
    }
  }
}

int game_installed(const char* executable) {
  char path[256] = {0};
  snprintf(path, sizeof(path), "%s%s", GAMES_PATH, executable);

  return access(path, X_OK) == 0;
}

void run_game(const char* executable) {
  char path[256] = {0};
  snprintf(path, sizeof(path), "./%s%s", GAMES_PATH, executable);
  endwin();

  system(path);

  initscr();
}

void install_game(const Game_t* const games, int i) {
  char cmd[512] = {0};
  snprintf(cmd, sizeof(cmd), "cd %s && make", games->makefile_dir);

  int result = system(cmd);

  if (result != 0) {
    clear();
    mvprintw(i + 15, 2, "ERROR: Failed to compile game");
    refresh();
  } else {
    char src_path[256] = {0}, dest_path[256] = {0};
    snprintf(src_path, sizeof(src_path), "%sbuild/%s", games->makefile_dir,
             games->executable);
    snprintf(dest_path, sizeof(dest_path), "%s%s", GAMES_PATH,
             games->executable);

    char mkdir_cmd[256] = {0};
    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", GAMES_PATH);
    system(mkdir_cmd);

    char mv_cmd[1024];
    snprintf(mv_cmd, sizeof(mv_cmd), "mv %s %s", src_path, dest_path);
    result = system(mv_cmd);

    if (result == 0) {
      clear();
      mvprintw(i + 15, 30, "Game installed successfully!");
    } else {
      clear();
      mvprintw(i + 15, 30, "Error: Failed to move executable");
    }
  }

  refresh();
}
