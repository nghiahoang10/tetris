#include <bits/stdc++.h>

#define WIDTH 10
#define HEIGHT 22
#define VISIBLE_HEIGHT 20
#define GRID_SIZE 30
#define ARRAY_COUNT(x) (sizeof(x) / sizeof((x)[0]))

const uint8_t FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1};

const float TARGET_SECONDS_PER_FRAME = 1.f / 60.f;

struct Tetrino
{
    const uint8_t *data;
    const int32_t side;
};

inline Tetrino
tetrino(const uint8_t *data, int32_t side)
{
    return {data, side};
}

const uint8_t TETRINO_1[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0};

const uint8_t TETRINO_2[] = {
    2, 2,
    2, 2};

const uint8_t TETRINO_3[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0};

const uint8_t TETRINO_4[] = {
    0, 4, 4,
    4, 4, 0,
    0, 0, 0};

const uint8_t TETRINO_5[] = {
    5, 5, 0,
    0, 5, 5,
    0, 0, 0};

const uint8_t TETRINO_6[] = {
    6, 0, 0,
    6, 6, 6,
    0, 0, 0};

const uint8_t TETRINO_7[] = {
    0, 0, 7,
    7, 7, 7,
    0, 0, 0};

const Tetrino TETRINOS[] = {
    tetrino(TETRINO_1, 4),
    tetrino(TETRINO_2, 2),
    tetrino(TETRINO_3, 3),
    tetrino(TETRINO_4, 3),
    tetrino(TETRINO_5, 3),
    tetrino(TETRINO_6, 3),
    tetrino(TETRINO_7, 3),
};

enum Game_Phase
{
    GAME_PHASE_START,
    GAME_PHASE_PLAY,
    GAME_PHASE_LINE,
    GAME_PHASE_GAMEOVER
};

struct Piece_State
{
    uint8_t tetrino_index;
    int32_t offset_row;
    int32_t offset_col;
    int32_t rotation;
};

struct Game_State
{
    uint8_t board[WIDTH * HEIGHT];
    uint8_t lines[HEIGHT];
    int32_t pending_line_count;

    Piece_State piece;

    Game_Phase phase;

    int32_t start_level;
    int32_t level;
    int32_t line_count;
    int32_t points;

    float next_drop_time;
    float highlight_end_time;
    float time;
};

struct Input_State
{
    uint8_t left;
    uint8_t right;
    uint8_t up;
    uint8_t down;

    uint8_t a;

    int8_t dleft;
    int8_t dright;
    int8_t dup;
    int8_t ddown;
    int8_t da;
};

enum Text_Align
{
    TEXT_ALIGN_LEFT,
    TEXT_ALIGN_CENTER,
    TEXT_ALIGN_RIGHT
};