# ASCII-Runner
A basic runner game built in C++ for Linux and rendered directly to the command line.


## 🚩 Dependencies
This game requires:

- **ncurses** library
- **g++** compiler
- **make** (optional)

## ✅ Installation (Ubuntu):

Execute the following in a terminal:

```bash
sudo apt update
sudo apt install build-essential libncurses5-dev libncursesw5-dev
```

This explicitly installs:

- `build-essential` (contains `g++` compiler and development tools)
- `ncurses` development libraries

## 🛠️ Building the Game

After cloning the project, navigate to the root directory (containing `main.cpp` and `Makefile`) and run the following:

```bash
make
```

This will build the game executable.

**If you don't have a Makefile**, build manually with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -lncurses -o ascii-runner
```

## 🎮 Running the Game

Run the executable with:

```bash
./ascii-runner
```

Follow on-screen prompts to select your desired level.


## 📁 Adding Custom Levels

- Place your custom level files (text files) in the game's root directory.
- Follow the on-screen prompt, selecting "Custom file" and entering your filename explicitly.

## 🎯 Controls

**Horizontal movement in either direction continues until either the opposite direction is input or
Spacebar is pressed.**

- **Left**: `a` or left arrow
- **Right**: `d` or right arrow
- **Stop horizontal movement**: Spacebar
- **Quit game**: `q`

---

**Enjoy!**