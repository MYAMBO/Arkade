/*
** EPITECH PROJECT, 2025
** Arkade
** File description:
** Parsing
*/

#pragma once

// std includes
#include <string>

#include "IDisplayModule.hpp"

class Parsing {
    public:
        Parsing();
        ~Parsing();
        
        std::string getLib() const;
        int ParseLib(std::map<std::string, std::shared_ptr<IDisplayModule>> displayModuleList);

        void setPathlib(std::string pathlib);
    private:
        std::string _lib;
        std::string _pathlib;
};
