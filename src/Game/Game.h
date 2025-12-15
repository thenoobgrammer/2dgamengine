#ifndef INC_2DGAMEENGINE_GAME_H
#define INC_2DGAMEENGINE_GAME_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"
#include <SDL.h>

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    bool debugColliders;
    int msPreviousFrame = 0;
    SDL_Window* win;
    SDL_Renderer* renderer;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup();
    void ProcessInput();
    void Update();
    void Render() const;
    void Destroy() const;
    void LoadLevel(int level);

    int windowWidth;
    int windowHeight;
};

#endif //INC_2DGAMEENGINE_GAME_H