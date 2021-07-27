#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "board.h"
#include "colors.h"

uint8_t tetrino_get(const Tetrino *tetrino, int32_t row, int32_t col, int32_t rotation);
uint8_t check_row_filled(const uint8_t *values, int32_t width, int32_t row);
uint8_t check_row_empty(const uint8_t *values, int32_t width, int32_t row);
int32_t find_lines(const uint8_t *values, int32_t width, int32_t height, uint8_t *lines_out);
void clear_lines(uint8_t *values, int32_t width, int32_t height, const uint8_t *lines);
bool check_piece_valid(const Piece_State *piece, const uint8_t *board, int32_t width, int32_t height);
void merge_piece(Game_State *game);
int32_t random_int(int32_t min, int32_t max);
float get_time_to_next_drop(int32_t level);
void spawn_piece(Game_State *game);
bool soft_drop(Game_State *game);
int32_t compute_points(int32_t level, int32_t line_count);
int32_t min(int32_t x, int32_t y);
int32_t max(int32_t x, int32_t y);
int32_t get_lines_for_next_level(int32_t start_level, int32_t level);
void update_game_start(Game_State *game, const Input_State *input);
void update_game_gameover(Game_State *game, const Input_State *input);
void update_game_line(Game_State *game);
void update_game_play(Game_State *game, const Input_State *input);
void update_game(Game_State *game, const Input_State *input);
void fill_rect(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t width, int32_t height, Color color);
void draw_rect(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t width, int32_t height, Color color);
void draw_string(SDL_Renderer *renderer, TTF_Font *font, const char *text, int32_t x, int32_t y, Text_Align alignment, Color color);
void draw_cell(SDL_Renderer *renderer, int32_t row, int32_t col, uint8_t value, int32_t offset_x, int32_t offset_y, bool outline = false);
void draw_piece(SDL_Renderer *renderer, const Piece_State *piece, int32_t offset_x, int32_t offset_y, bool outline = false);
void draw_board(SDL_Renderer *renderer, const uint8_t *board, int32_t width, int32_t height, int32_t offset_x, int32_t offset_y);
void render_game(const Game_State *game, SDL_Renderer *renderer, TTF_Font *font);
