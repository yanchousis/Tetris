#ifndef FRONTEND_H__
#define FRONTEND_H__

#include <locale.h>
#include <ncurses.h>
#include <time.h>

#include "../../api/api.h"

#define INIT_NCURSES                \
  {                                 \
    initscr();                      \
    noecho();                       \
    curs_set(0);                    \
    keypad(stdscr, TRUE);           \
    cbreak();                       \
    timeout(10);                    \
    start_color();                  \
    init_pair(1, 238, COLOR_BLACK); \
  }

typedef enum { SUCCESS = 0, ERROR } Error_t;

#define FIGURE_SIZE 4

#define BOARD_START 2
#define FIELD_BEGIN 3

#define PAUSE "||"
#define PLAY "|>"
#define INTRO_MESSAGE_1 "Press S"
#define INTRO_MESSAGE_2 "to start"

#define GET_USER_INPUT getch()

void game_loop();
UserAction_t input_char(int, int*);

void print_overlay();
void printw_full_screen(GameInfo_t* game);
void printw_borders();
void printw_score(const int score);
void printw_level(const int);
void printw_next_fig(int** fig);
void printw_pause(int** const, const int);
void printw_high_score(const int high_score);
void printw_start_msg();
void printw_gameover_msg();
void printw_new_score(const int new_high_score);

void printw_arr_2d(int**, const int, const int, const int, const int);

#endif
