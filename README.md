# spaceshooter
A small vertical spaceshooter using the jeninge game engine.

## Requirements

- CMake ≥ 3.16
- C++17 compiler (`clang++`)

Example using Ubuntu
```bash
sudo apt install clang
sudo snap install cmake --classic
```

## Build instructions

Fetch the sources
```bash
git clone https://github.com/jonathaneeckhout/spaceshooter.git
cd spaceshooter
```

Generate the embedded resources
```bash
./tools/generate_embedded_assets.sh
```

Create the build Directory
``` bash
cmake -B build
```

Build the game
``` bash
cmake --build build
```

## How to run

Run the game
```bash
./build/Spaceshooter
```

## To-do
- Add game loop
    - Add event when entity is destroyed
    - Listen to this event for player and last enemy
    - If player dies -> game over
    - If last enemy dies -> level complete
- Display Highscores
- Add components to player class
- Turn bullets to type objects
- Create settings menu
    - Enable disable music
    - Keybindings
- Add 2 extra levels
- Replace prototypes with assets
- (Optional) make support for bytecode to easily create new levels
