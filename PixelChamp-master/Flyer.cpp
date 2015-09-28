#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "Flyer.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "particleHeader.h"

//extern SDL_Surface *enemy2;
extern SDL_Surface *screen;
extern SDL_Surface *pixel;
extern SDL_Rect camera;
extern int NORMAL_TILES;
extern int TOTAL_PARTICLES;
extern int Solid_Tile;
extern Mix_Music *music;
extern SDL_Rect enemyClips[];
extern SDL_Rect enemyClipsBig[];
extern LTexture enemySheetClip;
extern LTexture enemySheetClipBig;
extern LTexture enemySheetClipOuch;
extern Mix_Chunk *enemyDeathSound;

Flyer::Flyer(int x, int y, int health, int w, int h):enemy(x, y, health, w, h)
{
    direction = true;
    home = true;
    int type = 1;
    //defence = 3;
}

void Flyer :: move(Tile *tiles[], Dot myDot)
{

     if(!touches_ground(tiles) && yVel < 24)
     {
    //     yVel++;
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

   //  xVel = 0;
  //   yVel = 0;
     box.y += yVel;


     box.x += xVel;

     if(detect)
        run(myDot, tiles);
     else
        goHome();

}

void Flyer:: goHome()
{
    if(getXpos() <= getSpawnX())
        xVel = 8;
    else if(getYpos() <= getSpawnY())
        yVel = 8;
    else if(getXpos() >= getSpawnX() + 50)
        xVel = -8;
    else if(getYpos() >= getSpawnY() + 50)
        yVel = -8;
    else
    {
        xVel = 0;
        yVel = 0;
        home = true;
    }

    if(home == false && detect == false && (getXpos() + box.w < camera.x || getXpos() > camera.x + camera.w || getYpos() + box.h < camera.y || getYpos() > camera.y + camera.h) && (getSpawnX() + box.w < camera.x || getSpawnX() > camera.x + camera.w || getSpawnY() + box.h < camera.y || getSpawnY() > camera.y + camera.h))
    {
        box.x = getSpawnX();
        box.y = getSpawnY();
    }
}

void Flyer:: run(Dot myDot, Tile *tiles[])
{

    if(myDot.getXpos() >= getXpos())
    {
        if(xVel <= 8)
            xVel++;
    }
    else
    {
        if(xVel >= -8)
            xVel--;
    }

    if(myDot.getYpos() >= getYpos() )
    {
        if(yVel <= 8)
            yVel++;
    }
    else
    {
        if(yVel >= -8)
            yVel--;
    }

}

void Flyer::collide()
{
     xVel = xVel * -1;
}

void Flyer::collide_down()
{
     yVel = 5;
}

void Flyer::lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv)
{
     if(get_health() <= 0)
               alive = false;

     move(tiles, myDot);
     tempvinsibility();
     hit(square, myDot, bullets, conv);
     collatural_damage();

     if(survey(myDot, tiles) == true)
        {
        detect = true;
        detect_counter = 0;
        home = false;
        }

     else if(survey(myDot, tiles) == false)
        detect_counter++;

     if(survey(myDot, tiles) == false && detect_counter > 150)
     {
        detect = false;
        detect_counter = 0;
     }

     if(detect && myDot.box.x > box.x)
        direction = true;
     else
        direction = false;

    ouched();
}

void Flyer :: knockBack(Dot myDot)
{
    int chance = rand() % 10;
    if(type == 5)
        chance = rand() % 15;
    if(chance > 2)
    {
         if(myDot.box.x < box.x)                          //NEEDS TO BE MADE ENEMY SPECIFIC
             xVel = 17;
         else
             xVel = -17;
         yVel = 6;
    }

}

bool Flyer :: survey(Dot myDot, Tile *tiles[])
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
            //    apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
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
          //      apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
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

void Flyer:: animation(Setup test)
{
    if(direction)
    {
        spriteNumber = 1;
        if(animate_counter > 5)
            spriteNumber = 4;
        if(animate_counter > 10)
            animate_counter = 0;
    }

    else
    {
        spriteNumber = 2;
        if(animate_counter > 5)
            spriteNumber = 3;
        if(animate_counter > 10)
            animate_counter = 0;
    }

    if(xVel != 0)
        animate_counter++;

    if(home)
        spriteNumber = 5;
}

void Flyer :: outWithABang()
{

    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        particles[ p ]->show();
        particles2[ p ]->show();
        particles[ p ]->PartLeft();
        particles2[ p ]->PartRight();
    }
}

void Flyer :: die()
{
    if(!dead)
    {
        for( int p = 0; p < TOTAL_PARTICLES; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y, 1);
            particles2[ p ] = new Particle( box.x, box.y, 1);
        }
        Mix_PlayChannel( -1, enemyDeathSound, 0 );
    }
    dead = true;
    outWithABang();
}


void Flyer:: show()
{
    if(check_collision( camera, box ) == true )
    {
        if(type == 1)
        {
            enemySheetClip.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
            if(ouch_counter < 5)
                enemySheetClipOuch.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
        }

        else if(type == 5)
        {
            enemySheetClipBig.render(box.x - camera.x, box.y - camera.y, &enemyClipsBig[spriteNumber]);
        }
    }
}


