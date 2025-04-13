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
void NCurses::init(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::string type;
    std::string path;
    
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        type = elt->second->getType();
        path = elt->second->getTexturePath();
        if (_isLoad[elt->first] == true)
            continue;
        if (type == SPRITE) {
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            int r = (properties.textColor >> 24) & 0xFF;
            int g = (properties.textColor >> 16) & 0xFF;
            int b = (properties.textColor >> 8) & 0xFF;
            int colorIndex;
            if (_colorIndices.find(elt->first) != _colorIndices.end()) {
                colorIndex = _colorIndices[elt->first];
            } else {
                colorIndex = _colorIndices.size() + 1;
                _colorIndices[elt->first] = colorIndex;
            }
            if (has_colors())
                init_pair(colorIndex, mapRGBToBasicColor(r, g, b), COLOR_BLACK);
            std::ifstream file("assets/" + path + ".txt");
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
            _isLoad[elt->first] = true;
        }
    }
}

void NCurses::initObject(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    this->_isLoad.clear();
    (void) objects;
}

int NCurses::getInput()
{
    MEVENT event;
    int ch = getch();

    if (getmouse(&event) == OK) {
        this->_mousePos.first = static_cast<int>((event.x * 1920.0) / COLS);
        this->_mousePos.second = static_cast<int>((event.y * 1080.0) / LINES);
        if (event.bstate == BUTTON1_PRESSED || event.bstate == BUTTON2_PRESSED)
            return K_RCLICK;
    }
    if (ch >= 1 && ch <= 26)
        return CTRL('A' + ch - 1);
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
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);
    timeout(10);
    start_color();
    std::cout << "\033[?1003h\n" << std::endl;
}

void NCurses::closeWindow()
{
    this->_isLoad.clear();
    std::cout << "\033[?1003l\n" << std::endl;
    endwin();
}

short NCurses::mapRGBToBasicColor(int r, int g, int b)
{
    if (r > g && r > b)
        return COLOR_RED;
    if (g > r && g > b)
        return COLOR_GREEN;
    if (b > r && b > g)
        return COLOR_BLUE;
    if (r > 200 && g > 200 && b > 200)
        return COLOR_WHITE;
    if (r < 50 && g < 50 && b < 50)
        return COLOR_BLACK;
    if (r > 200 && g > 200 && b < 100)
        return COLOR_YELLOW;
    if (r > 200 && b > 200 && g < 100)
        return COLOR_MAGENTA;
    if (g > 200 && b > 200 && r < 100)
        return COLOR_CYAN;
    return COLOR_WHITE;
}

void NCurses::display(std::map<std::string, std::unique_ptr<Arcade::IObject>>& objects)
{
    std::pair<int, int> pos;

    init(objects);
    clear();
    for (auto elt = objects.begin(); elt != objects.end(); elt++) {
        if (elt->second->getType() == SPRITE) {
            auto properties = std::get<Arcade::IObject::SpriteProperties>(elt->second->getProperties());
            int r = (properties.textColor >> 24) & 0xFF;
            int g = (properties.textColor >> 16) & 0xFF;
            int b = (properties.textColor >> 8) & 0xFF;
            int colorIndex;
            if (_colorIndices.find(elt->first) != _colorIndices.end()) {
                colorIndex = _colorIndices[elt->first];
            } else {
                colorIndex = _colorIndices.size() + 1;
                _colorIndices[elt->first] = colorIndex;
            }
            if (has_colors())
                init_pair(colorIndex, mapRGBToBasicColor(r, g, b), COLOR_BLACK);
            auto sprite = std::any_cast<std::list<std::string>>(elt->second->getSprite());
            int i = 0;
            pos = elt->second.get()->getPosition();
            if (_colorIndices.find(elt->first) != _colorIndices.end()) {
                int colorPair = _colorIndices[elt->first];
                attron(COLOR_PAIR(colorPair));
                for (auto elt2 : sprite) {
                    mvprintw(pos.second * LINES / 1080 + i, pos.first * COLS / 1920, "%s", elt2.c_str());
                    i++;
                }
                attroff(COLOR_PAIR(colorPair));
            } else {
                for (auto elt2 : sprite) {
                    mvprintw(pos.second * LINES / 1080 + i, pos.first * COLS / 1920, "%s", elt2.c_str());
                    i++;
                }
            }
        } else if (elt->second->getType() == TEXT) {
            std::string text = std::get<Arcade::IObject::TextProperties>(elt->second->getProperties()).text;
            pos = elt->second.get()->getPosition();
            mvprintw(pos.second * LINES / 1080, pos.first * COLS / 1920, "%s", text.c_str());
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
