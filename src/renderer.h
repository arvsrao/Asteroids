#ifndef ASTEROIDS_RENDERER_H
#define ASTEROIDS_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "RandomNumberBetween.h"
#include <string>


struct Textures {

    // background texture
    SDL_Texture* background;

    // health texture
    SDL_Texture* health;

    // player texture
    SDL_Texture* player;

    // asteroid texture
    SDL_Texture* asteroid;

    // asteroid fragments texture
    SDL_Texture* asteroidFragments;

    // phaser blast texture
    SDL_Texture* phaserBlast;

    // explosion texture
    SDL_Texture* explosion;
};

class Renderer {
public:
    Renderer(const int h, const int w);

    Renderer(const int h, const int w, Textures& textures);

    void clear();
    void drawBackground();
    void renderHealth(int health) const;
    void present(int score, int frame_count) const;
    void renderTexture(SDL_Texture *texture, const RenderableEntity& entity);

    void renderTexture(const RenderableEntity &entity);

    //Creates image from _font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

    int  getScreenWidth() const;
    int  generateY();
    SDL_Texture* loadImage(const char* filename);

    bool outsideScreen(const RenderableEntity& entity) const;

    void wrapEntityCoordinates(RenderableEntity* entity);

    ~Renderer();

private:
    const int SCREEN_WIDTH_, SCREEN_HEIGHT_;

    // the window into which stuff is rendered
    SDL_Window* _window;

    // render for the window
    SDL_Renderer* _renderer;

    //Globally used _font
    TTF_Font* _font;

    // background and health textures
    Textures _textures;

    RandomNumberBetween _randomY;

    void init();

};


#endif //ASTEROIDS_RENDERER_H
