#include "SDL.h"
#include "SDL_image.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "baseHeader.h"
#include "enemyHeader.h"
#include "setupHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "particleHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"

extern SDL_Surface *enemys;
extern SDL_Surface *screen;
extern SDL_Surface *pixel;
extern SDL_Rect camera;
extern int NORMAL_TILES;
extern int Solid_Tile;
extern bool dash_invul;
extern bool combo;
extern int TOTAL_PARTICLES;
extern bool direction;
extern int swordStr;
extern int gunStr;
LTexture damage;
LTexture damage1;
LTexture damageA;
LTexture damageA1;
int charge;
extern int charge1;
extern int charge2;
extern int charge3;
bool bouncing = false;

enemy:: enemy(int x, int y, int health, int w, int h)
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;                                                                 ////   ALERT
    he = health;                                                               //        |
    xVel = 0;                                                                  //        |
    yVel = 0;                                                                  //        |
    hurt = true;                                                               //        V
    hurt_counter = 0;
    jump_counter = 0;                                  ////changed this from 0 could be causing jumper problems //////////////
    detect = false;
    detect_counter = 0;
    alive = true;
    launchable = false;
    type = 1;
    spawnX = x;
    spawnY = y;
    box_num = 1;
    spriteNumber = 1;
    perPC = false;
    perPCG = false;
    ouch_counter = 20;
    dead = false;
    damage_counter = 40;
    damage_counter2 = 40;
    showing_damage1 = false;
    showing_damage2 = false;
    pain = 0;
    pain1 = 1;
}

enemy:: enemy()
{

}

int enemy:: get_health()
{
    return he;
}

int enemy :: getXpos()
{
    return box.x;
}


int enemy :: getYpos()
{
    return box.y;
}

int enemy :: getSpawnX()
{
    return spawnX;
}

int enemy :: getSpawnY()
{
    return spawnY;
}

void enemy:: show()
{

}

void enemy :: loadEnemyTiles()
{
 //   enemySpriteClip->loadFromFile( "EnemyClips.png" );
}

void enemy :: move(Tile *tiles[], Dot myDot)
{

}

bool enemy::touches_wall( Tile *tiles[])
{

    //Go through the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true)
            {
                return true;
            }
        }
    }
    return false;
}

void enemy::collide()
{

}


bool enemy::touches_ground(Tile *tiles[])
{

    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( ground_collision( box, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}

bool enemy::touches_ground2(Tile *tiles[])
{

    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( ground_collision2( box, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}

bool enemy::touches_left(Tile *tiles[])
{

    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( left_collision( box, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}

bool enemy::touches_right(Tile *tiles[])
{

    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( right_collision( box, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}




void enemy:: jump()
{
         yVel = -14;

}

void enemy:: run(Dot myDot, Tile *tiles[])
{

}

void enemy:: ouched()
{
     if(ouch_counter > 15)
     {

     }

     else
     {
        ouch_counter++;
     }

}

void enemy:: tempvinsibility()
{
     if(!hurt)
     {
       hurt_counter++;
     }

     if(hurt_counter == 6)
     {
        hurt = true;
        hurt_counter = 0;
     }
}

bool enemy::perPixelCollision(sword square, Converter conv)
{
    return false;
    if( check_collision( box, square.box) == true)
    {
        return false;
        conv.begin = true;
        box_num++;
    }

    if(conv.begin)
    {

        if(square.look_up)
        {
            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size6)
            {
                conv.pixel_array6[box_num].box.x = box.x + conv.pixel_array6[box_num].box.x;
                conv.pixel_array6[box_num].box.y = box.y + conv.pixel_array6[box_num].box.y;

                if( check_collision( conv.pixel_array6[box_num].box, box ) == true)
                {
                    if(conv.pixel_array6[box_num].level == 1 ||  conv.pixel_array6[box_num].level == 2 || conv.pixel_array6[box_num].level == 3 || conv.pixel_array6[box_num].level == 4 || conv.pixel_array6[box_num].level == 5)
                    {
                        conv.pixel_array6[box_num].box.x = conv.pixel_array6[box_num].box.x - box.x;
                        conv.pixel_array6[box_num].box.y = conv.pixel_array6[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array6[box_num].level == 6)
                    {
                        conv.pixel_array6[box_num].box.x = conv.pixel_array6[box_num].box.x - box.x;
                        conv.pixel_array6[box_num].box.y = conv.pixel_array6[box_num].box.y - box.y;
                        return true;
                    }
                }

                else
                {
                    if(conv.pixel_array6[box_num].jump < 1000)
                    {
                        conv.pixel_array6[box_num].box.x = conv.pixel_array6[box_num].box.x - box.x;
                        conv.pixel_array6[box_num].box.y = conv.pixel_array6[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array6[box_num].jump;;

                    }

                    else
                    {
                        conv.pixel_array6[box_num].box.x = conv.pixel_array6[box_num].box.x - box.x;
                        conv.pixel_array6[box_num].box.y = conv.pixel_array6[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }

                }

            }
        }


        else if(square.look_down)
        {
            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size5)
            {
                conv.pixel_array5[box_num].box.x = box.x + conv.pixel_array5[box_num].box.x;
                conv.pixel_array5[box_num].box.y = box.y + conv.pixel_array5[box_num].box.y;

                if( check_collision( conv.pixel_array5[box_num].box, box ) == true)
                {
                    if(conv.pixel_array5[box_num].level == 1 ||  conv.pixel_array5[box_num].level == 2 || conv.pixel_array5[box_num].level == 3 || conv.pixel_array5[box_num].level == 4 || conv.pixel_array5[box_num].level == 5)
                    {
                        conv.pixel_array5[box_num].box.x = conv.pixel_array5[box_num].box.x - box.x;
                        conv.pixel_array5[box_num].box.y = conv.pixel_array5[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array5[box_num].level == 6)
                    {
                        conv.pixel_array5[box_num].box.x = conv.pixel_array5[box_num].box.x - box.x;
                        conv.pixel_array5[box_num].box.y = conv.pixel_array5[box_num].box.y - box.y;
                        return true;
                    }
                }

                else
                {
                    if(conv.pixel_array5[box_num].jump < 1000)
                    {
                        conv.pixel_array5[box_num].box.x = conv.pixel_array5[box_num].box.x - box.x;
                        conv.pixel_array5[box_num].box.y = conv.pixel_array5[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array5[box_num].jump;;

                    }

                    else
                    {
                        conv.pixel_array5[box_num].box.x = conv.pixel_array5[box_num].box.x - box.x;
                        conv.pixel_array5[box_num].box.y = conv.pixel_array5[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }

                }

            }
        }


        else if(!direction)
        {
            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size4)
            {
                conv.pixel_array4[box_num].box.x = box.x + conv.pixel_array4[box_num].box.x;
                conv.pixel_array4[box_num].box.y = box.y + conv.pixel_array4[box_num].box.y;

                if( check_collision( conv.pixel_array4[box_num].box, box ) == true)
                {
                    if(conv.pixel_array4[box_num].level == 1 ||  conv.pixel_array4[box_num].level == 2 || conv.pixel_array4[box_num].level == 3 || conv.pixel_array4[box_num].level == 4 || conv.pixel_array4[box_num].level == 5)
                    {
                        conv.pixel_array4[box_num].box.x = conv.pixel_array4[box_num].box.x - box.x;
                        conv.pixel_array4[box_num].box.y = conv.pixel_array4[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array4[box_num].level == 6)
                    {
                        conv.pixel_array4[box_num].box.x = conv.pixel_array4[box_num].box.x - box.x;
                        conv.pixel_array4[box_num].box.y = conv.pixel_array4[box_num].box.y - box.y;
                        return true;
                    }
                }

                else
                {
                    if(conv.pixel_array4[box_num].jump < 1000)
                    {
                        conv.pixel_array4[box_num].box.x = conv.pixel_array4[box_num].box.x - box.x;
                        conv.pixel_array4[box_num].box.y = conv.pixel_array4[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array4[box_num].jump;;

                    }

                    else
                    {
                        conv.pixel_array4[box_num].box.x = conv.pixel_array4[box_num].box.x - box.x;
                        conv.pixel_array4[box_num].box.y = conv.pixel_array4[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }

                }

            }
        }

        else
        {
            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size3)
            {
                conv.pixel_array3[box_num].box.x = box.x + conv.pixel_array3[box_num].box.x;
                conv.pixel_array3[box_num].box.y = box.y + conv.pixel_array3[box_num].box.y;

                if( check_collision( conv.pixel_array3[box_num].box, box ) == true)
                {
                    if(conv.pixel_array3[box_num].level == 1 ||  conv.pixel_array3[box_num].level == 2 || conv.pixel_array3[box_num].level == 3 || conv.pixel_array3[box_num].level == 4 || conv.pixel_array3[box_num].level == 5)
                    {
                        conv.pixel_array3[box_num].box.x = conv.pixel_array3[box_num].box.x - box.x;
                        conv.pixel_array3[box_num].box.y = conv.pixel_array3[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array3[box_num].level == 6)
                    {
                        conv.pixel_array3[box_num].box.x = conv.pixel_array3[box_num].box.x - box.x;
                        conv.pixel_array3[box_num].box.y = conv.pixel_array3[box_num].box.y - box.y;
                        return true;
                    }
                }

                else
                {
                    if(conv.pixel_array3[box_num].jump < 1000)
                    {
                        conv.pixel_array3[box_num].box.x = conv.pixel_array3[box_num].box.x - box.x;
                        conv.pixel_array3[box_num].box.y = conv.pixel_array3[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array3[box_num].jump;;

                    }

                    else
                    {
                        conv.pixel_array3[box_num].box.x = conv.pixel_array3[box_num].box.x - box.x;
                        conv.pixel_array3[box_num].box.y = conv.pixel_array3[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }

                }

            }
        }

    }
    return false;
}


bool enemy:: test2(ColRect pixel_array6[], int size, SDL_Rect square)
{
        box_num = 0;
        while(box_num < size)
        {
            pixel_array6[box_num].box.x = square.x + pixel_array6[box_num].box.x;
            pixel_array6[box_num].box.y = square.y + pixel_array6[box_num].box.y;

            if( check_collision( pixel_array6[box_num].box, box ) == true)
            {
                if(pixel_array6[box_num].level == 1 ||  pixel_array6[box_num].level == 2 || pixel_array6[box_num].level == 3 || pixel_array6[box_num].level == 4 || pixel_array6[box_num].level == 5)
                {
                    pixel_array6[box_num].box.x = pixel_array6[box_num].box.x - square.x;
                    pixel_array6[box_num].box.y = pixel_array6[box_num].box.y - square.y;
                    box_num++;
                }

                else if(pixel_array6[box_num].level == 6)
                {
                    pixel_array6[box_num].box.x = pixel_array6[box_num].box.x - square.x;
                    pixel_array6[box_num].box.y = pixel_array6[box_num].box.y - square.y;
                    return true;
                }
            }

            else
            {
                if(pixel_array6[box_num].jump < 1000)
                {
                    pixel_array6[box_num].box.x = pixel_array6[box_num].box.x - square.x;
                    pixel_array6[box_num].box.y = pixel_array6[box_num].box.y - square.y;
                    box_num = box_num + pixel_array6[box_num].jump;;

                }

                else
                {
                    pixel_array6[box_num].box.x = pixel_array6[box_num].box.x - square.x;
                    pixel_array6[box_num].box.y = pixel_array6[box_num].box.y - square.y;
                    box_num = box_num + 5000;
                }

            }
        }
    return false;
}


void enemy:: hit(sword square, Dot myDot, gun *bullets[], Converter conv)
{

 //   if( check_collision( box, square.box) == true)
    {

         if(square.look_up)
         {
            if(test2(conv.pixel_array6, conv.size6, square.box))
                perPC = true;
            else
                perPC = false;
         }
         else if((square.look_down))
         {
            if(test2(conv.pixel_array5, conv.size5, square.box))
            {
                perPC = true;
                if(square.attack)
                    bouncing = true;
            }
            else
                perPC = false;
         }

         else if(!direction)
         {
            if(test2(conv.pixel_array4, conv.size4, square.box))
                perPC = true;
            else
                perPC = false;
         }

         else if(direction)
         {
            if(test2(conv.pixel_array3, conv.size3, square.box))
                perPC = true;
            else
                perPC = false;
         }
    }

    for(int j = 0; j < 3; j++)
    {
        if( check_collision( box, bullets[j]->box) == true && bullets[j]->shot)
        {
            if(square.look_up)
             {
                if(test2(conv.pixel_array10, conv.size10, bullets[j]->box))
                {
                    perPCG = true;
                    bullets[j]->shot = false;
                    if(j == 0)
                        charge = charge1;
                    else if(j == 1)
                        charge = charge2;
                    else
                        charge = charge3;
                }

                else
                    perPCG = false;
             }
             else if((square.look_down))
             {
                if(test2(conv.pixel_array9, conv.size9, bullets[j]->box))
                {
                    perPCG = true;
                    bullets[j]->shot = false;
                    if(j == 0)
                        charge = charge1;
                    else if(j == 1)
                        charge = charge2;
                    else
                        charge = charge3;

                }
                else
                    perPCG = false;
             }

             else if(!direction)
             {
                if(test2(conv.pixel_array8, conv.size8, bullets[j]->box))
                {
                    perPCG = true;
                    bullets[j]->shot = false;
                    if(j == 0)
                        charge = charge1;
                    else if(j == 1)
                        charge = charge2;
                    else
                        charge = charge3;
                }
                else
                    perPCG = false;
             }

             else if(direction)
             {
                if(test2(conv.pixel_array7, conv.size7, bullets[j]->box))
                {
                    perPCG = true;
                    bullets[j]->shot = false;
                    if(j == 0)
                        charge = charge1;
                    else if(j == 1)
                        charge = charge2;
                    else
                        charge = charge3;
                }
                else
                    perPCG = false;
             }
        }
    }



     if( check_collision( box, myDot.box) == true && square.attack && hurt && dash_invul)           //fix this, per pixel it
     {
        airStun();
     }

     else if( perPC && square.attack && hurt)
     {
        // he -= 10;
         if(!showing_damage1)
         {
            pain = (rand() % 3 + (5 + swordStr/4)) - defence;
            if(pain < 0)
                pain = 0;
            damage_counter = 0;
         }
         else
         {
            damage_counter2 = 0;
            pain1 = (rand() % 3 + (5 + swordStr/4)) - defence;
            if(pain1 < 0)
                pain1 = 0;
         }
         ouch_counter = 0;
         knockBack(myDot);
         hurt = false;
         combo = true;
         if(!square.look_up)
            launchable = true;

         if(!onGround)
            stunCounter += 2;
     }

     if( perPC && square.attack)
     {
        if(square.look_up && launchable == true)
         {
            launchable = false;
            airStun();
         }
     }
    if( perPCG  && hurt)
    {
        if(!showing_damage1)
        {
            pain = (rand() % 3 + (3 + gunStr/4) + charge/10 ) - defence;
            if(pain < 0)
                pain = 0;
            damage_counter = 0;
        }
        else
        {
            pain1 = (rand() % 3 + (3 + gunStr/4) + charge/10) - defence;
            if(pain1 < 0)
                pain1 = 0;
            damage_counter2 = 0;
        }


        hurt = false;
        ouch_counter = 0;
        //if(stunCounter > 0)
        //    yVel == -5;
    }


     if(!square.attack)
        launchable = false;

    perPC = false;
    perPCG = false;
}

void enemy :: collatural_damage()
{
     if(damage_counter < 40)
     {
        showing_damage1 = true;
        if(damage_counter == 0)
        {
            he -= pain;
        }
        std::stringstream ss;
        ss << pain;
        SDL_Color textColor4 = { 200, 0, 0 };
        SDL_Color textColor3 = { 200, 70, 70 };
        damage1.loadFromRenderedText( ss.str(), textColor3 );
        damage1.render(box.x - camera.x + box.w/2 + 2, (box.y - camera.y - 30) - damage_counter);
        damage.loadFromRenderedText( ss.str(), textColor4 );
        damage.render(box.x - camera.x + box.w/2, (box.y - camera.y - 30) - damage_counter);

        damage_counter++;

        if(damage_counter == 40)
            showing_damage1 = false;
     }

     if(damage_counter2 < 40)
     {
        if(damage_counter2 == 0)
        {
            he -= pain1;
        }
        std::stringstream ss1;
        ss1 << pain1;
        SDL_Color textColor1 = { 200, 0, 0 };
        SDL_Color textColor2 = { 200, 70, 70 };
        damageA1.loadFromRenderedText( ss1.str(), textColor2 );
        damageA1.render((box.x - camera.x + box.w/2 - 5) + 2, (box.y - camera.y - 30) - damage_counter2);
        damageA.loadFromRenderedText( ss1.str(), textColor1 );
        damageA.render(box.x - camera.x + box.w/2 - 5, (box.y - camera.y - 30) - damage_counter2);

        damage_counter2++;

        if(damage_counter2 == 40)
            showing_damage2 = false;
     }


}

void enemy :: knockBack(Dot myDot)
{
}

void enemy :: airStun()
{
}



bool enemy :: survey(Dot myDot, Tile *tiles[])
{

}

bool enemy::point2wall(Tile *tiles[])
{
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( point_collision( test, tiles[ t ]->get_box() ) == true )
            {
                 return true;
            }
        }
    }
    return false;
}


void enemy::lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv)
{

}

void enemy:: animation(Setup test)
{

}

void enemy:: die()
{
}

void enemy:: outWithABang()
{
}


