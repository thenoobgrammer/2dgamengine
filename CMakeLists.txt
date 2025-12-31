cmake_minimum_required(VERSION 3.21)
project(2dgameengine)

set(CMAKE_CXX_STANDARD 17)

# Point to your SDL2 directory
if(WIN32)
    set(SDL2_ROOT "C:/SDL2")
elseif (APPLE)
    set(SDL2_ROOT "/opt/homebrew")
endif()

# Add SDL include directories
include_directories(${SDL2_ROOT}/include/SDL2)

# Add libs directory (parent of glm, imgui, etc.)
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Add Lua include directory (where lua.h is)
include_directories(${CMAKE_SOURCE_DIR}/libs/lua)

include_directories(${CMAKE_SOURCE_DIR}/libs/jsoncpp)

# Add SDL library directory
link_directories(${SDL2_ROOT}/lib)

# Add Lua library directory (where liblua54.a is)
link_directories(${CMAKE_SOURCE_DIR}/libs/lua)

# Add Jsoncpp lib
link_directories(${CMAKE_SOURCE_DIR}/libs/jsoncpp)

# Add your source files
add_executable(2dgameengine src/Main.cpp
        src/Game/Game.h
        src/Game/Game.cpp
        src/Logger/Logger.h
        src/Logger/Logger.cpp
        src/Components/TransformComponent.h
        src/Systems/MovementSystem.h
        src/ECS/ECS.h
        src/ECS/ECS.cpp
        src/Components/RigidBodyComponent.h
        src/Components/SpriteComponent.h
        src/Systems/RenderSystem.h
        src/AssetStore/AssetStore.cpp
        src/AssetStore/AssetStore.h
        src/Components/AnimationComponent.h
        src/Systems/AnimationSystem.h
        src/Components/BoxColliderComponent.h
        src/Systems/CollisionSystem.h
        src/Events/CollisionEvent.h
        src/EventBus/EventBus.h
        src/EventBus/Event.h
        src/Systems/DamageSystem.h
        src/Systems/KeyboardControlSystem.h
        src/Events/KeyPressedEvent.h
        src/Components/KeyboardControlledComponent.h
        src/Components/CameraFollowComponent.h
        src/Systems/CameraMovementSystem.h
        src/Components/ProjectileEmitterComponent.h
        src/Systems/ProjectileEmitSystem.h
        src/Components/HealthComponent.h
        src/Components/TagComponent.h
        src/Systems/HealthSystem.h
        src/Events/DamageEvent.h
        src/Components/NameComponent.h
        src/Components/ProjectileComponent.h
        src/Components/TextComponent.h
        src/Systems/RenderTextSystem.h
        src/Components/LifeTimeComponent.h
        src/Systems/AISystem.h
        src/Components/AIComponent.h
        src/Factory/EnemyFactory.h
        src/Factory/EnemyFactory.cpp
        src/Systems/MouseTrackingSystem.h
        src/Components/PlayerComponent.h
        src/Events/MouseEvent.h
        src/Components/MouseTrackComponent.h
        src/Factory/LevelFactory.cpp
        src/Factory/LevelFactory.h
)

# Link libraries - use lua54 since you have liblua54.a
if(WIN32)
    target_link_libraries(2dgameengine
            mingw32
            SDL2main
            SDL2
            SDL2_image
            SDL2_ttf
            lua53
            jsoncpp_static
    )
elseif(APPLE)
    link_directories(/opt/homebrew/lib)
    target_link_libraries(2dgameengine
            SDL2
            SDL2_image
            SDL2_ttf
            lua
            jsoncpp
    )
endif()