#include "backend.h"

WideGameInfo_t* static_wide_game_info() {
  static WideGameInfo_t wide_game = {.state = START};

  return &wide_game;
}

void userInput(UserAction_t action, bool hold) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                ptr_w_game->ptr_figure);

  fsm(action);

  if (hold) {
  }
}

GameInfo_t updateCurrentState() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  fill_field_fig();
  choice_figure(ptr_w_game->figure_id_next, 0, ptr_w_game->ptr_figure);

  ptr_w_game->game.next = ptr_w_game->ptr_figure;
  GameInfo_t game = ptr_w_game->game;

  return game;
}

void fill_field_fig() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;

  for (int i = 0; i < F_SIZE; ++i) {
    for (int j = 0; j < F_SIZE; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1)
        ptr_w_game->game.field[i + ptr_w_game->y][j + ptr_w_game->x] = 1;
    }
  }
}

int** create_array_2d(const int rows, const int cols) {
  int** arr = malloc(sizeof(int*) * rows + sizeof(int) * rows * cols);
  if (!arr) return NULL;

  int* ptr = (int*)(arr + rows);

  for (int i = 0; i < rows; ++i) {
    arr[i] = ptr + i * cols;
  }

  fill_empty(arr, rows, cols);

  return arr;
}

void fill_empty(int** arr, const int rows, const int cols) {
  if (!arr) return;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      arr[i][j] = 0;
    }
  }
}

void destroy_array_2d(int*** arr) {
  free(*arr);
  *arr = NULL;
}

void clear_figure() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;

  for (int i = 0; i < F_SIZE; ++i) {
    for (int j = 0; j < F_SIZE; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1)
        ptr_w_game->game.field[i + ptr_w_game->y][j + ptr_w_game->x] = 0;
    }
  }
}

void spawn_figure() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  create_figure_matrix(ptr_w_game->rotate);
  check_gameover();
}

void fill_spawn_struct() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  ptr_w_game->x = SPAWN_X;
  ptr_w_game->y = SPAWN_Y;
  ptr_w_game->rotate = 0;
}

void fill_start_struct() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  ptr_w_game->game.field = create_array_2d(HIGH_POLE, WIDTH_POLE);
  ptr_w_game->ptr_figure = create_array_2d(F_SIZE, F_SIZE);
  ptr_w_game->game.high_score = get_high_score();
  ptr_w_game->game.pause = 0;
  ptr_w_game->figure_id = 1 + rand() % 7;
  ptr_w_game->figure_id_next = 0;
  ptr_w_game->game.score = 0;
  ptr_w_game->game.speed = 300;
  ptr_w_game->game.level = 1;
}

int get_high_score() {
  int high_score = 0;

  FILE* f = fopen(FILENAME, "r");
  if (f) {
    fscanf(f, "%d", &high_score);
    fclose(f);
  }

  return high_score;
}

int check_down_border(int i) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return 0;

  int retVal = 0;

  if (ptr_w_game->y + i + 1 == HIGH_POLE) {
    retVal = 1;
  }

  return retVal;
}

int check_down_fig(int i, int j) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return 0;

  int retVal = 0;

  if (ptr_w_game->y + i + 1 <= HIGH_POLE - 1 &&
      ptr_w_game->game.field[ptr_w_game->y + i + 1][ptr_w_game->x + j] == 1) {
    retVal = 1;
  }

  return retVal;
}

void check_down() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return;
  int collide = 0;

  for (int i = 0; i < F_SIZE && !collide; ++i) {
    for (int j = 0; j < F_SIZE && !collide; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1) {
        if (check_down_border(i) || check_down_fig(i, j)) collide = 1;
      }
    }
  }

  if (!collide) {
    ptr_w_game->y += 1;
  } else {
    ptr_w_game->state = ATTACHING;
  }
}

int check_left_border(int j) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return 0;

  int retVal = 0;

  if (ptr_w_game->x + j - 1 == -1) {
    retVal = 1;
  }

  return retVal;
}

int check_left_fig(int i, int j) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return 0;

  int retVal = 0;

  if (ptr_w_game->x + j - 1 >= 0 &&
      ptr_w_game->game.field[ptr_w_game->y + i][ptr_w_game->x + j - 1] == 1) {
    retVal = 1;
  }

  return retVal;
}

void check_left() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return;
  int collide = 0;

  for (int i = 0; i < F_SIZE && !collide; ++i) {
    for (int j = 0; j < F_SIZE && !collide; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1) {
        if (check_left_border(j) || check_left_fig(i, j)) collide = 1;
      }
    }
  }

  if (!collide) ptr_w_game->x -= 1;
}

int check_right_border(int j) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return 0;

  int retVal = 0;

  if (ptr_w_game->x + j + 1 == WIDTH_POLE) {
    retVal = 1;
  }

  return retVal;
}

int check_right_fig(int i, int j) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return 0;

  int retVal = 0;

  if (ptr_w_game->x + j + 1 <= WIDTH_POLE - 1 &&
      ptr_w_game->game.field[ptr_w_game->y + i][ptr_w_game->x + j + 1]) {
    retVal = 1;
  }

  return retVal;
}

void check_right() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return;
  int collide = 0;

  for (int i = 0; i < F_SIZE && !collide; ++i) {
    for (int j = 0; j < F_SIZE && !collide; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1) {
        if (check_right_border(j) || check_right_fig(i, j)) collide = 1;
      }
    }
  }

  if (!collide) ptr_w_game->x += 1;
}

int check_up_border(int i) {
  const WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure) return 0;

  int retVal = 0;

  if (ptr_w_game->y + i <= -1) {
    retVal = 1;
  }

  return retVal;
}

void check_rotate() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;
  int collide = 0;

  for (int i = 0; i < F_SIZE && !collide; ++i) {
    for (int j = 0; j < F_SIZE && !collide; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1) {
        if (ptr_w_game->x + j <= -1) {
          ptr_w_game->x += 1;
        }

        if (ptr_w_game->x + j >= WIDTH_POLE) {
          ptr_w_game->x -= 1;
        }

        if (ptr_w_game->y + i <= -1) {
          ptr_w_game->y += 1;
        }

        if (ptr_w_game->y + i >= HIGH_POLE) {
          collide = 1;
        }
      }
    }
  }

  if (collide) {
    ptr_w_game->rotate -= 1;
    choice_figure(ptr_w_game->figure_id, ptr_w_game->rotate,
                  ptr_w_game->ptr_figure);
  }
}

void check_gameover() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;
  int gameover = 0;

  for (int i = 0; i < F_SIZE && !gameover; ++i) {
    for (int j = 0; j < F_SIZE && !gameover; ++j) {
      if (ptr_w_game->ptr_figure[i][j] == 1) {
        if (check_down_fig(i, j) || check_up_border(i)) {
          gameover = 1;
        }
      }
    }
  }

  if (gameover) ptr_w_game->state = GAMEOVER;
}

void move_down_all_field(int start) {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;
  if (!start) return;

  for (int i = start; i > 0; --i) {
    for (int j = 0; j < WIDTH_POLE; ++j) {
      ptr_w_game->game.field[i][j] = ptr_w_game->game.field[i - 1][j];
    }
  }
  for (int j = 0; j < WIDTH_POLE; ++j) {
    ptr_w_game->game.field[0][j] = 0;
  }
}

void check_line() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();
  if (!ptr_w_game->ptr_figure || !ptr_w_game->game.field) return;

  const int points[5] = {0, 100, 300, 700, 1500};
  int count = 0;

  for (int i = HIGH_POLE - 1; i >= 0; --i) {
    int full_line = 1;

    for (int j = 0; j < WIDTH_POLE; ++j) {
      if (!ptr_w_game->game.field[i][j]) {
        full_line = 0;
      }
    }

    if (full_line) {
      move_down_all_field(i);
      ++i;
      ++count;
    }
  }

  ptr_w_game->game.score += points[count];
  check_speed();
}

void check_speed() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  const int speed[10] = {320, 300, 280, 260, 240, 220, 200, 180, 170, 160};

  int level = ptr_w_game->game.score / 600;
  ptr_w_game->game.level = ((level > 9) ? 9 : level) + 1;
  ptr_w_game->game.speed = speed[level];
}

void check_score() {
  WideGameInfo_t* ptr_w_game = static_wide_game_info();

  if (ptr_w_game->game.score > ptr_w_game->game.high_score) {
    ptr_w_game->game.high_score = ptr_w_game->game.score;

    FILE* f = fopen(FILENAME, "w");
    if (f) {
      fprintf(f, "%d", ptr_w_game->game.score);
      fclose(f);
    }
  }
}