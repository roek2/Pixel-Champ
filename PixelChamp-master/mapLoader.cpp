#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <fstream>
#include "setupHeader.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include "turretHeader.h"
#include "mtileHeader.h"
#include "mapLoaderHeader.h"
#include "LTextureHeader.h"
#include "enemyHeader.h"
#include "Flyer.h"
#include "chargerHeader.h"
#include "dotHeader.h"
#include <ctime>

using namespace std;

extern int Level;

const int TILE_SPRITES = 12;

extern int LEVEL_WIDTH;
extern int LEVEL_HEIGHT;
extern int TOTAL_TILES;
extern int NORMAL_TILES;
extern int MOVABLE_TILES;
extern int monster_count;
const int TILE_WIN = 0;
const int TILE_NONE = 1;
const int TILE_DEATH = 2;
const int TILE_WALL = 3;
const int TILE_PUSH = 4;
const int TILE_GADGET = 5;
const int TILE_BREAK = 6;
const int TILE_LEFT = 7;
const int TILE_RIGHT = 8;
extern int TURRETS;
extern int flyer_count;
extern int charger_count;
extern int crawler_count;
extern int jumper_count;
extern int exits;

extern int Win_Tile;
extern int Invisible_Tile;
extern int Death_Tile;
extern int Solid_Tile;
extern int Push_Tile;
extern int Gadget_Tile;
extern int left_exit;
extern int right_exit;
extern int down_exit;
extern int up_exit;
extern int break_Tile;

extern SDL_Surface *tileSheet;
extern SDL_Surface *tileSheet2;
extern SDL_Surface *background;
extern SDL_Surface *background2;
extern Mix_Music *music;

extern int TILE_WIDTH;
extern int TILE_HEIGHT;
extern int TOTAL_TILES;
extern int LEVEL_WIDTH;

extern LTexture tileSheetT;
extern LTexture backgroundT;
extern int camSpeed;
extern int currentCamX;
extern int currentCamY;
extern bool MAPDEBUG;
extern bool ENEMYDEBUG;
extern int test_success;
extern int test_failures;

extern Mon_storage mon_storage[];


int temp = 0;


SDL_Rect clips[TILE_SPRITES];

void mapLoader :: clip_tiles(SDL_Rect box)
{

    clips[ TILE_WIN ].x = 0;
    clips[ TILE_WIN ].y = 0;
    clips[ TILE_WIN ].w = box.w;
    clips[ TILE_WIN ].h = box.h;

    clips[ TILE_NONE ].x = 0;
    clips[ TILE_NONE ].y = 80;
    clips[ TILE_NONE ].w = box.w;
    clips[ TILE_NONE ].h = box.h;

    clips[ TILE_DEATH ].x = 0;
    clips[ TILE_DEATH ].y = 160;
    clips[ TILE_DEATH ].w = box.w;
    clips[ TILE_DEATH ].h = box.h;

    clips[ TILE_PUSH ].x = 160;
    clips[ TILE_PUSH ].y = 0;
    clips[ TILE_PUSH ].w = box.w;
    clips[ TILE_PUSH ].h = box.h;

    clips[ TILE_WALL ].x = 160;
    clips[ TILE_WALL ].y = 80;
    clips[ TILE_WALL ].w = box.w;
    clips[ TILE_WALL ].h = box.h;

    clips[ TILE_BREAK ].x = 160;
    clips[ TILE_BREAK ].y = 160;
    clips[ TILE_BREAK ].w = box.w;
    clips[ TILE_BREAK ].h = box.h;

    clips[ TILE_GADGET ].x = 300;
    clips[ TILE_GADGET ].y = 0;
    clips[ TILE_GADGET ].w = box.w;
    clips[ TILE_GADGET ].h = box.h;

    clips[ TILE_LEFT ].x = 240;
    clips[ TILE_LEFT ].y = 80;
    clips[ TILE_LEFT ].w = box.w;
    clips[ TILE_LEFT ].h = box.h;

    clips[ TILE_RIGHT ].x = 240;
    clips[ TILE_RIGHT ].y = 160;
    clips[ TILE_RIGHT ].w = box.w;
    clips[ TILE_RIGHT ].h = box.h;

    clips[ 9 ].x = 0;
    clips[ 9 ].y = 272;
    clips[ 9 ].w = box.w;
    clips[ 9 ].h = box.h;

    clips[ 10 ].x = 0;
    clips[ 10 ].y = 535;
    clips[ 10 ].w = box.w;
    clips[ 10 ].h = box.h;

    clips[ 11 ].x = 1120;
    clips[ 11 ].y = 0;
    clips[ 11 ].w = box.w;
    clips[ 11 ].h = box.h;



}

bool mapLoader :: set_tiles( Tile *tiles[], mTile *mtiles[], turret *turrets[], std::ifstream &map, enemy *monsters[], Dot &myDot )
{
   // load the maps
    int x = 0, y = 0;
    TURRETS = 0;
    MOVABLE_TILES = 0;
    NORMAL_TILES = 0;
    flyer_count = 0;
    charger_count = 0;
    crawler_count = 0;
    jumper_count = 0;
    monster_count = 0;


    int sC = 0;
    int dC = 0;
    int wC = 0;
    int gC = 0;
    int bC = 0;
    int leC = 0;
    int reC = 0;
    int deC = 0;
    int ueC = 0;

    if( map == NULL )
    {
        if(MAPDEBUG)
            printf("\nfail to load map for Level %d", Level);
        return false;
    }

    int m = 0;
    int n = 0;
    int s = 0;
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile and size of tile that will be made
        int tileType = -1;
        int artType = -1;
        int mappedwidth = -1;
        int mappedheight = -1;
        int innerposX = -1;
        int innerposY = -1;
        char bracket;

        map >> tileType;
        map >> artType;
        map >> mappedwidth;
        map >> mappedheight;
        map >> innerposX;
        map >> innerposY;
        //If the was a problem in reading the map
        if( map.fail() == true )
        {
            //Stop loading map
            map.close();
            return false;
        }

        //go through each map input and assign them to a tile, mtile or turret
        if( ( tileType == Death_Tile ) || ( tileType == Solid_Tile ) || (tileType == Win_Tile) || (tileType == Gadget_Tile) || (tileType == break_Tile) || (tileType == left_exit) || (tileType == right_exit) || (tileType == down_exit) || (tileType == up_exit) )
        {
            tiles[ s ] = new Tile( x + innerposX, y + innerposY, mappedwidth, mappedheight,tileType, artType );
            s++;
            NORMAL_TILES++;
   /*         if(tileType == Win_Tiles)
            {
                for(int i = 0; i < pack_count; i++ )
                {
                    if(tiles[ s ].x != packs[i].x && tiles[ s ].y != pack[i].y && Level != pack[i].Level)))
                    {

                    }
                }
            } */

            if(MAPDEBUG)
            {
                if(tileType == Death_Tile)
                    dC++;
                else if(tileType == Solid_Tile)
                    sC++;
                if(tileType == Win_Tile)
                    wC++;
                else if(tileType == Gadget_Tile)
                    gC++;
                else if(tileType == break_Tile)
                    bC++;
                else if(tileType == left_exit)
                    leC++;
                else if(tileType == right_exit)
                    reC++;
                else if(tileType == down_exit)
                    deC++;
                else if(tileType == up_exit)
                    ueC++;
            }


        }

        else if( tileType == Invisible_Tile)
        {
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= LEVEL_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    if(MAPDEBUG)
    {
        printf("\nSolid Tiles loaded: %d\n", sC);
        printf("Death Tiles loaded: %d\n", dC);
        printf("Win Tiles loaded: %d\n", wC);
        printf("Gadget Tiles loaded: %d\n", gC);
        printf("Break Tiles loaded: %d\n", bC);
        printf("Left exits loaded: %d\n", leC);
        printf("Right exits loaded: %d\n", reC);
        printf("Up exits loaded: %d\n", ueC);
        printf("Down exits loaded: %d\n", deC);
    }

    map >> camSpeed;
    map >> currentCamX;
    map >> currentCamY;
    map >> monster_count;


    for(int i = 0; i < NORMAL_TILES; i++)
    {
        if(tiles[i]->get_type() == right_exit)
        {
            if(exits == 1)
            {
                myDot.box.x = tiles[i]->get_box().x - 100;
                myDot.box.y = tiles[i]->get_box().y - 150;
            }
        }

        else if(tiles[i]->get_type() == left_exit)
        {
            if(exits == 2)
            {
                myDot.box.x = tiles[i]->get_box().x;
                myDot.box.y = tiles[i]->get_box().y -80;
            }
        }

        else if(tiles[i]->get_type() == up_exit)
        {
            if(exits == 3)
            {
                myDot.box.x = tiles[i]->get_box().x;
                myDot.box.y = tiles[i]->get_box().y + 0;
            }
        }

        else if(tiles[i]->get_type() == down_exit)
        {
            if(exits == 4)
            {
                myDot.box.x = tiles[i]->get_box().x;
                myDot.box.y = tiles[i]->get_box().y - 200;
            }
        }

        else if( exits == -1)
        {
            myDot.load();
        }


    }
    int EnemyType = 0;
    int EnemyX= 0;
    int EnemyY= 0;
    int EnemyHealth = 0;
    int EnemyW = 0;
    int EnemyH = 0;

    if(ENEMYDEBUG)
    {
        printf("\n---------------Enemy Tests for Level %d------------------\n\n", Level);
        test_success = 0;
        test_failures = 0;
    }

    for(int i = 0; i < monster_count; i++)
    {
        map >> EnemyType;
        map >> EnemyX;
        map >> EnemyY;
        map >> EnemyHealth;

        if(EnemyType == 1 || EnemyType == 5)
        {
            mon_storage[flyer_count].x = EnemyX;
            mon_storage[flyer_count].y = EnemyY;
            mon_storage[flyer_count].health = EnemyHealth;
            if(EnemyType == 1)
                mon_storage[flyer_count].type = 1;
            else
                mon_storage[flyer_count].type = 5;

            if(ENEMYDEBUG)
            {
                printf("\nFlyer Loaded:\n");
                printf("   Position: %d", mon_storage[flyer_count].x);
                printf(", %d\n",mon_storage[flyer_count].y);
                printf("   Health: %d\n", mon_storage[flyer_count].health);
                test_success++;

            }
            flyer_count++;
        }
        else if(EnemyType == 2)
        {
            mon_storage[charger_count + 10].x = EnemyX;
            mon_storage[charger_count + 10].y = EnemyY;
            mon_storage[charger_count + 10].health = EnemyHealth;

            if(ENEMYDEBUG)
            {
                printf("\nCharger Loaded:\n");
                printf("   Position: %d", mon_storage[charger_count].x);
                printf(", %d\n",mon_storage[charger_count].y);
                printf("   Health: %d\n", mon_storage[charger_count].health);
                test_success++;

            }

            charger_count++;
        }
        else if(EnemyType == 3)
        {
            mon_storage[crawler_count + 20].x = EnemyX;
            mon_storage[crawler_count + 20].y = EnemyY;
            mon_storage[crawler_count + 20].health = EnemyHealth;

            if(ENEMYDEBUG)
            {
                printf("\nCrawler Loaded:\n");
                printf("   Position: %d", mon_storage[crawler_count].x);
                printf(", %d\n",mon_storage[crawler_count].y);
                printf("   Health: %d\n", mon_storage[crawler_count].health);
                test_success++;
            }

            crawler_count++;
        }
        else if(EnemyType == 4 || EnemyType == 6)
        {
            mon_storage[jumper_count + 30].x = EnemyX;
            mon_storage[jumper_count + 30].y = EnemyY;
            mon_storage[jumper_count + 30].health = EnemyHealth;
            if(EnemyType == 4)
                mon_storage[jumper_count + 30].type = 4;
            else if(EnemyType == 6)
                mon_storage[jumper_count + 30].type = 6;

            if(ENEMYDEBUG)
            {
                printf("\nJumper Loaded:\n");
                printf("   Position: %d", mon_storage[jumper_count].x);
                printf(", %d\n",mon_storage[jumper_count].y);
                printf("   Health: %d\n", mon_storage[jumper_count].health);
                test_success++;
            }
            jumper_count++;
        }

        else if(EnemyType > 6)
        {
            test_failures++;
        }


    }

    //If the map was loaded fine
    map.close();


    if(ENEMYDEBUG)
    {
        printf("%d Flyers loaded\n", flyer_count);
        printf("%d Crawlers loaded\n", crawler_count);
        printf("%d Chargers loaded\n", charger_count);
        printf("%d Jumpers loaded\n", jumper_count);
        if((jumper_count + charger_count + crawler_count + flyer_count) == monster_count)
        {
            printf("\nSuccess: ");
            test_success++;
        }
        else
        {
            printf("\nFailure: ");
            test_failures++;
        }
        printf("Specified to load in %d,", monster_count);
        printf(" Actually loaded in %d,", (jumper_count + charger_count + crawler_count + flyer_count));
    }



    printf("\n%d Tests Succeded\n", test_success);
    printf("%d Tests Failed\n", test_failures);
    return true;
}

void mapLoader :: map_management(Tile *tiles[], mTile *mtiles[], turret *turrets[], enemy *monsters[], Dot &myDot)
{
    std::ifstream map20( "map/Lazy20.map");
    std::ifstream map21( "map/Lazy21.map");
    std::ifstream map121( "map/Lazy121.map");
    std::ifstream map221( "map/Lazy221.map");
    std::ifstream map222( "map/Lazy222.map");
    std::ifstream map223( "map/Lazy223.map");
    std::ifstream map224( "map/Lazy224.map");
    std::ifstream map322( "map/Lazy322.map");
    std::ifstream map323( "map/Lazy323.map");
    std::ifstream map324( "map/Lazy324.map");
    std::ifstream map325( "map/Lazy325.map");
    std::ifstream map326( "map/Lazy326.map");
    std::ifstream map327( "map/Lazy327.map");
    std::ifstream map424( "map/Lazy424.map");
    std::ifstream map425( "map/Lazy425.map");
    std::ifstream map426( "map/Lazy426.map");

    std::ifstream map427( "map/Lazy427.map");
    std::ifstream map428( "map/Lazy428.map");
    std::ifstream map526( "map/Lazy526.map");
    std::ifstream map527( "map/Lazy527.map");
    std::ifstream map528( "map/Lazy528.map");

    if(Level == 20)
        set_tiles( tiles , mtiles, turrets, map20, monsters, myDot);
    else if(Level == 21)
        set_tiles( tiles , mtiles, turrets, map21, monsters, myDot);
    else if(Level == 121)
        set_tiles( tiles , mtiles, turrets, map121, monsters, myDot);
    else if(Level == 221)
        set_tiles( tiles , mtiles, turrets, map221, monsters, myDot);
    else if(Level == 222)
        set_tiles( tiles , mtiles, turrets, map222, monsters, myDot);
    else if(Level == 223)
        set_tiles( tiles , mtiles, turrets, map223, monsters, myDot);
    else if(Level == 224)
        set_tiles( tiles , mtiles, turrets, map224, monsters, myDot);
//    else if(Level == 225)
//        set_tiles( tiles , mtiles, turrets, map225, monsters, myDot);
    else if(Level == 322)
        set_tiles( tiles , mtiles, turrets, map322, monsters, myDot);
    else if(Level == 323)
        set_tiles( tiles , mtiles, turrets, map323, monsters, myDot);
    else if(Level == 324)
        set_tiles( tiles , mtiles, turrets, map324, monsters, myDot);
    else if(Level == 325)
        set_tiles( tiles , mtiles, turrets, map325, monsters, myDot);
    else if(Level == 326)
        set_tiles( tiles , mtiles, turrets, map326, monsters, myDot);
    else if(Level == 327)
        set_tiles( tiles , mtiles, turrets, map327, monsters, myDot);
    else if(Level == 427)
        set_tiles( tiles , mtiles, turrets, map427, monsters, myDot);
    else if(Level == 428)
        set_tiles( tiles , mtiles, turrets, map428, monsters, myDot);
    else if(Level == 426)
        set_tiles( tiles , mtiles, turrets, map426, monsters, myDot);
    else if(Level == 425)
        set_tiles( tiles , mtiles, turrets, map425, monsters, myDot);
    else if(Level == 424)
        set_tiles( tiles , mtiles, turrets, map424, monsters, myDot);
    else if(Level == 526)
        set_tiles( tiles , mtiles, turrets, map526, monsters, myDot);
    else if(Level == 527)
        set_tiles( tiles , mtiles, turrets, map527, monsters, myDot);
    else if(Level == 528)
        set_tiles( tiles , mtiles, turrets, map528, monsters, myDot);
}

void mapLoader :: reset(mTile *mtiles[], Tile *tiles[], turret *turrets[])
{
}

//based on the level, the game loads up the appropraite tiles, background and music
void mapLoader :: set_level()
{
    if(Level == 20)
    {
        backgroundT.loadFromFile( "darkness.png");
        tileSheetT.loadFromFile( "PrtCave.png" );

    }

    else if(Level == 20)
    {
        backgroundT.loadFromFile( "darkness.png");
        tileSheetT.loadFromFile( "PrtCave.png" );
    }

    else if(Level == 102)
    {
        backgroundT.loadFromFile( "newbg.png");
        tileSheetT.loadFromFile( "newTile.png" );
    }

    else if(Level == 121)
    {
        backgroundT.loadFromFile( "long.png");
        tileSheetT.loadFromFile( "PrtCave.png" );
    }

    else if(Level == 221)
    {
        backgroundT.loadFromFile( "newbg.png");
        tileSheetT.loadFromFile( "newTile.png" );
    }

    else if(Level == 222)
    {
        backgroundT.loadFromFile( "newbg6.png");
        tileSheetT.loadFromFile( "newTile.png" );
    }

    else if(Level == 223)
    {
        backgroundT.loadFromFile( "newbg.png");
        tileSheetT.loadFromFile( "newTile.png" );
    }

    else if(Level == 528)
    {
        backgroundT.loadFromFile( "newbg6.png");
        tileSheetT.loadFromFile( "newTile.png" );
    }


}
