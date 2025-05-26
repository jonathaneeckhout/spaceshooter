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
