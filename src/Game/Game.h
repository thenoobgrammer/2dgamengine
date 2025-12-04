#ifndef INC_2DGAMEENGINE_GAME_H
#define INC_2DGAMEENGINE_GAME_H

#include "../ECS/ECS.h"
#include <SDL.h>

#include "../AssetStore/AssetStore.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    int msPreviousFrame = 0;
    SDL_Window* win;
    SDL_Renderer* renderer;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup() const;
    void ProcessInput();
    void Update();
    void Render() const;
    void Destroy() const;

    int windowWidth;
    int windowHeight;
};

#endif //INC_2DGAMEENGINE_GAME_H