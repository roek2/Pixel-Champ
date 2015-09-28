#include "SDL.h"
#ifndef MENUHEADER
#define MENUHEADER

class Generator;
class Menu
{
    public:
    bool loadImages();
    bool run(Generator gen);
    int select_path();
    void clearChar();
    void introChar();
    void show_sel();
    void show_stats(std::ifstream &save);
    void load_game();
};

#endif
