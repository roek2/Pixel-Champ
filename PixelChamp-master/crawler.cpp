#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "crawlerHeader.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "particleHeader.h"
//using namespace std;

extern SDL_Surface *screen;
extern SDL_Surface *pixel;
extern SDL_Rect camera;
extern int NORMAL_TILES;
extern int TOTAL_PARTICLES;
extern int Solid_Tile;
extern Mix_Music *music;
extern SDL_Rect enemyClips[];
extern LTexture enemySheetClip;
extern LTexture enemySheetClipOuch;

crawler:: crawler(int x, int y, int health, int w, int h)
         :enemy(x, y, health, w, h)
{
    xVel = 2;
    animate_counter = 0;
    direction = true;
    defence = 3;
}

 void crawler :: move(Tile *tiles[], Dot myDot)
{

     if(!touches_ground(tiles) && yVel < 24)
     {
         yVel++;
     }

  //  if(!touches_ground(tiles))
    {
        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( fix_collision( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (tiles[ t ]->box.y - (box.y + box.h)) < yVel)
                        yVel = ( tiles[ t ]->box.y - (box.y + box.h));
                }
            }
        }

        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( left_collision2( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (tiles[ t ]->box.x - (box.x + box.w)) < xVel)
                       collide();// xVel = xVel * -1;

                }
            }
        }

        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( right_collision2( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (box.x - (tiles[ t ]->box.x + tiles[ t ]->box.w ) > xVel))                                             ////absolute value?????
                        collide(); //xVel = xVel * -1;
                }
            }
        }


    }

    for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( fix_collision( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (tiles[ t ]->box.y - (box.y + box.h)) < yVel)
                        yVel = ( tiles[ t ]->box.y - (box.y + box.h));
                }
            }
        }




  //   else if(touches_left(tiles) || touches_right(tiles))
   //  {
   //      xVel = xVel * -1;
   //  }
    if(touches_ground2(tiles))
    {
        onGround = true;
    }

    else
    {
        onGround = false;
    }

     box.y += yVel;


     box.x += xVel;


     if(xVel < 0)
        direction = false;
     else
        direction = true;

     run(myDot, tiles);

}


void crawler:: run(Dot myDot, Tile *tiles[])
{

}

void crawler::collide()
{
     xVel = xVel * -1;
}

void crawler::lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv)
{
     if(get_health() <= 0)
               alive = false;

     move(tiles, myDot);
     tempvinsibility();
     hit(square, myDot, bullets, conv);
     collatural_damage();
     ouched();
     SDL_Color textColor4 = { 200, 0, 0 };
}

void crawler::collide_down()
{
     yVel = 5;
}

void crawler :: knockBack(Dot myDot)
{
     if(myDot.box.x < box.x)                          //NEEDS TO BE MADE ENEMY SPECIFIC
         xVel = 2;
     else
         xVel = -2;
     yVel = -5;

}

bool crawler :: survey(Dot myDot, Tile *tiles[])
{
        return false;
}

void crawler:: animation(Setup test)
{

    if(!direction)
    {
        spriteNumber = 10;
        animate_counter++;
        if(animate_counter < 10)
        {
            spriteNumber = 11;
        }
        else if(animate_counter > 20)
        {
            animate_counter = 0;
        }
    }

    else
    {
        spriteNumber = 12;
        animate_counter++;
        if(animate_counter < 10)
        {
            spriteNumber = 13;
        }
        else if(animate_counter > 20)
        {
            animate_counter = 0;
        }
    }

}

void crawler :: outWithABang()
{

    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        particles[ p ]->show();
        particles2[ p ]->show();
        particles[ p ]->PartLeft();
        particles2[ p ]->PartRight();
    }
}

void crawler :: die()
{
    if(!dead)
    {
        for( int p = 0; p < TOTAL_PARTICLES; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y, 3);
            particles2[ p ] = new Particle( box.x, box.y, 3);
        }
    }
    dead = true;
    outWithABang();
}


void crawler:: show()
{
    if(check_collision( camera, box ) == true )
    {
        enemySheetClip.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
        if(ouch_counter < 5)
            enemySheetClipOuch.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
    }
}
