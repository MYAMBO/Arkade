/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFML.cpp
*/

#include <SFML/Graphics.hpp>

#include "SFML.hpp"

SFML::SFML()
    :_window(nullptr), _event(nullptr)
{

}

SFML::~SFML()
{

}

void SFML::initObject(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        path = elt->second->getTexturePath();
        if (type == "sprite") {
            std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>> pair;
            auto texture = std::make_shared<sf::Texture>();
            auto sprite = std::make_shared<sf::Sprite>();

            texture->loadFromFile("assets/png/" + path + ".png");
            sprite->setTexture(*texture.get());
            sprite->setTextureRect({0, 0, 50, 50});
            texture.swap(pair.first);
            sprite.swap(pair.second);
            elt->second->setSprite(std::any(pair));
        }
    }
}

int SFML::getInput()
{
    while (this->_window->pollEvent(*this->_event))
        if (this->_event->type == sf::Event::KeyPressed)
            return this->_event->key.code + 'a';
    return -1;
}

std::pair<int, int> SFML::getMousePos() const
{
    sf::Vector2i pos = sf::Mouse::getPosition(*this->_window);

    return (std::pair<int, int>) {pos.x, pos.y};
}

SFML::click SFML::getMouseSTate() const
{
    return click::NOTHING;
}

void SFML::openWindow()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFML", sf::Style::Default);
    this->_window->setFramerateLimit(60);
    this->_event = std::make_unique<sf::Event>();
}

void SFML::closeWindow()
{
    this->_window->close();
}

void SFML::display(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::string type;
    std::pair<int, int> pos;
    sf::Vector2u windowSize = this->_window.get()->getSize();

    this->_window->clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        if (type == "sprite") {
            auto pair = std::any_cast<std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>>>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            pair.second.get()->setPosition(pos.first * windowSize.x / 1000, pos.second * windowSize.y / 1000);
            this->_window->draw(*pair.second.get());
        }
    }
    this->_window->display();
}
