/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** IDisplayModule.hpp
*/

#pragma once

// std includes
#include <memory>
#include <map>

// project includes
#include "IObject.hpp"

// Names for the display modules :
#define AA "AA"
#define QT "QT"
#define GTK "GTK"
#define SDL "SDL"
#define CACA "CACA"
#define XLIB "XLIB"
#define SFML "SFML"
#define OPENGL "OPENGL"
#define VULKAN "VULKAN"
#define ALLEGRO "ALLEGRO"
#define NCURSES "NCURSES"
#define IRRLICHT "IRRLICHT"

namespace Arcade {
    // Definition of the IDisplayModule interface
    class IDisplayModule {
        public:
            // Default virtual destructor
            virtual ~IDisplayModule() = default;
    
            // Initializes objects to be displays
            // takes a reference to the map of objects
            virtual void initObject(std::map<std::string, std::unique_ptr<IObject>>&) = 0;
    
            // Retrieves keyboard inputs
            virtual int getInput() = 0;
            // Retrieves mouse position
            virtual std::pair<int, int> getMousePos() const = 0;
    
            // Open the window
            virtual void openWindow() = 0;
            // Close the window
            virtual void closeWindow() = 0;
    
            // Displays the objects on screen
            // Takes a reference to the map of objects
            virtual void display(std::map<std::string, std::unique_ptr<IObject>>&) = 0;
    
            // Gets the name of the Display Module for example SFML
            virtual std::string getName() const = 0;
    };
}

typedef std::unique_ptr<Arcade::IDisplayModule> (*CreateInstanceIDisplay)();
