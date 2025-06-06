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

void SFMLModule::init(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
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

void SFMLModule::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    this->_isLoad.clear();
    (void) objects;
}

int SFMLModule::getInput()
{
    if (this->_window == nullptr)
        return 0;
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
                case sf::Keyboard::Space:
                    return ' ';
                case sf::Keyboard::BackSpace:
                    return K_BACKSPACE;
                case sf::Keyboard::Tab:
                    return '\t';
                case sf::Keyboard::Enter:
                    return '\n';
                case sf::Keyboard::Home:
                    return K_HOME;
                case sf::Keyboard::End:
                    return K_END;
                case sf::Keyboard::PageUp:
                    return K_PPAGE;
                case sf::Keyboard::PageDown:
                    return K_NPAGE;
                case sf::Keyboard::Insert:
                    return K_IC;
                case sf::Keyboard::Delete:
                    return K_DC;
                case sf::Keyboard::LShift:
                case sf::Keyboard::RShift:
                    return CTRL('S');
                case sf::Keyboard::LControl:
                case sf::Keyboard::RControl:
                    return CTRL('C');
                case sf::Keyboard::LAlt:
                case sf::Keyboard::RAlt:
                    return CTRL('A');
                case sf::Keyboard::LSystem:
                case sf::Keyboard::RSystem:
                    return CTRL('Y');
                case sf::Keyboard::F1:
                    return K_F1;
                case sf::Keyboard::F2:
                    return K_F2;
                case sf::Keyboard::F3:
                    return K_F3;
                case sf::Keyboard::F4:
                    return K_F4;
                case sf::Keyboard::F5:
                    return K_F5;
                case sf::Keyboard::F6:
                    return K_F6;
                case sf::Keyboard::F7:
                    return K_F7;
                case sf::Keyboard::F8:
                    return K_F8;
                case sf::Keyboard::F9:
                    return K_F9;
                case sf::Keyboard::F10:
                    return K_F10;
                case sf::Keyboard::F11:
                    return K_F11;
                case sf::Keyboard::F12:
                    return K_F12;
                case sf::Keyboard::Num0:
                    return '0';
                case sf::Keyboard::Num1:
                    return '1';
                case sf::Keyboard::Num2:
                    return '2';
                case sf::Keyboard::Num3:
                    return '3';
                case sf::Keyboard::Num4:
                    return '4';
                case sf::Keyboard::Num5:
                    return '5';
                case sf::Keyboard::Num6:
                    return '6';
                case sf::Keyboard::Num7:
                    return '7';
                case sf::Keyboard::Num8:
                    return '8';
                case sf::Keyboard::Num9:
                    return '9';
                case sf::Keyboard::Numpad0:
                    return '0';
                case sf::Keyboard::Numpad1:
                    return '1';
                case sf::Keyboard::Numpad2:
                    return '2';
                case sf::Keyboard::Numpad3:
                    return '3';
                case sf::Keyboard::Numpad4:
                    return '4';
                case sf::Keyboard::Numpad5:
                    return '5';
                case sf::Keyboard::Numpad6:
                    return '6';
                case sf::Keyboard::Numpad7:
                    return '7';
                case sf::Keyboard::Numpad8:
                    return '8';
                case sf::Keyboard::Numpad9:
                    return '9';
                default:
                    break;
            }
            if (this->_event.key.code >= sf::Keyboard::A && this->_event.key.code <= sf::Keyboard::Z) {
                if (this->_event.key.control) {
                    return 1 + (this->_event.key.code - sf::Keyboard::A);
                } else {
                    return this->_event.key.code + 'a';
                }
            }
            else if (this->_event.key.code >= sf::Keyboard::Num0 && this->_event.key.code <= sf::Keyboard::Num9) {
                return '0' + (this->_event.key.code - sf::Keyboard::Num0);
            }
            else if (this->_event.key.code >= sf::Keyboard::Numpad0 && this->_event.key.code <= sf::Keyboard::Numpad9) {
                return '0' + (this->_event.key.code - sf::Keyboard::Numpad0);
            }
        }
        if (this->_event.type == sf::Event::MouseButtonPressed) {
            switch (this->_event.mouseButton.button) {
                case sf::Mouse::Left:
                    return K_MOUSE;
                default:
                    return K_RCLICK;
            }
        }
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
    this->_isLoad.clear();
    this->_window->close();
}

void SFMLModule::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::pair<int, int> pos;
    sf::Vector2u windowSize = this->_window.get()->getSize();

    init(objects);
    this->_window->clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        if (type == SPRITE) {
            if (!elt->second->getSprite().has_value()) {
                auto texture = std::make_shared<sf::Texture>();
                sf::Sprite sprite;
                auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());

                texture->loadFromFile("assets/" + elt->second->getTexturePath() + ".png");
                sprite.setTexture(*texture.get());
                sprite.setTextureRect({properties.offset.first, properties.offset.second, properties.size.first, properties.size.second});
                sprite.setScale(properties.scale.first, properties.scale.second);
                sprite.setColor(sf::Color(properties.textColor));
                elt->second->setTexture(texture);
                elt->second->setSprite(sprite);
                this->_isLoad[elt->first] = true;
            }
            auto sprite = std::any_cast<sf::Sprite>(elt->second->getSprite());
            pos = elt->second.get()->getPosition();
            sprite.setPosition(pos.first * windowSize.x / 1920, pos.second * windowSize.y / 1080);
            sprite.setColor(sf::Color(std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties()).textColor));
            this->_window->draw(sprite);
        }
        if (type == TEXT) {
            if (!elt->second->getSprite().has_value()) {
                sf::Text text;
                auto font = std::make_shared<sf::Font>();
                auto properties = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties());

                font->loadFromFile("assets/" + elt->second->getTexturePath() + ".ttf");
                text.setFont(*font.get());
                text.setString(properties.text);
                text.setCharacterSize(properties.characterSize);
                text.setFillColor(sf::Color::White);
                text.setOrigin(properties.characterSize / 2, 0);
                elt->second->setTexture(font);
                elt->second->setSprite(text);
                this->_isLoad[elt->first] = true;
            }
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
