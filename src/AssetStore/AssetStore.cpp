#include <SDL_image.h>
#include <SDL_ttf.h>
#include "AssetStore.h"
#include "../Logger/Logger.h"

AssetStore::AssetStore() {
    Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore() {
    ClearAssets();
    Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets() {
    for (auto texture: textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
    Logger::Log("Assets cleared");
}

void AssetStore::LoadTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& assetPath) {
    SDL_Surface* surface = IMG_Load(assetPath.c_str());
    if (!surface) {
        Logger::Err("Failed to load image: " + assetPath);
        Logger::Err("IMG_Load Error: " + std::string(IMG_GetError()));
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        Logger::Err("Failed to create texture from: " + assetPath);
        Logger::Err("SDL Error: " + std::string(SDL_GetError()));
        return;
    }

    textures.emplace(assetId, texture);
    Logger::Log("Successfully loaded texture: " + assetId + " from " + assetPath);
}

void AssetStore::LoadFont(const std::string& fontId, const std::string& fontPath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        Logger::Err("Failed to load font from: " + fontPath);
        return;
    }
    fonts[fontId] = font;
    Logger::Log("Successfully loaded font: " + fontId + " from " + fontPath);
}

TTF_Font* AssetStore::GetFont(const std::string& fontId) {
    return fonts[fontId];
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    return textures[assetId];
}