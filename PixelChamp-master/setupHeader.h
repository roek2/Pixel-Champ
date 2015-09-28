#include "SDL.h"
#ifndef SETUPHEADER
#define SETUPHEADER

class Dot;

class Setup
{
     public:
        //initialises the game
     bool init();
        //loads an image
     SDL_Surface *load_image( std::string filename );
        //loads all the needed files for the game
     bool load_files();

     bool animate(Dot myDot);

     void clip_tiles();
};

#endif
