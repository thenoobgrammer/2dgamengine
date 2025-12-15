#include "Game.h"

#include <fstream>

#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>

#include "../Components/BoxColliderComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardMovementSystem.h"

class AnimationComponent;

Game::Game() {
  isRunning = false;
  debugColliders = false;
  registry = std::make_unique<Registry>();
  assetStore = std::make_unique<AssetStore>();
  eventBus = std::make_unique<EventBus>();
  Logger::Log("Game constructor called");
}

Game::~Game() {
  Logger::Log("Game destructor called");
}

void Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::Log("SDL_Init error");
    return;
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 1920;//displayMode.w;
  windowHeight = 1080;//displayMode.h;
  win = SDL_CreateWindow(
    "2d Game Engine",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    windowWidth,
    windowHeight,
    SDL_WINDOW_BORDERLESS);
  if (!win) {
    Logger::Err("SDL_CreateWindow error");
    return;
  }

  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    Logger::Err("SDL_CreateRenderer error");
  }

  // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetWindowSize(win, windowWidth, windowHeight);
  isRunning = true;
}

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          isRunning = false;
        } else if (event.key.keysym.sym == SDLK_d) {
          debugColliders = !debugColliders;
        }
        eventBus->Emit<KeyPressedEvent>(event.key.keysym.sym);
        break;
    }
  }
}

void Game::LoadLevel(const int level) {
  // Add the systems that need to be processed in our game
  registry->AddSystem<MovementSystem>();
  registry->AddSystem<RenderSystem>();
  registry->AddSystem<AnimationSystem>();
  registry->AddSystem<CollisionSystem>();
  registry->AddSystem<DamageSystem>();
  registry->AddSystem<KeyboardMovementSystem>();

  // Adding assets to the assets store
  assetStore->LoadTexture(renderer, "chopper-image", "../assets/images/chopper.png");
  assetStore->LoadTexture(renderer, "tank-image", "../assets/images/tank-panther-right.png");
  assetStore->LoadTexture(renderer, "truck-image", "../assets/images/truck-ford-right.png");
  assetStore->LoadTexture(renderer, "radar-image", "../assets/images/radar.png");
  assetStore->LoadTexture(renderer, "tilemap-image", "../assets/tilemaps/jungle.png");

  // TODO: Load the tilemaps
  //  We need to load the tilemap textures from ./assets/tilemaps/jungle.png
  int tileSize = 32;
  double tileScale = 2.0;
  int mapNumCols = 25;
  int mapNumRows = 20;
  std::fstream mapFile;
  mapFile.open("../assets/tilemaps/jungle.map");

  for (int y = 0; y < mapNumRows; y++) {
    for (int x = 0; x < mapNumCols; x++) {
      char ch;
      mapFile.get(ch);
      int srcRectY = std::atoi(&ch) * tileSize;
      mapFile.get(ch);
      int srcRectX = std::atoi(&ch) * tileSize;
      mapFile.ignore();

      Entity tile = registry->CreateEntity();
      tile.AddComponent<TransformComponent>(glm::vec2(x*tileScale*tileSize, y*tileScale*tileSize), glm::vec2(tileScale, tileScale), 0.0);
      tile.AddComponent<SpriteComponent>("tilemap-image", 0, tileSize, tileSize, srcRectX, srcRectY);
    }
  }
  mapFile.close();

  // Create the entity
  Entity chopper = registry->CreateEntity();
  chopper.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
  chopper.AddComponent<RigidBodyComponent>(glm::vec2(25.0, 0.0));
  chopper.AddComponent<SpriteComponent>("chopper-image", 2, 32, 32);
  chopper.AddComponent<AnimationComponent>(2, 10, true);

  Entity radar = registry->CreateEntity();
  radar.AddComponent<TransformComponent>(glm::vec2(windowWidth - 100.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
  radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
  radar.AddComponent<SpriteComponent>("radar-image", 2, 64, 64);
  radar.AddComponent<AnimationComponent>(8, 15, true);

  Entity tank = registry->CreateEntity();
  tank.AddComponent<TransformComponent>(glm::vec2(100.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
  tank.AddComponent<RigidBodyComponent>(glm::vec2(-30.0, 0.0));
  tank.AddComponent<SpriteComponent>("tank-image", 2, 32, 32);
  tank.AddComponent<BoxColliderComponent>(32, 32);

  Entity truck = registry->CreateEntity();
  truck.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
  truck.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
  truck.AddComponent<SpriteComponent>("truck-image", 1, 32, 32);
  truck.AddComponent<BoxColliderComponent>(32, 32);
}

void Game::Setup() {
  LoadLevel(1);
}

void Game::Update() {
  //  Waste time to let each frame reach its intended MS_PER_FRAME cap
  int timeToWait = MILLISECONDS_PER_FRAME - (SDL_GetTicks() - msPreviousFrame);
  if (timeToWait > 0 && timeToWait < MILLISECONDS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  // Difference in ticks since the last frame, converted to seconds
  double deltaTime = (SDL_GetTicks() - msPreviousFrame) / 1000.0;

  msPreviousFrame = SDL_GetTicks();

  // Reset all event handlers for the current frame
  eventBus->Reset();

  // Perform subscriptions of the events of all systems
  registry->GetSystem<DamageSystem>().Subscribe(eventBus);
  registry->GetSystem<KeyboardMovementSystem>().Subscribe(eventBus);

  // Update the registry to process the netities that are waiting to be created/deleted
  registry->Update();

  // Ask all systems to update
  registry->GetSystem<MovementSystem>().Update(deltaTime);
  registry->GetSystem<AnimationSystem>().Update();
  registry->GetSystem<CollisionSystem>().Update(eventBus);

}

void Game::Render() const {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

  if (debugColliders) {
    registry->GetSystem<CollisionSystem>().RenderCollisionBox(renderer);
  }

  SDL_RenderPresent(renderer);
}

void Game::Run() {
  Setup();
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void Game::Destroy() const {
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
