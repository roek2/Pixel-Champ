#include "SDL.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "playerTileHeader.h"
#include "playerCreatorHeader.h"
#include "LTextureHeader.h"
#include <fstream>

extern SDL_Rect camera;
extern SDL_Surface *screen;
extern SDL_Surface *tileSheet3;
int PTILE_WIDTH = 10;
int PTILE_HEIGHT = 10;
extern SDL_Rect select;
extern int TOTAL_PLAYER_TILES;
LTexture gModulatedTexture;
extern LTexture monitorT;
extern LTexture compT;
extern int zoom;
extern SDL_Rect zooming[4];
extern SDL_Rect zooming2[4];

PlayerTile::PlayerTile( int x, int y, int red, int green, int length, int height, int blue, int isUsed )
{
    //Get the offsets
    box.x = x;
    box.y = y;

    chosen = false;

    //Set the collision box
    box.w = PTILE_WIDTH;
    box.h = PTILE_HEIGHT;


    used = isUsed;

    //Get the tile type
    colRed = red;
    colGreen = green;
    colBlue = blue;
    le = length;
    he = height;
    isGrabbed = false;
}

void PlayerTile::show()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        //Show the tile
        gModulatedTexture.loadFromFile( "blank.png" );
        gModulatedTexture.setColor( colRed, colGreen, colBlue );
        gModulatedTexture.render( box.x - camera.x, box.y - camera.y, &zooming2[ 10/10 ]);

    }
}

void PlayerTile::show3()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        //Show the tile
        compT.render( box.x - camera.x , box.y - camera.y , &zooming2[ 10/10 ]);

    }
}

void PlayerTile::show4()
{

    gModulatedTexture.loadFromFile( "blank.png" );
    gModulatedTexture.setColor( colRed, colGreen, colBlue );
    gModulatedTexture.render( box.x - camera.x, box.y - camera.y);

}


void PlayerTile::show2()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
        if(isUsed())
            show();
        compT.render( box.x - camera.x , box.y - camera.y , &zooming2[ 10/10 ]);
    }
}


int PlayerTile::get_red()
{
    return colRed;
}

int PlayerTile::get_green()
{
    return colGreen;
}

int PlayerTile::get_length()
{
    return le;
}

int PlayerTile::get_height()
{
    return he;
}

int PlayerTile::get_x()
{
    return box.x;
}

int PlayerTile::get_y()
{
    return box.y;
}


int PlayerTile::get_blue()
{
    return colBlue;
}

int PlayerTile::isUsed()
{
    return used;
}

SDL_Rect &PlayerTile::get_box()
{
    return box;
}

bool PlayerTile::is_chosen()
{
    return chosen;
}


