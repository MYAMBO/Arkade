/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFML.hpp
*/

#include <SFML/Graphics.hpp>

#include "IDisplayModule.hpp"

class SFML : public IDisplayModule
{
    public:
        SFML();
        ~SFML();

        void initObject(std::map<std::string, std::unique_ptr<IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;
        click getMouseSTate() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<IObject>>&);
    private:
        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<sf::Event> _event;
        click _state;
};

extern "C" {
    IDisplayModule* createInstance() {
        return new SFML();
    }
    
    void destroyInstance(IDisplayModule* instance) {
        delete instance;
    }
}
