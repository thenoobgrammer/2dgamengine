#include <fstream>
#include <iostream>
#include <SDL.h>
#include <glm/glm.hpp>

#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/RenderSystem.h"
#include "Game.h"

#include "../Components/MouseTrackComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/TagComponent.h"
#include "../Systems/AISystem.h"
#include "../Systems/HealthSystem.h"
#include "../Systems/MouseTrackingSystem.h"
#include "../Systems/RenderTextSystem.h"

#include <sstream>

int Game::windowWidth;
int Game::windowHeight;
int Game::mapWidth;
int Game::mapHeight;
int Game::mouseX;
int Game::mouseY;

Game::Game() {
  isRunning = false;
  debugColliders = false;
  registry = std::make_unique<Registry>();
  assetStore = std::make_unique<AssetStore>();
  eventBus = std::make_unique<EventBus>();
  enemyFactory = std::make_unique<EnemyFactory>(registry);
  levelFactory = std::make_unique<LevelFactory>(registry);
}

Game::~Game() = default;

void Game::Destroy() const {
  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void Game::Initialize() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::Log("SDL_Init error");
    return;
  }

  if (TTF_Init() != 0) {
    Logger::Err("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
  }

  SDL_DisplayMode displayMode;
  SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 1280;//displayMode.w;
  windowHeight = 720;//displayMode.h;
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

  // initialize the camera with the entire screen area
  camera.x = 0;
  camera.y = 0;
  camera.w = windowWidth;
  camera.h = windowHeight;
}

void Game::LoadAssets() const {
  assetStore->LoadTexture(renderer, "player-image", "../assetsv2/images/TX Player.png");
  assetStore->LoadTexture(renderer, "chopper-image", "../assets/images/chopper-spritesheet.png");
  assetStore->LoadTexture(renderer, "tank-image", "../assets/images/tank-panther-right.png");
  assetStore->LoadTexture(renderer, "truck-image", "../assets/images/truck-ford-right.png");
  assetStore->LoadTexture(renderer, "radar-image", "../assets/images/radar.png");
  assetStore->LoadTexture(renderer, "tilemap-image", "../assets/tilemaps/jungle.png");
  assetStore->LoadTexture(renderer, "bullet-image", "../assets/images/bullet.png");

  assetStore->LoadTexture(renderer, "tileset-grass", "../assetsv2/tilesets/TX Tileset Grass.png");
  assetStore->LoadTexture(renderer, "tileset-stone-ground", "../assetsv2/tilesets/TX Tileset Stone Ground.png");
  assetStore->LoadTexture(renderer, "tileset-wall", "../assetsv2/tilesets/TX Tileset Wall.png");
}

void Game::LoadFonts() const {
  assetStore->LoadFont("damage-font", "../assets/fonts/charriot.ttf", 14);
}

void Game::LoadLevel(const int level) const {
  RegisterSystems();
  LoadAssets();
  LoadFonts();
  levelFactory->LoadLevel(level);
  SpawnEntities(level);
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
    case SDL_MOUSEBUTTONDOWN:
      eventBus->Emit<MouseEvent>(event.button);
      break;
    case SDL_MOUSEMOTION:
      eventBus->Emit<MouseEvent>(event.motion);
      break;
    }
  }
}

void Game::RegisterSystems() const {
  registry->AddSystem<MovementSystem>();
  registry->AddSystem<RenderSystem>();
  registry->AddSystem<AnimationSystem>();
  registry->AddSystem<CollisionSystem>();
  registry->AddSystem<DamageSystem>();
  registry->AddSystem<KeyboardControlSystem>();
  registry->AddSystem<CameraMovementSystem>();
  registry->AddSystem<ProjectileEmitSystem>();
  registry->AddSystem<HealthSystem>();
  registry->AddSystem<RenderTextSystem>();
  registry->AddSystem<AISystem>();
  registry->AddSystem<MouseTrackingSystem>();
}

void Game::Render() const {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
  registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore);

  if (debugColliders) {
    registry->GetSystem<CollisionSystem>().RenderCollisionBox(renderer, camera);
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

void Game::Setup() {
  LoadLevel(0);
}

void Game::SpawnEntities(const int level) const {
  SpawnPlayer();
  SpawnTank();
  SpawnTruck();
  SpawnUI();
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
  registry->GetSystem<KeyboardControlSystem>().Subscribe(eventBus);
  registry->GetSystem<HealthSystem>().Subscribe(eventBus, registry);
  registry->GetSystem<MouseTrackingSystem>().Subscribe(eventBus);

  // Update the registry to process the netities that are waiting to be created/deleted
  registry->Update();

  // Ask all systems to update
  registry->GetSystem<MovementSystem>().Update(deltaTime);
  registry->GetSystem<AnimationSystem>().Update();
  registry->GetSystem<CollisionSystem>().Update(eventBus);
  registry->GetSystem<ProjectileEmitSystem>().Update(registry);
  registry->GetSystem<CameraMovementSystem>().Update(camera);
  registry->GetSystem<HealthSystem>().Update();
  registry->GetSystem<AISystem>().Update();
  registry->GetSystem<MouseTrackingSystem>().Update();
}

void Game::SpawnPlayer() const {
  Entity player = registry->CreateEntity();
  player.AddComponent<PlayerComponent>();
  player.AddComponent<NameComponent>("player");
  player.AddComponent<TransformComponent>(glm::vec2(50.0, 120.0), glm::vec2(1.0, 1.0), 0.0);
  player.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
  player.AddComponent<SpriteComponent>("player-image", 32, 128, 2);
  player.AddComponent<TagComponent>(Tag::Player);
  player.AddComponent<AnimationComponent>(1, 1, 10, true);
  player.AddComponent<KeyboardControlledComponent>(
      glm::vec2(0, -200),
      glm::vec2(200, 0),
      glm::vec2(0, 200),
      glm::vec2(-200, 0)
  );
  player.AddComponent<CameraFollowComponent>();
  player.AddComponent<ProjectileEmitterComponent>(glm::vec2(0), 0, 10000);
  player.AddComponent<MouseTrackComponent>();
}

void Game::SpawnTank() const {
  enemyFactory->Spawn(EnemyType::Tank, glm::vec2(10.0, 10.0));
}

void Game::SpawnTruck() const {
  enemyFactory->Spawn(EnemyType::Truck, glm::vec2(500.0, 10.0));
}

void Game::SpawnUI() const {
  Entity healthIndicator = registry->CreateEntity();
  healthIndicator.AddComponent<NameComponent>("healthIndicator");
  healthIndicator.AddComponent<TagComponent>(Tag::UIElement);
  healthIndicator.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  healthIndicator.AddComponent<TransformComponent>(glm::vec2(30, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  healthIndicator.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity armorIndicator = registry->CreateEntity();
  armorIndicator.AddComponent<NameComponent>("armorIndicator");
  armorIndicator.AddComponent<TagComponent>(Tag::UIElement);
  armorIndicator.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  armorIndicator.AddComponent<TransformComponent>(glm::vec2(30 + 64, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  armorIndicator.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity weaponSlot1 = registry->CreateEntity();
  weaponSlot1.AddComponent<NameComponent>("weaponSlot1");
  weaponSlot1.AddComponent<TagComponent>(Tag::UIElement);
  weaponSlot1.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  weaponSlot1.AddComponent<TransformComponent>(glm::vec2(windowWidth/2 - 128, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  weaponSlot1.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity weaponSlot2 = registry->CreateEntity();
  weaponSlot2.AddComponent<NameComponent>("weaponSlot2");
  weaponSlot2.AddComponent<TagComponent>(Tag::UIElement);
  weaponSlot2.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  weaponSlot2.AddComponent<TransformComponent>(glm::vec2(windowWidth/2 - 64, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  weaponSlot2.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity attackSlot1 = registry->CreateEntity();
  attackSlot1.AddComponent<NameComponent>("attackSlot1");
  attackSlot1.AddComponent<TagComponent>(Tag::UIElement);
  attackSlot1.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  attackSlot1.AddComponent<TransformComponent>(glm::vec2(windowWidth/2 + 64, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  attackSlot1.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity attackSlot2 = registry->CreateEntity();
  attackSlot2.AddComponent<NameComponent>("attackSlot2");
  attackSlot2.AddComponent<TagComponent>(Tag::UIElement);
  attackSlot2.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  attackSlot2.AddComponent<TransformComponent>(glm::vec2(windowWidth/2 + 128, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  attackSlot2.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity attackSlot3 = registry->CreateEntity();
  attackSlot3.AddComponent<NameComponent>("attackSlot3");
  attackSlot3.AddComponent<TagComponent>(Tag::UIElement);
  attackSlot3.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  attackSlot3.AddComponent<TransformComponent>(glm::vec2(windowWidth/2 + 192, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  attackSlot3.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity specialAttackGauger = registry->CreateEntity();
  specialAttackGauger.AddComponent<NameComponent>("specialAttackGauger");
  specialAttackGauger.AddComponent<TagComponent>(Tag::UIElement);
  specialAttackGauger.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  specialAttackGauger.AddComponent<TransformComponent>(glm::vec2(windowWidth - 64 - 30, windowHeight - 96), glm::vec2(1.0, 1.0), 0.0);
  specialAttackGauger.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));

  Entity itemBags = registry->CreateEntity();
  itemBags.AddComponent<NameComponent>("itemBags");
  itemBags.AddComponent<TagComponent>(Tag::UIElement);
  itemBags.AddComponent<SpriteComponent>("", 64, 64, 2, true);
  itemBags.AddComponent<TransformComponent>(glm::vec2(windowWidth - 64 - 30, 30), glm::vec2(1.0, 1.0), 0.0);
  itemBags.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
}

