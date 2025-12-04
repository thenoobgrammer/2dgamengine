#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

Game::Game() {
  isRunning = false;
  registry = std::make_unique<Registry>();
  assetStore = std::make_unique<AssetStore>();
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
  windowWidth = displayMode.w;
  windowHeight = displayMode.h;
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

  SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN | SDL_RENDERER_PRESENTVSYNC);

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
        }
        break;
    }
  }
}

void Game::Setup() const {
  // Add the systems that need to be processed in our game
  registry->AddSystem<MovementSystem>();
  registry->AddSystem<RenderSystem>();

  // Adding assets to the assets store
  assetStore->LoadTexture(renderer,"tank-image", "../assets/images/tank-panther-right.png");
  assetStore->LoadTexture(renderer, "truck-image", "../assets/images/truck-ford-right.png");

  // Create the entity
  Entity tank = registry->CreateEntity();
  tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
  tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));
  tank.AddComponent<SpriteComponent>("tank-image", 32, 32);


  Entity truck = registry->CreateEntity();
  truck.AddComponent<TransformComponent>(glm::vec2(50.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
  truck.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 50.0));
  truck.AddComponent<SpriteComponent>("truck-image", 32, 32);
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

  // Update the registry to process the netities that are waiting to be created/deleted
  registry->Update();

  // Ask all systems to update
  registry->GetSystem<MovementSystem>().Update(deltaTime);
}

void Game::Render() const {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

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
