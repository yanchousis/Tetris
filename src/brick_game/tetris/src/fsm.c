#include "fsm.h"

void fsm(UserAction_t action) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  ptr_w_game->action = action;
  if (action == Pause) {
    ptr_w_game->game.pause = 1;
    ptr_w_game->state = NONE;
  } else if (action == Start && ptr_w_game->state == NONE) {
    ptr_w_game->state = SHIFTING;
    ptr_w_game->game.pause = 0;
  } else if (action == Start && ptr_w_game->state == GAMEOVER) {
    ptr_w_game->state = START;
  }

  switch (ptr_w_game->state) {
    case START:
      on_start_state();
      break;
    case SPAWN:
      on_spawn_state();
      break;
    case SHIFTING:
      on_shifting_state();
      break;
    case ATTACHING:
      on_attaching_state();
      break;
    case GAMEOVER:
      on_gameover_state();
      break;
    default:
      break;
  }
}

void on_start_state() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  switch (ptr_w_game->action) {
    case Start:
      fill_start_struct();

      ptr_w_game->state = SPAWN;
      break;
    default:
      ptr_w_game->game.pause = 1;
      ptr_w_game->state = START;
      break;
  }
}

void on_spawn_state() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  check_line();
  fill_spawn_struct();

  ptr_w_game->state = SHIFTING;
  spawn_figure();
}

void on_shifting_state() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  switch (ptr_w_game->action) {
    case Left:
      clear_figure();
      ptr_w_game->state = SHIFTING;
      check_left();

      break;
    case Right:
      clear_figure();
      ptr_w_game->state = SHIFTING;
      check_right();

      break;
    case Down:
      clear_figure();
      ptr_w_game->state = SHIFTING;
      for (int i = 0; i < HIGH_POLE; ++i) {
        check_down();
      }

      break;
    case Action:
      clear_figure();
      ptr_w_game->rotate += 1;

      choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                    ptr_w_game->ptr_figure);
      check_rotate();

      ptr_w_game->state = SHIFTING;
      break;
    default:
      clear_figure();
      check_down();

      break;
  }
}

void on_attaching_state() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  ptr_w_game->figure_id = ptr_w_game->figure_id_next;

  ptr_w_game->state = SPAWN;
}

void on_gameover_state() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  destroy_array_2d(&ptr_w_game->game.field);
  destroy_array_2d(&ptr_w_game->ptr_figure);
  check_score();
}