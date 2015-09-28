#include "SDL.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "dotHeader.h"
#include "companionHeader.h"
#include "tileHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include "converterHeader.h"
#include "particleHeader.h"
#include "LTextureHeader.h"
#include <fstream>

LTexture comp1;
extern SDL_Rect camera;
extern bool direction;
extern bool moving_left;
extern bool moving_right;
int anim_counter = 0;
int anim_counter2 = 0;
extern int scene;

companion:: companion()
{
    box.x = 0;
    box.y = 1250;
    box.w = 40;
    box.h = 50;
    moving = false;
    jump_counter = 31;
}

int companion:: get_xVel()
{
    return xVel;
}

void companion:: live(Dot myDot, Tile *tiles[] )
{
   //  apply_surface( box.x - camera.x, box.y - camera.y, comp, screen );



     if(!direction)
     {
        if(box.x < myDot.box.x - 60)
        {
            xVel = 10;
        }

        else if(box.x > myDot.box.x - 50)
        {
            xVel = -10;
        }

        else
         {
            xVel = 0;
         }
     }

     if(direction)
     {
        if(box.x < myDot.box.x + 50)
        {
            xVel = 8;
            moving = true;
        }

        else if(box.x > myDot.box.x + 60)
        {
            xVel = -8;
            moving = true;
        }

        else
        {
            xVel = 0;

        }

     }

     if(myDot.box.y + 100 < box.y && (myDot.box.x -box.x > 100 || box.y - myDot.box.x > 100 ))
        {
            if(onGround && !jump && canJump){
            jump = true;
            onGround = false;
            yVel =- 25;
     }
        }

    if(scene == 1)
    {
        xVel = 4;
        direction = false;
    }

    if(scene == 2)
    {
        xVel = 8;
        if(onGround && !jump && canJump && box.x > 2300 && jump_counter != 50){
            jump = true;
            onGround = false;
            yVel =- 25;
            jump_counter = 0;

        }

        if(jump_counter == 30)
        {
            for( int p = 0; p < 20; p++ )
            {
                particles[ p ] = new Particle( box.x, box.y + box.h, 5);
                particles2[ p ] = new Particle( box.x + box.w, box.y + box.h, 5);
            }

            yVel = -25;
            jump = true;
            second_jump = true;
            jump_counter = 50;
        }
    }


    if(jump_counter < 30)
        jump_counter++;

    move2(tiles);

}

void companion :: animate(Dot myDot)
{

     part_effect(box);
     if(xVel != 0)
        anim_counter++;

     if(box.x > myDot.box.x && scene != 2)
     {
           comp1.loadFromFile( "companion3.png" );
          // comp = load_image( "Untitled_c2.png" );

           if(anim_counter > 4 && is_onGround())
           {
                 comp1.loadFromFile( "companion4.png" );
            //     comp = load_image( "Untitled_c4.png" );
                 if(anim_counter2 == 2)
                 {
                    anim_counter = 0;
                    anim_counter2 = 0;
                 }
                 anim_counter2++;
                 //return false;
           }
     }

     else
     {
          comp1.loadFromFile( "companion.png" );
          if(anim_counter > 4 && is_onGround())
          {
                 comp1.loadFromFile( "companion2.png" );
           //      comp = load_image( "Untitled_c3.png" );
                 if(anim_counter2 == 2)
                 {
                    anim_counter = 0;
                    anim_counter2 = 0;
                 }
                 anim_counter2++;
                 //return false;
          }
     }
     comp1.render(box.x - camera.x, box.y - camera.y);
}
