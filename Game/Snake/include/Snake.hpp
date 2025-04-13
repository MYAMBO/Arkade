/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Snake.hpp
*/

#pragma once

#include <list>
#include <chrono>

#include "IGameModule.hpp"

class Snake : public Arcade::IGameModule {
    public:
        Snake();
        ~Snake();

        void Init();
        void Restart();
        std::string getName() const;
        std::size_t getScore() const;
        std::map<std::string, std::unique_ptr<Arcade::IObject>>& getObjects();

        bool update(std::pair<int, int> mousePos, int input);

        void deleteObject(std::string name);
        void addObject(std::string type, std::string name);

        void Eat();
        void PlaceFruit();
    private:
        std::map<std::string, std::unique_ptr<Arcade::IObject>>& _objects;
        std::chrono::steady_clock::time_point _previousTime;
        std::chrono::steady_clock::time_point _currentTime;
        std::list<std::string> _snakeList;
        unsigned short _snakeSize;
        std::size_t _score;
        int _pastDir;
        int _dir;
};
