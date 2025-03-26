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

        void setPosition(std::pair<int, int> pos);
        std::pair<int, int> getPosition() const;

        void setSprite(std::any sprite);
        std::any getSprite() const;

        void setTexturePath(std::string path);
        std::string getTexturePath();
        
        std::string getType() const;

        std::string getName() const;
    private:
        std::pair<int, int> _position;
        std::any _sprite;
        std::string _path;
        std::string _type;
        std::string _name;
};
