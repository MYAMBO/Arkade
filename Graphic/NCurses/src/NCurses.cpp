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

    if (getmouse(&event) == OK) {
        this->_mousePos.first = static_cast<int>((event.x * 1000.0) / COLS);
        this->_mousePos.second = static_cast<int>((event.y * 1000.0) / LINES);
        if (event.bstate == BUTTON1_PRESSED || event.bstate == BUTTON2_PRESSED)
            return KEY_RCLICK;
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

std::string getSubString(std::string str, int x, bool isSpriteSheet)
{
    size_t pos;

    if (!isSpriteSheet)
        return str;
    for (int i = 0; i < x; i++) {
        pos = str.find("¤§");
        if (pos == std::string::npos)
            return str;
        str = str.substr(pos + 4);
    }
    pos = str.find("¤§");
    if (pos == std::string::npos)
        return str;
    str = str.substr(0, pos);
    return str;
}

void NCurses::display(std::map<std::string, std::unique_ptr<IObject>>& objects)
{
    std::pair<int, int> pos;
    short i;

    clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        if (elt->second->getType() == SPRITE) {
            auto sprite = std::any_cast<std::list<std::string>>(elt->second->getSprite());
            bool isSpriteSheet = false;
            int x = elt->second->getOffset().first + 1;
            (void)x;
            int y = elt->second->getOffset().second + 1;
            i = 0;
            pos = elt->second.get()->getPosition();
            for (auto elt2 : sprite) {
                if (elt2.find("§¤") != std::string::npos) {
                    y--;
                    isSpriteSheet = true;
                    continue;
                }
                if ((isSpriteSheet && y == 0) || !isSpriteSheet) {
                    mvprintw(pos.second * LINES / 1000 + i, pos.first * COLS / 1000, "%s", getSubString(elt2, x, isSpriteSheet).c_str());
                    i++;
                }
            }
        } else if (elt->second->getType() == TEXT) {
            std::string text = elt->second->getText();
            pos = elt->second.get()->getPosition();
            mvprintw(pos.second * LINES / 1000, pos.first * COLS / 1000 + text.size() / 2, "%s", text.c_str());
        }
    }
    refresh();
}
