#ifndef INC_2DGAMEENGINE_ASSETSTORE_H
#define INC_2DGAMEENGINE_ASSETSTORE_H

#include <SDL_render.h>
#include <string>
#include <map>


class AssetStore {
    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();
        void LoadTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& assetPath);
        SDL_Texture* GetTexture(const std::string& assetId);

    private:
        std::map<std::string, SDL_Texture*> textures;

};


#endif //INC_2DGAMEENGINE_ASSETSTORE_H