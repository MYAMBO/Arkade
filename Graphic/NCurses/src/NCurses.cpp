/*
** EPITECH PROJECT, 2025
** arkade
** File description:
** NCurses.cpp
*/

#include <list>
#include <fstream>

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

void NCurses::initObject(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::string type;
    std::string path;

    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        path = elt->second->getTexturePath();
        if (type == SPRITE) {
            std::ifstream file ("assets/string/" + path + ".txt");
            std::string line;
            std::list<std::string> strList;

            while (std::getline(file, line))
                strList.push_back(line);
            elt->second->setSprite(std::any(strList));
        }
    }
}

int NCurses::getInput()
{
    MEVENT event;
    int ch = getch();

    if (ch == KEY_MOUSE && getmouse(&event) == OK) {
        this->_mousePos.first = static_cast<int>((event.x * 1000.0) / COLS);
        this->_mousePos.second = static_cast<int>((event.y * 1000.0) / LINES);
    }
    return ch;
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
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
    timeout(10);
}

void NCurses::closeWindow()
{
    endwin();
}

void NCurses::display(std::map<std::string, std::unique_ptr<IObject>>& objects)
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
            continue;
        }
        if (elt->second->getType() == TEXT) {
            auto text = std::any_cast<std::string>(elt->second->getText());
            pos = elt->second.get()->getPosition();
            mvprintw(pos.second * LINES / 1000 + i, pos.first * COLS / 1000, "%s", text.c_str());
            continue;
        }
    }
    refresh();
}
