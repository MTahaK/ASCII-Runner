#include <ncurses.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "level.h"

/* FIRST DRAFT BASED OFF OF CODE FROM CHATGPT */


// Game constants
const int FPS = 30;
const double FRAME_TIME = 1000.0 / FPS; // in milliseconds

// The map dimensions
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 40;

// Player attributes
int playerX = MAP_WIDTH / 2;   // Start horizontally centered
int playerY = level.size() - 2;  // Player starts within the level

// The "camera" or the forward progress measure
int cameraY = 0;  // We'll treat the top as y=0, increasing downward



// Double buffers: We'll store two 2D char arrays
char frontBuffer[MAP_HEIGHT][MAP_WIDTH];
char backBuffer[MAP_HEIGHT][MAP_WIDTH];

// Helper to copy one buffer to another
void copyBuffer(char dest[MAP_HEIGHT][MAP_WIDTH], char src[MAP_HEIGHT][MAP_WIDTH]) {
    // Simple character by character copy, row major
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++){
            dest[i][j] = src[i][j];
        }
    }
}

// Initialize buffers
void clearBuffer(char buffer[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            buffer[i][j] = ' ';
        }
    }
}

// Render the backBuffer to the screen using ncurses
void renderBuffer(char buffer[MAP_HEIGHT][MAP_WIDTH]) {
    // Move cursor to (0,0) in ncurses
    move(0, 0);

    // NOTE: There is a potential weakness here - this function
    // assumes that the 'canvas' dimensions match MAP_HEIGHT and
    // MAP_WIDTH.
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            addch(buffer[i][j]);
        }
        // After all chars for a row are copied, move to next row
        addch('\n');
    }
}

// Populate the backBuffer based on the level data, the camera offset, and the player's position
// The backBuffer is essentially the next state of all objects on the screen.
void updateBackBuffer() {
    clearBuffer(backBuffer);

    // Draw level, offset by cameraY
    // We'll treat the top row of the screen as cameraY in the level
    for (int screenY = 0; screenY < MAP_HEIGHT; screenY++) {
        int levelY = screenY + cameraY;
        // Given we only scroll in the Y direction, we only perform
        // bounds checking in the vertical direction.
        if (levelY < 0 || levelY >= (int)level.size()) {
            // outside the level, just fill with blanks
            for (int x = 0; x < MAP_WIDTH; x++) {
                backBuffer[screenY][x] = ' ';
            }
        } else {
            for (int x = 0; x < MAP_WIDTH; x++) {
                // If within bounds, fill using the level geometry
                backBuffer[screenY][x] = level[levelY][x];
            }
        }
    }

    // Draw the player if they're in view
    int playerScreenY = playerY - cameraY;
    if (playerScreenY >= 0 && playerScreenY < MAP_HEIGHT) {
        backBuffer[playerScreenY][playerX] = '^';
    }
}

bool checkCollision() {
    int levelY = playerY;
    if (levelY >= 0 && levelY < (int)level.size()) {
        if (level[levelY][playerX] == '#') {
            return true; // collision with a wall
        }
        // Check if collision on either side of player
        // playerX > 0, playerX < MAP_WIDTH always
        // for altlevel, where walls use a different character
        if(level[levelY][playerX - 1] == '|' || level[levelY][playerX + 1] == '|'){
            return true;
        }
    }
    return false;
}

int main() {
    // Initialize ncurses
    initscr();
    noecho();            // Don't echo typed characters
    cbreak();            // Disable line buffering
    curs_set(FALSE);     // Hide cursor
    keypad(stdscr, TRUE); // Capture special keys (arrows, etc.)
    nodelay(stdscr, TRUE); // Non-blocking getch()

    // Clear the front & back buffers initially
    clearBuffer(frontBuffer);
    clearBuffer(backBuffer);

    bool running = true;
    bool win = false; // if the player reaches the end

    while (running) {
        auto frameStart = std::chrono::steady_clock::now();

        // 1. Input
        int ch = getch();
        if (ch != ERR) {
            switch (ch) {
                case KEY_LEFT:
                case 'a':
                    if (playerX > 1) {
                        playerX--;
                    }
                    break;
                case KEY_RIGHT:
                case 'd':
                    if (playerX < MAP_WIDTH - 2) {
                        playerX++;
                    }
                    break;
                case 'q':
                    // Quit
                    running = false;
                    break;
                default:
                    break;
            }
        }

        // 2. Update logic
        // The player automatically moves "forward" => downward in this example
        playerY--;

        // Or if you want them to move up the screen, you can do playerY--, 
        // but let's assume y=0 is the top, so we might do playerY--;
        // We'll invert it here so "forward" means up on the screen.
        // We'll keep the camera locked to the player’s position
        cameraY = playerY - (MAP_HEIGHT / 2);
        if (cameraY < 0) cameraY = 0;

        // Check collision
        if (checkCollision()) {
            running = false;
        }

        // Check if we've reached the end of the level
        // Let's say the last row of the level is row 14 in 'level' vector, 
        // so if the player has gone above row 1 or 0, they've "won".
        if (playerY <= 0) {
            running = false;
            win = true;
        }

        // 3. Render
        updateBackBuffer();  // build the new backBuffer
        renderBuffer(backBuffer); // draw backBuffer to the screen
        refresh(); // ncurses refresh

        // 4. Double buffering: copy backBuffer into frontBuffer if you want to compare changes, etc.
        // Not strictly necessary, but here's where you'd do it:
        copyBuffer(frontBuffer, backBuffer);

        // 5. Frame time control
        auto frameEnd = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(frameEnd - frameStart).count();
        if (elapsed < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(FRAME_TIME - elapsed)));
        }
    }

    // Cleanup
    endwin();

    // Show win/lose result in normal console mode:
    if (win) {
        printf("You win!\n");
    } else {
        printf("Game over!\n");
    }

    return 0;
}