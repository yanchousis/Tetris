#ifndef FSM_H__
#define FSM_H__

#include "backend.h"
#include "objects.h"

void fsm(UserAction_t action);

void on_start_state();
void on_spawn_state();
void on_shifting_state();
void on_attaching_state();
void on_gameover_state();

#endif