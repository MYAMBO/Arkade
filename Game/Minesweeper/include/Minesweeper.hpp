/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** Minesweeper.hpp
*/

#include "IGameModule.hpp"

class Minesweeper : public IGameModule
{
    public:
        Minesweeper();
        ~Minesweeper();

        std::string getName() const;

        bool update(std::pair<int, int>, click state, int input);

        void addObject(std::string name);
        void deleteObject(std::string name);
        std::map<std::string, std::unique_ptr<IObject>> getObjects() const;
};

extern "C"
{
    IGameModule *createInstanceIGame()
    {
        return new Minesweeper();
    }
}
