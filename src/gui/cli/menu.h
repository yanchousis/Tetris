#ifndef MENU_H__
#define MENU_H__

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GET_USER_INPUT getch()
#define GAMES_PATH "build/"

typedef struct {
  const char* name;
  const char* executable;
  const char* makefile_dir;
} Game_t;

void menu();

int game_installed(const char* executable);
void run_game(const char* executable);
void install_game(const Game_t* const games, int i);

#endif