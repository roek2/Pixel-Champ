#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <fstream>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "chargerHeader.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "particleHeader.h"

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

charger:: charger(int x, int y, int health, int w, int h)
         :enemy(x, y, health,w , h)
{
         direction = true;
         counter2 = 51;                                 ///THis isnt great, needs to be re-done
         left_charge = false;
         right_charge = false;
         mozey_counter = 0;
         startingX = x;
         startingY = y;
         charge = 0;
         animate_counter = 0;
         animate_counter2 = 0;
         moving = false;
         angry = false;
         stunAnimCount = 0;
         defence = 2;
}

void charger :: move(Tile *tiles[], Dot myDot)
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
                       collide_left();// xVel = xVel * -1;

                }
            }
        }

        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( right_collision2( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (box.x - (tiles[ t ]->box.x + tiles[ t ]->box.w) > xVel))                                             ////absolute value?????
                        collide_right(); //xVel = xVel * -1;
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
 //    xVel = 0;
     box.y += yVel;

     box.x += xVel;

     run(myDot, tiles);

}

void charger:: collide_down()
{
    yVel = 5;
}


void charger:: run(Dot myDot, Tile *tiles[])
{
     int dis = 10;
     xVel = 0;



        if((myDot.box.x > box.x && charge < 50 && !left_charge && jump_counter > 50) || (charge < 50 & right_charge))
        {
        // jump();
         xVel = dis;
         charge++;
         right_charge = true;

        }
        else if((myDot.box.x <= box.x && charge < 50 && !right_charge && jump_counter > 50) || (charge < 50 & left_charge))
        {
        // jump();
         xVel = -dis;
         charge++;
         left_charge = true;

        }

        if(charge >= 50)
        {
           counter2++;
           if(counter2 >= 100)
           {
              charge = 0;
              jump_counter = 0;
              counter2 = 0;
           }
        }

        if(charge == 0)
        {
         right_charge = false;
         left_charge = false;

        }

}

void charger :: knockBack(Dot myDot)
{
     yVel = -6;
     if(myDot.box.x < box.x)                          //NEEDS TO BE MADE ENEMY SPECIFIC
        xVel = 5;
     else
        xVel = -5;

}

void charger :: airStun()
{
    yVel = -15;
    launched = true;
}


void charger::collide_left()
{
     mozey_counter = 0;
     if(right_charge == true)
     {
      //  knockback();
     //   xVel = -20;
        charge = 50;

     }
}

void charger::collide_right()
{
   //  mozey_counter = 121;
     if(left_charge == true)
     {
       // knockback();
        xVel = 10;
        charge = 50;
     }
}

void charger::lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv)
{
     if(get_health() <= 0)
               alive = false;

     if(xVel < 0)
             direction = true;
     else if(xVel > 0)
             direction = false;

     move(tiles, myDot);
     tempvinsibility();
     hit(square, myDot, bullets, conv);
     collatural_damage();

     if(survey(myDot, tiles) == true)
     {
        detect = true;
        detect_counter = 0;
        jump_counter++;
     }

     else if(survey(myDot, tiles) == false)
     {
        detect_counter++;
        detect = false;
     }

     if(detect_counter > 100)
     {
        jump_counter = 0;
     }

     if(jump_counter > 30)
     {
        angry = true;
     }
     else
        angry = false;


     if(left_charge == true || right_charge == true)
     {
         mozey_counter = 20;
     }

     if(detect == false && right_charge == false && left_charge == false)
     {
        mozey();
     }

    if(xVel != 0)
    {
        moving = true;
    }

    else
    {
        moving = false;
    }

    launcher();
    ouched();


}

void charger :: launcher()
{
    if(stunCounter > 0 || launched)
    {
        xVel = 0;
        moving = false;
    }

    if(stunCounter > 0)
    {
        yVel = -1;
        stunCounter--;
    }

    if(launched && yVel == 0)
    {
        launched = false;
        stunCounter = 30;
    }
}

bool charger :: survey(Dot myDot, Tile *tiles[])
{

     test.x = box.x + 39;
     test.y = box.y + 40;
     int i = 0;
     int z = 5;
     if(direction == true)
     {
        for(int j = 0; j < 10; j++ )
        {
             //the line are 30 points long as long as they dont collide with a wall, then the lines end
            while(i < 30 && point2wall(tiles) == false)
            {
                //the gap between the points
                test.x -= 10;
                test.y += z;
 //               apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
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
      }

    else
    {
        for(int j = 0; j < 10; j++ )
        {
            while(i < 30 && point2wall(tiles) == false)
            {
                test.x += 10;
                test.y += z;
       //         apply_surface( test.x - camera.x, test.y - camera.y, pixel, screen );
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
    }

    return false;
}

void charger :: mozey()                                                            //re-do to be positions not counters?
{

     if(mozey_counter < 0)
     {

     }

     else if (mozey_counter <= 50)
     {
        xVel = 4;

     }

     else if (mozey_counter <= 120)
     {

     }

     else if (mozey_counter >= 120 && mozey_counter <= 240)
     {
        xVel = -4;
     }

     else if (mozey_counter >= 240 && mozey_counter <= 320)
     {
     }

     else if (box.x < startingX)
     {
        xVel = 4;
     }

     else if (box.x > startingX)
     {
        xVel = -4;                                                                                      // make these actions random :D
     }

     else if (mozey_counter >= 500)
     {
        mozey_counter = 0;
     }


     mozey_counter++;

}

void charger:: animation(Setup test)
{
     animate_counter++;

     if(direction == true )
     {
           spriteNumber = 15;
           if(angry == true && !moving)
                spriteNumber = 20;
           if(left_charge || right_charge)
                spriteNumber = 22;

           if(animate_counter > 6 && moving)
           {
                 spriteNumber = 17;
                 if(left_charge || right_charge)
                    spriteNumber = 19;

                 if(animate_counter2 == 6)
                 {
                    animate_counter = 0;
                    animate_counter2 = 0;
                 }
                 animate_counter2++;
                 //return false;
           }
      //    if((stunCounter > 0 || launched) && stunAnimCount <= 2)
      //    {
      //      enemys = test.load_image( "NpcEggs3.bmp" );
      //      stunAnimCount++;
       //   }
     //     else if((stunCounter > 0 || launched) && stunAnimCount <= 4)
      //    {
      //      enemys = test.load_image( "NpcEggs23.bmp" );
       //     stunAnimCount++;
    //      }

          if((stunCounter > 0 || launched))
          {
              spriteNumber = 14;
              stunAnimCount++;
          }

    //      else if((stunCounter > 0 || launched) && stunAnimCount <= 8)
    //      {
    //          enemys = test.load_image( "NpcEggs43.bmp" );
    //          stunAnimCount++;
    //      }

    //      else if((stunCounter > 0 || launched) && stunAnimCount > 8)
   //       {
   //         enemys = test.load_image( "NpcEggs3.bmp" );
  //          stunAnimCount = 1;
    //      }


     }

     else
     {
         // dot = load_image( "first_test5.bmp" );
          spriteNumber = 16;
          if(angry == true && !moving)
            spriteNumber = 21;
          if(left_charge || right_charge)
            spriteNumber = 23;

          if(animate_counter > 6 && moving)
          {
                 spriteNumber = 18;
                if(left_charge || right_charge)
                    spriteNumber = 24;
                 if(animate_counter2 == 6)
                 {
                    animate_counter = 0;
                    animate_counter2 = 0;
                 }
                 animate_counter2++;
                 //return false;
          }
      //    if((stunCounter > 0 || launched) && stunAnimCount <= 2)
      //    {
      //      enemys = test.load_image( "NpcEggs3.bmp" );
      //      stunAnimCount++;
       //   }
     //     else if((stunCounter > 0 || launched) && stunAnimCount <= 4)
      //    {
      //      enemys = test.load_image( "NpcEggs23.bmp" );
       //     stunAnimCount++;
    //      }

          if((stunCounter > 0 || launched))
          {
              spriteNumber = 14;
              stunAnimCount++;
          }

    //      else if((stunCounter > 0 || launched) && stunAnimCount <= 8)
    //      {
    //          enemys = test.load_image( "NpcEggs43.bmp" );
    //          stunAnimCount++;
    //      }

    //      else if((stunCounter > 0 || launched) && stunAnimCount > 8)
   //       {
   //         enemys = test.load_image( "NpcEggs3.bmp" );
  //          stunAnimCount = 1;
    //      }

     }

     if(stunCounter == 0 && !launched)
        stunAnimCount = 0;

}

void charger :: outWithABang()
{

    for( int p = 0; p < TOTAL_PARTICLES; p++ )
    {
        particles[ p ]->show();
        particles2[ p ]->show();
        particles[ p ]->PartLeft();
        particles2[ p ]->PartRight();
    }
}

void charger :: die()
{
    if(!dead)
    {
        for( int p = 0; p < TOTAL_PARTICLES; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y, 2);
            particles2[ p ] = new Particle( box.x, box.y, 2);
        }
    }
    dead = true;
    outWithABang();
}


void charger:: show()
{
    if(check_collision( camera, box ) == true )
    {
        enemySheetClip.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
        if(ouch_counter < 5)
            enemySheetClipOuch.render(box.x - camera.x, box.y - camera.y, &enemyClips[spriteNumber]);
    }
}


