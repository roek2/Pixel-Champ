#include "SDL.h"
#include "SDL_image.h"
#include "baseHeader.h"
#include "tileHeader.h"
#include "LTextureHeader.h"
#include <fstream>

extern int TILE_WIDTH;
extern int TILE_HEIGHT;

extern bool blending;
extern int alpha;

extern SDL_Surface *screen;
extern SDL_Surface *tileSheet;
extern SDL_Surface *tileSheet2;
extern LTexture dotT;
extern LTexture tileSheetT;
extern SDL_Rect clips[];

extern SDL_Rect camera;

Tile::Tile( int x, int y, int height, int width, int tileType ,int artType)
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = width;
    box.h = height;

    //Get the tile type
    type = tileType;

    art = artType;

    active = true;

}


void Tile::show()
{
    //If the tile is on screen
    if( check_collision( camera, box ) == true )
    {
            //apply_surface( box.x - camera.x, box.y - camera.y, tileSheet, screen, &clips[ art ] );
            //apply_surface( box.x - camera.x, box.y - camera.y, tileSheet2, screen, &clips[ art ] );
            tileSheetT.render(box.x - camera.x, box.y - camera.y, &clips[art]);
    }
   // tileSheetT.render(box.x - camera.x, box.y - camera.y, &clips[art]);
    //tileSheetT.render(0 - camera.x, 0 - camera.y);

}

//return the type of the tile
int Tile::get_type()
{
    return type;
}

int Tile::get_art()
{
    return art;
}

//returns the sedl rect of that tile
SDL_Rect Tile::get_box()
{
    return box;
}
