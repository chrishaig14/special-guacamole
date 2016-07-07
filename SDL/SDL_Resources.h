#ifndef CITY_SDL_RESOURCES_H
#define CITY_SDL_RESOURCES_H

#endif //CITY_SDL_RESOURCES_H

class SDL_Resources {
    SDL::Renderer *renderer;
    std::map<std::string, SDL::Texture *> _textures;
    std::map<std::string, SDL::Sound *> _sounds;
    std::map<std::string, SDL::Music *> _musics;
public:
    SDL_Resources(SDL::Renderer *renderer);

    void addTexture(std::string id, std::string filename);

    void addSound(std::string id, std::string filename);

    void addMusic(std::string id, std::string filename);

    SDL::Texture * getTexture(std::string id);

    SDL::Sound * getSound(std::string id);

    SDL::Music * getMusic(std::string id);

    ~SDL_Resources();
};