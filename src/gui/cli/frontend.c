#include "frontend.h"

int main(void) {
  INIT_NCURSES;
  setlocale(LC_ALL, "");
  srand(time(NULL));
  print_overlay();
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  GameInfo_t game = {0};
  UserAction_t signal = -1;
  int break_flag = 0;

  while (!break_flag) {
    int ch = 0;
    userInput(signal, 0);
    game = updateCurrentState();

    printw_full_screen(&game);

    ch = GET_USER_INPUT;
    flushinp();
    signal = input_char(ch, &break_flag);
  }

  destroy_array_2d(&game.field);
  destroy_array_2d(&game.next);
}

UserAction_t input_char(int user_input, int* break_flag) {
  UserAction_t action = -1;

  switch (user_input) {
    case 'S':
    case 's':
      action = Start;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case ' ':
      action = Action;
      break;
    case KEY_LEFT:
    case 'l':
      action = Left;
      break;
    case KEY_RIGHT:
    case 'r':
      action = Right;
      break;
    case KEY_DOWN:
    case 'd':
      action = Down;
      break;
    case KEY_UP:
      action = Up;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      *break_flag = 1;
      break;
    default:
      break;
  }

  return action;
}

void print_overlay() {
  printw_borders();
  printw_high_score(0);
  printw_score(0);
  printw_next_fig(NULL);
  printw_level(1);
  printw_pause(NULL, 1);

  mvprintw(5 + HIGH_POLE, FIELD_BEGIN, "Arrows: move figures");
  mvprintw(5 + HIGH_POLE + 1, FIELD_BEGIN, "Q: exit");
  mvprintw(5 + HIGH_POLE + 2, FIELD_BEGIN, "Space: action");
  mvprintw(5 + HIGH_POLE + 3, FIELD_BEGIN, "P: pause");

  refresh();
}

void printw_borders() {
  mvaddch(BOARD_START, BOARD_START, ACS_ULCORNER);
  mvaddch(BOARD_START, BOARD_START + WIDTH_POLE + 1, ACS_URCORNER);
  mvaddch(BOARD_START + HIGH_POLE + 1, BOARD_START, ACS_LLCORNER);
  mvaddch(BOARD_START + HIGH_POLE + 1, BOARD_START + WIDTH_POLE + 1,
          ACS_LRCORNER);

  for (int j = 0; j < WIDTH_POLE; ++j) {
    mvaddch(BOARD_START, BOARD_START + j + 1, ACS_HLINE);
    mvaddch(BOARD_START + HIGH_POLE + 1, BOARD_START + j + 1, ACS_HLINE);
  }

  for (int i = BOARD_START + 1; i < BOARD_START + HIGH_POLE + 1; ++i) {
    mvaddch(i, BOARD_START, ACS_VLINE);
    mvaddch(i, BOARD_START + WIDTH_POLE + 1, ACS_VLINE);
  }
}

void printw_start_msg() {
  attron(A_BOLD);
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2, WIDTH_POLE / 2 - 1, INTRO_MESSAGE_1);
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 1, WIDTH_POLE / 2 - 1,
           INTRO_MESSAGE_2);
  attroff(A_BOLD);
}

void printw_gameover_msg() {
  attron(A_BOLD | A_BLINK);
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 - 1, WIDTH_POLE / 2 - 1, "        ");
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2, WIDTH_POLE / 2 - 2, "GAME OVER");
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 1, WIDTH_POLE / 2 - 1, "        ");
  attroff(A_BOLD | A_BLINK);
}

void printw_full_screen(GameInfo_t* game) {
  printw_arr_2d(game->field, FIELD_BEGIN, FIELD_BEGIN, HIGH_POLE, WIDTH_POLE);

  if (!game->field && !game->next && !game->speed) {
    printw_start_msg();
  } else if (!game->field && !game->next && game->speed) {
    printw_gameover_msg();

    if (game->score == game->high_score && game->score)
      printw_new_score(game->high_score);
  }

  printw_high_score(game->high_score);
  printw_score(game->score);
  printw_next_fig(game->next);
  printw_level(game->level);
  printw_pause(game->field, game->pause);

  refresh();
  napms(game->speed);
}

void printw_high_score(const int high_score) {
  mvprintw(4, BOARD_START + WIDTH_POLE + 4, "High score: ");
  mvprintw(4, BOARD_START + WIDTH_POLE + 4 + 12, "%d", high_score);
}

void printw_score(const int score) {
  mvprintw(5, BOARD_START + WIDTH_POLE + 4 + 12, "          ");
  mvprintw(5, BOARD_START + WIDTH_POLE + 4, "Score: %6d", score);
}

void printw_level(const int level) {
  mvprintw(19, BOARD_START + WIDTH_POLE + 4, "Level: %d", level);
}

void printw_pause(int** const field, const int pause) {
  if (pause) {
    attron(A_BOLD | A_BLINK);

    mvprintw(BOARD_START + HIGH_POLE, 6 + WIDTH_POLE, PAUSE);
    if (field) mvprintw(BOARD_START + HIGH_POLE, 9 + WIDTH_POLE, "Pause");

    attroff(A_BOLD | A_BLINK);
  } else {
    attron(A_BOLD);
    mvprintw(BOARD_START + HIGH_POLE, 6 + WIDTH_POLE, PLAY);
    attroff(A_BOLD);

    if (field) mvprintw(BOARD_START + HIGH_POLE, 9 + WIDTH_POLE, "     ");
  }
}

void printw_next_fig(int** fig) {
  mvprintw(9, BOARD_START + WIDTH_POLE + 4, "Next");

  if (fig) {
    printw_arr_2d(fig, 10, BOARD_START + WIDTH_POLE + 4, FIGURE_SIZE,
                  FIGURE_SIZE);
  }
}

void printw_arr_2d(int** arr, const int start_y, const int start_x,
                   const int rows, const int cols) {
  if (!arr) return;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (arr[i][j] == 1) {
        attron(A_BOLD);
        mvaddch(i + start_y, j + start_x, ACS_BLOCK);
        attroff(A_BOLD);
      } else {
        attron(COLOR_PAIR(1));
        mvaddch(i + start_y, j + start_x, ACS_BULLET);
        attroff(COLOR_PAIR(1));
      }
    }
  }

  refresh();
}

void printw_new_score(const int new_high_score) {
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 2, WIDTH_POLE / 2 - 2, "New score");
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 2 + 1, WIDTH_POLE / 2 - 2,
           "          ");
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 2 + 2, WIDTH_POLE / 2 - 2,
           "          ");
  mvprintw((FIELD_BEGIN + HIGH_POLE) / 2 + 2 + 1,
           (FIELD_BEGIN + WIDTH_POLE) / 2 + 1, "%d", new_high_score);
}
