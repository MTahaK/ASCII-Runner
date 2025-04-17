#include <ncurses.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "level.h"


// auto level = level1;
// auto level = readLevelFromFile("levelscroll.txt");
// Game constants
const int FPS = 30;
const double FRAME_TIME = 1000.0 / FPS; // in milliseconds

// The map dimensions
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 40;

// // Player attributes
// int playerX = level[level.size() - 2].size() / 2;   // Start horizontally centered
// int playerY = level.size() - 1;  // Player starts within the level

// // The "camera" or the forward progress measure
// int cameraY = 0;  // We'll treat the top as y=0, increasing downward
// int cameraX = 0;  // We'll treat the left as x=0, increasing rightward

// Declare global variables without initialization 
std::vector<std::string> level;
int playerX;
int playerY;
int cameraX;
int cameraY;


// Double buffering for rendering without flicker
char frontBuffer[MAP_HEIGHT][MAP_WIDTH];
char backBuffer[MAP_HEIGHT][MAP_WIDTH];

// Helper to copy one buffer to another
void copyBuffer(char dest[MAP_HEIGHT][MAP_WIDTH], char src[MAP_HEIGHT][MAP_WIDTH]) {
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
// void updateBackBuffer() {
//     clearBuffer(backBuffer);

//     // Draw level, offset by cameraY
//     // We'll treat the top row of the screen as cameraY in the level
//     for (int screenY = 0; screenY < MAP_HEIGHT; screenY++) {
//         int levelY = screenY + cameraY;
//         for(int screenX = 0; screenX < MAP_WIDTH; screenX++){
//             int levelX = screenX + cameraX;
//             if (levelY < 0 || levelY >= (int)level.size()) {
//                 // outside the level, just fill with blanks
//                 for (int x = 0; x < MAP_WIDTH; x++) {
//                     backBuffer[screenY][x] = ' ';
//                 }
//             } else {
//                 for (int x = 0; x < MAP_WIDTH; x++) {
//                     // If within bounds, fill using the level geometry
//                     backBuffer[screenY][x] = level[levelY][x];
//                 }
//             }
//         }
//         // Given we only scroll in the Y direction, we only perform
//         // bounds checking in the vertical direction.
        
//     }

//     // Draw the player if they're in view
//     int playerScreenY = playerY - cameraY;
//     if (playerScreenY >= 0 && playerScreenY < MAP_HEIGHT) {
//         backBuffer[playerScreenY][playerX] = '^';
//     }

//     // Horizontal direction for horizontal scrolling
//     for(int screenX = 0; screenX < MAP_WIDTH; screenX++){
//         int levelX = screenX + cameraX;
//         if(levelX < 0 || levelX >= (int)level[0].size()){
//             for(int y = 0; y < MAP_HEIGHT; y++){
//                 backBuffer[y][screenX] = ' ';
//             }
//         } else {
//             for(int y = 0; y < MAP_HEIGHT; y++){
//                 backBuffer[y][screenX] = level[y][levelX];
//             }
//         }
//     }

//     // Draw the player if they're in view
//     int playerScreenX = playerX - cameraX;
//     if (playerScreenX >= 0 && playerScreenX < MAP_WIDTH) {
//         backBuffer[playerY][playerScreenX] = '^';
//     }
// }

// Revised update function for horizontal scrolling support
void updateBackBuffer() {
    clearBuffer(backBuffer);

    // Single double-nested loop for Y and X
    for (int screenY = 0; screenY < MAP_HEIGHT; screenY++) {
        int levelY = screenY + cameraY;

        for (int screenX = 0; screenX < MAP_WIDTH; screenX++) {
            int levelX = screenX + cameraX;

            // Check vertical bounds
            if (levelY < 0 || levelY >= (int)level.size()) {
                backBuffer[screenY][screenX] = ' ';
            } else {
                // Check horizontal bounds for this row (levelY is current row)
                if (levelX < 0 || levelX >= (int)level[levelY].size()) {
                    backBuffer[screenY][screenX] = ' ';
                } else {
                    // Copy the character from the level data
                    backBuffer[screenY][screenX] = level[levelY][levelX];
                }
            }
        }
    }

    // Draw the player if it's in view
    int playerScreenY = playerY - cameraY;
    int playerScreenX = playerX - cameraX;
    if (playerScreenY >= 0 && playerScreenY < MAP_HEIGHT
        && playerScreenX >= 0 && playerScreenX < MAP_WIDTH)
    {
        backBuffer[playerScreenY][playerScreenX] = '^';
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
    nodelay(stdscr, FALSE); // Accept user input


    // Prompt for level type
    mvprintw(MAP_HEIGHT / 2 - 2, (MAP_WIDTH / 2) - 15, "Select level source:");
    mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2) - 15, "1 - Built-in levels");
    mvprintw(MAP_HEIGHT / 2 + 1, (MAP_WIDTH / 2) - 15, "2 - Custom file");
    mvprintw(MAP_HEIGHT / 2 + 3, (MAP_WIDTH / 2) - 15, "Enter choice (1/2): ");
    refresh();

    int choice = getch();

    char levelInput[100];

    clear();

    if (choice == '1') {
        mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2) - 15, "Enter built-in level name:");
        refresh();
        echo();
        getnstr(levelInput, 99);
        noecho();

        std::string chosenLevel(levelInput);

        if (chosenLevel == "level1") level = level1;
        else if (chosenLevel == "level2") level = level2;
        else if (chosenLevel == "level3") level = level3;
        else if (chosenLevel == "level4") level = level4;
        else if (chosenLevel == "level5") level = level5;
        else if (chosenLevel == "altlevel") level = altlevel;
        else {
            endwin();
            printf("Invalid built-in level name!\n");
            return 1;
        }
    }
    else if (choice == '2') {
        mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2) - 15, "Enter level file path:");
        refresh();
        echo();
        getnstr(levelInput, 99);
        noecho();

        level = readLevelFromFile(std::string(levelInput));
    }
    else {
        endwin();
        printf("Invalid choice!\n");
        return 1;
    }

    // Initialize player and camera explicitly based on loaded level
    playerX = level[level.size() - 2].size() / 2;
    playerY = level.size() - 1;
    cameraY = 0;
    cameraX = 0;

    // Prompt to start the game
    clear();
    mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2) - 10, "Press any key to start...");
    refresh();
    getch();

    // Add a 3-second countdown explicitly before game starts
    for (int countdown = 3; countdown > 0; countdown--) {
        clear();
        mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2), "%d", countdown);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Display "Go!" explicitly
    clear();
    mvprintw(MAP_HEIGHT / 2, (MAP_WIDTH / 2) - 1, "Go!");
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    nodelay(stdscr, TRUE); // Set non-blocking for gameplay
    
    // Clear the front & back buffers initially
    clearBuffer(frontBuffer);
    clearBuffer(backBuffer);

    bool running = true;
    bool win = false; // if the player reaches the end
    bool lose = false; // if the player collides with a wall
    bool dir_pressed = false;
    int last_key = 0;

    
    while (running) {
        auto frameStart = std::chrono::steady_clock::now();
        // 1. Input
        int ch = getch(); // Non-blocking due to nodelay()
        if (ch != ERR) {
            while(getch() == ch);
        }
            size_t rowWidth = level[playerY].size();
            if(last_key != 0){
                // Continue moving in the last direction without any key press
                if( last_key == 'a' || last_key == KEY_LEFT){
                    if (playerX > 1) {
                        playerX--; // Minimal movement
                    }
                }
                if( last_key == 'd' || last_key == KEY_RIGHT){
                    if (playerX < (int)rowWidth - 1) {
                        playerX++;
                    }
                }

            }
            switch (ch) {
                // Idea: SHIFT+Arrow Key moves player 2 spaces left or right?
                case KEY_LEFT:
                case 'a':
                    if (playerX > 1) {
                        // Check if possible to move the player 2 spots left instead
                        // if (playerX > 2 && level[playerY][playerX - 2] != '#') {
                        //     playerX -= 2;
                        // } else 
                        if(!dir_pressed || last_key == 'd' || last_key == KEY_RIGHT){ 
                            // If the player is not moving or was moving right, allow left movement
                            playerX--; // Minimal movement
                            last_key = ch;
                            dir_pressed = true;
                        }
                    }
                    break;
                case KEY_RIGHT:
                case 'd':
                    if (playerX < (int)rowWidth - 1) {
                        // Check if possible to move the player 2 spots right instead
                        // if (playerX < MAP_WIDTH - 3 && level[playerY][playerX + 2] != '#') {
                        //     playerX += 2;
                        // } else 
                        if(!dir_pressed || last_key == 'a' || last_key == KEY_LEFT){
                            // If the player is not moving or was moving left, allow right movement
                            playerX++;
                            last_key = ch;
                            dir_pressed = true;
                        }
                    }
                    break;
                case 'q':
                    // Quit
                    running = false;
                    endwin();
                    printf("Game quit by user.\n");
                    return 0;
                case ' ':
                    // If spacebar is pressed, stop the sideways movement
                    last_key = 0;
                    dir_pressed = false;
                    break;
                default:
                    break;
            }
        

        // 2. Update logic
        // The player automatically moves "forward" => upward in this example
        // (playerY decreases as the player moves up)
        playerY--;

        cameraY = playerY - (MAP_HEIGHT / 2);
        if (cameraY < 0) cameraY = 0;

        // Deadzone is computed as 5 pixels on either side of the center
        // of the screen, so the player can move left/right without moving the camera
        int deadZoneLeft  = (MAP_WIDTH / 2) - 5;    
        int deadZoneRight = (MAP_WIDTH / 2) + 5;
        
        
        // 1. Calculate the world coordinates for the dead zone edges
        int worldDeadZoneLeft  = cameraX + deadZoneLeft;
        int worldDeadZoneRight = cameraX + deadZoneRight;

        // 2. If the player crosses left boundary, shift camera left
        if (playerX < worldDeadZoneLeft) {
            cameraX -= (worldDeadZoneLeft - playerX);
        }
        // 3. If player crosses right boundary, shift camera right
        else if (playerX > worldDeadZoneRight) {
            cameraX += (playerX - worldDeadZoneRight);
        }

        // 4. Clamp camera so it doesn’t go negative or past the level’s max width
        if (cameraX < 0) cameraX = 0;
        

        // Check collision
        if (checkCollision()) {
            running = false;
            lose = true;
        }

        // Check if we've reached the end of the level
        // ie if the last row of the level is row 14 in 'level' vector, 
        // so if the player has gone above row 1 or 0, they've "won".
        if (playerY <= 0) {
            running = false;
            win = true;
        }

        // 3. Render
        updateBackBuffer();  // build the new backBuffer
        renderBuffer(backBuffer); // draw backBuffer to the screen
        refresh(); // ncurses refresh

        // 4. Double buffering: copy backBuffer into frontBuffer
        copyBuffer(frontBuffer, backBuffer);

        // 5. Frame time control
        auto frameEnd = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double, std::milli>(frameEnd - frameStart).count();
        if (elapsed < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(FRAME_TIME - elapsed)));
        }
        if (win) {
            endwin();
            printf("You win! Would you like to play again?\n");
        } else if (lose) {
            endwin();
            printf("Game over!\n");
        }
    }
    return 0;
}