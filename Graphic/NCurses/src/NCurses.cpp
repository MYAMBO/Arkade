/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** NCurses.cpp
*/

#include <list>
#include <fstream>
#include <iostream>

#include "NCurses.hpp"

NCurses::NCurses()
{
    
}

NCurses::~NCurses()
{

}

std::string NCurses::getName() const
{
    return NCURSES;
}

void NCurses::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        path = elt->second->getTexturePath();
        if (type == SPRITE) {
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            std::ifstream file ("assets/" + path + ".txt");
            std::string line;
            std::list<std::string> strList;
            int i = 0;

            while (std::getline(file, line)) {
                i++;
                if (i <= properties.textOffset.second || i > properties.textSize.second + properties.textOffset.second)
                    continue;
                strList.push_back(line.substr(properties.textOffset.first, properties.textSize.first));
            }
            elt->second->setSprite(std::any(strList));
        }
    }
}

int NCurses::getInput()
{
    MEVENT event;

    if (getmouse(&event) == OK) {
        this->_mousePos.first = static_cast<int>((event.x * 1000.0) / COLS);
        this->_mousePos.second = static_cast<int>((event.y * 1000.0) / LINES);
        if (event.bstate == BUTTON1_PRESSED || event.bstate == BUTTON2_PRESSED)
            return K_RCLICK;
    }
    return getch();
}

std::pair<int, int> NCurses::getMousePos() const
{
    return this->_mousePos;
}

void NCurses::openWindow()
{
    initscr();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);
    timeout(10);
    std::cout << "\033[?1003h\n" << std::endl;
}

void NCurses::closeWindow()
{
    std::cout << "\033[?1003l\n" << std::endl;
    endwin();
}

void NCurses::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::pair<int, int> pos;
    short i;

    clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        if (elt->second->getType() == SPRITE) {
            auto sprite = std::any_cast<std::list<std::string>>(elt->second->getSprite());
            i = 0;
            pos = elt->second.get()->getPosition();
            for (auto elt2 : sprite) {
                mvprintw(pos.second * LINES / 1000 + i, pos.first * COLS / 1000, "%s", elt2.c_str());
                i++;
            }
        } else if (elt->second->getType() == TEXT) {
            std::string text = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).text;
            pos = elt->second.get()->getPosition();
            mvprintw(pos.second * LINES / 1000, pos.first * COLS / 1000 + text.size() / 2, "%s", text.c_str());
        }
    }
    refresh();
}

extern "C"
{
    std::unique_ptr<Arcade::IDisplayModule> createInstanceIDisplay()
    {
        return std::make_unique<NCurses>();
    }
}
