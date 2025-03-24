/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** NCurses.hpp
*/

#include "IDisplayModule.hpp"

class NCurses : public IDisplayModule
{
    public:
        NCurses();
        ~NCurses();

        void initObject(std::map<std::string, std::unique_ptr<IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;
        click getMouseSTate() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<IObject>>&);
    private:
        int _input;
};

extern "C" {
    IDisplayModule* createInstance() {
        return new NCurses();
    }
    
    void destroyInstance(IDisplayModule* instance) {
        delete instance;
    }
}
