# 2D Game Engine

## Dependencies

### macOS
```bash
brew install sdl2 sdl2_image sdl2_ttf lua jsoncpp
```

### Windows
Place SDL2 (including SDL2_image and SDL2_ttf) at `C:/SDL2`. Lua and jsoncpp are bundled in `libs/`.

## Build & Run

### Generate the compile_commands.json
```bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cp build/compile_commands.json .
```

### Build & run the game
```bash
cmake -B build # ./build folder created
cmake --build build # compile
```

**macOS:** `./build/2dgameengine`

**Windows:** `.\build\2dgameengine.exe`
