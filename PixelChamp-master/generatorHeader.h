#include "SDL.h"
#ifndef GENERATORHEADER
#define GENERATORHEADER

class PlayerStats;
class Generator
{
    public:
    bool loadImages();
    bool loadImages2();
    bool run(PlayerStats &stats);
    bool run2();
    bool run3();
    bool select_path(PlayerStats &stats);
    bool select_path2();
    bool select_path3();
    bool select_path4();
    bool select_path5();
    void show_sel();
    void show_sel2();
    void show_sel4();
    void show_sel5();
    void count_pixels();
    void switchChar1();
    void saveChar1();
    void saveGame();
    void show_stats();


};

#endif
