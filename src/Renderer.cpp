#include <iostream>

#include <SDL_image.h>

#include "Renderer.h"
#include "Player.h"
#include "util.h"

void Renderer::clear() {
    SDL_RenderClear(_renderer);
}

int Renderer::generateY() { return _randomY(); }

int Renderer::getScreenWidth() const {
    return SCREEN_WIDTH_;
}

void Renderer::present(int count) const {
    auto msg = "thread count: " + std::to_string(count);
    SDL_SetWindowTitle(_window, msg.c_str());
    SDL_RenderPresent(_renderer);
}

bool Renderer::outsideScreen(const RenderableEntity& entity) const {
    return entity.getX() < -50 || entity.getY() < -50 || entity.getX() > SCREEN_WIDTH_ || entity.getY() > SCREEN_HEIGHT_ + 50;
}

void Renderer::wrapEntityCoordinates(RenderableEntity* entity) const {
    // the ship should wrap around screen boundaries
    entity->setX(math::modulo(entity->getX(), SCREEN_WIDTH_));
    entity->setY(math::modulo(entity->getY(), SCREEN_HEIGHT_));
}

SDL_Texture* Renderer::loadImage(const char *filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    return IMG_LoadTexture(_renderer, filename);
}

/**
 * Render a texture such that the northwest corner of the texture is located at pixel (x,y).
 *
 * @param texture to be rendered
 * @param x is the x-coordinate of the northwest corner of the texture
 * @param y is the y-coordinate of the northwest corner of the texture
 * @param angle the texture is rotated about the provided center
 * @param center the point about which the texture is rotated
 */
void Renderer::renderTexture(SDL_Texture *texture, const RenderableEntity& entity) {
    SDL_Rect dest;
    dest.x = entity.getX();
    dest.y = entity.getY();
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopyEx(_renderer, texture, nullptr, &dest, entity.getAngle(), entity.getRotationCenter(), SDL_FLIP_NONE);
}

void Renderer::renderTexture(const RenderableEntity& entity) {

    switch (entity.getEntityType()) {
        case PLAYER:
            renderTexture(_textures.player, entity);
            break;
        case ASTEROID:
            renderTexture(_textures.asteroid, entity);
            break;
        case ASTEROID_FRAGMENTS:
            renderTexture(_textures.asteroidFragments, entity);
            break;
        case PHASER_BLAST:
            renderTexture(_textures.phaserBlast, entity);
            break;
        case EXPLOSION:
            renderTexture(_textures.explosion, entity);
            break;
    }
}

void Renderer::renderHealth(int health) const {
    SDL_Rect dest;
    dest.y = 5;
    dest.w = 25;
    dest.h = 25;

    for (int idx = 0; idx < health + 1; ++idx) {
        dest.x = SCREEN_WIDTH_ - 30 * idx;
        SDL_RenderCopy(_renderer, _textures.health, nullptr, &dest);
    }
}

void Renderer::drawBackground() {
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH_;
    dest.h = SCREEN_HEIGHT_;
    SDL_RenderCopy(_renderer, _textures.background, nullptr, &dest);
}

void Renderer::init() {

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // initialize SDL. SDL_Init returns 0 if successful.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    _window = SDL_CreateWindow("hello world!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_,SCREEN_HEIGHT_, 0);
    if (_window == nullptr) {
        std::cout << "SDL_CreateWindow error !! " << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cout << "SDL_CreateRenderer error !! " << SDL_GetError() << "\n";
        exit(1);
    }

    //Open the _font
    TTF_Init();
    _font = TTF_OpenFont("../resources/fonts/ARCADE_N.TTF", 28);
    if(_font == nullptr) {
        printf("Failed to load lazy _font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

Renderer::Renderer(const int h, const int w, Textures& textures) :
    SCREEN_WIDTH_(w), SCREEN_HEIGHT_(h), _window(nullptr), _renderer(nullptr),
    _textures(textures), _randomY(RandomNumberBetween{0,h}) {
    init();
}

Renderer::Renderer(const int h, const int w) :
    SCREEN_WIDTH_(w), SCREEN_HEIGHT_(h), _window(nullptr), _renderer(nullptr), _randomY(RandomNumberBetween{0,h}) {
    init();
    _textures = Textures {
            loadImage("../resources/low-angle-shot-mesmerizing-starry-sky-klein.png"),
            loadImage("../resources/heart.png"),
            loadImage("../resources/starship-enterprise.png"),
            loadImage("../resources/asteroid.png"),
            loadImage("../resources/asteroid-fragments.png"),
            loadImage("../resources/phaser.png"),
            loadImage("../resources/tiny-explosion.png")
    };
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Renderer::loadFromRenderedText(const std::string& text, const SDL_Color& textColor) {

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(_font, text.c_str(), textColor);
    auto mTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

    SDL_Rect dest;
    dest.x = 5;
    dest.y = 5;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopy(_renderer, mTexture, nullptr, &dest);

    //Return success
    return mTexture != nullptr;
}