#include <iostream>

#include <SDL_image.h>

#include "renderer.h"
#include "Player.h"
#include "util.h"

void Renderer::clear() {
    SDL_RenderClear(renderer_);
}

int Renderer::generateY() { return distribution_(random_engine_); }

void Renderer::present(int score, int frame_count) const {
    auto msg = "SCORE: " + std::to_string(score) + " | HEALTH: " + std::to_string(frame_count);
    SDL_SetWindowTitle(window_, msg.c_str());
    SDL_RenderPresent(renderer_);
}

bool Renderer::outsideScreen(const RenderableEntity& entity) const {
    return entity.getX() < -50 || entity.getY() < -50 || entity.getX() > SCREEN_WIDTH_ || entity.getY() > SCREEN_HEIGHT_ + 50;
}

void Renderer::wrapEntityCoordinates(Player& player) const {
    // the ship should wrap around screen boundaries
    player.setX(math::modulo(player.getX(), SCREEN_WIDTH_));
    player.setY(math::modulo(player.getY(), SCREEN_HEIGHT_));
}

SDL_Texture* Renderer::loadImage(const char *filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    return IMG_LoadTexture(renderer_, filename);
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
void Renderer::renderTexture(SDL_Texture *texture, RenderableEntity& entity) {
    SDL_Rect dest;
    dest.x = entity.getX();
    dest.y = entity.getY();
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopyEx(renderer_, texture, nullptr, &dest, entity.getAngle(), entity.getRotationCenter(), SDL_FLIP_NONE);
}

void Renderer::drawBackground(SDL_Texture *texture) {
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH_;
    dest.h = SCREEN_HEIGHT_;
    SDL_RenderCopy(renderer_, texture, nullptr, &dest);
}

void Renderer::init() {

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    // the surface contained by the window
    // SDL_Surface* surface = nullptr;

    // initialize SDL. SDL_Init returns 0 if successful.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window_ = SDL_CreateWindow("hello world!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_,
                               SCREEN_HEIGHT_, 0);
    if (window_ == nullptr) {
        std::cout << "SDL_CreateWindow error !! " << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cout << "SDL_CreateRenderer error !! " << SDL_GetError() << "\n";
        exit(1);
    }
}

Renderer::Renderer(const int h, const int w, const char* background_filename) : SCREEN_HEIGHT_(h), SCREEN_WIDTH_(w), window_(nullptr),
                                               renderer_(nullptr),
                                               random_engine_{std::random_device{}()},
                                               distribution_{0,h},
                                               background_(loadImage(background_filename)) {
    init();
}

Renderer::Renderer(const int h, const int w) : SCREEN_HEIGHT_(h), SCREEN_WIDTH_(w), window_(nullptr),
                                               renderer_(nullptr),
                                               random_engine_{std::random_device{}()},
                                               distribution_{0, h },
                                               background_(loadImage("../resources/low-angle-shot-mesmerizing-starry-sky-klein.png")){
    init();
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

int Renderer::getScreenWidth() {
    return SCREEN_WIDTH_;
}
