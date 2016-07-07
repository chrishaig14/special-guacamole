#include "Texture.h"
#include "SDL.h"
#include <map>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_Resources.h"
#include "Sound.h"
#include "Music.h"

SDL_Resources::SDL_Resources(SDL::Renderer *renderer){
    this -> renderer = renderer;
}

void SDL_Resources::addTexture(std::string id, std::string filename) {
    SDL::Texture* texture = new SDL::Texture(renderer,filename);
    _textures[id] = texture;
}

void SDL_Resources::addSound(std::string id, std::string filename) {
    SDL::Sound* sound = new SDL::Sound(filename);
    _sounds[id] = sound;
}

void SDL_Resources::addMusic(std::string id, std::string filename) {
    SDL::Music* music = new SDL::Music(filename);
    _musics[id] = music;
}

SDL_Resources::~SDL_Resources() {
    for(std::map<std::string, SDL::Texture*>::iterator i = _textures.begin(); i != _textures.end(); ++i){
        delete i->second;
    }
    for(std::map<std::string, SDL::Sound*>::iterator i = _sounds.begin(); i != _sounds.end(); ++i){
        delete i->second;
    }
    for(std::map<std::string, SDL::Music*>::iterator i = _musics.begin(); i != _musics.end(); ++i){
        delete i->second;
    }
}

SDL::Texture *SDL_Resources::getTexture(std::string id) {
    return _textures[id];
}

SDL::Sound *SDL_Resources::getSound(std::string id) {
    return _sounds[id];
}

SDL::Music *SDL_Resources::getMusic(std::string id) {
    return _musics[id];
}