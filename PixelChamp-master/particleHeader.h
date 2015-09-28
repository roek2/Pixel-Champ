#include "SDL.h"
#ifndef PARTICLEHEADER
#define PARTICLEHEADER

class Tile;
class Particle : public base
{
    private:
    //Offsets
    int x, y, colour;

    //Current frame of animation
    int frame;

    //Type of particle
    SDL_Surface *type;

    public:
    //Constructor
    Particle( int X, int Y, int C );

    //Shows the particle
    void show();

    int getFrame();

    void PartLeft();

    void PartRight();

    void PartLeft2();

    void PartRight2();

    void orbit(SDL_Rect box);

    void orbit2();

    int fallLeft();

    void orbit_start(SDL_Rect);

    //Checks if particle is dead
    bool is_dead();

    int is_falling();

    int to_player();

    bool done;
};

#endif
