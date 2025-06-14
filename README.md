# spaceshooter
A small vertical space shooter built using the Jengine game engine. This project was created purely for educational purposes, but I’m happy with the results. It doesn’t have a lot of content, but it’s definitely challenging!

## Screenshots
Some gameplay screenshots

![alt text](https://github.com/jonathaneeckhout/spaceshooter/blob/main/screenshots/menu.png "menu")

![alt text](https://github.com/jonathaneeckhout/spaceshooter/blob/main/screenshots/astroids.png "Astroids")

![alt text](https://github.com/jonathaneeckhout/spaceshooter/blob/main/screenshots/enemies.png "Enemies")


## Requirements

- CMake ≥ 3.16
- C++20 compiler (`clang++`)

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

## Controls

* Movement: WSAD
* Shooting: numpad 1
* Selecting: Enter
