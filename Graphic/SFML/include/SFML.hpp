/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** SFML.hpp
*/

#include <SFML/Graphics.hpp>

#include "IDisplayModule.hpp"

class SFMLModule : public IDisplayModule
{
    public:
        SFMLModule();
        ~SFMLModule();

        std::string getName() const;

        void initObject(std::map<std::string, std::unique_ptr<IObject>>&);

        int getInput();
        std::pair<int, int> getMousePos() const;

        void openWindow();
        void closeWindow();

        void display(std::map<std::string, std::unique_ptr<IObject>>&);
    private:
        std::unique_ptr<sf::RenderWindow> _window;
        sf::Event _event;
};

extern "C"
{
    std::unique_ptr<IDisplayModule> createInstanceIDisplay()
    {
        return std::make_unique<SFMLModule>();
    }
}
