#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#define WIDTH 10
#define HEIGHT 22
#define VISIBLE_HEIGHT 20

enum Game_Phase
{
    GAME_PHASE_PLAY
};

struct Tetrino
{
    const uint8_t *data;
    const int32_t side;
};

struct Input_State
{
    int8_t dleft;
    int8_t dright;
    int8_t dup;
};

inline Tetrino tetrino(const uint8_t *data, int32_t side)
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

const Tetrino TETRINOS[] = {
    tetrino(TETRINO_1, 4),
    tetrino(TETRINO_2, 2),
    tetrino(TETRINO_3, 3),
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
    Piece_State piece;
    Game_Phase phase;
};

inline uint8_t
matrix_get(const uint8_t *values, int32_t width, int32_t row, int32_t col)
{
    int32_t index = row * width + col;
    return values[index];
}

inline void matrix_set(uint8_t *values, int32_t width, int32_t row, int32_t col, uint8_t value)
{
    int32_t index = row * width + col;
    values[index] = value;
}

inline uint8_t tetrino_get(const Tetrino *tetrino, int32_t row, int32_t col, int32_t rotation)
{
    int32_t side = tetrino->side;
    switch (rotation)
    {
    case 0:
        return tetrino->data[row * side + col];
    case 1:
        return tetrino->data[(side - col - 1) * side + row];
    case 2:
        return tetrino->data[(side - row - 1) * side + (side - col - 1)];
    case 3:
        return tetrino->data[col * side + (side - row - 1)];
    }
    return 0;
}

bool check_piece_valid(Piece_State *piece, const uint8_t *board, int32_t width, int32_t height)
{
    const Tetrino *tetrino = TETRINOS + piece->tetrino_index;
    for (int32_t row = 0; row < height; ++row)
    {
        for (int32_t col = 0; col < width; ++col)
        {
            uint8_t value = tetrino_get(tetrino, row, col, piece->rotation);
            if (value > 0)
            {
                int32_t board_row = piece->offset_row;
                int32_t board_col = piece->offset_col;
                if (board_row < 0)
                {
                    return false;
                }
                if (board_row >= height)
                {
                    return false;
                }
                if (board_col < 0)
                {
                    return false;
                }
                if (board_col >= width)
                {
                    return false;
                }
                if (matrix_get(board, width, board_row, board_col))
                {
                    return false;
                }
            }
        }
        return true;
    }
}

void update_game_play(Game_State *game, const Input_State *input)
{
    Piece_State piece = game->piece;
    if (input->dleft > 0)
    {
        --piece.offset_col;
    }
    if (input->dright > 0)
    {
        ++piece.offset_col;
    }
    if (input->dup > 0)
    {
        piece.rotation = (piece.rotation + 1) % 4;
    }
    if (check_piece_valid(&piece, game->board, WIDTH, HEIGHT))
    {
        game->piece = piece;
    }
}

void update_game(Game_State *game, const Input_State *input)
{
    switch (game->phase)
    {
    case GAME_PHASE_PLAY:
        return update_game_play(game, input);
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return 0;
}