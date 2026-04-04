cmake_minimum_required(VERSION 3.21)
project(2dgameengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
        src/Systems/SpellBindSystem.h
        src/Systems/InventorySystem.h
        src/Systems/EquipmentSystem.h
        src/Components/ItemComponent.h
        src/Components/ConsumableComponent.h
        src/Components/EquippableComponent.h
        src/Components/InventoryComponent.h
        src/Components/LootTableComponent.h
        src/Components/elements/DropItem.h
        src/Components/elements/EnemyVariantClass.h
        src/Components/elements/AIBehavior.h
        src/Systems/LootSystem.h
        src/Factory/ItemFactory.cpp
        src/Factory/ItemFactory.h
        src/Components/elements/Item.h
        src/Events/DropLootEvent.h
        src/Components/elements/ItemType.h
        src/Systems/ScannerSystem.h
)

target_compile_definitions(2dgameengine PRIVATE
        ASSETS_PATH="${CMAKE_SOURCE_DIR}/"
)

# Link libraries - use lua54 since you have liblua54.a
if(WIN32)
    add_custom_command(TARGET 2dgameengine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SDL2/bin/SDL2.dll"
            "C:/SDL2/bin/SDL2_image.dll"
            "C:/SDL2/bin/SDL2_ttf.dll"
            "C:/SDL2/bin/libavif-16.dll"
            "C:/SDL2/bin/libtiff-5.dll"
            "C:/SDL2/bin/libwebp-7.dll"
            "C:/SDL2/bin/libwebpdemux-2.dll"
            "C:/Users/tonyo/scoop/apps/mingw/current/bin/libgcc_s_seh-1.dll"
            "C:/Users/tonyo/scoop/apps/mingw/current/bin/libstdc++-6.dll"
            $<TARGET_FILE_DIR:2dgameengine>
    )
    target_link_libraries(2dgameengine
            mingw32
            SDL2main
            SDL2
            SDL2_image
            SDL2_ttf
            ${CMAKE_SOURCE_DIR}/libs/lua/liblua54.a
            ${CMAKE_SOURCE_DIR}/libs/jsoncpp/libjsoncpp_static.a
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
