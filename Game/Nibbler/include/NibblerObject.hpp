/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** NibllerObject
*/

#pragma once

#include "IObject.hpp"

class NibblerObject : public IObject
{
    public:
        NibblerObject(std::string type, std::string name);
        ~NibblerObject();

        void setPosition(std::pair<int, int>);
        std::pair<int, int> getPosition() const;

        void setSprite(std::any);
        std::any& getSprite();

        std::any& getTexture();
        void setTexture(std::any);

        void setTexturePath(std::string);
        std::string getTexturePath();

        void setProperties(Properties properties);
        Properties getProperties();

        std::string getType() const;
    private:
        std::pair<int, int> _position;
        std::any _sprite;
        std::string _path;
        std::string _type;
        std::string _name;
        std::any _texture;
        std::string _text;
        IObject::Properties _properties;
};
