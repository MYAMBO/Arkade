/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** NCurses.cpp
*/

#include <list>
#include <fstream>
#include <ncurses.h>

#include "NCurses.hpp"

NCurses::NCurses()
{
    
}

NCurses::~NCurses()
{
    std::cout << "ncurses is destroy" << std::endl;
}

std::string NCurses::getName() const
{
    return "NCurses";
}

void NCurses::initObject(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second.get()->getType();
        path = elt->second.get()->getTexturePath();
        if (type == "sprite") {
            std::ifstream file ("assets/string/" + path + ".txt");
            std::string line;
            std::list<std::string> strList;

            while (std::getline(file, line))
                strList.push_back(line);
            elt->second.get()->setSprite(std::any(strList));
        }
    }
}

int NCurses::getInput()
{
    return getch();
}

std::pair<int, int> NCurses::getMousePos() const
{
    return std::pair(0, 0);
}

NCurses::click NCurses::getMouseSTate() const
{
    return click::NOTHING;
}

void NCurses::openWindow()
{
    initscr();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    nodelay(stdscr, true);
}
void NCurses::closeWindow()
{
    endwin();
}

void NCurses::display(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::list<std::string> sprite;
    std::pair<int, int> pos;
    short i;

    erase();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        if (elt->second.get()->getType() == "sprite") {
            sprite = std::any_cast<std::list<std::string>>(elt->second.get()->getSprite());
            i = 0;
            pos = elt->second.get()->getPosition();
            for (auto elt : sprite) {
                mvprintw(pos.second * LINES / 1000 + i, pos.first * COLS / 1000, elt.c_str());
                i++;
            }
        }
    }
    refresh();
}
