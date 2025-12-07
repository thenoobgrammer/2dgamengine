cmake_minimum_required(VERSION 3.21)
project(2dgameengine)

set(CMAKE_CXX_STANDARD 17)

# Point to your SDL2 directory
set(SDL2_ROOT "C:/SDL2")

# Add SDL include directories
include_directories(${SDL2_ROOT}/include/SDL2)

# Add libs directory (parent of glm, imgui, etc.)
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Add Lua include directory (where lua.h is)
include_directories(${CMAKE_SOURCE_DIR}/libs/lua)

# Add SDL library directory
link_directories(${SDL2_ROOT}/lib)

# Add Lua library directory (where liblua54.a is)
link_directories(${CMAKE_SOURCE_DIR}/libs/lua)

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
)

# Link libraries - use lua54 since you have liblua54.a
target_link_libraries(2dgameengine
        mingw32
        SDL2main
        SDL2
        SDL2_image
        lua53
)