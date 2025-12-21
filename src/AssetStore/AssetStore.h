#ifndef INC_2DGAMEENGINE_ASSETSTORE_H
#define INC_2DGAMEENGINE_ASSETSTORE_H

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class AssetStore {
    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();
        void LoadFont(const std::string& fontId, const std::string& fontPath, int fontSize);
        void LoadTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& assetPath);
        TTF_Font* GetFont(const std::string& fontId);
        SDL_Texture* GetTexture(const std::string& assetId);

    private:
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
};


#endif //INC_2DGAMEENGINE_ASSETSTORE_H