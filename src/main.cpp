#include "main.h"

// Global Variables
static constexpr int FPS = 30;
static constexpr int window_w = 800;
static constexpr int window_h = 450;
static auto window_title = "A super fun game of Tic Tac Toe";

enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Struct to store the game state
struct TicTacToeGame {
    GameState currentState;
    bool playerTurn; // true for Player X, false for Player O
    char board[3][3]; // 3x3 grid for the board
};

void init_game(TicTacToeGame &game) {
    game.currentState = MENU;
    game.playerTurn = true;

    // Initialize the board with empty spaces
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            game.board[row][col] = ' ';
        }
    }
}

void draw_menu() {
    DrawText("Tic Tac Toe", window_w / 2 - MeasureText("Tic Tac Toe", 40) / 2, 100, 40, BLACK);
    DrawText("Press ENTER to Start", window_w / 2 - MeasureText("Press ENTER to Start", 20) / 2, 200, 20, GRAY);
}

// Draw game board. 3x3
void draw_board() {
    constexpr int cell_width = window_w / 3;
    constexpr int cell_height = window_h / 3;

    // Draw vertical lines
    for (int i = 1; i < 3; i++) {
        DrawLine(i * cell_width, 0, i * cell_width, window_h, BLACK);
    }

    // Draw horizontal lines
    for (int i = 1; i < 3; i++) {
        DrawLine(0, i * cell_height, window_w, i * cell_height, BLACK);
    }
}

int main() {
    InitWindow(window_w, window_h, window_title);
    SetTargetFPS(FPS);

    TicTacToeGame game{};
    init_game(game);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Game state logic
        if (game.currentState == MENU) {
            draw_menu();
            if (IsKeyPressed(KEY_ENTER)) {
                game.currentState = PLAYING;
            }
        }
        else if (game.currentState == PLAYING) {
            draw_board();
            // (Gameplay logic will go here)
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}