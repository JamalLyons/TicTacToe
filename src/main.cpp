#include "main.h"

// Global Variables
static constexpr int FPS = 30;
static constexpr int window_w = 800;
static constexpr int window_h = 450;
static auto window_title = "CodingWithJamal - Tic Tac Toe";

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
    char winner; // 'X' or 'O' or ' ' for no winner
};

void init_game(TicTacToeGame &game) {
    game.currentState = MENU;
    game.playerTurn = true;
    game.winner = ' ';

    // Initialize the board with empty spaces
    for (auto & row : game.board) {
        for (char & col : row) {
            col = ' ';
        }
    }
}

void draw_menu() {
    DrawText("Tic Tac Toe", window_w / 2 - MeasureText("Tic Tac Toe", 40) / 2, 100, 40, BLACK);
    DrawText("Press ENTER to Start", window_w / 2 - MeasureText("Press ENTER to Start", 20) / 2, 200, 20, GRAY);
}

// Draw game board. 3x3
void draw_board(const TicTacToeGame &game) {
    constexpr int cell_width = window_w / 3;
    constexpr int cell_height = window_h / 3;

    // Draw grid lines
    for (int i = 1; i < 3; i++) {
        DrawLine(i * cell_width, 0, i * cell_width, window_h, BLACK);
        DrawLine(0, i * cell_height, window_w, i * cell_height, BLACK);
    }

    // Draw symbols
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            const int x = col * cell_width + cell_width / 2;
            const int y = row * cell_height + cell_height / 2;

            if (game.board[row][col] == 'X') {
                DrawText("X", x - 20, y - 20, 40, RED);
            } else if (game.board[row][col] == 'O') {
                DrawText("O", x - 20, y - 20, 40, BLUE);
            }
        }
    }
}

// Check if a player has won the game
bool check_winner(TicTacToeGame &game) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (game.board[i][0] == game.board[i][1] && game.board[i][1] == game.board[i][2] && game.board[i][0] != ' ') {
            game.winner = game.board[i][0];
            return true;
        }
        if (game.board[0][i] == game.board[1][i] && game.board[1][i] == game.board[2][i] && game.board[0][i] != ' ') {
            game.winner = game.board[0][i];
            return true;
        }
    }

    // Check diagonals
    if (game.board[0][0] == game.board[1][1] && game.board[1][1] == game.board[2][2] && game.board[0][0] != ' ') {
        game.winner = game.board[0][0];
        return true;
    }
    if (game.board[0][2] == game.board[1][1] && game.board[1][1] == game.board[2][0] && game.board[0][2] != ' ') {
        game.winner = game.board[0][2];
        return true;
    }

    return false;
}

bool check_draw(const TicTacToeGame &game) {
    for (const auto row : game.board) {
        for (int col = 0; col < 3; col++) {
            if (row[col] == ' ') {
                return false; // Found an empty cell
            }
        }
    }
    return true; // No empty cells
}

// Handle user input when clicking on the board
void handle_input(TicTacToeGame &game) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        constexpr int cell_width = window_w / 3;
        constexpr int cell_height = window_h / 3;

        Vector2 mouse = GetMousePosition();
        const int col = mouse.x / cell_width;
        const int row = mouse.y / cell_height;

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && game.board[row][col] == ' ') {
            game.board[row][col] = game.playerTurn ? 'X' : 'O';
            game.playerTurn = !game.playerTurn;

            if (check_winner(game)) {
                game.currentState = GAME_OVER;
            } else if (check_draw(game)) {
                game.currentState = GAME_OVER;
                game.winner = ' '; // No winner
            }
        }
    }
}

void draw_game_over(const TicTacToeGame &game) {
    const char *message = (game.winner == ' ') ? "It's a Draw!" : TextFormat("%c Wins!", game.winner);
    DrawText(message, window_w / 2 - MeasureText(message, 40) / 2, 200, 40, BLACK);
    DrawText("Press ENTER to Restart", window_w / 2 - MeasureText("Press ENTER to Restart", 20) / 2, 300, 20, GRAY);
}

// UI alert to show whose turn it is in the game
void draw_status(const TicTacToeGame &game) {
    constexpr int status_height = 50;

    // Draw a rectangle for the status bar
    DrawRectangle(0, window_h - status_height, window_w, status_height, LIGHTGRAY);

    // Display the current player's turn
    const char *status_message = game.playerTurn ? "Player X's Turn" : "Player O's Turn";
    DrawText(
        status_message,
        window_w / 2 - MeasureText(status_message, 20) / 2,
        window_h - status_height + 15,
        20,
        BLACK
    );
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
        switch (game.currentState) {
            case MENU:
                draw_menu();
            if (IsKeyPressed(KEY_ENTER)) {
                game.currentState = PLAYING;
            }
            break;

            case PLAYING:
                draw_board(game);
                draw_status(game);
                handle_input(game);
            break;

            case GAME_OVER:
                draw_game_over(game);
            if (IsKeyPressed(KEY_ENTER)) {
                init_game(game);
            }
            break;

            default:
                break;
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}