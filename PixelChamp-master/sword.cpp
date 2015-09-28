#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "weaponHeader.h"
#include "dotHeader.h"
#include "setupHeader.h"
#include "swordHeader.h"
#include "LTextureHeader.h"

extern SDL_Event event;
extern bool direction;
extern SDL_Surface *weapons;
extern SDL_Surface *screen;
extern SDL_Rect camera;
extern bool up;
extern bool down;
extern LTexture weaponsT;
extern bool swording;
extern Mix_Chunk *swordSound;
extern int trueWidth;
extern int trueHeight;
extern int properHeight;

sword:: sword(int length, int width)
         :weapon(length, width)
{
    attack_damage = 10;
}

SDL_Rect sword :: get_position(Dot myDot, Setup foo)
{
    if(look_up)
    {
        box.x = myDot.box.x;
        box.y = (myDot.box.y - le) + properHeight;
        weaponsT.loadFromFile( "first_test12.bmp" );

    }

    else if(look_down && !myDot.is_onGround())                      ///very much so temp--- this should be its own move, once i get moves sorted :D
    {
        box.x = myDot.box.x;
        box.y = myDot.box.y + myDot.box.h;
        weaponsT.loadFromFile( "first_test11.bmp" );
    }

    else
    {

         if(!direction)
         {
             box.x = myDot.box.x +  trueWidth;
             weaponsT.loadFromFile( "first_test10.bmp" );
         }
         else
         {
             box.x = (myDot.box.x - 128) + (128 - trueWidth);
             weaponsT.loadFromFile( "first_test9.bmp" );
         }
         box.y = myDot.box.y + trueHeight/2;
         return box;
    }
}

void sword:: weaponControl()
{

    if(swording  && canAttack == true)
    {
        melee();
        Mix_PlayChannel( -1, swordSound, 0 );
    }
    else if(!swording)
    {
        canAttack = true;
    }

    if(up)
    {
         look_up = true;
    }

    else
    {
         look_up = false;
    }

    if(down)
    {
         look_down = true;
    }

    else
    {
         look_down = false;
    }

}

void sword:: show()
{
        weaponsT.render(box.x - camera.x, box.y - camera.y);
}

