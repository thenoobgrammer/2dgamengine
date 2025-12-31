#ifndef INC_2DGAMEENGINE_GAME_H
#define INC_2DGAMEENGINE_GAME_H

#include <SDL.h>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Factory/EnemyFactory.h"
#include "../Factory/LevelFactory.h"

const int FPS = 60;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    bool debugColliders;
    int msPreviousFrame = 0;
    SDL_Window* win;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;
    std::unique_ptr<EnemyFactory> enemyFactory;
    std::unique_ptr<LevelFactory> levelFactory;

    void RegisterSystems() const;
    void LoadAssets() const;
    void LoadFonts() const;
    void SpawnEntities(const int level) const;
    void SpawnPlayer() const;
    void SpawnTank() const;
    void SpawnTruck() const;
    void SpawnUI() const;

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render() const;
    void Destroy() const;
    void LoadLevel(int level) const;
    void Setup();

    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;
    static int mouseX;
    static int mouseY;
};

#endif //INC_2DGAMEENGINE_GAME_H