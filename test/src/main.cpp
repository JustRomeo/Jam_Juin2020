/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Main
*/

#include "ICoreGame.hpp"
#include "IDisplay.hpp"
#include "CoreGame.hpp"
#include "Exception.hpp"
#include "Launcher.hpp"
#include <memory>

int main(int ac, char **av, char **env)
{
    std::string lib;
    std::unique_ptr<arcade::Launcher> launcher;

    try
    {
        if (ac != 2)
            throw Exception("Usage: ./arcade {path to a gfx library}");
        lib = av[1];
        launcher = std::make_unique<arcade::Launcher>(lib);
        if (launcher == nullptr)    
            return (84);
        launcher->menu();
    }
    catch (std::bad_alloc const &bad) 
    {
        std::cerr << bad.what() << std::endl;
        return (84);
    }
    catch (Exception const &e)
    {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    return (0);
}
