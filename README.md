# spaceshooter
A small vertical spaceshooter using the jeninge game engine. This project was purely made for educational purposes but I am happy with the results. It's doesn't have a lot of game content but it is pretty hard!

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