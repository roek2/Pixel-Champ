#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "dotHeader.h"
#include "enemyHeader.h"
#include "jumperHeader.h"
#include "chargerHeader.h"
#include "tileHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include "playerstatsHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "particleHeader.h"
#include <fstream>
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int pixel_capacity;
extern int DOT_WIDTH;
extern int DOT_HEIGHT;

extern SDL_Surface *dot;
extern SDL_Surface *screen;

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int NORMAL_TILES;
extern int MOVABLE_TILES;
extern int TURRETS;
extern bool direction;
extern int animate_counter;

extern int Win_Tile;
extern int Death_Tile;
extern int Solid_Tile;
extern int Push_Tile;
extern int Gadget_Tile;
extern int left_turret;
extern int right_turret;
extern int break_Tile;
extern bool s_has_been_pressed;
extern bool o_has_been_pressed;
extern SDL_Event event;

extern Mix_Chunk *win;
extern Mix_Chunk *lose;
extern bool pause;
extern Mix_Chunk *jumpSound;
extern Mix_Chunk *dashSound;

extern SDL_Rect camera;
extern bool dead;
extern int Level;
extern bool pause;
extern bool direction;
extern int pixelcount;
extern int invul;
extern bool hurt_invul;
extern bool dash_invul;
extern bool dash_end;
extern int dash_invul_counter;
bool knockedleft = false;
bool knockedright = false;
int buildup = 0;
bool hold = false;
bool moving_left = false;
bool moving_right = false;
int jump_moment = 0;
int box_num = 1;
bool shoot_down = false;
int temp_Y = 0;
extern bool combo;
extern bool dontFall;
extern LTexture dotT;
extern int cutscene_counter;
extern bool up;
extern bool down;
bool swording;
extern bool shooting;
extern bool rPressed;
extern bool bouncing;
extern int ammo;
extern int charge1;
extern int charge2;
extern int charge3;
extern bool x_pressed;
extern bool charging;
extern int currentCamX;
extern int currentCamY;
extern int scene;
extern bool condemned;
bool double_time = false;
extern int pixelcountM;
extern SDL_GameController* gGameController;
extern bool intro;
extern bool jump_galore;
bool start = false;

Dot::Dot()
{

    xVel = 200;
    yVel = 260;
    jump = false;
    onGround = false;
    respawnX = 3500;
    respawnY = 440;
    combo_counter = 0;
   // dontFall = false;

    box.x = 10;
    box.y = 1250;
    box.w = DOT_WIDTH;
    box.h = DOT_HEIGHT;
    turnL = false;
    turnR = false;
    bigJump = false;
    canJump = true;
    can_dash = false;
    stats = new PlayerStats();
    second_jump = false;
    turning = false;
    init = false;
    dashX = 0;
    dashY = 0;

}

int Dot :: getXpos()
{
    return box.x;
}

int Dot :: getYpos()
{
    return box.y;
}

void Dot::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_CONTROLLERBUTTONDOWN )
    {
        //Adjust the velocity

        switch( event.cbutton.button )
        {
            //if the player presses escape
            case SDLK_ESCAPE: togglePause(); break;
            //if the player presses left, the character's velocity becomes negative
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT: if(xVel >= -4 && !dash_invul) xVel -= 5; if(!direction){turnL = true; turning = true;}direction = true; hold = true; moving_left = true; break;
            //if the player presses right, the character's velocity increases
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: if(xVel <= 4 && !dash_invul) xVel += 5; if(direction){turnR = true; turning = true;} direction = false; hold = true; moving_right = true; break;
            //if the player presses space then the player jumps
            case SDL_CONTROLLER_BUTTON_A: if(canJump && !onGround)double_jump(); makeJump(); bigJump = true; canJump = false; break;

            case SDL_CONTROLLER_BUTTON_Y: if(can_dash) dash(); dashX = box.x; dashY = box.y; break;

            case SDL_CONTROLLER_BUTTON_DPAD_UP: up = true; break;

            case SDL_CONTROLLER_BUTTON_DPAD_DOWN: down = true; break;

            case SDL_CONTROLLER_BUTTON_B: swording = true; break;

            case SDL_CONTROLLER_BUTTON_X: x_pressed = true; init_particle(); break;

            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: rPressed = true; break;

            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: s_has_been_pressed = true; break;

            case SDL_CONTROLLER_BUTTON_START: o_has_been_pressed = true; break;
        }

    }
    //If a key was released
    else if( event.type == SDL_CONTROLLERBUTTONUP)
    {
        //Adjust the velocity
        switch( event.cbutton.button )
        {
            //when the player lets go of left or right the velocity returns to 0
            case SDL_CONTROLLER_BUTTON_X: shooting = true; x_pressed = false; init = false; break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT: hold = false; moving_left = false; turnL = false; break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: hold = false; moving_right = false; turnR = false; break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP: up = false; break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN: down = false; break;
            case SDL_CONTROLLER_BUTTON_A: bigJump = false; canJump = true; break;
            case SDL_CONTROLLER_BUTTON_B: swording = false;break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: rPressed = false; break;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: s_has_been_pressed = false; break;
            case SDL_CONTROLLER_BUTTON_START: o_has_been_pressed = false; break;
        }
    }

    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            //if the player presses escape
            case SDLK_ESCAPE: togglePause(); break;
            //if the player presses left, the character's velocity becomes negative
            case SDLK_LEFT: if(xVel >= -4 && !dash_invul) xVel -= 5; if(!direction){turnL = true; turning = true;}direction = true; hold = true; moving_left = true; break;
            //if the player presses right, the character's velocity increases
            case SDLK_RIGHT: if(xVel <= 4 && !dash_invul) xVel += 5; if(direction){turnR = true; turning = true;} direction = false; hold = true; moving_right = true; break;
            //if the player presses space then the player jumps
            case SDLK_SPACE: if(canJump && !onGround)double_jump(); makeJump(); bigJump = true; canJump = false; break;

            case SDLK_x: if(can_dash) dash(); dashX = box.x; dashY = box.y; break;

            case SDLK_UP: up = true; break;

            case SDLK_DOWN: down = true; break;

            case SDLK_d: swording = true; break;

            case SDLK_a: x_pressed = true; init_particle(); break;

            case SDLK_r: rPressed = true; break;

            case SDLK_w: s_has_been_pressed = true; break;

            case SDLK_RETURN: o_has_been_pressed = true; break;
        }

    }
    //If a key was released
    else if( event.type == SDL_KEYUP)
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            //when the player lets go of left or right the velocity returns to 0
            case SDLK_a: shooting = true; x_pressed = false; init = false; break;
            case SDLK_LEFT: hold = false; moving_left = false; turnL = false; break;
            case SDLK_RIGHT: hold = false; moving_right = false; turnR = false; break;
            case SDLK_UP: up = false; break;
            case SDLK_DOWN: down = false; break;
            case SDLK_SPACE: bigJump = false; canJump = true; break;
            case SDLK_d: swording = false;break;
            case SDLK_r: rPressed = false; break;
            case SDLK_w: s_has_been_pressed = false; break;
            case SDLK_RETURN: o_has_been_pressed = false; break;
        }
    }



}

bool Dot::touches_wall( SDL_Rect box, Tile *tiles[], Converter conv )
{

    //Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )
        {

                if( check_collision( box, tiles[ t ]->get_box() ) == true)
                {

                    conv.begin = true;
                    //return true;
              //      box_num++;
      ///        return true;
                }


                if(conv.begin)
                {
                    if(!direction)
                    {

                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                            conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                            if( check_collision( conv.pixel_array[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array[box_num].level == 6)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    return true;
                                }
                            }
                          //  return true;
                            else
                            {
                                if(conv.pixel_array[box_num].jump < 1000)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array[box_num].jump;;

                                }
                                else
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }
                            }
                        }
                    }

                    else
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size2)
                        {

                            conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                            conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                            if( check_collision( conv.pixel_array2[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array2[box_num].level == 6)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array2[box_num].jump < 1000)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array2[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }
                    }
                }

        }
    }
    //If no wall tiles were touched
    return false;
}

bool Dot::touches_ground(SDL_Rect box, Tile *tiles[], Converter conv)
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

bool Dot::touches_ground2(SDL_Rect box, Tile *tiles[], Converter conv)
{

    //goes through each tile and if the player is on top of a tile, mtile or turret then it returns true
    for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile ){
            if( ground_collision2( box, tiles[ t ]->get_box() ) == true )
            {
                 conv.begin = true;
            }

                if(conv.begin)
                {
                    if(!direction)
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                            conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                            if( ground_collision2( conv.pixel_array[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array[box_num].level == 6)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array[box_num].jump < 1000)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }
                            }

                        }

                    }

                    else
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                            conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                            if( ground_collision2( conv.pixel_array2[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array2[box_num].level == 6)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array2[box_num].jump < 1000)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array2[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2 [box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }
                            }

                        }

                    }

                }


        }
    }

    return false;
}

bool Dot :: turnRight(Tile *tiles[], Converter conv)
{
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )
        {

                if( check_collision( box, tiles[ t ]->get_box() ) == true)
                {

                    conv.begin = true;
                }


                if(conv.begin)
                {

                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                            conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                            if( check_collision( conv.pixel_array[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array[box_num].level == 6)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    direction = true;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array[box_num].jump < 1000)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }
                    }
                }
        }
        turnR = false;
        direction = false;
        return false;
}

bool Dot:: turnLeft(Tile *tiles[], Converter conv)
{

    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )
        {

                if( check_collision( box, tiles[ t ]->get_box() ) == true)
                {

                    conv.begin = true;
                }

                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size2)
                        {

                            conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                            conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                            if( check_collision( conv.pixel_array2[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array2[box_num].level == 6)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    direction = false;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array2[box_num].jump < 1000)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array2[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }

        }
    }
    turnL = false;
    direction = true;
    return false;
}



bool Dot::touches_roof(SDL_Rect box, Tile *tiles[], Converter conv)
{

    //goes through each tile and if the top of the player hits off the bottom of a tile or mtile then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile){
            if( roof_collision( box, tiles[ t ]->get_box() ) == true )
            {
                conv.begin = true;
              //  return true;
            }

                if(conv.begin)
                {
                    if(!direction)
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                            conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                            if( roof_collision( conv.pixel_array[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array[box_num].level == 6)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array[box_num].jump < 1000)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }
                    }
                    else
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size2)
                        {

                            conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                            conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                            if( roof_collision( conv.pixel_array2[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array2[box_num].level == 6)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array2[box_num].jump < 1000)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array2[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }
                    }

                }


        }
    }


     return false;
}

void Dot::init_particle()
{
    if(!init)
    {
        for( int p = 0; p < 20; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y + box.h, 4);
            particles2[ p ] = new Particle( box.x + box.w, box.y + box.h, 4);
            particles[ p ]->orbit_start(box);
            particles2[ p ]->orbit_start(box);
        }
        init = true;
    }

}

bool Dot::touches_death( SDL_Rect box, Tile *tiles[], Converter conv )
{
    //Go through the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a death type tile
        if( ( tiles[ t ]->get_type() == Death_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                conv.begin = true;
                    //return true;
              //      box_num++;
      ///        return true;
                }


                if(conv.begin)
                {
                    if(!direction)
                    {

                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size)
                        {

                            conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                            conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                            if( check_collision( conv.pixel_array[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array[box_num].level == 6)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    return true;
                                }
                            }
                          //  return true;
                            else
                            {
                                if(conv.pixel_array[box_num].jump < 1000)
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array[box_num].jump;;

                                }
                                else
                                {
                                    conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                                    conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }
                            }
                        }
                    }

                    else
                    {
                        conv.begin = false;
                        box_num = 0;
                        while(box_num < conv.size2)
                        {

                            conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                            conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                            if( check_collision( conv.pixel_array2[box_num].box, tiles[ t ]->get_box() ) == true)
                            {
                                if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num++;
                                }

                                else if(conv.pixel_array2[box_num].level == 6)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    return true;
                                }
                            }

                            else
                            {

                                if(conv.pixel_array2[box_num].jump < 1000)
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + conv.pixel_array2[box_num].jump;;

                                }

                                else
                                {
                                    conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                                    conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                                    box_num = box_num + 5000;
                                }

                            }

                        }
                    }
                }

        }
    }
    return false;
}

void Dot:: dashable()
{
    if(stats->get_energy() < 100)
    {
        can_dash = false;
    }
    else
    {
        can_dash = true;
    }

    if(!dash_invul && stats->energy <= (stats->maxEnergy - 2) && !charging)
    {
        stats->energy += 2;
    }
    else if(!dash_invul && stats->energy == (stats->maxEnergy - 1) && !charging)
        stats->energy -= 1;

    if(charging && stats->energy > 0)
    {
        stats->energy -= 1;
    }
}

bool Dot::touches_wallA( SDL_Rect box, Tile *tiles[] )
{

    //Uint8 *keystates = SDL_GetKeyState( NULL );
    //Go through the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( ( tiles[ t ]->get_type() == Solid_Tile ) )
        {

                if( check_collision( box, tiles[ t ]->get_box() ) == true)
                {
                    return true;
                }
        }
    }
}


bool Dot::touches_groundA(SDL_Rect box, Tile *tiles[])
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


bool Dot::touches_roofA(SDL_Rect box, Tile *tiles[])
{

    //goes through each tile and if the top of the player hits off the bottom of a tile or mtile then it returns true
     for( int t = 0; t < NORMAL_TILES; t++ )
     {
        if( tiles[ t ]->get_type() == Solid_Tile){
            if( roof_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
              //  return true;
            }
        }
     }
}

bool Dot::touches_ground2A(SDL_Rect box, Tile *tiles[])
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
}

void Dot::move( Tile *tiles[], Converter conv)
{
    //Move the dot left or right
    box.x += xVel;

    //If the dot went too far to the left or right or touched a wall
    if( touches_wall( box, tiles, conv ) )
    {
        //move back
        box.x -= xVel;
    }

    //Move the dot up or down
    box.y += yVel;

    //If the dot went too far up or down or touched a wall
    if( touches_wall( box, tiles,  conv ) )
    {
        //move back
        box.y -= yVel;
    }

    //if the player is touches the ground then it is onGround
    if( touches_ground2( box, tiles, conv) )
    {
         onGround = true;
    }
    else
    {
         onGround = false;
    }

    if((!(touches_ground(box, tiles, conv)) && !jump) || touches_roof(box, tiles, conv) == true)
    {
                //the player will fall


                if(!dontFall)
                {
                    if(!start)
                    {
                        yVel = 10;
                        start = true;
                    }
                    else if(yVel < 15)
                        yVel++;
                }

                else
                {
                    start = false;
                    yVel = 0;
                }
    }

    if((!(touches_ground(box, tiles, conv)) && !jump) || touches_roof(box, tiles, conv) == true)
    {
        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( fix_collision( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (tiles[ t ]->box.y - (box.y + box.h)) < 15)
                       // yVel = 10;
                        yVel = ( tiles[ t ]->box.y - (box.y + box.h));
                }
            }
        }
    }
    //when the player jumps and is holding space the player looses momentum slower and can as a result jump higher
    if(jump && yVel < 8 && bigJump)
    {
            yVel++;
    }

    //when the player jumps, the y velocity reduces the momentum of the jump and pulls the player back down
    else if(jump && yVel < 8)
    {
         yVel = yVel + 2;
    }


    else
         jump = false;

    if(!onGround && !(moving_left || moving_right) && xVel > 0)
    {
       if(jump_moment > 3)
       {
          xVel--;
          jump_moment = 0;
       }
       jump_moment++;

    }

    else if(!onGround && !(moving_left || moving_right) && xVel < 0)
    {
       if(jump_moment > 3)
       {
          xVel++;
          jump_moment = 0;
       }
       jump_moment++;
    }

    else if(!(moving_left || moving_right) && xVel == 1)
    {
       xVel -= 1;
    }

    else if(!(moving_left || moving_right) && xVel > 0)
    {
       xVel -= 2;
    }

    else if(!(moving_left || moving_right) && xVel == -1)
    {
       xVel += 1;
    }

    else if(!(moving_left || moving_right) && xVel < 0)
    {
       xVel += 2;
    }

    else if((moving_left && xVel < -10) || (moving_right && xVel < 10))
    {
       xVel++;
    }

    else if((moving_left && xVel > -10) || (moving_right && xVel > 10))
    {
       xVel--;
    }

  //  if(shoot_down && yVel > 5)
    {
  //      yVel -= 5;
  //      shoot_down = false;
    }

  //  else if(shoot_down)
    {
  //      yVel -= 2;
  //      shoot_down = false;
    }

    if(dash_invul)
    {
        box.y = temp_Y;
    }

    if(dash_end)
    {
        dash_end = false;
        xVel = 0;
    }

    if(airCombo() ||dash_invul)
    {
        dontFall = true;
    }

    else
        dontFall = false;

    if(combo)
    {
        combo_counter++;
        if(combo_counter == 6)                      ///changes launch air-time
        {
            combo = false;
            combo_counter = 0;
        }
    }

    if(turnL)
        turnLeft(tiles, conv);
    else if(turnR)
        turnRight(tiles, conv);

    dashable();
    stats->set_defence();

    if(onGround)
        second_jump = false;

    if(turnR || turnL)
        turning = true;

    bounce();

    cutscene();

}

void Dot :: cutscene()
{
    if(scene == 1)
    {
        xVel = 5;
        direction = false;
        //moving_right = true;
        if(cutscene_counter >= 100)
        {
            xVel = -5;
            moving_right = false;
        }
    }

    if(scene == 2 || scene == 3 && cutscene_counter < 0)
    {
        xVel = 0;
        moving_right = false;
    }

    if(scene == 10 || scene == 11)
    {
        if(direction)
        {
            xVel = -5;
            if(scene == 10)
                yVel = 0;
            moving_right = true;
        }
        else
        {
            xVel = 5;
            if(scene == 10)
                yVel = 0;
            moving_left = true;
        }
    }

    if(scene == 13 || scene == 12 || scene == 4)
    {

        if(scene == 12)
        {
            yVel = -15;
        }
        xVel = 0;
    }



    if(scene == 11 && cutscene_counter > 90)
    {
        xVel = 0;
        moving_right = false;
        moving_left = false;
    }


    if(condemned)
    {
        xVel -= 1;
        yVel -= 12;
        condemned = false;
    }


}

void Dot::load()
{
    if(Level == 222)
    {
        box.x = 1090;
        box.y = 1050;
        moving_right = false;
        double_time = true;
        xVel = 0;
    }

    else if(Level == 528)
    {
        box.x = 1000;
        box.y = 600;
        moving_right = false;
        double_time = true;
        xVel = 0;
    }
}


void Dot::move2( Tile *tiles[])
{
    //Move the dot left or right
    box.x += xVel;

    //If the dot went too far to the left or right or touched a wall
    if( ( box.x < 0 ) || ( box.x + DOT_WIDTH > LEVEL_WIDTH ) || touches_wallA( box, tiles) )
    {
        //move back
        box.x -= xVel;
    }

    //Move the dot up or down
    box.y += yVel;

    //If the dot went too far up or down or touched a wall
    if( ( box.y < 0 ) || ( box.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touches_wallA( box, tiles) )
    {
        //move back
        box.y -= yVel;
    }

    //if the player is touches the ground then it is onGround
    if( touches_groundA( box, tiles) )
    {
         onGround = true;
    }
    else
    {
         onGround = false;
    }

    if((!(touches_groundA(box, tiles)) && !jump) || touches_roofA(box, tiles) == true)
    {
                //the player will fall
                if(!dontFall)
                  yVel = 8;//(pixelcount/280);
                else
                    yVel = 0;
    }

    if((!(touches_groundA(box, tiles)) && !jump) || touches_roofA(box, tiles) == true)
    {
        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            if( tiles[ t ]->get_type() == Solid_Tile )
            {
                if( fix_collision( box, tiles[ t ]->get_box() ) == true )
                {
                    if( (tiles[ t ]->box.y - (box.y + box.h)) < 8)
                        yVel = ( tiles[ t ]->box.y - (box.y + box.h));
                }
            }
        }
    }
    //when the player jumps and is holding space the player looses momentum slower and can as a result jump higher
    if(jump && yVel < 8 && bigJump)
    {
            yVel++;
    }

    //when the player jumps, the y velocity reduces the momentum of the jump and pulls the player back down
    else if(jump && yVel < 8)
    {
         yVel = yVel + 2;
    }


    else
         jump = false;


    if(dash_invul)
    {
        box.y = temp_Y;
    }

    if(dash_end)
    {
        dash_end = false;
        xVel = 0;
    }

    if(airCombo() ||dash_invul)
    {
        dontFall = true;
    }

    else
        dontFall = false;

    if(combo)
    {
        combo_counter++;
        if(combo_counter == 6)                      ///changes launch air-time
        {
            combo = false;
            combo_counter = 0;
        }
    }

    dashable();

    if(onGround)
        second_jump = false;

    bounce();

}



bool Dot:: airCombo()
{
    if(combo && !onGround)
        return true;
    return false;
}

bool Dot::touches_win( Tile *tiles[] )
{
    //Go through the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a win type tile
        if( ( tiles[ t ]->get_type() == Win_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    return false;
}

void Dot:: bounce()
{
    if(bouncing && down)
    {
        yVel = -18;
        jump = true;
        bouncing = false;
    }
}

//checks if the player had beaten a level
bool Dot:: wins(Tile *tiles[])
{
    if(touches_win(tiles) == true){
            return true;
    }
}

//checks if the player has touched a killer block
bool Dot:: dies(Tile *tiles[], Converter conv)
{
    if(dead == true || stats->health <= 0){
        Mix_PlayChannel( -1, lose, 0 );
        //the player is reset to their respawn position
        dead = false;
        stats->health = 200;
        load();
        return true;
        //return true;
    }

    if(touches_death(box, tiles, conv) == true && !knockedleft && !invul)
    {
        yVel -= 8;
       // knockedleft = true;
        hurt_invul = true;
        stats->health -= (20 - stats->defence);
    }
    return false;
}

void Dot:: makeJump()
{
    //if the player jumps their y velocity becomes negative, sending the player in the air.
     if(onGround && !jump && canJump){
            jump = true;
            onGround = false;
            if(intro)pixelcountM = 100;
            yVel =- (18 - pixelcountM/300);
     }
}

void Dot::double_jump()
{
    if(jump_galore)
    {
        for( int p = 0; p < 20; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y + box.h, 4);
            particles2[ p ] = new Particle( box.x + box.w, box.y + box.h, 4);
        }

        yVel =- (18 - pixelcountM/300);

        jump = true;
        second_jump = true;
        Mix_PlayChannel( -1, jumpSound, 0 );
    }

    else if(stats->energy >= 100 && !second_jump && double_time)
    {
        for( int p = 0; p < 20; p++ )
        {
            particles[ p ] = new Particle( box.x, box.y + box.h, 4);
            particles2[ p ] = new Particle( box.x + box.w, box.y + box.h, 4);
        }

        yVel =- (18 - pixelcountM/300);
        stats->energy -= 100;
        jump = true;
        second_jump = true;
        Mix_PlayChannel( -1, jumpSound, 0 );
    }
}

void Dot:: dash()
{

  dash_invul = true;
  temp_Y = box.y;
  Mix_PlayChannel( -1, dashSound, 0 );

  if(onGround)
  {
     if(direction)
         xVel = -25;
     else
         xVel = 25;
  }

  else
  {
    if(direction)
         xVel = -20;
     else
         xVel = 20;
  }

  stats->energy -= 100;
  can_dash = false;

}

//checks if the player has acquired the time change gadget
bool Dot:: getTime(SDL_Rect box, Tile *tiles[], bool timeGadget)
{
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        //If the tile is a time type tile
        if( ( tiles[ t ]->get_type() == Gadget_Tile ))
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }
    return false;
}

 //depending on what level the player is in, the player is assigned a different respawn point
void Dot :: set_respawn()
{

}

void Dot:: part_effect(SDL_Rect box)
{
    if(second_jump && jump)
    {
        for( int p = 0; p < 10; p++ )
        {
            particles[ p ]->PartLeft2();
            particles2[ p ]->PartRight2();
            particles[ p ]->show();
            particles2[ p ]->show();
        }
    }

    if((ammo == 0 && charge1 > 20) || (ammo == 1 && charge2 > 20) || (ammo == 2 && charge3 > 20) )
    {
        for( int p = 0; p < 10; p++ )
        {
            particles[ p ]->orbit2();
            particles2[ p ]->orbit2();
            particles[ p ]->show();
            particles2[ p ]->show();
        }
    }
}

void Dot::show()
{
    if(hurt_invul)
    {
        dotT.setBlendMode( SDL_BLENDMODE_BLEND );
        dotT.setAlpha(100);
    }
    else
    {
        dotT.setBlendMode( SDL_BLENDMODE_BLEND );
        dotT.setAlpha(255);
    }
    dotT.render(box.x - camera.x, box.y - camera.y);
    part_effect(box);

    if(dash_invul)
    {
        dotT.setBlendMode( SDL_BLENDMODE_BLEND );
        dotT.setAlpha(100);
        dotT.render(dashX - camera.x, dashY - camera.y);
        if((dashX - box.x < -80) && !direction)
        {
            if(onGround)
                dotT.render((dashX - camera.x) + 80, dashY - camera.y);
            else
                dotT.render((dashX - camera.x) + 100, dashY - camera.y);
        }

        else if((dashX - box.x > 80) && direction)
        {
            if(onGround)
                dotT.render((dashX - camera.x) - 80, dashY - camera.y);
            else
                dotT.render((dashX - camera.x) - 100, dashY - camera.y);
        }

        else if((dashX - box.x > 160) && direction)
        {
            if(onGround)
                dotT.render((dashX - camera.x) - 80, dashY - camera.y);
            else
                dotT.render((dashX - camera.x) - 160, dashY - camera.y);
        }



    }
    //apply_surface( box.x - camera.x, box.y - camera.y, dot, screen );
}

void Dot::set_camera()
{
    //Center the camera over the dot
    if(turning)
    {
        if(direction)
        {
            if(camera.x > box.x - ((SCREEN_WIDTH / 3)*2))
            {
                camera.x += xVel - 5;
            }
            else
            {
                turning = false;
            }
        }

        else
        {
            if(camera.x < box.x - SCREEN_WIDTH / 3)
            {
                if(((box.x - SCREEN_WIDTH / 3) - camera.x) < xVel + 5)
                    camera.x += ((box.x - SCREEN_WIDTH / 3) - camera.x);
                else
                    camera.x += xVel + 5;
            }
            else
            {
                turning = false;
            }
        }
    }
    else
    {
        if(direction)
        {
            if(camera.x > box.x - ((SCREEN_WIDTH / 3)*2))
            {
                camera.x += xVel;
            }
        }

        else
        {
            if(camera.x < box.x - SCREEN_WIDTH / 3)
            {
                camera.x += xVel;
            }
        }
    }

    if(box.x < camera.x + SCREEN_WIDTH / 3)
    {
        camera.x = box.x - SCREEN_WIDTH / 3;
    }

    else if(box.x > camera.x + ((SCREEN_WIDTH / 3)*2))
    {
        camera.x = box.x - ((SCREEN_WIDTH / 3)*2);
    }

    camera.y = ( box.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds.
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > currentCamX - camera.w )
    {
        camera.x = currentCamX - camera.w;
    }
    if( camera.y > currentCamY - camera.h )
    {
        camera.y = currentCamY - camera.h;
    }
}

bool Dot::is_onGround()
{
    //the player cant move when the game is paused
     return onGround;
}


void Dot::togglePause()
{
    //the player cant move when the game is paused
     pause = !pause;
}

bool Dot::per_pixel(SDL_Rect box, SDL_Rect mon, Converter conv)
{
    if( check_collision( box, mon ) == true)
    {

        conv.begin = true;
        //return true;
  //      box_num++;
///        return true;
    }


    if(conv.begin)
    {
        if(!direction)
        {

            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size)
            {

                conv.pixel_array[box_num].box.x = box.x + conv.pixel_array[box_num].box.x;
                conv.pixel_array[box_num].box.y = box.y + conv.pixel_array[box_num].box.y;

                if( check_collision( conv.pixel_array[box_num].box, mon ) == true)
                {
                    if(conv.pixel_array[box_num].level == 1 ||  conv.pixel_array[box_num].level == 2 || conv.pixel_array[box_num].level == 3 || conv.pixel_array[box_num].level == 4 || conv.pixel_array[box_num].level == 5)
                    {
                        conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                        conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array[box_num].level == 6)
                    {
                        conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                        conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                        return true;
                    }
                }
              //  return true;
                else
                {
                    if(conv.pixel_array[box_num].jump < 1000)
                    {
                        conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                        conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array[box_num].jump;;

                    }
                    else
                    {
                        conv.pixel_array[box_num].box.x = conv.pixel_array[box_num].box.x - box.x;
                        conv.pixel_array[box_num].box.y = conv.pixel_array[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }
                }
            }
        }

        else
        {
            conv.begin = false;
            box_num = 0;
            while(box_num < conv.size2)
            {

                conv.pixel_array2[box_num].box.x = box.x + conv.pixel_array2[box_num].box.x;
                conv.pixel_array2[box_num].box.y = box.y + conv.pixel_array2[box_num].box.y;

                if( check_collision( conv.pixel_array2[box_num].box, mon ) == true)
                {
                    if(conv.pixel_array2[box_num].level == 1 ||  conv.pixel_array2[box_num].level == 2 || conv.pixel_array2[box_num].level == 3 || conv.pixel_array2[box_num].level == 4 || conv.pixel_array2[box_num].level == 5)
                    {
                        conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                        conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                        box_num++;
                    }

                    else if(conv.pixel_array2[box_num].level == 6)
                    {
                        conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                        conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                        return true;
                    }
                }

                else
                {

                    if(conv.pixel_array2[box_num].jump < 1000)
                    {
                        conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                        conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                        box_num = box_num + conv.pixel_array2[box_num].jump;;

                    }

                    else
                    {
                        conv.pixel_array2[box_num].box.x = conv.pixel_array2[box_num].box.x - box.x;
                        conv.pixel_array2[box_num].box.y = conv.pixel_array2[box_num].box.y - box.y;
                        box_num = box_num + 5000;
                    }

                }

            }
        }
    }
    //If no wall tiles were touched
    return false;
}


bool Dot:: knockback(enemy monster, Converter conv)
{

    if(per_pixel(box, monster.box, conv) && !knockedleft && !knockedright && monster.box.x > box.x && monster.alive && !invul)
    {
        // stats.health -= 20;
         if(stats->health > 0)
         {
              xVel = -14;
              yVel = -5;
         }
         knockedleft = true;
         hurt_invul = true;
         stats->health -= (25 - pixelcountM/300);
         return true;
    }

    else if(per_pixel(box, monster.box, conv) && !knockedleft && !knockedright && monster.box.x < box.x && monster.alive && !invul)
    {
       //  stats.health -= 20;
         if(stats->health > 0)
         {
              xVel = 14;
              yVel = -5;
         }

         knockedright = true;
         hurt_invul = true;
         stats->health -= (25 - pixelcountM/300);
         return true;
    }


    else if((knockedleft || knockedright) && !invul)
    {
         knockedleft = false;
         knockedright = false;
    }

    return false;

}

