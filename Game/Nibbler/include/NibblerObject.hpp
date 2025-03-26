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

        void setTexturePath(std::string);
        std::string getTexturePath();

        std::string getType() const;

        std::pair<int, int> getSize() const;
        void setSize(std::pair<int, int>);

        std::pair<int, int> getOffset() const;
        void setOffset(std::pair<int, int>);

        std::any& getTexture();
        void setTexture(std::any);

        std::string getText();
        void setText(std::string);
    private:
        std::pair<int, int> _position;
        std::any _sprite;
        std::string _path;
        std::string _type;
        std::string _name;
        std::pair<int, int> _size;
        std::pair<int, int> _offset;
        std::any _texture;
        std::string _text;
};
