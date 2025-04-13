/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
** created and edited by antoiix.
** All rights reserved
*/

#include "SDL2.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <KeyCodes.hpp>
#include <ostream>

SDL2Module::SDL2Module()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
}

SDL2Module::~SDL2Module()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::string SDL2Module::getName() const
{
    return SDL;
}

void SDL2Module::init(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++)
    {
        type = elt->second->getType();
        if (type == SPRITE)
        {
            if (this->_isLoad[elt->first] == true)
                continue;
            path = "assets/" + elt->second->getTexturePath() + ".png";
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (surface == nullptr)
            {
                std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
            }
            elt->second->setTexture(surface);
            this->_isLoad[elt->first] = true;
        }
        if (type == TEXT)
        {
            auto properties = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties());
            path = "assets/" + elt->second->getTexturePath() + ".ttf";
            TTF_Font* font = TTF_OpenFont(path.c_str(), properties.characterSize);
            if (!font)
            {
                std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
                continue;
            }

            SDL_Color color = {255, 255, 255, 255};
            SDL_Surface* surface = TTF_RenderText_Blended(font, properties.text.c_str(), color);

            SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer.get(), surface);
            if (surface == nullptr)
                std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
            else
                elt->second->setTexture(texture);

            TTF_CloseFont(font);
            this->_isLoad[elt->first] = true;
        }
    }
}


void SDL2Module::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    this->_isLoad.clear();
    (void)objects;
}

int SDL2Module::getInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0)
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return K_ESC;
            case SDLK_UP:
                return K_UP;
            case SDLK_DOWN:
                return K_DOWN;
            case SDLK_LEFT:
                return K_LEFT;
            case SDLK_RIGHT:
                return K_RIGHT;
            case SDLK_SPACE:
                return ' ';
            case SDLK_BACKSPACE:
                return K_BACKSPACE;
            case SDLK_TAB:
                return '\t';
            case SDLK_RETURN:
                return '\n';
            case SDLK_HOME:
                return K_HOME;
            case SDLK_END:
                return K_END;
            case SDLK_PAGEUP:
                return K_PPAGE;
            case SDLK_PAGEDOWN:
                return K_NPAGE;
            case SDLK_INSERT:
                return K_IC;
            case SDLK_DELETE:
                return K_DC;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                return CTRL('S');
            case SDLK_LCTRL:
            case SDLK_RCTRL:
                return CTRL('C');
            case SDLK_LALT:
            case SDLK_RALT:
                return CTRL('A');
            case SDLK_LGUI:
            case SDLK_RGUI:
                return CTRL('Y');
            case SDLK_F1:
                return K_F1;
            case SDLK_F2:
                return K_F2;
            case SDLK_F3:
                return K_F3;
            case SDLK_F4:
                return K_F4;
            case SDLK_F5:
                return K_F5;
            case SDLK_F6:
                return K_F6;
            case SDLK_F7:
                return K_F7;
            case SDLK_F8:
                return K_F8;
            case SDLK_F9:
                return K_F9;
            case SDLK_F10:
                return K_F10;
            case SDLK_F11:
                return K_F11;
            case SDLK_F12:
                return K_F12;
            case SDLK_0:
                return '0';
            case SDLK_1:
                return '1';
            case SDLK_2:
                return '2';
            case SDLK_3:
                return '3';
            case SDLK_4:
                return '4';
            case SDLK_5:
                return '5';
            case SDLK_6:
                return '6';
            case SDLK_7:
                return '7';
            case SDLK_8:
                return '8';
            case SDLK_9:
                return '9';
            case SDLK_x:
                if (e.key.keysym.mod & KMOD_CTRL)
                    return CTRL('X');
                else
                    return 'x';
            default:
                if (e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z)
                {
                    if (e.key.keysym.mod & KMOD_CTRL)
                        return 1 + (e.key.keysym.sym - SDLK_a);
                    else
                        return e.key.keysym.sym;
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
                return K_MOUSE;
            if (e.button.button == SDL_BUTTON_RIGHT)
                return K_RCLICK;
            break;
        }
    }
    return -1;
}

void SDL2Module::closeWindow()
{
    this->_isLoad.clear();
    if (_renderer)
        _renderer.reset();
    if (_window)
        _window.reset();
}

std::pair<int, int> SDL2Module::getMousePos() const
{
    int x, y;
    int width, height;

    SDL_GetWindowSize(_window.get(), &width, &height);
    SDL_GetMouseState(&x, &y);
    return (std::pair<int, int>){1920 * x / width, 1080 * y / height};
}

void SDL2Module::openWindow()
{
    this->_window.reset(SDL_CreateWindow("SDL Window",
                                         SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         1920, 1080,
                                         SDL_WINDOW_SHOWN));

    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
}

void SDL2Module::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    int width, height;

    SDL_GetRendererOutputSize(this->_renderer.get(), &width, &height);
    init(objects);
    SDL_RenderClear(this->_renderer.get());
    for (auto elt = objects.begin(); elt != objects.end(); elt++)
    {
        type = elt->second->getType();
        if (type == SPRITE)
        {
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            SDL_Surface* surface = nullptr;
            surface = std::any_cast<SDL_Surface*>(elt->second->getTexture());
            if (surface)
            {
                std::pair<int, int> pos = elt->second.get()->getPosition();
                SDL_Rect srcRect = {
                    properties.offset.first, properties.offset.second, properties.size.first, properties.size.second
                };
                SDL_Rect dstRect = {
                    pos.first * width / 1920, pos.second * height / 1080,
                    static_cast<int>(properties.size.first * properties.scale.first),
                    static_cast<int>(properties.size.second * properties.scale.second)
                };
                SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer.get(), surface);
                int r = (properties.textColor >> 24) & 0xFF;
                int g = (properties.textColor >> 16) & 0xFF;
                int b = (properties.textColor >> 8) & 0xFF;
                SDL_SetTextureColorMod(texture, r, g, b);
                SDL_RenderCopy(this->_renderer.get(), texture, &srcRect, &dstRect);
                SDL_DestroyTexture(texture);
            }
        }
        if (type == TEXT)
        {
            auto texture = std::any_cast<SDL_Texture*>(elt->second->getTexture());

            std::pair<int, int> pos = elt->second.get()->getPosition();
            SDL_Rect textRect = {pos.first * width / 1920, static_cast<int>(pos.second * height / 1080 * 0.95), 0, 0};
            SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderCopy(this->_renderer.get(), texture, NULL, &textRect);
            SDL_DestroyTexture(texture);
        }
    }
    SDL_RenderPresent(this->_renderer.get());
}

extern "C" {
std::unique_ptr<Arcade::IDisplayModule> createInstanceIDisplay()
{
    return std::make_unique<SDL2Module>();
}
}
