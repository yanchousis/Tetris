#ifndef API_H__
#define API_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HIGH_POLE 20
#define WIDTH_POLE 10

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);
void destroy_array_2d(int*** arr);

#endif