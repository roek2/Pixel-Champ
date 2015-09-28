#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "jumperHeader.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "particleHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"

extern SDL_Surface *screen;
extern SDL_Surface *pixel;
extern SDL_Rect camera;
extern int NORMAL_TILES;
extern int Solid_Tile;
extern Mix_Music *music;
extern int TOTAL_PARTICLES;
extern SDL_Rect enemyClips[];
extern LTexture enemySheetClip;
extern LTexture enemySheetClipOuch;
extern Mix_Chunk *enemyDeathSound;
extern LTexture enemySheetClipBig;
extern SDL_Rect enemyClipsBig[];

jumper:: jumper(int x, int y, int health, int w, int h)
         :enemy(x, y, health, w, h)
{
    jumping = false;
    direction = true;
    defence = 2;
    died = false;
}

bool jumper:: isJumping()
{
    return jumping;
}

 void jumper :: move(Tile *tiles[], Dot myDot)
{

     if(!touches_ground(tiles) && yVel < 24)
     {
         yVel++;
         jumping = true;
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

    for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( roof_collision( box, tiles[ t ]->get_box() ) == true )
                {
                    if( ((tiles[ t ]->box.y + tiles[ t ]->box.h) - box.y) > yVel)
                        collide_down();
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

     run(myDot, tiles);

}


void jumper:: run(Dot myDot, Tile *tiles[])
{

     int dis = 4;
     if((myDot.box.x < box.x && box.x - myDot.box.x < 60) || (myDot.box.x > box.x &&  myDot.box.x - (box.x + box.w) < 60))
     {
             dis = 2;
     }

     if(touches_ground(tiles) && jump_counter < 25)
     {
        xVel = 0;

     }

     if(touches_ground(tiles))
        jumping = false;
     else
        jumping = true;

     if(touches_ground(tiles) && detect)
     {
         jump_counter++;
     }

        if(myDot.box.x > box.x && onGround && jump_counter > 25)
        {
         jump();
         xVel = dis;
         jump_counter = 0;
         direction = true;
        }
        else if(myDot.box.x < box.x && onGround && jump_counter > 25 )
        {
         jump();
         xVel = -dis;
         jump_counter = 0;
         direction = false;

         }
}

void jumper::collide()
{
     xVel = xVel * -1;
}

void jumper::lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv)
{
     if(get_health() <= 0)
        alive = false;

    if(alive)
        died = false;

     move(tiles, myDot);
     tempvinsibility();
     hit(square, myDot, bullets, conv);
     collatural_damage();

     if(survey(myDot, tiles) == true)
        {
        detect = true;
        detect_counter = 0;
        }

     else if(survey(myDot, tiles) == false)
        detect_counter++;

     if(survey(myDot, tiles) == false && detect_counter > 150)
     {
        detect = false;

        detect_counter = 0;
     }

    ouched();

}

void jumper:: collide_down()
{
    yVel = 5;
}

void jumper :: outWithABang()
{

    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        particles[ p ]->show();
        particles2[ p ]->show();
        particles[ p ]->PartLeft();
        particles2[ p ]->PartRight();

    }
}

void jumper :: die()
{
    if(!died)
    {
        for( int p = 0; p < TOTAL_PARTICLES; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y, 0);
            particles2[ p ] = new Particle( box.x, box.y, 0);
        }
        Mix_PlayChannel( -1, enemyDeathSound, 0 );
    }
    died = true;
    outWithABang();
    dead = true;
}

void jumper :: knockBack(Dot myDot)
{
     if(myDot.box.x < box.x)                          //NEEDS TO BE MADE ENEMY SPECIFIC
         xVel = 5;
     else
         xVel = -5;
     yVel = -6;
}

bool jumper :: survey(Dot myDot, Tile *tiles[])
{

     test.x = box.x + 39;
     test.y = box.y + 40;
     int i = 0;
     int z = 5;
        for(int j = 0; j < 10; j++ )
        {
             //the line are 30 points long as long as they dont collide with a wall, then the lines end
            while(i < 30 && point2wall(tiles) == false)
            {
                //the gap between the points
                test.x -= 10;
                test.y += z;
              //  apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
                if(point_collision(test, myDot.box))
                {
                    return true;
                }
                i++;
            }

        test.x = box.x + 39;
        test.y = box.y + 40;
        //angle changes
        z -= 2;
        i = 0;
        }

        i = 0;
        z = 5;
        test.x = box.x + 41;
        test.y = box.y + 40;

        for(int j = 0; j < 10; j++ )
        {
            while(i < 30 && point2wall(tiles) == false)
            {
                test.x += 10;
                test.y += z;
               // apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
                if(point_collision(test, myDot.box))
                {

                    return true;
                }
                i++;
            }

            test.x = box.x + 41;
            test.y = box.y + 40;
            z -= 2;
            i = 0;
        }


        return false;
}

void jumper:: animation(Setup test)
{
    if(!direction)
    {
        spriteNumber = 8;
        if(isJumping())
        {
            spriteNumber = 6;
        }
    }

    else
    {
        spriteNumber = 7;
        if(isJumping())
        {
            spriteNumber = 9;
        }
    }

}

void jumper:: show()
{
    if(check_collision( camera, box ) == true )
    {

        if(type == 6)
        {
            enemySheetClipBig.render(box.x - camera.x, box.y - camera.y, &enemyClipsBig[spriteNumber]);
        }
        else
        {
            enemySheetClip.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
            if(ouch_counter < 5)
                enemySheetClipOuch.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
        }
    }
}
