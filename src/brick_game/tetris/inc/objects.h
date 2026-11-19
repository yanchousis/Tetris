#ifndef OBJECTS_H__
#define OBJECTS_H__

#include "backend.h"

#define F_SIZE 4

typedef enum {
  FIGURE_NONE = 0,
  FIGURE_T,
  FIGURE_I,
  FIGURE_S,
  FIGURE_LZ,
  FIGURE_RZ,
  FIGURE_LG,
  FIGURE_RG,
} Figure_t;

typedef enum {
  START = 0,
  SPAWN,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  TERMINATE,
  NONE
} State_t;

typedef struct {
  GameInfo_t game;
  Figure_t figure_id;
  Figure_t figure_id_next;
  State_t state;
  UserAction_t action;
  int** ptr_figure;
  int x;
  int y;
  int rotate;
} WideGameInfo_t;

WideGameInfo_t* static_wide_game_info();

#endif