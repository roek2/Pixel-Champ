#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "setupHeader.h"
#include "weaponHeader.h"
#include "dotHeader.h"
#include "gunHeader.h"
#include "enemyHeader.h"
#include "tileHeader.h"
#include "LTextureHeader.h"
#include "converterHeader.h"
#include "particleHeader.h"

extern SDL_Event event;
extern bool direction;
extern int NORMAL_TILES;
extern bool shoot_down;
extern SDL_Surface *screen;
extern SDL_Rect camera;
extern SDL_Surface *weapons2;
extern int monster_count;
extern LTexture weapons2T;
extern bool up;
extern bool down;
int box_num2 = 1;
extern int Solid_Tile;
extern Mix_Chunk *gunSound;
extern int trueWidth;
extern int trueHeight;


gun:: gun(int length, int width)
         :weapon(length, width)
{
    project = 0;
    shot = false;
    shot_dis = 0;
    right = false;
    left = false;
    speed = 30;
    charge = 0;
}

SDL_Rect gun :: get_position(Dot myDot, Setup foo)
{
    if(look_up)
    {
        box.x = myDot.box.x;
        box.y = myDot.box.y;
        weapons2T.loadFromFile( "first_test16.bmp" );
    }

    else if(look_down && !myDot.is_onGround())                      ///very much so temp--- this should be its own move, once i get moves sorted :D
    {
        box.x = myDot.box.x;
        box.y = myDot.box.y + (myDot.box.h - speed);
        weapons2T.loadFromFile( "first_test15.bmp" );
    }

    else
    {

         if(!direction)
         {
             box.x = myDot.box.x +  (trueWidth - speed);
             weapons2T.loadFromFile( "first_test14.bmp" );
         }
         else
         {
             box.x = (myDot.box.x - 128) + (128 - trueWidth);
             weapons2T.loadFromFile( "first_test13.bmp" );
         }
         box.y = myDot.box.y + trueHeight/2;
    }
    return box;
}

void gun:: weaponControl(Dot myDot)
{
 // Uint8 *keystates = SDL_GetKeyState( NULL );
    Mix_PlayChannel( -1, gunSound, 0 );
    if(!direction)
    {
        right = true;
        left = false;
    }
    else
    {
        left = true;
        right = false;
    }

    if(up)
    {
         look_up = true;
         right = false;
         left = false;
    }

    else
    {
         look_up = false;
    }

    if(down && !myDot.is_onGround())
    {
         look_down = true;
    }

    else
    {
         look_down = false;
    }

    for( int p = 0; p < 20; p++ )
    {
        particles[ p ] = new Particle( box.x, box.y, 4);
    }

}

bool gun::perPixel( ColRect pixel_array6[], int size, SDL_Rect box2)
{

        box_num2 = 0;
        while(box_num2 < size)
        {
            pixel_array6[box_num2].box.x = box.x + pixel_array6[box_num2].box.x;
            pixel_array6[box_num2].box.y = box.y + pixel_array6[box_num2].box.y;

            if( check_collision( pixel_array6[box_num2].box, box2 ) == true)
            {
                if(pixel_array6[box_num2].level == 1 ||  pixel_array6[box_num2].level == 2 || pixel_array6[box_num2].level == 3 || pixel_array6[box_num2].level == 4 || pixel_array6[box_num2].level == 5)
                {
                    pixel_array6[box_num2].box.x = pixel_array6[box_num2].box.x - box.x;
                    pixel_array6[box_num2].box.y = pixel_array6[box_num2].box.y - box.y;
                    box_num2++;
                }

                else if(pixel_array6[box_num2].level == 6)
                {
                    pixel_array6[box_num2].box.x = pixel_array6[box_num2].box.x - box.x;
                    pixel_array6[box_num2].box.y = pixel_array6[box_num2].box.y - box.y;
                    return true;
                }
            }

            else
            {
                if(pixel_array6[box_num2].jump < 1000)
                {
                    pixel_array6[box_num2].box.x = pixel_array6[box_num2].box.x - box.x;
                    pixel_array6[box_num2].box.y = pixel_array6[box_num2].box.y - box.y;
                    box_num2 = box_num2 + pixel_array6[box_num2].jump;;

                }

                else
                {
                    pixel_array6[box_num2].box.x = pixel_array6[box_num2].box.x - box.x;
                    pixel_array6[box_num2].box.y = pixel_array6[box_num2].box.y - box.y;
                    box_num2 = box_num2 + 5000;
                }

            }
        }
    //If no wall tiles were touched
    return false;
}



void gun:: shoot(Dot myDot, enemy *monsters[], Tile *tiles[], Converter conv)
{
    melee();
    if(look_up)
        box.y -= speed;
    else if(look_down)
    {
        shoot_down = true;
        box.y += speed;
    }
    else if(right)
        box.x += speed;              //   take away speed, creates little mines
    else if(left)
        box.x -= speed;
    shot = true;

    shot_dis++;

    for(int i = 0; i < monster_count; i++)
    {
        if(check_collision( box, monsters[i]->box) == true && monsters[i]->alive)
        {
         //   shot = false;
            shot_dis = 0;
        }
    }


    for( int i = 0; i < NORMAL_TILES; i++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->get_type() == Solid_Tile ) )
        {

            if(check_collision( box, tiles[i]->box) == true)
            {

                if(look_up)
                {
                    if(perPixel(conv.pixel_array10, conv.size10, tiles[i]->get_box()))
                    {
                        shot = false;
                        shot_dis = 0;
                    }
                }

                else if(look_down)
                {
                    if(perPixel(conv.pixel_array9, conv.size9, tiles[i]->get_box()))
                    {
                        shot = false;
                        shot_dis = 0;
                    }
                }

                else if(!direction)
                {
                    if(perPixel(conv.pixel_array8, conv.size8, tiles[i]->get_box()))
                    {
                        shot = false;
                        shot_dis = 0;
                    }
                }
                else
                {
                    if(perPixel(conv.pixel_array7, conv.size7, tiles[i]->get_box()))
                    {
                        shot = false;
                        shot_dis = 0;
                    }
                }
            }
        }
    }
}

void gun:: power_surge()
{
    for( int p = 0; p < 10; p++ )
    {
        particles[ p ]->orbit(box);
        particles[ p ]->show();
    }
}

void gun:: show()
{
    if(check_collision(box, camera))
        weapons2T.render(box.x - camera.x, box.y - camera.y);
}
