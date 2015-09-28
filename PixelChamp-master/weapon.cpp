#include "SDL.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "weaponHeader.h"
#include "dotHeader.h"
#include <fstream>

extern SDL_Surface *weapons;
extern SDL_Surface *screen;
extern SDL_Rect camera;
extern SDL_Event event;
extern bool direction;


weapon:: weapon(int length, int width)
{
         box.x = 20;
         box.y = 30;
         box.w = length;
         box.h = width;
         le = length;
         wi = width;
         attack = false;
         hit = false;
         canAttack = true;
         look_up = false;
         look_down = false;

}

int weapon:: get_width()
{
    return wi;
}

SDL_Rect weapon :: get_position(Dot myDot)
{
}

void weapon:: weaponControl()
{

}

void weapon:: melee()
{
     attack = true;
     if(attack)
        canAttack = false;
}

void weapon:: show()
{

}
