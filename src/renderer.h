#ifndef ASTEROIDS_RENDERER_H
#define ASTEROIDS_RENDERER_H

#include <SDL.h>
#include "Player.h"
#include "RandomNumberBetween.h"

class Renderer {
public:
    Renderer(const int h, const int w);

    Renderer(const int h, const int w, const char *background_filename);

    void clear();
    void drawBackground(SDL_Texture *texture);
    void present(int score, int frame_count) const;
    void renderTexture(SDL_Texture *texture, const RenderableEntity& entity);

    int  getScreenWidth();
    int  generateY();
    SDL_Texture* loadImage(const char* filename);

    bool outsideScreen(const RenderableEntity& entity) const;

    void wrapEntityCoordinates(Player *player) const;

    ~Renderer();

private:
    const int SCREEN_WIDTH_, SCREEN_HEIGHT_;

    // the window into which stuff is rendered
    SDL_Window* window_;

    // render for the window
    SDL_Renderer* renderer_;

    // background texture
    const SDL_Texture* background_;

    // background texture
    const SDL_Texture* player_;

    // background texture
    const SDL_Texture* phaser_blast_;

    void init();

    RandomNumberBetween _randomY;

};


#endif //ASTEROIDS_RENDERER_H
