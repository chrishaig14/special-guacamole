#include "Texture.h"
#include "SDL.h"
#include <map>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_Resources.h"

class SDL_Resources {
    SDL_Renderer *renderer;
    std::map<std::string, SDL::Texture *> textures;
    std::map<std::string, SDL::Texture *> sounds;
    std::map<std::string, SDL::Texture *> musics;
public:
    SDL_Resources(SDL_Renderer *renderer) {
        this -> renderer = renderer;
    }

    void addTexture(std::string id, std::string filename){
        SDL::Texture* texture = new SDL::Texture();
        texture->loadImage(renderer,filename);
    }

    void addSound(std::string id, std::string filename){

    }
    void addMusic(std::string id, std::string filename){

    }
};