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

## 🛠️ Creating Custom Levels

Custom levels are expected to be in the form of a .txt file consisting solely of the ASCII layout of the level. You have the option of manually typing a level out, of course. However, I HIGHLY recommend making use of the following open-source software - a website that allows you to paint in a canvas using standard characters:

### [ASCII Art Paint by Kirilllive](https://kirilllive.github.io/ASCII_Art_Paint/ascii_paint.html)

This tool works amazingly well for creating levels without having to painstakingly shape out the level geometry manually. You can find the repository for the site [here.](https://github.com/Kirilllive/ASCII_Art_Paint)

1. Unlock and resize the canvas as you see fit. The game *should* support any canvas dimensions, but I haven't tested very large canvas sizes.
    - Use the canvas height to set the total length of the level. Use the canvas width to define the *total horizontal bound* for the level. That is, if you wish to make use of the horizontal scrolling feature, set the width to account for the furthest out horizontally the level may be.
2. If required, change the symbol palette to include the `#` and `.` symbols. These will define the play area.
3. Paint out the level walls using the Pencil tool after selecting the `#` symbol.
4. Fill in the interior area of the level using the Bucket tool after selecting the `.` symbol. This will define the space the player character can move around in.
5. Make any desired manual adjustments.
6. Once you've drawn out your desired level, click on the `Copy Text` button on the top ribbon. This will copy the ENTIRE canvas space to your clipboard.
7. Paste the level text into a `.txt` file, and name it whatever you wish (not tested, but I don't recommend including spaces in the name).


For an example of horizontally scrolling level geometry, reference `levelscroll.txt`.

## 📁 Adding Custom Levels

1. Place your custom level files (text files) in the game's root directory.
2. Follow the on-screen prompt, selecting "Custom file" and entering your filename explicitly.

## 🎯 Controls

**Horizontal movement in either direction continues until either the opposite direction is input or
Spacebar is pressed.**

- **Left**: `a` or left arrow
- **Right**: `d` or right arrow
- **Stop horizontal movement**: Spacebar
- **Quit game**: `q`

---

**Enjoy!**