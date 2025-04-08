/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFMLModule.cpp
*/

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
        if (type == SPRITE) {
            auto texture = std::make_shared<sf::Texture>();
            auto sprite = std::make_shared<sf::Sprite>();

            texture->loadFromFile("assets/png/" + path + ".png");
            sprite->setTexture(*texture.get());
            sprite->setTextureRect(
                {std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).offset.first * std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).size.first
                , std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).offset.second * std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).size.second
                , std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).size.first, std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).size.second});
            sprite->setScale(std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).scale.first, std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).scale.second);
            elt->second->setTexture(std::any(texture));
            elt->second->setSprite(std::any(sprite));
        }
        if (type == TEXT) {
            auto text = std::make_shared<sf::Text>();
            auto font = std::make_shared<sf::Font>();

            font->loadFromFile("assets/" + path + ".ttf");
            text->setFont(*font.get());
            text->setString(std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).text);
            text->setCharacterSize(std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).characterSize);
            text->setFillColor(sf::Color::White);
            text->setOrigin(std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).characterSize / 2, 0);
            elt->second->setTexture(std::any(font));
            elt->second->setSprite(std::any(text));
        }
    }
}

int SFMLModule::getInput()
{
    while (this->_window->pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::KeyPressed)
            return this->_event.key.code + 'a';
        if (this->_event.type == sf::Event::MouseButtonPressed)
            return K_RCLICK;
    }
    return -1;
}

std::pair<int, int> SFMLModule::getMousePos() const
{
    auto pos = sf::Mouse::getPosition(*this->_window);
    auto windowSize = this->_window->getSize();

    return (std::pair<int, int>) {1000 * pos.x / windowSize.x, 1000 * pos.y / windowSize.y};
}

void SFMLModule::openWindow()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFMLModule", sf::Style::Default);
    this->_window->setFramerateLimit(60);
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
            auto sprite = std::any_cast<std::shared_ptr<sf::Sprite>>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            sprite.get()->setPosition(pos.first * windowSize.x / 1000, pos.second * windowSize.y / 1000);
            this->_window->draw(*sprite.get());
        }
        if (type == TEXT) {
            auto text = std::any_cast<std::shared_ptr<sf::Text>>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            text.get()->setString(std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).text);
            text.get()->setPosition(pos.first * windowSize.x / 1000, pos.second * windowSize.y / 1000);
            this->_window->draw(*text.get());
        }
    }
    this->_window->display();
}
