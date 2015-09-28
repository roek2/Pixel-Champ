/*This source code copyrighted by Lazy Foo' Productions (2004-2012)
and may not be redistributed without written permission.*/

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_ttf.h"
#include <string>
#include <fstream>
#include "bitmap_image.hpp"
#include "bitmap_image.hpp"
#include "baseHeader.h"
#include "tileHeader.h"
#include "dotHeader.h"
#include "enemyHeader.h"
#include "timerHeader.h"
#include "setupHeader.h"
#include "mtileHeader.h"
#include "turretHeader.h"
#include "mapLoaderHeader.h"
#include "weaponHeader.h"
#include "swordHeader.h"
#include "gunHeader.h"
#include "enemyHeader.h"
#include "jumperHeader.h"
#include "chargerHeader.h"
#include "Flyer.h"
#include "crawlerHeader.h"
#include "playerstatsHeader.h"
#include "companionHeader.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include "playerTileHeader.h"
#include "playerCreatorHeader.h"
#include "generatorHeader.h"
#include "charSelect.h"
#include "MenuHeader.h"
#include "particleHeader.h"
#include "testSuite.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

int debug;
//Used to determine when to blend the backgrounds
bool blending;

int animate_counter = 0;

//stores mtile characteristics when the time is changed on a map
struct reload{
        int opX;    //original poistion of the mtile
        int opY;
        int thisLevel;  //]level number
        int currX;      //current position
        int currY;
};

bool direction = true;
int total_pielcount = 0;


//sttributes of the game screen
int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 640;
int SCREEN_BPP = 32;

int pixel_capacity = 17000;
int exits = 0;
bool s_has_been_pressed = false;
bool o_has_been_pressed = false;

//the amount rreload structs that can be stored on a map
const int TOTAL_MTILES = 5;

//determines how visible a surface is
int alpha = SDL_ALPHA_OPAQUE;           //SDL_ALPHA_OPAQUE = 255

int monster_count = 0;

//Game frame rate
int FRAMES_PER_SECOND = 30;

//The dot dimensions
int DOT_WIDTH = 128;
int DOT_HEIGHT = 128;
int sword_counter = 0;
bool x_pressed = false;
bool cutscene2 = false;
bool cutscene3 = false;
int trueWidth = 0;
int trueHeight = 128;
int properHeight = 0;

//The dimensions of the first level
int LEVEL_WIDTH = 3600;
int LEVEL_HEIGHT = 3500;
bool up = false;
bool down = false;
int currentCamX = 3500;
int currentCamY = 850;
int camSpeed = 7;
int credit_counter = 0;
//The level the player is on.
bool load_out1 = true;

Mon_storage mon_storage[50];
int out = 0;

//tt standing for text-time, determines the amount of time dialogue appears on the screen
int tt = 0;
bool can_shoot = true;                                                                                                           ///*****

//Tile boundary characteristics
int TILE_WIDTH = 80;
int TILE_HEIGHT = 80;
int TOTAL_TILES = 540 * 3;
int NORMAL_TILES = 405 * 3;
int MOVABLE_TILES = 15;
int TURRETS = 10;
bool shooting = false;
int cutscene_counter = 0;
bool cutscene5 = false;
bool speechIn = true;
int creds = 0;
bool jump_galore = false;

//The different types of tiles
int Win_Tile = 0;          //This tile is the goal of each level, touching it loads up the next level
int Invisible_Tile = 1;    //The entire map is made up of tiles, these tiles are see threw so you can see the background
int Death_Tile = 2;        //Touching this tile kills the player and causes him to respawn at the start of the level
int Solid_Tile = 3;        //This tile is like a wall, the player cant move threw it
int Push_Tile = 4;        // This tile, which has its own derived class, can be pushed and pulled by the player
int Gadget_Tile = 5;       // This tile unlocks the players ability to switch between times
int break_Tile = 6;       // If you stand on this tile it breaks underneath you and fall until it hits ground
int left_exit = 7;       //This tile is a turret that faces left
int right_exit = 8;      //This tile is a turret that faces left
int down_exit = 9;
int up_exit = 10;
int pixel_pause_counter = 0;
bool rPressed;
int charge1 = 0;
int charge2 = 0;
int charge3 = 0;
bool fadeOut2 = false;
int ammo = 0;
SDL_Rect cutOut;
int flyer_count = 0;
int charger_count = 0;
int crawler_count = 0;
int jumper_count = 0;
char text[100];
int pack_acquired = 0;

extern LTexture dotT;
extern LTexture tileSheetT;
extern LTexture backgroundT;
extern LTexture textOfSorts;
extern LTexture textOfSorts2;
extern LTexture prompt1;
extern LTexture prompt2;
extern LTexture blackBackground;
extern LTexture life_bar;
extern LTexture energy_bar;
extern LTexture life_bar_con;
extern LTexture dark;
extern LTexture fadeIn;
extern LTexture baddy;
extern LTexture baddy2;
extern LTexture pink;
extern LTexture speech2;
extern LTexture speech_bubble;
extern LTexture falling;
extern LTexture freeFall;
extern LTexture darken1;
extern LTexture credit1;
extern LTexture credit2;
extern LTexture pLeft;
extern LTexture pixelBox;
extern int pixels_left;
extern int sword_pixels_used;
extern int gun_pixels_used;
extern int stat_pixels;
extern int man_pixels_used;
bool load_game = false;
// LTexture energy_bar_con;
extern LTexture heart;
int credit_alpha = 0;
int fall = 0;
int fall2 = 640;
extern LTexture power;
extern int maxHealth;
extern int maxEnergy;
bool cutscene11 = false;
SDL_Color textColor3 = { 163, 163, 163 };
int curX = 0;
int curY = 0;
int StartingHour = 0;
int StartingMin = 0;
int StartingSec = 0;
int StartingDate = 0;

bool DEBUG = false;
bool MEDIADEBUG = true;
bool MUSICDEBUG = true;
bool FONTDEBUG = true;
bool IMAGEDEBUG = true;
bool MAPDEBUG = true;
bool ENEMYDEBUG = true;
bool LAZYDEBUG = true;
bool CHARDEBUG = true;

int test_success = 0;
int test_failures = 0;

extern int fadeInAlpha;
bool cutscene10 = false;
//The surfaces
SDL_Surface *dot = NULL;        //The surface that represents athe character
SDL_Surface *bits = NULL;
SDL_Surface *comp = NULL;
SDL_Surface *weapons = NULL;
SDL_Surface *weapons2 = NULL;
SDL_Surface *enemys = NULL;
SDL_Surface *enemy4 = NULL;
SDL_Surface *monitor = NULL;
SDL_Surface *pixel = NULL;      //shows the sight of a turret                                       (probably temporary)
SDL_Surface *screen = NULL;     //what is shown on the screen
SDL_Surface *tileSheet = NULL;      //The surface for each tile
SDL_Surface *tileSheet2 = NULL;
SDL_Surface *tileSheet3 = NULL;
SDL_Surface *playerbg = NULL;
SDL_Surface *background = NULL;     //The background surface
SDL_Surface *background2 = NULL;
bool dash_end = false;
//SDL_Surface *text[10];
bool dead = false;                  // A boolean to detrmine id the players alive
bool countdown = false;             //checks if a turret has seen you or not
bool pause = false;                 //determines if the game is paused
bool canChange = true;             //decides if the player can change to a different time or not
extern int pixelcount;
bool invul = false;
bool hurt_invul = false;
bool dash_invul = false;
int hurt_invul_counter = 0;
int dash_invul_counter = 0;
int dash_charge = 0;
bool can_dash = false;
bool reload_count = false;
int reload_counter = 0;
bool combo = false;
bool dontFall = false;
int TOTAL_PARTICLES = 100;
SDL_Rect life;
SDL_Rect stat;
SDL_Rect stat2;
SDL_Rect energy;
SDL_Rect life_con;
SDL_Rect life_bar_con_end;
bool charging = false;
int scene = 1;
bool kidnapped = false;
bool condemned = false;
int speech_alpha = 0;
bool opening_credits = false;
bool credits_fadeIn = true;
bool intro = true;
bool menu = true;
bool beginning = false;
int Level = 20;
extern bool double_time;
extern int generatorNum;
extern Mix_Music *gMusic;
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

ifstream readfile4;
ofstream newfile4;

//Globally used font
TTF_Font *gFont = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

extern int totalHour;
extern int totalMin;
extern int totalSec;


//For loading writing fonts

//The different sound effects and music of the game
Mix_Chunk *win = NULL;
Mix_Chunk *lose = NULL;
Mix_Chunk *notime = NULL;
Mix_Chunk *alert = NULL;
Mix_Music *music = NULL;


//The event structure
SDL_Event event;

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


void clean_up( Tile *tiles[], mTile *mtiles[], turret *turrets[] )
{
    //Free the surfaces
    SDL_FreeSurface( dot );
    SDL_FreeSurface( background);
    SDL_FreeSurface( background2 );
    SDL_FreeSurface( tileSheet );
    SDL_FreeSurface( tileSheet2 );
    SDL_FreeSurface( pixel);
    SDL_FreeSurface( screen );

    //Free music
    Mix_FreeChunk( win );
    Mix_FreeChunk( lose );
    Mix_FreeChunk( notime );
    Mix_FreeChunk( alert );
    Mix_FreeMusic( music );

    //Free the tiles
    for( int t = 0; t < NORMAL_TILES; t++ )
    {
        delete tiles[ t ];
    }
    for( int t = 0; t < MOVABLE_TILES; t++ )
    {
        delete mtiles[ t ];
    }
    for( int t = 0; t < TURRETS; t++ )
    {
        delete turrets[ t ];
    }

    //Quit SDL
    SDL_Quit();
}

int cutscene_management(Dot myDot, companion &cp)
{
        if(cutscene_counter == 100)
        {
            scene = 0;
            cutscene_counter = 0;
        }
        if(scene > 0)
            cutscene_counter++;

        if(Level == 21 && myDot.box.x > 2250 && cutscene2 == false)
        {
            scene = 2;
            cutscene2 = true;
            cutscene_counter = -50;
            speechIn = true;
        }

        if(cutscene2 == true && cutscene_counter == 100)
            kidnapped = true;

        if(Level == 21 && myDot.box.x > 3000 && cutscene3 == false)
        {
            scene = 3;
            cutscene3 = true;
            cutscene_counter = -50;
        }

        if(cutscene3 == true && cutscene_counter == 100 && Level < 100)
        {
            scene = 5;
            cutscene_counter = -50;
        //    cout << "Hello2  ";
        }

        if(cutscene10 == false && scene == 10)
        {
            cutscene_counter = 30;
            fadeOut2 = true;
            cutscene10 = true;
            cutscene11 = false;
        }

        if(cutscene10 == false && scene == 12)
        {
            cutscene_counter = 30;
            fadeOut2 = true;
            cutscene10 = true;
            cutscene11 = false;
           // fadeOut2 = true;
        }

        if(cutscene10 == false && scene == 14)
        {
            cutscene_counter = 0;
            fadeOut2 = true;
            cutscene10 = true;
            cutscene11 = false;
        }

        if(cutscene11 == false && scene == 13)
        {
            cutscene_counter = 90;
            //fadeOut2 = true;
            cutscene10 = false;
            cutscene11 = true;
        }

        if(cutscene11 == false && scene == 11)
        {
            cutscene_counter = 80;
            cutscene11 = true;
            cutscene10 = false;
            cp.box.x += 10;
        }


        if(scene == 5 && !cutscene5)
        {
            fadeOut2 = true;
            cutscene5 = true;
        //    cout << "Hello  ";
        }

        if(scene == 5 && fadeInAlpha > 250)
        {
            scene = 6;
            fadeOut2 = false;
            opening_credits = true;
            intro = false;
        }

        if(Level == 121 && myDot.box.y < 200)
        {
            fadeOut2 = true;
           // scene = 10;
        //    cout << "Hello  ";
        }


       // if(scene)
}


void switchChar()
{

    if(load_out1)
    {
        readfile4.open("slot1.map");
        newfile4.open("lazy.map");

        char ch;
        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotA1.map");
        newfile4.open("lazyA.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotB1.map");
        newfile4.open("lazyB.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotU1.map");
        newfile4.open("lazyU.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }
        readfile4.close();
        newfile4.close();
        load_out1 = false;
    }

    else
    {
        readfile4.open("slot2.map");
        newfile4.open("lazy.map");

        char ch;
        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotA2.map");
        newfile4.open("lazyA.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotB2.map");
        newfile4.open("lazyB.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }

        readfile4.close();
        newfile4.close();

        readfile4.open("slotU2.map");
        newfile4.open("lazyU.map");

        while(!readfile4.eof())
        {
            readfile4.get(ch);
            newfile4<<ch;
        }
        readfile4.close();
        newfile4.close();
        load_out1 = true;
    }
}


void credits()
{
        backgroundT.render(0,0);
        if(fall2 == 0)
        {
            fall = 0;
            fall2 = 640;
        }
        falling.render(0,fall);
        falling.render(0,fall2);
        fall -= 10;
        fall2 -= 10;
        freeFall.render(500,300);
        darken1.render(0,0);
        darken1.render(0,0);
        darken1.render(0,0);
        darken1.render(120,0);
        darken1.render(120,0);
        darken1.render(240,0);

        darken1.render(1080,0);
        darken1.render(1080,0);
        darken1.render(1080,0);
        darken1.render(960,0);
        darken1.render(960,0);
        darken1.render(840,0);


        if(credit_counter > 600)
        {
            fadeOut2 = false;
            Level = 221;
            opening_credits = false;
            scene = 0;
            beginning = true;
        }

        else if(credit_counter > 500)
        {
            fadeOut2 = true;
        }

        else if(credit_counter > 300 && credit_alpha <= 252)
        {
            creds = 2;
            credits_fadeIn = true;
        }

        else if(credit_counter > 100)
        {
            creds = 1;
        }

        if(creds == 1)
        {
            if(credit_alpha < 252 && credits_fadeIn)
                credit_alpha += 3;

            if(credit_alpha > 0 && !credits_fadeIn)
                credit_alpha -= 3;

            if(credit_alpha >= 252)
            {
                credits_fadeIn = false;
            }


        }

        if(creds == 2)
        {
            if(credit_alpha < 252 && credits_fadeIn)
                credit_alpha += 3;

            if(credit_alpha > 0 && !credits_fadeIn)
                credit_alpha -= 3;

            if(credit_alpha >= 252)
            {
                credits_fadeIn = false;
            }


        }

        credit1.setBlendMode( SDL_BLENDMODE_BLEND );
        credit1.setAlpha(credit_alpha);
        credit2.setBlendMode( SDL_BLENDMODE_BLEND );
        credit2.setAlpha(credit_alpha);
        credit_counter++;

        if(creds == 1)
            credit1.render(465, 100);
        if(creds == 2)
            credit2.render(456,100);

      //  if(credit_counter > 600)




}




int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The dot
    Dot myDot;

    companion pal;

 //   PlayerStats stats;

    //The class in f with setting up many of the SDL basics
    Setup foo;

    //The base class
    base b;

    //loads each map
    mapLoader Fman;

    PlayerCreator mumbo;

    Converter conv;

    Generator gen;
    Menu men;

    companion cp;

//    cs.copyCharacter();

    //The delay between a turret seeing the player and it killing the player
    int count = 0;

    sword square(128, 128);

  //  gun shooter(80, 80);

    gun *bullets [3];

    bullets[0] = new gun(128, 128);
    bullets[1] = new gun(128, 128);
    bullets[2] = new gun(128, 128);
    Particle *particles[400];

    //To highlight which option the player is on in the pause menu
    bool highlight = true;

    // player cant change time until they acquire the time gadget.
    bool timeGadget = false;

    strcpy(text, "Yooo");

    //The tiles that will be used
    Tile *tiles[ NORMAL_TILES ];

    //movable tiles
    mTile *mtiles[ MOVABLE_TILES ];

    //turrets
    turret *turrets[ TURRETS ];

    enemy *monsters[ 50 ];
    for(int i = 0; i < 10; i++)
    {
        monsters[i] = new Flyer(500, 600, 70, 60, 60);
        monsters[i + 10] = new charger(500, 500, 70, 100, 75);
        monsters[i + 20] = new crawler(500, 500, 70, 80, 38);
        monsters[i + 30] = new jumper(500, 500, 70, 96, 70);
    }

    //The frame rate regulator
    Timer fps;

/*    monsters[0] = new charger(200, 200, 60, 100, 67);
    monsters[1] = new crawler(800, 100, 60, 80, 38);
    monsters[2] = new Flyer(3300, 300, 60, 60, 60);
    monsters[3] = new jumper(2100, 200, 60, 96, 70);
    monsters[4] = new crawler(850, 100, 60, 80, 38);
    monsters[5] = new Flyer(2800, 200, 60, 60, 60);
    monsters[6] = new jumper(900, 400, 60, 96, 70);
    monsters[7] = new Flyer(2000, 200, 60, 60, 60);
    monsters[8] = new charger(400, 200, 60, 100, 67);
    monsters[9] = new charger(500, 200, 60, 100, 67); */

    //Initialize
    if( foo.init() == false )
    {

        return 1;
    }


    if(DEBUG)
    {
        testSuite tests;
        tests.testCrawler();
        tests.testJumper();
        tests.testCharger();
        tests.testFlyer();
        tests.testcharSelect();
        tests.testGenerator();
        tests.testPlayer();
        tests.testWeapons();
    }

    //Load the files
    if( foo.load_files() == false )
    {
        return 1;
    }

    foo.clip_tiles();

    for(int i = 0; i < monster_count; i++)
    {
        monsters[i]->loadEnemyTiles();
    }

    //sets where the player will respawn for that level
    myDot.set_respawn();
    //Mix_PlayMusic(music, -1);
    //sets the attributes for that level
    Fman.set_level();
    //sets the tiles for that level
   // Mix_PlayMusic(music, -1);
    std::ifstream map( "map/Lazy20.map");
 //   if( Fman.set_tiles( tiles , mtiles, turrets, map, monsters, myDot) == false )
    {
        //Mix_PlayMusic(music, -1);
  //      return 1;
    }


    for(int i = 0; i < 400; i++)
    {
            particles[ i ] = new Particle( rand() %rand() % 1300 + camera.x, rand() % 500 + camera.y, 6);
    }

    gen.count_pixels();

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );


    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
           // if(!pause)
                if(scene == 0 || scene == 13 || scene == 12)
                    myDot.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

   //     cs.run();

        //if the game is paused the character cant mov

        if(menu)
        {
            Fman.set_level();
            Fman.map_management(tiles, mtiles, turrets, monsters, myDot);
            if(men.run(gen) == 1)
            {
                quit = true;
            }
            conv.construct();
            Fman.set_level();
            Fman.map_management(tiles, mtiles, turrets, monsters, myDot);
            myDot.load();
            myDot.xVel = 0;
            menu = false;
            scene = 0;
        }

        if(!pause)
        {
            //moves the character
            myDot.move( tiles, conv );                           //
        }

      //  Fman.set_level();
       // Fman.map_management(tiles, mtiles, turrets, monsters, myDot);

        curX = myDot.getXpos();
        curY = myDot.getYpos();

        if(!kidnapped)
            cp.live(myDot, tiles);

        //if the player dies...
        if(myDot.dies(tiles, conv) || load_game)
        {
            //the map is reset to what was before the player entered the room
           // if(generatorNum == 1)
            Level = 222;
            exits = -1;
            Fman.set_level();
            Fman.map_management(tiles, mtiles, turrets, monsters, myDot);
            load_game = false;
            //all mtile structs are set to there original co ordinates.
        }

        //Set the camera
        myDot.set_camera();

        if(hurt_invul && !pause)
        {
            hurt_invul_counter++;

            if(hurt_invul_counter == 30)
            {
                hurt_invul = false;
                hurt_invul_counter = 0;
            }
        }

        if(dash_invul)
        {
            dash_invul_counter++;

            if(dash_invul_counter == 15)
            {
                dash_invul = false;
                dash_end = true;
                dash_invul_counter = 0;
            }
        }

        if(hurt_invul || dash_invul)
        {
            invul = true;
        }
        else
        {
            invul = false;
        }

        cutscene_management(myDot, cp);

        //Show the dot on the screen
        if(sword_counter == 6)
        {
            square.attack = false;
            square.canAttack = false;
            sword_counter = 0;
        }

      //  if(square.attack == false)
        //    square.canAttack = true;
            //Show the dot
        if(!pause)
        {
            if(!foo.animate(myDot))
            {
    //       return 0;
            }
        }

        backgroundT.render(0 - camera.x/camSpeed ,0 - camera.y/camSpeed);

        if(!pause)
        {
            for(int i = 0; i < flyer_count; i++)
            {
                myDot.knockback(*monsters[i], conv);

            }

            for(int i = 10; i < charger_count + 10; i++)
            {
                myDot.knockback(*monsters[i], conv);
            }

            for(int i = 20; i < crawler_count + 20; i++)
            {
                myDot.knockback(*monsters[i], conv);
            }

            for(int i = 30; i < jumper_count + 30; i++)
            {
                myDot.knockback(*monsters[i], conv);
            }

        }

        if(s_has_been_pressed)
        {
            switchChar();
            conv.construct();
            gen.count_pixels();
        }

        if(o_has_been_pressed)
        {
            camera.x = 0; camera.y= 0;
            gen.run3();
            conv.construct();
            gen.count_pixels();
            o_has_been_pressed = false;
        }

        square.get_position(myDot, foo);
        square.weaponControl();
        if(square.attack)
        {
           square.show();
           if(!pause)
             sword_counter++;
        }

        if(x_pressed && myDot.stats->energy > 0)
        {

            if(ammo == 0 && charge1 < 30)
            {
                charge1++;
                charging = true;
            }
            else if(ammo == 1 && charge2 < 30)
            {
                charge2++;
                charging = true;
            }

            else if (ammo == 2 && charge3 < 30)
            {
                charge3++;
                charging = true;
            }
        }
        else if(!x_pressed)
        {
            charging = false;
        }

    //    cout << "[  X pos:" << myDot.getXpos() << "  ]";
    //    cout << "[  y pos:" << myDot.getYpos() << "  ]";

        if(shooting)
        {
            if(can_shoot && bullets[ammo]->shot == false)
            {
  //              bullets[ammo]->charge = charge;
                bullets[ammo]->weaponControl(myDot);
                bullets[ammo]->get_position(myDot, foo);
                bullets[ammo]->shot = true;
                if(ammo == 2)
                    ammo = 0;
                else
                    ammo++;
                can_shoot = false;
                reload_count = true;

            }
            shooting = false;
        }

        if(reload_counter == 7)
        {
            can_shoot = true;
            reload_counter = 0;
            reload_count = false;
        }

        if(reload_count)
        {
            reload_counter++;
        }

        for(int p = 0; p < 3; p++)
        {
            if(bullets[p]->shot == true && bullets[p]->shot_dis < 30)
            {
              //  if(!pause)
                    bullets[p]->shoot(myDot, monsters, tiles, conv);
                bullets[p]->show();
                if(p == 0 && charge1 > 25)
                    bullets[p]->power_surge();
                else if(p == 1 && charge2 > 25)
                    bullets[p]->power_surge();
                else
                    if(p == 2 && charge3 > 25)
                    bullets[p]->power_surge();
            }

            if(bullets[p]->shot_dis >= 30)
            {
                bullets[p]->shot = false;
                bullets[p]->shot_dis = 0;

            }

            if(bullets[p]->shot == false && !x_pressed)
            {
                if(p == 0)
                    charge1 = 0;
                else if (p == 1)
                    charge2 = 0;
                else
                    charge3 = 0;
            }

        }


                //
        for(int i = 0; i < flyer_count; i++)
        {
           if(monsters[i]->alive)
           {
               if(!pause)
               {
                    monsters[i]->animation(foo);
                    monsters[i]->lives(myDot, tiles, square, bullets, conv);
               }
                monsters[i]->show();
           }
           else
           {
         //     if(monsters[i]->dead == false)
           //     cout << "dead2";
              monsters[i]->die();
           }
        }
        for(int i = 10; i < charger_count + 10; i++)
        {
           if(monsters[i]->alive)
           {
               if(!pause)
               {
                    monsters[i]->animation(foo);
                    monsters[i]->lives(myDot, tiles, square, bullets, conv);
               }
                monsters[i]->show();
           }
           else
              monsters[i]->die();
        }


        for(int i = 20; i < crawler_count + 20; i++)
        {
           if(monsters[i]->alive)
           {
               if(!pause)
               {
                    monsters[i]->animation(foo);
                    monsters[i]->lives(myDot, tiles, square, bullets, conv);
               }
                monsters[i]->show();
           }
           else
              monsters[i]->die();
        }

        for(int i = 30; i < jumper_count + 30; i++)
        {
           if(monsters[i]->alive)
           {
               if(!pause)
               {
                    monsters[i]->animation(foo);
                    monsters[i]->lives(myDot, tiles, square, bullets, conv);
               }
                monsters[i]->show();
           }
           else
           {
           //   if(monsters[i]->dead == false)
           //     cout << "dead";
              monsters[i]->die();
              monsters[i]->dead = true;
           }
        }

        if(!kidnapped)
            cp.animate(myDot);
        if(Level == 21 && scene == 3 && cutscene_counter > 20)
        {
            baddy2.render(3340 - camera.x, 1440 -camera.y);
            if(cutscene_counter > 80)
                condemned = true;
        }

        else if(Level == 21)
            baddy.render(3350 - camera.x, 1440 -camera.y);
        if(Level == 21)
            pink.render(3400 - camera.x, 1500 -camera.y);

        for( int t = 0; t < NORMAL_TILES; t++ )
        {
            Fman.clip_tiles(tiles[ t ]->get_box());
            if(tiles[ t ]->active)             //
                tiles[ t ]->show();                                       //
        }

        if(beginning)
        {
            Fman.set_level();
            Fman.map_management(tiles, mtiles, turrets, monsters, myDot);
            myDot.box.x = 2300;
            myDot.box.y = 1850;
            beginning = false;
        }

        if(pack_acquired >= 2)
        {
            jump_galore = true;
        }

        for( int t = 0; t < NORMAL_TILES; t++ )
        {                                          //
            if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == Win_Tile && tiles[ t ]->active)
            {

                tiles[t]->active = false;
                pixel_capacity += 300;
                pack_acquired++;
                pixel_pause_counter = 50;
            }

            if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == break_Tile)
            {

                prompt2.render((myDot.getXpos() - camera.x) + 18, (myDot.getYpos() - camera.y) - 40);
                prompt1.render((myDot.getXpos() - camera.x) + 15, (myDot.getYpos() - camera.y) - 40);
                if(rPressed)
                {
                    camera.x = 0; camera.y= 0;
                    gen.run(*myDot.stats);
                    conv.construct();
                }
            }

            if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && (tiles[ t ]->get_type() == left_exit || tiles[ t ]->get_type() == right_exit || tiles[ t ]->get_type() == down_exit || tiles[ t ]->get_type() == up_exit) && tiles[ t ]->active && scene == 0)
            {
                if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == left_exit && tiles[ t ]->active)
                {
                    out = 1;
                    scene = 10;
                }
                else if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == right_exit && tiles[ t ]->active)
                {
                    out = 2;
                    scene = 10;
                }
                else if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == down_exit && tiles[ t ]->active)
                {
                    out = 3;
                    scene = 14;
                }

                else if(myDot.check_collision(tiles[ t ]->get_box(), myDot.box) && tiles[ t ]->get_type() == up_exit && tiles[ t ]->active)
                {
                    out = 4;
                    scene = 12;
                }
            }

            if((scene == 10 || scene == 12 || scene == 14) && cutscene_counter == 50)
            {

                if(out == 1)
                {
                    Level--;
                    exits = 1;
                    scene = 11;
                }


                if(out == 2)
                {
                    Level++;
                    exits = 2;
                    scene = 11;
                }

                if(out == 3)
                {
                    Level += 100;
                    exits = 3;
                    scene = 13;
                }

                if(out == 4)
                {
                    Level -= 100;
                    exits = 4;
                    scene = 13;
                }

               // cout << "new level " << Level;

                //scene = 0;
               // cutscene_counter = 0;


                Fman.set_level();
                Fman.map_management(tiles, mtiles, turrets, monsters, myDot);
                //myDot.box.y = 200;
                cp.box.x = myDot.box.x - 20;
                cp.box.y = myDot.box.y;
                for(int i = 0; i < flyer_count; i++)
                {
                    monsters[i]->alive = true;
                    monsters[i]->dead = false;
                    monsters[i]->detect = false;
                    monsters[i]->box.x = mon_storage[i].x;
                    monsters[i]->box.y = mon_storage[i].y;
                    monsters[i]->spawnX = mon_storage[i].x;
                    monsters[i]->spawnY = mon_storage[i].y;
                    //cout << mon_storage[i].type;
                    if(mon_storage[i].type == 5)
                    {
                        monsters[i]->box.w = 200;
                        monsters[i]->box.h = 200;
                        monsters[i]->type = 5;
                    //    cout << "reach";
                    }
                    //cout << "reach2";
                    monsters[i]->he = mon_storage[i].health;
                }

                for(int i = 10; i < charger_count + 10; i++)
                {
                    monsters[i]->alive = true;
                    monsters[i]->dead = false;
                    monsters[i]->detect = false;
                    monsters[i]->box.x = mon_storage[i].x;
                    monsters[i]->box.y = mon_storage[i].y;
                    monsters[i]->he = mon_storage[i].health;
                }

                for(int i = 20; i < crawler_count + 20; i++)
                {
                    monsters[i]->alive = true;
                    monsters[i]->dead = false;
                    monsters[i]->box.x = mon_storage[i].x;
                    monsters[i]->box.y = mon_storage[i].y;
                    monsters[i]->he = mon_storage[i].health;
                }

                for(int i = 30; i < jumper_count + 30; i++)
                {
                    monsters[i]->alive = true;
                    monsters[i]->dead = false;
                    monsters[i]->detect = false;
                    monsters[i]->box.x = mon_storage[i].x;
                    monsters[i]->box.y = mon_storage[i].y;
                    monsters[i]->he = mon_storage[i].health;
                    monsters[i]->dead = false;
                //    cout << mon_storage[i].type;
                    if(mon_storage[i].type == 6)
                    {
                        monsters[i]->box.w = 300;
                        monsters[i]->box.h = 200;
                        monsters[i]->type = 6;
                  //      cout << "reach 6";
                    }
                }

         //       cutscene_counter = 0;
                //scene = 11;
            }
        }


        if(intro)
        {
            for(int i = 0; i < 400; i++)
            {
                particles[i]->fallLeft();
                particles[i]->show();
                if(particles[i]->is_dead())
                {
                    delete particles[ i ];
                    particles[ i ] = new Particle( rand() % 1300 + camera.x, rand() % 500 + camera.y, 6 );
                }
            }
        }

        if(pixel_pause_counter > 0)
        {
            blackBackground.render(400, 270, &cutOut);
            textOfSorts2.render(510, 310);
            textOfSorts.render(507, 310);
            pause = true;
            pixel_pause_counter--;
            if(pixel_pause_counter == 0)
            {
                pause = false;
            }

        }

       // cout << " x " << myDot.box.x << " ";
    //    cout << " y " << myDot.box.y << " ";
        myDot.show();
        if(!intro)
        {
            heart.render(5, 28);
            life_con.w = myDot.stats->maxHealth + 3;
            life_bar_con.render(29, 28, &life_con);
            life_bar_con.render((32 + myDot.stats->maxHealth), 28, &life_bar_con_end);
            life.w = myDot.stats->health;
            life_bar.render(32, 30, &life);

            power.render(5, 50);
            life_con.w = myDot.stats->maxEnergy + 3;
            life_bar_con.render(29, 50, &life_con);
            life_bar_con.render((32 + myDot.stats->maxEnergy), 50, &life_bar_con_end);
            life.w = myDot.stats->energy;
            energy_bar.render(32, 52, &life);

            pixelBox.render(1053, 30);
            gFont = TTF_OpenFont( "font2.ttf", 25 );
            pixels_left = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);
            std::stringstream ss1;
            ss1 << pixels_left;
            SDL_Color textColor2 = { 0, 162, 232 };
            SDL_Color textColor3 = { 0, 0, 232 };
            pLeft.loadFromRenderedText( ss1.str(), textColor3 );
            pLeft.render(1060, 35);
            pLeft.loadFromRenderedText( ss1.str(), textColor2 );
            pLeft.render(1058, 35);
        }

        if(intro)
        {
            if(scene == 2)
            {
                speech2.render(600, 500);
                double_time = true;
            }
            else
            {
                speech_bubble.render(200, 150);
            }
        }

        if(opening_credits)
        {
            credits();
        }

        if(intro || opening_credits)
            dark.render(0,0);
        speech_bubble.setBlendMode( SDL_BLENDMODE_BLEND );
        speech_bubble.setAlpha(speech_alpha);
        speech2.setBlendMode( SDL_BLENDMODE_BLEND );
        speech2.setAlpha(speech_alpha);
        if(speech_alpha < 250 && speechIn)
            speech_alpha += 3;
        else if(speech_alpha > 5)
            speech_alpha -= 8;

        if(speech_alpha >= 250)
            speechIn = false;
//        strcat(text, talking[i]);
  //      speech.render(200,200);

        fadeIn.setAlpha(fadeInAlpha);
        fadeIn.render(0,0);
        if(fadeInAlpha > 0 && !fadeOut2)
            fadeInAlpha -= 5;
        else if(fadeOut2 && fadeInAlpha < 255)
        {
                fadeInAlpha += 15;
               // cout << "Hello  ";
        }
        if(fadeInAlpha > 240 && (scene == 11 || scene == 13))
            fadeOut2 = false;

        SDL_RenderPresent( gRenderer );


        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }


    //Clean up
    clean_up( tiles ,mtiles, turrets );

    return 0;
}
