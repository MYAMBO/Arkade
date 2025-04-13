/*
** EPITECH PROJECT, 2024
** arkade
** File description:
** Snake.cpp
*/

#include <chrono>

#include "Snake.hpp"
#include "SnakeObject.hpp"

void Snake::Init()
{
    addObject(SPRITE, "2/snakehead");
    _objects["2/snakehead"]->setTexturePath("Snake/snakeHeadDown");
    _objects["2/snakehead"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {0, 0}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/snakehead"]->setPosition({16 * 5 * 5, 16 * 5 * 5});
    addObject(SPRITE, "2/wall1");
    _objects["2/wall1"]->setTexturePath("Snake/snake");
    _objects["2/wall1"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall1"]->setPosition({0, 0});
    addObject(SPRITE, "2/wall2");
    _objects["2/wall2"]->setTexturePath("Snake/snake");
    _objects["2/wall2"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall2"]->setPosition({16 * 5, 0});
    addObject(SPRITE, "2/wall3");
    _objects["2/wall3"]->setTexturePath("Snake/snake");
    _objects["2/wall3"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall3"]->setPosition({16 * 5 * 2, 0});
    addObject(SPRITE, "2/wall4");
    _objects["2/wall4"]->setTexturePath("Snake/snake");
    _objects["2/wall4"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall4"]->setPosition({16 * 5 * 3, 0});
    addObject(SPRITE, "2/wall5");
    _objects["2/wall5"]->setTexturePath("Snake/snake");
    _objects["2/wall5"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall5"]->setPosition({16 * 5 * 4, 0});
    addObject(SPRITE, "2/wall6");
    _objects["2/wall6"]->setTexturePath("Snake/snake");
    _objects["2/wall6"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall6"]->setPosition({16 * 5 * 5, 0});
    addObject(SPRITE, "2/wall7");
    _objects["2/wall7"]->setTexturePath("Snake/snake");
    _objects["2/wall7"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall7"]->setPosition({16 * 5 * 6, 0});
    addObject(SPRITE, "2/wall8");
    _objects["2/wall8"]->setTexturePath("Snake/snake");
    _objects["2/wall8"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall8"]->setPosition({16 * 5 * 7, 0});
    addObject(SPRITE, "2/wall9");
    _objects["2/wall9"]->setTexturePath("Snake/snake");
    _objects["2/wall9"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall9"]->setPosition({16 * 5 * 8, 0});
    addObject(SPRITE, "2/wall10");
    _objects["2/wall10"]->setTexturePath("Snake/snake");
    _objects["2/wall10"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall10"]->setPosition({16 * 5 * 9, 0});
    addObject(SPRITE, "2/wall11");
    _objects["2/wall11"]->setTexturePath("Snake/snake");
    _objects["2/wall11"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall11"]->setPosition({16 * 5 * 10, 0});
    addObject(SPRITE, "2/wall12");
    _objects["2/wall12"]->setTexturePath("Snake/snake");
    _objects["2/wall12"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall12"]->setPosition({16 * 5 * 11, 0});
    addObject(SPRITE, "2/wall13");
    _objects["2/wall13"]->setTexturePath("Snake/snake");
    _objects["2/wall13"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall13"]->setPosition({16 * 5 * 12, 0});
    addObject(SPRITE, "2/wall14");
    _objects["2/wall14"]->setTexturePath("Snake/snake");
    _objects["2/wall14"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall14"]->setPosition({16 * 5 * 12, 16 * 5});
    addObject(SPRITE, "2/wall15");
    _objects["2/wall15"]->setTexturePath("Snake/snake");
    _objects["2/wall15"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall15"]->setPosition({16 * 5 * 12, 16 * 5 * 2});
    addObject(SPRITE, "2/wall16");
    _objects["2/wall16"]->setTexturePath("Snake/snake");
    _objects["2/wall16"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall16"]->setPosition({16 * 5 * 12, 16 * 5 * 3});
    addObject(SPRITE, "2/wall17");
    _objects["2/wall17"]->setTexturePath("Snake/snake");
    _objects["2/wall17"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall17"]->setPosition({16 * 5 * 12, 16 * 5 * 4});
    addObject(SPRITE, "2/wall18");
    _objects["2/wall18"]->setTexturePath("Snake/snake");
    _objects["2/wall18"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall18"]->setPosition({16 * 5 * 12, 16 * 5 * 5});
    addObject(SPRITE, "2/wall19");
    _objects["2/wall19"]->setTexturePath("Snake/snake");
    _objects["2/wall19"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall19"]->setPosition({16 * 5 * 12, 16 * 5 * 6});
    addObject(SPRITE, "2/wall20");
    _objects["2/wall20"]->setTexturePath("Snake/snake");
    _objects["2/wall20"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall20"]->setPosition({16 * 5 * 12, 16 * 5 * 7});
    addObject(SPRITE, "2/wall21");
    _objects["2/wall21"]->setTexturePath("Snake/snake");
    _objects["2/wall21"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall21"]->setPosition({16 * 5 * 12, 16 * 5 * 8});
    addObject(SPRITE, "2/wall22");
    _objects["2/wall22"]->setTexturePath("Snake/snake");
    _objects["2/wall22"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall22"]->setPosition({16 * 5 * 12, 16 * 5 * 9});
    addObject(SPRITE, "2/wall23");
    _objects["2/wall23"]->setTexturePath("Snake/snake");
    _objects["2/wall23"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall23"]->setPosition({16 * 5 * 12, 16 * 5 * 10});
    addObject(SPRITE, "2/wall24");
    _objects["2/wall24"]->setTexturePath("Snake/snake");
    _objects["2/wall24"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall24"]->setPosition({16 * 5 * 12, 16 * 5 * 11});
    addObject(SPRITE, "2/wall25");
    _objects["2/wall25"]->setTexturePath("Snake/snake");
    _objects["2/wall25"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall25"]->setPosition({16 * 5 * 12, 16 * 5 * 12});
    addObject(SPRITE, "2/wall26");
    _objects["2/wall26"]->setTexturePath("Snake/snake");
    _objects["2/wall26"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall26"]->setPosition({16 * 5 * 11, 16 * 5 * 12});
    addObject(SPRITE, "2/wall27");
    _objects["2/wall27"]->setTexturePath("Snake/snake");
    _objects["2/wall27"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall27"]->setPosition({16 * 5 * 10, 16 * 5 * 12});
    addObject(SPRITE, "2/wall28");
    _objects["2/wall28"]->setTexturePath("Snake/snake");
    _objects["2/wall28"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall28"]->setPosition({16 * 5 * 9, 16 * 5 * 12});
    addObject(SPRITE, "2/wall29");
    _objects["2/wall29"]->setTexturePath("Snake/snake");
    _objects["2/wall29"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall29"]->setPosition({16 * 5 * 8, 16 * 5 * 12});
    addObject(SPRITE, "2/wall30");
    _objects["2/wall30"]->setTexturePath("Snake/snake");
    _objects["2/wall30"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall30"]->setPosition({16 * 5 * 7, 16 * 5 * 12});
    addObject(SPRITE, "2/wall31");
    _objects["2/wall31"]->setTexturePath("Snake/snake");
    _objects["2/wall31"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall31"]->setPosition({16 * 5 * 6, 16 * 5 * 12});
    addObject(SPRITE, "2/wall32");
    _objects["2/wall32"]->setTexturePath("Snake/snake");
    _objects["2/wall32"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall32"]->setPosition({16 * 5 * 5, 16 * 5 * 12});
    addObject(SPRITE, "2/wall33");
    _objects["2/wall33"]->setTexturePath("Snake/snake");
    _objects["2/wall33"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall33"]->setPosition({16 * 5 * 4, 16 * 5 * 12});
    addObject(SPRITE, "2/wall34");
    _objects["2/wall34"]->setTexturePath("Snake/snake");
    _objects["2/wall34"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall34"]->setPosition({16 * 5 * 3, 16 * 5 * 12});
    addObject(SPRITE, "2/wall35");
    _objects["2/wall35"]->setTexturePath("Snake/snake");
    _objects["2/wall35"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall35"]->setPosition({16 * 5 * 2, 16 * 5 * 12});
    addObject(SPRITE, "2/wall36");
    _objects["2/wall36"]->setTexturePath("Snake/snake");
    _objects["2/wall36"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall36"]->setPosition({16 * 5, 16 * 5 * 12});
    addObject(SPRITE, "2/wall37");
    _objects["2/wall37"]->setTexturePath("Snake/snake");
    _objects["2/wall37"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall37"]->setPosition({0, 16 * 5 * 12});
    addObject(SPRITE, "2/wall38");
    _objects["2/wall38"]->setTexturePath("Snake/snake");
    _objects["2/wall38"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall38"]->setPosition({0, 16 * 5 * 11});
    addObject(SPRITE, "2/wall39");
    _objects["2/wall39"]->setTexturePath("Snake/snake");
    _objects["2/wall39"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall39"]->setPosition({0, 16 * 5 * 10});
    addObject(SPRITE, "2/wall40");
    _objects["2/wall40"]->setTexturePath("Snake/snake");
    _objects["2/wall40"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall40"]->setPosition({0, 16 * 5 * 9});
    addObject(SPRITE, "2/wall41");
    _objects["2/wall41"]->setTexturePath("Snake/snake");
    _objects["2/wall41"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall41"]->setPosition({0, 16 * 5 * 8});
    addObject(SPRITE, "2/wall42");
    _objects["2/wall42"]->setTexturePath("Snake/snake");
    _objects["2/wall42"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall42"]->setPosition({0, 16 * 5 * 7});
    addObject(SPRITE, "2/wall43");
    _objects["2/wall43"]->setTexturePath("Snake/snake");
    _objects["2/wall43"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall43"]->setPosition({0, 16 * 5 * 6});
    addObject(SPRITE, "2/wall44");
    _objects["2/wall44"]->setTexturePath("Snake/snake");
    _objects["2/wall44"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall44"]->setPosition({0, 16 * 5 * 5});
    addObject(SPRITE, "2/wall45");
    _objects["2/wall45"]->setTexturePath("Snake/snake");
    _objects["2/wall45"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall45"]->setPosition({0, 16 * 5 * 4});
    addObject(SPRITE, "2/wall46");
    _objects["2/wall46"]->setTexturePath("Snake/snake");
    _objects["2/wall46"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall46"]->setPosition({0, 16 * 5 * 3});
    addObject(SPRITE, "2/wall47");
    _objects["2/wall47"]->setTexturePath("Snake/snake");
    _objects["2/wall47"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall47"]->setPosition({0, 16 * 5 * 2});
    addObject(SPRITE, "2/wall48");
    _objects["2/wall48"]->setTexturePath("Snake/snake");
    _objects["2/wall48"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {16, 16}, {6, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["2/wall48"]->setPosition({0, 16 * 5});
    addObject(SPRITE, "1/food");
    _objects["1/food"]->setTexturePath("Snake/apple");
    _objects["1/food"]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {0, 0}, {5, 4}, {0, 0}, {5, 5}, WHITE});
    _objects["1/food"]->setPosition({(std::rand() % 11 + 1) * 16 * 5, (std::rand() % 11 + 1) * 16 * 5});
    this->_previousTime = std::chrono::steady_clock::now();
    this->_pastDir = 0;
    this->_dir = 1;
    Eat();
    _objects["2/snake" + std::to_string(this->_snakeSize - 1)]->setPosition({16 * 5 * 5, 16 * 5 * 5});
    Eat();
    _objects["2/snake" + std::to_string(this->_snakeSize - 1)]->setPosition({16 * 5 * 5, 16 * 5 * 4});
    Eat();
    _objects["2/snake" + std::to_string(this->_snakeSize - 1)]->setPosition({16 * 5 * 5, 16 * 5 * 3});
    Eat();
    _objects["2/snake" + std::to_string(this->_snakeSize - 1)]->setPosition({16 * 5 * 5, 16 * 5 * 2});
    this->_score = 0;
}

Snake::Snake()
    : _objects(*(new std::map<std::string, std::unique_ptr<Arcade::IObject>>()))
{
    this->_score = 0;
    this->_scoretmp = 0;
    this->_snakeSize = 1;
    Init();
}

Snake::~Snake()
{
    delete &_objects;
}

void Snake::Restart()
{
    this->_scoretmp = _score;
    _objects["2/snakehead"]->setPosition({16 * 5 * 5, 16 * 5 * 5});
    this->_dir = 1;
    for (auto elt : this->_snakeList)
        this->_objects.erase(elt);
    this->_snakeList.clear();
    Init();
}

void Snake::PlaceFruit()
{
    _objects["1/food"]->setPosition({(std::rand() % 11 + 1) * 16 * 5, (std::rand() % 11 + 1) * 16 * 5});
    for (auto elt : this->_snakeList)
        if (this->_objects[elt]->getPosition() == _objects["1/food"]->getPosition())
            PlaceFruit();
}

void Snake::Eat()
{
    addObject(SPRITE, "2/snake" + std::to_string(this->_snakeSize));
    _objects["2/snake" + std::to_string(this->_snakeSize)]->setTexturePath("Snake/snake");
    _objects["2/snake" + std::to_string(this->_snakeSize)]->setProperties(Arcade::IObject::SpriteProperties{{16, 16}, {6 * 16, 32}, {6, 4}, {6, 0}, {5, 5}, WHITE});
    this->_snakeList.push_back("2/snake" + std::to_string(this->_snakeSize));
    PlaceFruit();
    this->_snakeSize++;
    this->_score++;
}

bool Snake::update(std::pair<int, int> mousePos, int input)
{    
    (void) mousePos;
    if (input == 'r') {
        Restart();
        return false;
    }
    switch (input) {
        case 'z':
            if (this->_pastDir != 1)
                this->_dir = 0;
            break;
        case 's':
            if (this->_pastDir != 0)
                this->_dir = 1;
            break;
        case 'q':
            if (this->_pastDir != 3)
                this->_dir = 2;
            break;
        case 'd':
            if (this->_pastDir != 2)
                this->_dir = 3;
            break;
        default:
            break;
    }
    this->_currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = this->_currentTime - this->_previousTime;
    if (deltaTime.count() < 0.4)
        return false;
    this->_pastDir = this->_dir;
    this->_previousTime = this->_currentTime;
    auto pos = _objects["2/snakehead"]->getPosition();
    switch (this->_dir) {
        case 0:
            _objects["2/snakehead"]->setPosition({pos.first, pos.second - 16 * 5});
            break;
        case 1:
            _objects["2/snakehead"]->setPosition({pos.first, pos.second + 16 * 5});
            break;
        case 2:
            _objects["2/snakehead"]->setPosition({pos.first - 16 * 5, pos.second});
            break;
        case 3:
            _objects["2/snakehead"]->setPosition({pos.first + 16 * 5, pos.second});
            break;
    }
    pos = _objects["2/snakehead"]->getPosition();
    auto applePos = _objects["1/food"]->getPosition();
    if (pos.first > 16 * 5 * 11 || pos.first < 16 * 5 || pos.second > 16 * 5 * 11 || pos.second < 16 * 5) {
        Restart();
        return true;
    }
    if (pos.first == applePos.first && pos.second == applePos.second)
        Eat();
    if (this->_score == 121)
        return true;
    auto headPos = pos;
    for (auto elt : this->_snakeList) {
        auto tmp = _objects[elt]->getPosition();
        if (tmp.first == headPos.first && tmp.second == headPos.second) {
            Restart();
            return true;
        }
        _objects[elt]->setPosition(pos);
        pos = tmp;
    }
    return false;
}

void Snake::addObject(std::string type, std::string name)
{
    if (_objects.find(name) == _objects.end())
        _objects[name] = std::make_unique<SnakeObject>(type, name);
}

void Snake::deleteObject(std::string name)
{
    _objects.erase(name);
}

std::map<std::string, std::unique_ptr<Arcade::IObject>>& Snake::getObjects()
{
    return _objects;
}

std::string Snake::getName() const
{
    return SNAKE;
}

std::size_t Snake::getScore() const
{
    return this->_scoretmp;
}

extern "C"
{
    std::unique_ptr<Arcade::IGameModule> createInstanceIGame()
    {
        return std::make_unique<Snake>();
    }
}
