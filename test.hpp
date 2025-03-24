/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** test.hpp
*/

#include "IObject.hpp"

class test : public IObject
{
    public:
        test(std::string type)
        {
            _type = type;
            _path = "pacman";
            _position = {0, 0};
        }
        ~test() {}

        void setPosition(std::pair<int, int> pos) {this->_position = pos;}
        std::pair<int, int> getPosition() const {return _position;}

        void setSprite(std::any sprite) {this->_sprite = sprite;}
        std::any getSprite() const {return this->_sprite;}

        void setTexturePath(std::string path) {this->_path = path;}
        std::string getTexturePath() {return _path;}
        
        std::string getType() const {return _type;}
    private:
        std::pair<int, int> _position;
        std::any _sprite;
        std::string _path;
        std::string _type;
};
