/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFMLModule.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>

#include "SFML.hpp"
#include "KeyCodes.hpp"

SFMLModule::SFMLModule()
    :_window(nullptr)
{

}

SFMLModule::~SFMLModule()
{
    
}

std::string SFMLModule::getName() const
{
    return SFML;
}

void SFMLModule::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        path = elt->second->getTexturePath();
        if (this->_isLoad[elt->first] == true)
            continue;
        if (type == SPRITE) {
            auto texture = std::make_shared<sf::Texture>();
            sf::Sprite sprite;
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());

            texture->loadFromFile("assets/" + path + ".png");
            sprite.setTexture(*texture.get());
            sprite.setTextureRect({properties.offset.first, properties.offset.second, properties.size.first, properties.size.second});
            sprite.setScale(properties.scale.first, properties.scale.second);
            sprite.setColor(sf::Color(properties.textColor));
            elt->second->setTexture(texture);
            elt->second->setSprite(sprite);
            this->_isLoad[elt->first] = true;
        } else if (type == TEXT) {
            sf::Text text;
            auto font = std::make_shared<sf::Font>();
            auto properties = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties());

            font->loadFromFile("assets/" + path + ".ttf");
            text.setFont(*font.get());
            text.setString(properties.text);
            text.setCharacterSize(properties.characterSize);
            text.setFillColor(sf::Color::White);
            text.setOrigin(properties.characterSize / 2, 0);
            elt->second->setTexture(font);
            elt->second->setSprite(text);
            this->_isLoad[elt->first] = true;
        }
    }
}

int SFMLModule::getInput()
{
    while (this->_window->pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::KeyPressed) {
            switch (this->_event.key.code) {
                case sf::Keyboard::Up:
                    return K_UP;
                case sf::Keyboard::Down:
                    return K_DOWN;
                case sf::Keyboard::Left:
                    return K_LEFT;
                case sf::Keyboard::Right:
                    return K_RIGHT;
                case sf::Keyboard::Escape:
                    return K_ESC;
                default:
                    break;
            }
            return this->_event.key.code + 'a';
        }
        if (this->_event.type == sf::Event::MouseButtonPressed)
            return K_RCLICK;
    }
    return 0;
}

std::pair<int, int> SFMLModule::getMousePos() const
{
    auto pos = sf::Mouse::getPosition(*this->_window);
    auto windowSize = this->_window->getSize();

    return (std::pair<int, int>) {1920 * pos.x / windowSize.x, 1080 * pos.y / windowSize.y};
}

void SFMLModule::openWindow()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFMLModule", sf::Style::Default);
    this->_window->setFramerateLimit(60);
    this->_window->setKeyRepeatEnabled(false);
}

void SFMLModule::closeWindow()
{
    this->_window->close();
}

void SFMLModule::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::pair<int, int> pos;
    sf::Vector2u windowSize = this->_window.get()->getSize();

    this->_window->clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        if (type == SPRITE) {
            auto sprite = std::any_cast<sf::Sprite>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            sprite.setPosition(pos.first * windowSize.x / 1920, pos.second * windowSize.y / 1080);
            this->_window->draw(sprite);
        }
        if (type == TEXT) {
            auto text = std::any_cast<sf::Text>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            text.setString(std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).text);
            text.setPosition(pos.first * windowSize.x / 1920, pos.second * windowSize.y / 1080);
            this->_window->draw(text);
        }
    }
    this->_window->display();
}

extern "C"
{
    std::unique_ptr<Arcade::IDisplayModule> createInstanceIDisplay()
    {
        return std::make_unique<SFMLModule>();
    }
}
