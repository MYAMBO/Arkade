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
            :_sprite(*new std::any()), _texture(*new std::any())
        {
            _type = type;
            _path = "pacman";
            _position = {0, 0};
        }
        ~test() {}

        void setPosition(std::pair<int, int> pos) {this->_position = pos;}
        std::pair<int, int> getPosition() const {return _position;}

        void setSprite(std::any sprite) {this->_sprite = sprite;}
        std::any& getSprite() {return this->_sprite;}

        void setTexturePath(std::string path) {this->_path = path;}
        std::string getTexturePath() {return _path;}
        
        std::string getType() const {return _type;}

        void setSize(std::pair<int, int> size) {_size = size;}
        std::pair<int, int> getSize() const {return _size;}

        void setOffset(std::pair<int, int> offset) {_offset = offset;}
        std::pair<int, int> getOffset() const {return _offset;}

        void setTexture(std::any texture) {_texture = texture;}
        std::any& getTexture() {return _texture;}

        std::string getText() {return _text;}
        void setText(std::string text) {_text = text;}
    private:
        std::pair<int, int> _position;
        std::pair<int, int> _offset;
        std::pair<int, int> _size;
        std::any& _sprite;
        std::any& _texture;
        std::string _path;
        std::string _type;
        std::string _text;
};
