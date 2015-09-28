#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "baseHeader.h"
#include "playerCreatorHeader.h"
#include "baseHeader.h"
#include "playerTileHeader.h"
#include "TimerHeader.h"
#include "LTextureHeader.h"
#include <fstream>
#include <cmath>
#include <sstream>

int TOTAL_PLAYER_TILES  = 4096 * 4;               //2240
extern int FRAMES_PER_SECOND ;
int PLEVEL_WIDTH = 1280;
extern int PTILE_WIDTH;
extern int PTILE_HEIGHT;
extern SDL_Rect camera;
extern int FRAMES_PER_SECOND;
bool selected = false;
int pixels_remaining = 0;
int red = 0;
int gre = 0;
int blu = 0;
int currentLength = 0;
int currentHeight = 0;
int pixelUsed = 0;
extern SDL_Event event;
int total_pixels_used = 0;
int man_pixels_used = 0;
int sword_pixels_used = 0;
int gun_pixels_used = 0;
extern int pixel_capacity;
bool atCapacity = false;
int WIDTH = 128;
int HEIGHT = 128;
bool tempOn = false;
int tempRed = 0;
int tempGreen = 0;
int tempLength = 0;
int tempHeight = 0;
int tempBlue = 0;
int tempUsed = 0;
bool paste = false;
bool canChooseColour = false;
bool red_chosen = false;
bool blue_chosen = false;
bool green_chosen = false;
extern int stat_pixels;

SDL_Rect buttons[20];

int currentRed = 255;
int currentBlue = 0;
int currentGreen = 0;

int startSquare = 0;

extern SDL_Renderer* gRenderer;
extern LTexture blank;
extern LTexture monitorT;
extern LTexture monitorT2;
extern LTexture blackT;
extern LTexture creatorInterface;
extern LTexture creatorInterface2;
extern LTexture button1;
extern LTexture Sel5;
extern LTexture Sel6;
extern LTexture button_click1;
extern LTexture pixelDisplay;
extern LTexture paletteDisplay;
int zoom = 5;
bool canPaint = true;
bool paint = false;
bool canRubber = false;
bool rubber = false;
bool canFill = false;
bool canSelect = false;
bool canSquare = false;
bool canGrab = false;
bool canPaste = false;
bool copying = false;
bool copyBufferFull = false;
int pointer_width = 0;
SDL_Rect zooming[5];
SDL_Rect zooming2[5];
SDL_Rect zooming3[5];
SDL_Rect zooming4[5];
SDL_Rect clicked_button[8];
int left_padding = 280;
PlayerTile *copyTiles[ 4096 * 4 ];
int count = 0;
bool zoom_width_clicked = false;
int copyXLength = 0;
int copyYLength = 0;
int selectXLength = 0;
int selectYLength = 0;
extern TTF_Font *gFont;

PlayerCreator :: PlayerCreator()
{
   // left_padding = 200;
}

void PlayerCreator:: clip()
{
     zooming[1].x = 0;
     zooming[1].y = 0;
     zooming[1].w = zoom;
     zooming[1].h = zoom;

     zooming[2].x = 11;
     zooming[2].y = 0;
     zooming[2].w = zoom;
     zooming[2].h = zoom;

     zooming[4].x = 30;
     zooming[4].y = 0;
     zooming[4].w = zoom;
     zooming[4].h = zoom;

     zooming2[1].x = 0;
     zooming2[1].y = 0;
     zooming2[1].w = zoom;
     zooming2[1].h = zoom;

     zooming2[2].x = 10;
     zooming2[2].y = 0;
     zooming2[2].w = zoom;
     zooming2[2].h = zoom;

     zooming2[4].x = 30;
     zooming2[4].y = 0;
     zooming2[4].w = zoom;
     zooming2[4].h = zoom;

     zooming3[1].x = 0;
     zooming3[1].y = 0;
     zooming3[1].w = zoom;
     zooming3[1].h = zoom;

     zooming3[2].x = 11;
     zooming3[2].y = 0;
     zooming3[2].w = zoom;
     zooming3[2].h = zoom;

     zooming3[4].x = 32;
     zooming3[4].y = 0;
     zooming3[4].w = zoom;
     zooming3[4].h = zoom;

     zooming4[0].x = 0;
     zooming4[0].y = 0;
     zooming4[0].w = 147;
     zooming4[0].h = 56;

     zooming4[1].x = 0;
     zooming4[1].y = 57;
     zooming4[1].w = 147;
     zooming4[1].h = 55;

     zooming4[2].x = 0;
     zooming4[2].y = 113;
     zooming4[2].w = 147;
     zooming4[2].h = 55;

     zooming4[3].x = 0;
     zooming4[3].y = 170;
     zooming4[3].w = 140;
     zooming4[3].h = 50;

     zooming4[4].x = 0;
     zooming4[4].y = 220;
     zooming4[4].w = 140;
     zooming4[4].h = 50;

     clicked_button[0].x = 0;
     clicked_button[0].y = 0;
     clicked_button[0].w = 130;
     clicked_button[0].h = 42;

     clicked_button[1].x = 0;
     clicked_button[1].y = 42;
     clicked_button[1].w = 130;
     clicked_button[1].h = 42;

     clicked_button[2].x = 0;
     clicked_button[2].y = 84;
     clicked_button[2].w = 130;
     clicked_button[2].h = 42;

     clicked_button[3].x = 0;
     clicked_button[3].y = 126;
     clicked_button[3].w = 130;
     clicked_button[3].h = 42;

     clicked_button[4].x = 0;
     clicked_button[4].y = 168;
     clicked_button[4].w = 20;
     clicked_button[4].h = 24;

     clicked_button[5].x = 20;
     clicked_button[5].y = 168;
     clicked_button[5].w = 20;
     clicked_button[5].h = 24;

     clicked_button[6].x = 0;
     clicked_button[6].y = 192;
     clicked_button[6].w = 46;
     clicked_button[6].h = 26;

     clicked_button[7].x = 46;
     clicked_button[7].y = 192;
     clicked_button[7].w = 46;
     clicked_button[7].h = 26;

}

void PlayerCreator:: setup_buttons()
{
    buttons[0].x = 37 + camera.x;
    buttons[0].y = 33 + camera.y;
    buttons[0].w = 130;
    buttons[0].h = 42;

    buttons[1].x = 37 + camera.x;
    buttons[1].y = 100 + camera.y;
    buttons[1].w = 130;
    buttons[1].h = 42;

    buttons[2].x = 37 + camera.x;
    buttons[2].y = 168 + camera.y;
    buttons[2].w = 130;
    buttons[2].h = 42;

    buttons[3].x = 37 + camera.x;
    buttons[3].y = 243 + camera.y;
    buttons[3].w = 130;
    buttons[3].h = 42;

    buttons[4].x = 37 + camera.x;
    buttons[4].y = 315 + camera.y;
    buttons[4].w = 130;
    buttons[4].h = 42;

    buttons[5].x = 30 + camera.x;
    buttons[5].y = 435 + camera.y;
    buttons[5].w = 20;
    buttons[5].h = 24;

    buttons[6].x = 30 + camera.x;
    buttons[6].y = 467 + camera.y;
    buttons[6].w = 20;
    buttons[6].h = 24;

    buttons[7].x = 27 + camera.x;
    buttons[7].y = 575 + camera.y;
    buttons[7].w = 90;
    buttons[7].h = 41;

    buttons[8].x = 1040 + camera.x;
    buttons[8].y = 127 + camera.y;
    buttons[8].w = 130;
    buttons[8].h = 42;

    buttons[9].x = 1040 + camera.x;
    buttons[9].y = 190 + camera.y;
    buttons[9].w = 130;
    buttons[9].h = 42;

    buttons[10].x = 1040 + camera.x;
    buttons[10].y = 258 + camera.y;
    buttons[10].w = 130;
    buttons[10].h = 42;

    buttons[11].x = 1033 + camera.x;
    buttons[11].y = 370 + camera.y;
    buttons[11].w = 20;
    buttons[11].h = 24;

    buttons[12].x = 1033 + camera.x;
    buttons[12].y = 402 + camera.y;
    buttons[12].w = 20;
    buttons[12].h = 24;

    buttons[13].x = 1061 + camera.x;
    buttons[13].y = 450 + camera.y;
    buttons[13].w = 100;
    buttons[13].h = 43;

    buttons[14].x = 1071 + camera.x;
    buttons[14].y = 575 + camera.y;
    buttons[14].w = 90;
    buttons[14].h = 41;

    buttons[15].x = 1015 + camera.x;
    buttons[15].y = 359 + camera.y;
    buttons[15].w = 44;
    buttons[15].h = 35;

    buttons[16].x = 1080 + camera.x;
    buttons[16].y = 359 + camera.y;
    buttons[16].w = 44;
    buttons[16].h = 35;

    buttons[17].x = 1145 + camera.x;
    buttons[17].y = 359 + camera.y;
    buttons[17].w = 44;
    buttons[17].h = 35;

    buttons[18].x = 1047 + camera.x;
    buttons[18].y = 400 + camera.y;
    buttons[18].w = 42;
    buttons[18].h = 20;

    buttons[19].x = 1100 + camera.x;
    buttons[19].y = 400 + camera.y;
    buttons[19].w = 42;
    buttons[19].h = 20;

}

void PlayerCreator :: set_palette(PlayerTile *palette[])
{

    palette[0] = new PlayerTile( 1011 + camera.x , 122 + camera.y, 0, 0, 40, 40, 0, 0 );
    palette[1] = new PlayerTile( 1056 + camera.x, 122 + camera.y, 127, 127, 40, 40, 127, 0 );
    palette[2] = new PlayerTile( 1101 + camera.x, 122 + camera.y, 136, 0, 40, 40, 21, 0 );
    palette[3] = new PlayerTile( 1146 + camera.x, 122 + camera.y, 237, 28, 40, 40, 36, 0 );
    palette[4] = new PlayerTile( 1011 + camera.x, 167 + camera.y, 255, 127, 40, 40, 39, 0 );
    palette[5] = new PlayerTile( 1056 + camera.x, 167 + camera.y, 255, 242, 40, 40, 0, 0 );
    palette[6] = new PlayerTile( 1101 + camera.x, 167 + camera.y, 34, 177, 40, 40, 76, 0 );
    palette[7] = new PlayerTile( 1146 + camera.x, 167 + camera.y, 0, 162, 40, 40, 232, 0 );
    palette[8] = new PlayerTile( 1011 + camera.x, 212 + camera.y, 63, 72, 40, 40, 204, 0 );
    palette[9] = new PlayerTile( 1056 + camera.x, 212 + camera.y, 163, 73, 40, 40, 164, 0 );
    palette[10] = new PlayerTile( 1101 + camera.x, 212 + camera.y, 255, 255, 40, 40, 255, 0 );
    palette[11] = new PlayerTile( 1146 + camera.x, 212 + camera.y, 195, 195, 40, 40, 195, 0 );
    palette[12] = new PlayerTile( 1011 + camera.x, 257 + camera.y, 185, 122, 40, 40, 87, 0 );
    palette[13] = new PlayerTile( 1056 + camera.x, 257 + camera.y, 255, 174, 40, 40, 201, 0 );
    palette[14] = new PlayerTile( 1101 + camera.x, 257 + camera.y, 255, 201, 40, 40, 14, 0 );
    palette[15] = new PlayerTile( 1146 + camera.x, 257 + camera.y, 239, 228, 40, 40, 176, 0 );
    palette[16] = new PlayerTile( 1011 + camera.x, 302 + camera.y, 181, 230, 40, 40, 29, 0 );
    palette[17] = new PlayerTile( 1056 + camera.x, 302 + camera.y, 153, 217, 40, 40, 234, 0 );
    palette[18] = new PlayerTile( 1101 + camera.x, 302 + camera.y, 112, 146, 40, 40, 190, 0 );
    palette[19] = new PlayerTile( 1146 + camera.x, 302 + camera.y, 200, 191, 40, 40, 231, 0 );
    palette[20] = new PlayerTile( 1017 + camera.x, 454 + camera.y, currentRed, currentGreen, 40, 40, currentBlue, 0 );

}

void PlayerCreator :: select_colour(PlayerTile *palette[])
{
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

     //   {
    for(int t = 0; t < 20; t++)
    {
        SDL_Rect box = palette[ t ]->get_box();
        if(( x >= box.x) && ( x < box.x + 40) && ( y >= box.y ) && ( y < box.y + 40))
        {
            currentRed = palette[t]->get_red();
            currentGreen = palette[t]->get_green();
            currentBlue = palette[t]->get_blue();
        }
    }
}


void PlayerCreator:: select_tile( PlayerTile *tiles[], PlayerTile *highlight[])
{
    //Mouse offsets
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

    //Go through tiles
    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
    {
        //Get tile's collision box
        SDL_Rect box = tiles[ t ]->get_box();

        if(tiles[ t ]->chosen == true)
        {
            if(tiles[ t ]->isUsed())
            {
                tiles[ t ]->show();
            }

            else
            {
                monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[10/10]);
            }

            tiles[ t ]->chosen = false;
            selected = false;
         //    tiles[t]->show();
        }
    }
    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
    {
        SDL_Rect box = tiles[ t ]->get_box();
        //If the mouse is inside the tile
        if( ( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom) && tiles[ t ]->chosen == false && selected == false)
        {
            tiles[ t ]->chosen = true;
            selected = true;
            red = tiles[ t ]->get_red();
            gre = tiles[ t ]->get_green();
            currentLength = tiles[ t ]->get_length();
            currentHeight = tiles[ t ]->get_height();
            blu = tiles[ t ]->get_blue();
            pixelUsed = tiles[ t ]->isUsed();
            highlight[ 0 ] = new PlayerTile( box.x, box.y, 0, 0, 80,  80, 0, 0 );
        }

    }
}

bool PlayerCreator:: put_tile( PlayerTile *tiles[], int red, int green, int length, int height, int blue, int isUsed)
{
    //Mouse offsets
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

    //Go through tiles
    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
    {
        //Get tile's collision box
        SDL_Rect box = tiles[ t ]->get_box();

        //If the mouse is inside the tile
        if( tiles[ t ]->is_chosen() )
        {
            //Get rid of old tile
            delete tiles[ t ];


            //Replace it with new one
            tiles[ t ] = new PlayerTile( box.x, box.y, red, green, zoom, zoom, blue, isUsed );
            tiles[ t ]->chosen = true;
            tiles[ t ]-> show();
        }
    }
    return true;
}

bool PlayerCreator:: set_tiles( PlayerTile *tiles[], std::ifstream &map )
{
    //The tile offsets
    int tile_num = 0;
    int x = 0, y = 0, temp1 = 0, temp2 = 0;

    selected = false;
    //If the map couldn't be loaded
    if( map == NULL )
    {
        //Initialize the tiles
        for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //Put a floor tile
            tiles[ t ] = new PlayerTile( x, y, t, 0, 0, 0, 0, 0 );

            //Move to next tile spot
            x += PTILE_WIDTH;

            //If we've gone too far
            if( x >= PTILE_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += PTILE_HEIGHT;
            }
        }
    }
    else
    {
        //Initialize the tiles
        for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //Determines what kind of tile will be made
            int redType = -1;
            int greenType = -1;
            int length = -1;
            int height = -1;
            int blueType = -1;
            int isUsed = -1;

            //Read tile from map file
            map >> redType;
            map >> greenType;
            map >> temp1;
            map >> temp2;
            map >> blueType;
            map >> isUsed;


            //If there was a problem in reading the map
            if( map.fail() == true )
            {
                //Stop loading map
                map.close();
                return false;
            }

            //If the number is a valid tile number

            tiles[ t ] = new PlayerTile( x + left_padding, y, redType, greenType, zoom, zoom, blueType, isUsed );
            //If we don't recognize the tile type


            //Move to next tile spot
            x += zoom;

            //If we've gone too far
            tile_num++;
            if( tile_num % 128 == 0 )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += zoom;
            }
        }

        //Close the file
        map.close();
    }

    return true;
}




void PlayerCreator:: save_tiles( PlayerTile *tiles[], std::ofstream &map )
{

    //Go through the tiles
    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
    {
        //Write tile type to file
        map << tiles[ t ]->get_red() << " ";
        map << tiles[ t ]->get_green() << " ";
        map << ((tiles[ t ]->get_x() - left_padding)*10)/zoom << " ";
        map << (tiles[ t ]->get_y()*10)/zoom << " ";
        map << tiles[ t ]->get_blue() << " ";
        map << tiles[ t ]->isUsed() << " ";
    }

    //Close the file
    map.close();
}


bool PlayerCreator:: zoomInAndOut(PlayerTile *tiles[])
{
  //  Create();
    camera.x = 0;
    camera.y = 0;
    clip();
    setup_buttons();

   // std::ifstream map("lazy.map");
   for( int t = 0; t < HEIGHT; t++ )
   {

        for( int v = 0; v < WIDTH; v++ )
        {
            tiles[ t + (v * WIDTH) ]->box.w = zoom;
            tiles[ t + (v * WIDTH) ]->box.h = zoom;
            tiles[ t + (v * WIDTH) ]->box.x = (t * zoom) + left_padding;
            tiles[ t + (v * WIDTH) ]->box.y = v * zoom;
        }

   }
    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
    {
        if(tiles[ t ]->isUsed())
            tiles[ t ]->show();
        if(!tiles[t]->isUsed())
        {
            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[10/10]);
        }
    }
       creatorInterface.render(0 ,0);
       creatorInterface2.render(1000, 0);

    selected = false;


}

void PlayerCreator:: FillAcc(PlayerTile *tiles[])
{
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;
    canFill = false;

    for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
    {
        SDL_Rect box = tiles[ i ]->get_box();
        if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
            if((tiles[i]->get_blue() != currentBlue || tiles[i]->get_red() != currentRed || tiles[i]->get_green() != currentGreen) && tiles[i]->isUsed() )
                Fill(tiles, i);
    }
    canFill = true;
}
void PlayerCreator:: Fill(PlayerTile *tiles[], int i)
{
    int tempRed = 0;
    int tempGreen = 0;
    int tempBlue = 0;

    tempRed = tiles[i]->get_red();
    tempGreen = tiles[i]->get_green();
    tempBlue = tiles[i]->get_blue();
    tiles[i] = new PlayerTile( tiles[i]->box.x, tiles[i]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
    tiles[i]->show();

    if(i + 1 <= TOTAL_PLAYER_TILES)
    {
        if(tiles[i + 1]->isUsed() && tempRed == tiles[i + 1]->get_red() && tempGreen == tiles[i + 1]->get_green() && tempBlue == tiles[i + 1]->get_blue())
        {
            Fill(tiles, (i + 1));
        }
    }

    if(i - 1 >= 0)
    {
        if(tiles[i - 1]->isUsed() && tempRed == tiles[i - 1]->get_red() && tempGreen == tiles[i - 1]->get_green() && tempBlue == tiles[i - 1]->get_blue())
        {
            Fill(tiles, (i - 1));
        }
    }

    if(i + WIDTH <= TOTAL_PLAYER_TILES)
    {
        if(tiles[i + WIDTH]->isUsed() && tempRed == tiles[i + WIDTH]->get_red() && tempGreen == tiles[i + WIDTH]->get_green() && tempBlue == tiles[i + WIDTH]->get_blue())
        {
            Fill(tiles, (i + WIDTH));
        }
    }

    if(i - WIDTH >= 0)
    {
        if(tiles[i - WIDTH]->isUsed() && tempRed == tiles[i - WIDTH]->get_red() && tempGreen == tiles[i - WIDTH]->get_green() && tempBlue == tiles[i - WIDTH]->get_blue())
        {
            Fill(tiles, (i - WIDTH));
        }
    }
}

int PlayerCreator:: Create()
{
    bool quit = false;

    clip();
    setup_buttons();
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderClear( gRenderer );
    std::ifstream map( "lazy.map" );

    //The tiles that will be used
    PlayerTile *tiles[ TOTAL_PLAYER_TILES ];

    PlayerTile *highlight[ 1 ];

    PlayerTile *palette[ 21 ];
    //The frame rate regulator
    Timer fps;

    //Set the tiles
    if( set_tiles( tiles, map ) == false )
    {
        return 1;
    }

 //   blackT.render(left_padding, 0, &zooming3[zoom/10]);


    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //SDL_SetRenderDrawColor( gRenderer, 68, 0xFF, 0xFF, 0xFF );
          //  SDL_RenderClear( gRenderer );
            if(tiles[ t ]->isUsed())
                tiles[ t ]->show();
            else
            {
               // black.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[1]);
                monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[10/10]);
            }
        }



    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            if(canSquare)
                square(tiles);
        }

        set_palette(palette);

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(canRubber)
                        rubber = true;
                    else if(canPaint)
                        paint = true;
                    else if(canGrab)
                        selectSquare(tiles, copyTiles);
                    else if(canPaste)
                        pasteSquare(tiles, copyTiles);
                    else if(canFill)
                        FillAcc(tiles);
                    else if(canSelect)
                        select_tile(tiles, highlight);

                    int temp = interface(tiles, copyTiles);
                    if( temp == 1)
                        return 0;
                    else if(temp == 2)
                    {
                        std::ofstream map2( "lazy.map" );
                        save_tiles( tiles, map2 );
                        return 1;
                    }

                    if(canChooseColour)
                        select_colour(palette);
                }
            }

            if(event.type == SDL_MOUSEBUTTONUP )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    rubber = false;
                    paint = false;
                    if(canSquare)
                    {
                        square(tiles);
                    }
                    if(canGrab)
                    {
                        selectSquare(tiles, copyTiles);
                    }

                    interface2(tiles, copyTiles);
                    zoom_width_clicked = false;
                }
            }


            if( event.type == SDL_QUIT )
            {
                //Quit the program
                std::ofstream map2( "lazy.map" );
                save_tiles( tiles, map2 );
                return 1;
            }

            if( event.type == SDL_KEYDOWN )
            {


            if( event.key.keysym.sym == SDLK_RIGHT && zoom >= 10)
                {
                    camera.x = camera.x + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                     }

                 }

                else if( event.key.keysym.sym == SDLK_LEFT && zoom >= 10)
                {
                    camera.x = camera.x - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_DOWN && zoom >= 10)
                {
                    camera.y = camera.y + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_UP && zoom >= 10)
                {
                    camera.y = camera.y - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                        }

                     }

                 }

            }

        }
//        clip();

        //Show the tiles
        if(selected)
        {
            highlight[ 0 ]->show2();
        }

        if(paint)
            draw(tiles);

        if(rubber)
            rub(tiles);

        if(copying)
            Sel(tiles);

        if(!canGrab || paste)
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                if(tiles[t]->isGrabbed)
                {
                    if(tiles[t]->isUsed())
                        tiles[t]->show();
                    else
                        monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                    tiles[t]->isGrabbed = false;
                }
            }
            paste = false;
        }

        creatorInterface.render(0 ,0);
        creatorInterface2.render(1000, 0);
        palette[20]->show4();

        gFont = TTF_OpenFont( "font2.ttf", 24 );
        pixels_remaining = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);
        std::stringstream ss1;
        ss1 << pixels_remaining;
        SDL_Color textColor2 = { 163, 163, 163 };
        pixelDisplay.loadFromRenderedText( ss1.str(), textColor2 );
        pixelDisplay.render(1054, 70);

        std::stringstream ss2;
        ss2 << zoom/10;
        pixelDisplay.loadFromRenderedText( ss2.str(), textColor2 );
        pixelDisplay.render(75, 455);

        std::stringstream ss3;
        ss3 << pointer_width + 1;
        pixelDisplay.loadFromRenderedText( ss3.str(), textColor2 );
        pixelDisplay.render(1074, 388);

        int temp = 0;
        for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
        {
            if(tiles[i]->isUsed() == 1)
            {
                temp++;
            }
        }
        man_pixels_used = temp;

        if(check_capacity())
            atCapacity = false;
        else
            atCapacity = true;


        if(canPaint)
        {
            Sel5.render(1038, 127);
        }

        else if(canRubber)
        {
            Sel5.render(1038, 190);
        }

        else if(canFill)
        {
            Sel5.render(1038, 258);
        }

        else if(canGrab)
        {
            Sel5.render(37, 33);
        }

        else if(canPaste)
        {
            Sel5.render(35, 168);
        }

        else if(canSquare)
        {
            Sel5.render(35, 240);
        }

        if(buttonsClicked() == 1)
        {
            button_click1.render(35, 97, &clicked_button[0]);
        }

        else if(buttonsClicked() == 2)
        {
            button_click1.render(35, 168, &clicked_button[1]);
        }

        else if(buttonsClicked() == 3)
        {
            button_click1.render(35, 240, &clicked_button[2]);
        }

        else if(buttonsClicked() == 4)
        {
            button_click1.render(35, 312, &clicked_button[3]);
        }

        else if(buttonsClicked() == 5)
        {
            button_click1.render(28, 439, &clicked_button[4]);
        }

        else if(buttonsClicked() == 6)
        {
            button_click1.render(28, 471, &clicked_button[5]);
        }

        else if(buttonsClicked() == 11)
        {
            button_click1.render(1027, 372, &clicked_button[4]);
        }

        else if(buttonsClicked() == 12)
        {
            button_click1.render(1027, 404, &clicked_button[5]);
        }

        if(canChooseColour)
        {
            paletteDisplay.render(1000, 120);

            for(int i = 0; i < 20; i++)
            {
                palette[i]->show4();
            }

            if(buttonsClicked() == 18)
            {
                button_click1.render(1045, 398, &clicked_button[6]);
            }

            else if(buttonsClicked() == 19)
            {
                button_click1.render(1103, 398, &clicked_button[7]);
            }

            gFont = TTF_OpenFont( "font2.ttf", 18 );
            std::stringstream ss4;
            ss4 << currentRed;
            pixelDisplay.loadFromRenderedText( ss4.str(), textColor2 );
            pixelDisplay.render(1020, 370);

            std::stringstream ss5;
            ss5 << currentGreen;
            pixelDisplay.loadFromRenderedText( ss5.str(), textColor2 );
            pixelDisplay.render(1085, 370);

            std::stringstream ss6;
            ss6 << currentBlue;
            pixelDisplay.loadFromRenderedText( ss6.str(), textColor2 );
            pixelDisplay.render(1150, 370);

        }

        if(red_chosen)
        {
            Sel6.render(1015, 359);
        }

        if(green_chosen)
        {
            Sel6.render(1080, 359);
        }

        if(blue_chosen)
        {
            Sel6.render(1145, 359);
        }


        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    std::ofstream map2( "lazy.map" );
    save_tiles( tiles, map2 );


    return 0;
}

int PlayerCreator:: buttonsClicked()
{
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;


    SDL_PumpEvents();
    if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
    {
        for(int i = 0; i < 20; i++)
        {
            SDL_Rect box = buttons[ i ];
            if(( x >= box.x) && ( x < box.x + box.w) && ( y >= box.y ) && ( y < box.y + box.h))
            {
                if(canChooseColour)
                {
                    if(i == 18)
                        return 18;
                    else if(i == 19)
                        return 19;
                }

                if(i == 1)
                    return 1;
                else if (i == 2)
                    return 2;
                else if(i == 3)
                    return 3;
                else if(i == 4)
                    return 4;
                else if(i == 5)
                    return 5;
                else if(i == 6)
                    return 6;
                else if(i == 11)
                    return 11;
                else if(i == 12)
                    return 12;
            }
        }
    }
    return 0;

}

bool PlayerCreator:: check_capacity()
{
    total_pixels_used = man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels;
    if(total_pixels_used < pixel_capacity)
    {
        return true;
    }
    else
        return false;
}

void PlayerCreator:: draw(PlayerTile *tiles[])
{

    int x = 0, y = 0;

    int new_pixel_count = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;


        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                SDL_Rect box = tiles[ t ]->get_box();
                if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
                {
                    if(tiles[ t ]->isUsed() || new_pixel_count < pixels_remaining)
                    {
                        if(!tiles[ t ]->isUsed())
                        {
                            new_pixel_count++;
                        }
                        tiles[ t ] = new PlayerTile( box.x, box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                        tiles[ t ]->show();
                    }

                    if(pointer_width == 1)
                    {
                        int p = t  + pointer_width;
                        if( p < TOTAL_PLAYER_TILES)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  - pointer_width;
                        if(p >= 0)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  + (WIDTH * pointer_width) - pointer_width;
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  + (WIDTH * pointer_width);
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  + (WIDTH * pointer_width) + pointer_width;
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  - (WIDTH * pointer_width) - pointer_width;
                        if(p >= 0)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  - (WIDTH * pointer_width);
                        if(p >= 0)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }

                        p = t  - (WIDTH * pointer_width) + pointer_width;
                        if(p >= 0)
                        {
                            if(tiles[ p ]->isUsed() || new_pixel_count < pixels_remaining)
                            {
                                if(!tiles[ p ]->isUsed())
                                {
                                    new_pixel_count++;
                                }
                                tiles[ p ] = new PlayerTile( tiles[ p ]->box.x, tiles[ p ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                                tiles[ p ]->show();
                            }
                        }


                    }
                }
            }
        }
}


void PlayerCreator:: rub(PlayerTile *tiles[])
{

    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;


        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                SDL_Rect box = tiles[ t ]->get_box();
                if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
                {
                    tiles[ t ] = new PlayerTile( box.x, box.y, tiles[ t ]->get_red() , tiles[ t ]->get_green(), zoom, zoom, tiles[ t ]->get_blue(), 0 );
                    monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[10/10]);

                    if(pointer_width == 1)
                    {
                        int p = t + pointer_width;
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            tiles[ p ] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[ p ]->get_red() , tiles[ p ]->get_green(), zoom, zoom, tiles[p]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = t  - pointer_width;
                        if(p >= 0)
                        {
                            tiles[p] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[p ]->get_green(), zoom, zoom, tiles[ p]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = (t  - pointer_width)+ (WIDTH * pointer_width);
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            tiles[p] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[p]->get_green(), zoom, zoom, tiles[p]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = t  + (WIDTH * pointer_width);
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            tiles[ p ] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[p]->get_green(), zoom, zoom, tiles[p]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = (t  + pointer_width)+ (WIDTH * pointer_width);
                        if(p < TOTAL_PLAYER_TILES)
                        {
                            tiles[p] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[p]->get_green(), zoom, zoom, tiles[p]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = t  - (WIDTH * pointer_width);
                        if(p >= 0)
                        {
                            tiles[ p ] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[ p ]->get_green(), zoom, zoom, tiles[ p ]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = (t  + pointer_width)- (WIDTH * pointer_width);
                        if(p >= 0)
                        {
                            tiles[ p ] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[ p ]->get_green(), zoom, zoom, tiles[ p ]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                        p = (t  - pointer_width)- (WIDTH * pointer_width);
                        if(p >= 0)
                        {
                            tiles[ p ] = new PlayerTile( tiles[p]->box.x, tiles[p]->box.y, tiles[p]->get_red() , tiles[ p ]->get_green(), zoom, zoom, tiles[ p ]->get_blue(), 0 );
                            monitorT2.render(tiles[p]->get_box().x - camera.x, tiles[p]->get_box().y - camera.y, &zooming[10/10]);
                        }

                    }
                }
            }
        }
}

void PlayerCreator:: selectSquare(PlayerTile *tiles[], PlayerTile *copyTiles[])
{
    int x = 0, y = 0;
    count = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;


        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                SDL_Rect box = tiles[ t ]->get_box();
                if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
                {
                    startSquare = t;
                    copying = true;
                }
            }
        }
        else
        {
            copying = false;
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                SDL_Rect box = tiles[ t ]->get_box();
                if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
                {
                    int a = t % WIDTH;
                    int b = startSquare % WIDTH;
                    int c = a - b;                  //x difference

                    selectXLength = c;

                    double aTemp = t/WIDTH;
                    int a1 = ceil(aTemp);
                    double bTemp = startSquare/WIDTH;
                    int b1 = ceil(bTemp);
                    int c1 = a1 - b1;               //y difference
                    selectYLength = c1;   //do stuff here


                }
            }
        }
}

void PlayerCreator :: copySelect(PlayerTile *tiles[], PlayerTile *copyTiles[])
{

        copyXLength = selectXLength;
        copyYLength = selectYLength;
        if(copyYLength >= 0)
        {
            for(int i = 0; i <= copyYLength; i++)
            {
                if(copyXLength >= 0)
                {
                    for(int j = 0; j <= copyXLength ; j++)
                    {
                        copyTiles[count] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), tiles[ (startSquare + j) + (i * WIDTH) ]->isUsed());
                        count++;
                    }
                }
                else
                {

                    for(int j = copyXLength ; j <= 0; j++)
                    {
                        copyTiles[count] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), tiles[ (startSquare + j) + (i * WIDTH) ]->isUsed() );
                        count++;
                    }


                }

            }
        }

        else
        {

            for(int i = copyYLength; i <= 0; i++)
            {
                if(copyXLength >= 0)
                {
                    for(int j = 0; j <= copyXLength;  j++)
                    {
                        copyTiles[count] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y,tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), tiles[ (startSquare + j) + (i * WIDTH) ]->isUsed() );
                        count++;
                    }
                }
                else
                {

                    for(int j = copyXLength ; j <= 0; j++)
                    {
                        copyTiles[count] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), tiles[ (startSquare + j) + (i * WIDTH) ]->isUsed() );
                        count++;
                    }
                }

            }

        }

        copyBufferFull = true;
}

void PlayerCreator:: pasteSquare(PlayerTile *tiles[], PlayerTile *copyTiles[])
{
    int x = 0, y = 0;
    int new_pixel_count = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;
    int p = 0;

    if(copyXLength < 0)
        copyXLength = copyXLength * (-1);
    if(copyYLength < 0)
        copyYLength = copyYLength * (-1);

    int t = startSquare;
    for(int i = 0; i <= copyYLength; i++)
    {
        for(int j = 0; j <= copyXLength; j++)
        {
            if(t + j + (i * WIDTH) < TOTAL_PLAYER_TILES)
            {
                if((tiles[t + j + (i * WIDTH)]->isUsed() || !copyTiles[p]->isUsed()) || (new_pixel_count < pixels_remaining))
                {
                    if(!tiles[t + j + (i * WIDTH)]->isUsed() && copyTiles[p]->isUsed())
                    {
                        new_pixel_count++;
                    }
                    else if(tiles[t + j + (i * WIDTH)]->isUsed() && !copyTiles[p]->isUsed())
                    {
                        new_pixel_count--;
                    }

                    tiles[t + j + (i * WIDTH)] = new PlayerTile(tiles[t + j + (i * WIDTH)]->box.x, tiles[t + j + (i * WIDTH)]->box.y, copyTiles[p]->get_red(), copyTiles[p]->get_green(), zoom, zoom, copyTiles[p]->get_blue(), copyTiles[p]->isUsed());
                    if(tiles[t + j + (i * WIDTH)]->isUsed())
                        tiles[t + j + (i * WIDTH)]->show();
                    else
                    {
                        monitorT2.render(tiles[t + j + (i * WIDTH)]->get_box().x - camera.x, tiles[t + j + (i * WIDTH)]->get_box().y - camera.y, &zooming[10/10]);
                    }
                }
            }
            p++;

        }
    }

}


void PlayerCreator:: square(PlayerTile *tiles[])
{
    int new_pixel_count = 0;
    if(selectYLength >= 0)
    {
        for(int i = 0; i <= selectYLength; i++)
        {
            if(selectXLength >= 0)
            {
                for(int j = 0; j <= selectXLength; j++)
                {
                    if(tiles[(startSquare + j) + (i * WIDTH)]->isUsed() || (new_pixel_count < pixels_remaining))
                    {
                        if(!tiles[(startSquare + j) + (i * WIDTH)]->isUsed())
                            new_pixel_count++;
                        tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                        tiles[(startSquare + j) + (i * WIDTH)]->show();
                    }
                }
            }
            else
            {
                for(int j = selectXLength; j <= 0; j++)
                {
                    if(tiles[(startSquare + j) + (i * WIDTH)]->isUsed() || new_pixel_count < pixels_remaining)
                    {
                        if(!tiles[(startSquare + j) + (i * WIDTH)]->isUsed())
                            new_pixel_count++;
                        tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                        tiles[(startSquare + j) + (i * WIDTH)]->show();
                    }
                }
            }

        }
    }

    else
    {
        for(int i = selectYLength; i <= 0; i++)
        {
            if(selectXLength >= 0)
            {
                for(int j = 0; j <= selectXLength; j++)
                {
                    if(tiles[(startSquare + j) + (i * WIDTH)]->isUsed() || new_pixel_count < pixels_remaining)
                    {
                        if(!tiles[(startSquare + j) + (i * WIDTH)]->isUsed())
                            new_pixel_count++;
                        tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                        tiles[(startSquare + j) + (i * WIDTH)]->show();
                    }
                }
            }
            else
            {
                for(int j = selectXLength; j <= 0; j++)
                {
                    if(tiles[(startSquare + j) + (i * WIDTH)]->isUsed() || new_pixel_count < pixels_remaining)
                    {
                        if(!tiles[(startSquare + j) + (i * WIDTH)]->isUsed())
                            new_pixel_count++;
                        tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, currentRed, currentGreen, zoom, zoom, currentBlue, 1 );
                        tiles[(startSquare + j) + (i * WIDTH)]->show();
                    }
                }
            }

        }
    }

}

void PlayerCreator:: deleteSquare(PlayerTile *tiles[])
{
    if(selectYLength >= 0)
    {
        for(int i = 0; i <= selectYLength; i++)
        {
            if(selectXLength >= 0)
            {
                for(int j = 0; j <= selectXLength; j++)
                {
                    tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), 0 );
                    monitorT2.render(tiles[(startSquare + j) + (i * WIDTH)]->get_box().x - camera.x, tiles[(startSquare + j) + (i * WIDTH)]->get_box().y - camera.y, &zooming[10/10]);
                }
            }
            else
            {
                for(int j = selectXLength; j <= 0; j++)
                {
                    tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), 0 );
                    monitorT2.render(tiles[(startSquare + j) + (i * WIDTH)]->get_box().x - camera.x, tiles[(startSquare + j) + (i * WIDTH)]->get_box().y - camera.y, &zooming[10/10]);
                }
            }

        }
    }

    else
    {
        for(int i = selectYLength; i <= 0; i++)
        {
            if(selectXLength >= 0)
            {
                for(int j = 0; j <= selectXLength; j++)
                {
                    tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), 0 );
                    monitorT2.render(tiles[(startSquare + j) + (i * WIDTH)]->get_box().x - camera.x, tiles[(startSquare + j) + (i * WIDTH)]->get_box().y - camera.y, &zooming[10/10]);
                }
            }
            else
            {
                for(int j = selectXLength; j <= 0; j++)
                {
                    tiles[(startSquare + j) + (i * WIDTH)] = new PlayerTile( tiles[(startSquare + j) + (i * WIDTH) ]->box.x, tiles[ (startSquare + j) + (i * WIDTH) ]->box.y, tiles[ (startSquare + j) + (i * WIDTH) ]->get_red(), tiles[ (startSquare + j) + (i * WIDTH) ]->get_green(), zoom, zoom, tiles[ (startSquare + j) + (i * WIDTH) ]->get_blue(), 0 );
                    monitorT2.render(tiles[(startSquare + j) + (i * WIDTH)]->get_box().x - camera.x, tiles[(startSquare + j) + (i * WIDTH)]->get_box().y - camera.y, &zooming[10 /10]);
                }
            }

        }
    }

}


void PlayerCreator:: Sel(PlayerTile *tiles[])
{

    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
    {
        if(tiles[t]->isGrabbed)
        {
            tiles[t]->isGrabbed = false;
            if(tiles[t]->isUsed())
                tiles[t]->show();
            else
            {
                    monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[100/10]);
            }
        }
    }

    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
    {

        SDL_Rect box = tiles[ t ]->get_box();
        if(( x >= box.x) && ( x < box.x + zoom) && ( y >= box.y ) && ( y < box.y + zoom))
        {
            int a = t % WIDTH;
            int b = startSquare % WIDTH;
            int c = a - b;                  //x difference

            double aTemp = t/WIDTH;
            int a1 = ceil(aTemp);
            double bTemp = startSquare/WIDTH;
            int b1 = ceil(bTemp);

            int c1 = a1 - b1;               //y difference

            if(c1 >= 0)
            {
                for(int i = 0; i <= c1; i++)
                {
                    if(c >= 0)
                    {
                        for(int j = 0; j <= c; j++)
                        {
                            if(j == 0 || i == 0 || j == c || i == c1)
                            {
                                tiles[(startSquare + j) + (i * WIDTH)]->show3();
                                tiles[(startSquare + j) + (i * WIDTH)]->isGrabbed = true;
                            }
                        }
                    }
                    else
                    {
                        for(int j = c; j <= 0; j++)
                        {
                            if(j == 0 || i == 0 || j == c || i == c1)
                            {
                                tiles[(startSquare + j) + (i * WIDTH)]->show3();
                                tiles[(startSquare + j) + (i * WIDTH)]->isGrabbed = true;
                            }
                        }
                    }

                }
            }

            else
            {
                for(int i = c1; i <= 0; i++)
                {
                    if(c >= 0)
                    {
                        for(int j = 0; j <= c; j++)
                        {
                            if(j == 0 || i == 0 || j == c || i == c1)
                            {
                                tiles[(startSquare + j) + (i * WIDTH)]->show3();
                                tiles[(startSquare + j) + (i * WIDTH)]->isGrabbed = true;
                            }
                        }
                    }
                    else
                    {
                        for(int j = c; j <= 0; j++)
                        {
                            if(j == 0 || i == 0 || j == c || i == c1)
                            {
                                tiles[(startSquare + j) + (i * WIDTH)]->show3();
                                tiles[(startSquare + j) + (i * WIDTH)]->isGrabbed = true;
                            }
                        }
                    }

                }
            }
        }
    }

}

int PlayerCreator:: Create2()
{
    bool quit = false;

    clip();
    setup_buttons();
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderClear( gRenderer );
    std::ifstream map( "lazyA.map" );

    //The tiles that will be used
    PlayerTile *tiles[ TOTAL_PLAYER_TILES ];

    PlayerTile *highlight[ 1 ];

    PlayerTile *palette[ 21 ];
    //The frame rate regulator
    Timer fps;

    //Set the tiles
    if( set_tiles( tiles, map ) == false )
    {
        return 1;
    }

 //   blackT.render(left_padding, 0, &zooming3[zoom/10]);


    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //SDL_SetRenderDrawColor( gRenderer, 68, 0xFF, 0xFF, 0xFF );
          //  SDL_RenderClear( gRenderer );
            if(tiles[ t ]->isUsed())
                tiles[ t ]->show();
            else
            {
               // black.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[1]);
                monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
            }
        }



    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            if(canSquare)
                square(tiles);
        }

        set_palette(palette);

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(canRubber)
                        rubber = true;
                    else if(canPaint)
                        paint = true;
                    else if(canGrab)
                        selectSquare(tiles, copyTiles);
                    else if(canPaste)
                        pasteSquare(tiles, copyTiles);
                    else if(canFill)
                        FillAcc(tiles);
                    else if(canSelect)
                        select_tile(tiles, highlight);

                    int temp = interface(tiles, copyTiles);
                    if( temp == 1)
                        return 0;
                    else if(temp == 2)
                    {
                        std::ofstream map2( "lazyA.map" );
                        save_tiles( tiles, map2 );
                        return 1;
                    }

                    if(canChooseColour)
                        select_colour(palette);
                }
            }

            if(event.type == SDL_MOUSEBUTTONUP )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    rubber = false;
                    paint = false;
                    if(canSquare)
                    {
                        square(tiles);
                    }
                    if(canGrab)
                    {
                        selectSquare(tiles, copyTiles);
                    }

                    interface2(tiles, copyTiles);
                    zoom_width_clicked = false;
                }
            }


            if( event.type == SDL_QUIT )
            {
                //Quit the program
                std::ofstream map2( "lazyA.map" );
                save_tiles( tiles, map2 );
                return 1;
            }

            if( event.type == SDL_KEYDOWN )
            {


            if( event.key.keysym.sym == SDLK_RIGHT && zoom > 10)
                {
                    camera.x = camera.x + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                     }

                 }

                else if( event.key.keysym.sym == SDLK_LEFT && zoom > 10)
                {
                    camera.x = camera.x - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_DOWN && zoom > 10)
                {
                    camera.y = camera.y + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_UP && zoom > 10)
                {
                    camera.y = camera.y - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                        }

                     }

                 }

            }

        }
//        clip();

        //Show the tiles
        if(selected)
        {
            highlight[ 0 ]->show2();
        }

        if(paint && !atCapacity)
            draw(tiles);

        if(rubber)
            rub(tiles);

        if(copying)
            Sel(tiles);

        if(!canGrab || paste)
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                if(tiles[t]->isGrabbed)
                {
                    if(tiles[t]->isUsed())
                        tiles[t]->show();
                    else
                        monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                    tiles[t]->isGrabbed = false;
                }
            }
            paste = false;
        }

        creatorInterface.render(0 ,0);
        creatorInterface2.render(1000, 0);
        palette[20]->show4();

        gFont = TTF_OpenFont( "font2.ttf", 24 );
        pixels_remaining = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);
        std::stringstream ss1;
        ss1 << pixels_remaining;
        SDL_Color textColor2 = { 163, 163, 163 };
        pixelDisplay.loadFromRenderedText( ss1.str(), textColor2 );
        pixelDisplay.render(1054, 70);

        std::stringstream ss2;
        ss2 << zoom/10;
        pixelDisplay.loadFromRenderedText( ss2.str(), textColor2 );
        pixelDisplay.render(75, 455);

        std::stringstream ss3;
        ss3 << pointer_width + 1;
        pixelDisplay.loadFromRenderedText( ss3.str(), textColor2 );
        pixelDisplay.render(1074, 388);

        if(check_capacity())
            atCapacity = false;
        else
            atCapacity = true;


        if(canPaint)
        {
            Sel5.render(1038, 127);
        }

        else if(canRubber)
        {
            Sel5.render(1038, 190);
        }

        else if(canFill)
        {
            Sel5.render(1038, 258);
        }

        else if(canGrab)
        {
            Sel5.render(37, 33);
        }

        else if(canPaste)
        {
            Sel5.render(35, 168);
        }

        else if(canSquare)
        {
            Sel5.render(35, 240);
        }

        if(buttonsClicked() == 1)
        {
            button_click1.render(35, 97, &clicked_button[0]);
        }

        else if(buttonsClicked() == 2)
        {
            button_click1.render(35, 168, &clicked_button[1]);
        }

        else if(buttonsClicked() == 3)
        {
            button_click1.render(35, 240, &clicked_button[2]);
        }

        else if(buttonsClicked() == 4)
        {
            button_click1.render(35, 312, &clicked_button[3]);
        }

        else if(buttonsClicked() == 5)
        {
            button_click1.render(28, 439, &clicked_button[4]);
        }

        else if(buttonsClicked() == 6)
        {
            button_click1.render(28, 471, &clicked_button[5]);
        }

        else if(buttonsClicked() == 11)
        {
            button_click1.render(1027, 372, &clicked_button[4]);
        }

        else if(buttonsClicked() == 12)
        {
            button_click1.render(1027, 404, &clicked_button[5]);
        }

        if(canChooseColour)
        {
            paletteDisplay.render(1000, 120);

            for(int i = 0; i < 20; i++)
            {
                palette[i]->show4();
            }

            if(buttonsClicked() == 18)
            {
                button_click1.render(1045, 398, &clicked_button[6]);
            }

            else if(buttonsClicked() == 19)
            {
                button_click1.render(1103, 398, &clicked_button[7]);
            }

            gFont = TTF_OpenFont( "font2.ttf", 18 );
            std::stringstream ss4;
            ss4 << currentRed;
            pixelDisplay.loadFromRenderedText( ss4.str(), textColor2 );
            pixelDisplay.render(1020, 370);

            std::stringstream ss5;
            ss5 << currentGreen;
            pixelDisplay.loadFromRenderedText( ss5.str(), textColor2 );
            pixelDisplay.render(1085, 370);

            std::stringstream ss6;
            ss6 << currentBlue;
            pixelDisplay.loadFromRenderedText( ss6.str(), textColor2 );
            pixelDisplay.render(1150, 370);

        }

        if(red_chosen)
        {
            Sel6.render(1015, 359);
        }

        if(green_chosen)
        {
            Sel6.render(1080, 359);
        }

        if(blue_chosen)
        {
            Sel6.render(1145, 359);
        }


        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    std::ofstream map2( "lazyA.map" );
    save_tiles( tiles, map2 );


    return 0;
}

int PlayerCreator:: interface(PlayerTile *tiles[], PlayerTile *copyTiles[])
{
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

     //   {
            for(int t = 0; t < 20; t++)
            {
                SDL_Rect box = buttons[ t ];
                if(( x >= box.x) && ( x < box.x + box.w) && ( y >= box.y ) && ( y < box.y + box.h))
                {

                    if( t == 7)
                    {
                        return 1;
                    }

                    else if( t == 14)
                    {
                        return 2;
                    }

                    else if( t == 8 && !canChooseColour)
                    {
                        canPaint = true;
                        canRubber = false;
                        canFill = false;
                        canSelect = false;
                        selected = false;
                        canSquare = false;
                        canGrab = false;
                        canPaste = false;
                    }

                    else if( t == 13)
                    {
                        if(!canChooseColour)
                        {
                            canChooseColour = true;
                        }
                        else if(canChooseColour)
                        {
                            canChooseColour = false;
                            red_chosen = false;
                            green_chosen = false;
                            blue_chosen = false;
                        }
                    }

                    else if( t == 9 && !canChooseColour)
                    {
                        canRubber = true;
                        canPaint = false;
                        canFill = false;
                        canSelect = false;
                        selected = false;
                        canSquare = false;
                        canGrab = false;
                        canPaste = false;
                    }

                    else if( t == 10 && !canChooseColour)
                    {
                        canFill = true;
                        canPaint = false;
                        canRubber = false;
                        canSelect = false;
                        selected = false;
                        canSquare = false;
                        canGrab = false;
                        canPaste = false;
                    }

                    else if( t == 11 && !canChooseColour)
                    {
                        zoom_width_clicked = true;
                    }

                    else if( t == 12 && !canChooseColour)
                    {
                        zoom_width_clicked = true;
                    }

                    else if( t == 0)
                    {
                        canGrab = true;
                        canPaint = false;
                        canRubber = false;
                        canFill = false;
                        selected = false;
                        canSquare = false;
                        canSelect = false;
                        canPaste = false;
                    }

                    if(t == 5 && zoom < 40)
                    {
                        zoom_width_clicked = true;
                    }

                    if(t == 6 && zoom > 5)
                    {
                        zoom_width_clicked = true;
                    }


                    else if( t == 3 && canGrab )
                    {
                        square(tiles);
                    }

                    else if( t == 1 && canGrab)
                    {
                        copySelect(tiles, copyTiles);
                    }

                    else if( t == 2 && copyBufferFull)
                    {
                        pasteSquare(tiles, copyTiles);
                        paste = true;
                    }

                    else if( t == 4 && canGrab)
                    {
                        deleteSquare(tiles);
                    }

                    else if(t == 15 && canChooseColour)
                    {
                        red_chosen = true;
                        green_chosen = false;
                        blue_chosen = false;
                    }

                    else if(t == 16 && canChooseColour)
                    {
                        red_chosen = false;
                        green_chosen = true;
                        blue_chosen = false;
                    }


                    else if(t == 17 && canChooseColour)
                    {
                        red_chosen = false;
                        green_chosen = false;
                        blue_chosen = true;
                    }

                    else if(t == 18 && canChooseColour)
                    {
                        if(red_chosen && currentRed > 0)
                            currentRed--;
                        else if(green_chosen && currentGreen > 0)
                            currentGreen--;
                        else if(blue_chosen && currentBlue > 0)
                            currentBlue--;
                    }


                    else if(t == 19 && canChooseColour)
                    {
                        if(red_chosen && currentRed < 255)
                            currentRed++;
                        else if(green_chosen && currentGreen < 255)
                            currentGreen++;
                        else if(blue_chosen && currentBlue < 255)
                            currentBlue++;
                    }

                }
            }
     return 0;
}

void PlayerCreator:: interface2(PlayerTile *tiles[], PlayerTile *copyTiles[])
{
    int x = 0, y = 0;

    //Get mouse offsets
    SDL_GetMouseState( &x, &y );

    //Adjust to camera
    x += camera.x;
    y += camera.y;

     //   {
        for(int t = 0; t < 15; t++)
        {
            SDL_Rect box = buttons[ t ];
            if(( x >= box.x) && ( x < box.x + box.w) && ( y >= box.y ) && ( y < box.y + box.h))
            {
                if(t == 5 && zoom_width_clicked)
                {
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
                    SDL_RenderClear( gRenderer );
                    zoom =  zoom * 2;
                    if(zoom == 10)
                        left_padding = 280;
                    zoomInAndOut(tiles);
                }

                if(t == 6 && zoom_width_clicked)
                {
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
                    SDL_RenderClear( gRenderer );
                    zoom =  zoom / 2;
                    if(zoom == 10)
                        left_padding = 280;
                    zoomInAndOut(tiles);
                }

                if(t == 11 && zoom_width_clicked && pointer_width == 0)
                {
                    pointer_width++;
                }

                if(t == 12 && zoom_width_clicked && pointer_width == 1)
                {
                    pointer_width--;
                }


            }
        }
 }


int PlayerCreator:: Create3()
{
    bool quit = false;

    clip();
    setup_buttons();
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderClear( gRenderer );
    std::ifstream map( "lazyB.map" );

    //The tiles that will be used
    PlayerTile *tiles[ TOTAL_PLAYER_TILES ];

    PlayerTile *highlight[ 1 ];

    PlayerTile *palette[ 21 ];
    //The frame rate regulator
    Timer fps;

    //Set the tiles
    if( set_tiles( tiles, map ) == false )
    {
        return 1;
    }

 //   blackT.render(left_padding, 0, &zooming3[zoom/10]);


    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //SDL_SetRenderDrawColor( gRenderer, 68, 0xFF, 0xFF, 0xFF );
          //  SDL_RenderClear( gRenderer );
            if(tiles[ t ]->isUsed())
                tiles[ t ]->show();
            else
            {
               // black.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[1]);
                monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
            }
        }



    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            if(canSquare)
                square(tiles);
        }

        set_palette(palette);

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(canRubber)
                        rubber = true;
                    else if(canPaint)
                        paint = true;
                    else if(canGrab)
                        selectSquare(tiles, copyTiles);
                    else if(canPaste)
                        pasteSquare(tiles, copyTiles);
                    else if(canFill)
                        FillAcc(tiles);
                    else if(canSelect)
                        select_tile(tiles, highlight);

                    int temp = interface(tiles, copyTiles);
                    if( temp == 1)
                        return 0;
                    else if(temp == 2)
                    {
                        std::ofstream map2( "lazyB.map" );
                        save_tiles( tiles, map2 );
                        return 1;
                    }

                    if(canChooseColour)
                        select_colour(palette);
                }
            }

            if(event.type == SDL_MOUSEBUTTONUP )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    rubber = false;
                    paint = false;
                    if(canSquare)
                    {
                        square(tiles);
                    }
                    if(canGrab)
                    {
                        selectSquare(tiles, copyTiles);
                    }

                    interface2(tiles, copyTiles);
                    zoom_width_clicked = false;
                }
            }


            if( event.type == SDL_QUIT )
            {
                //Quit the program
                std::ofstream map2( "lazyB.map" );
                save_tiles( tiles, map2 );
                return 1;
            }

            if( event.type == SDL_KEYDOWN )
            {


            if( event.key.keysym.sym == SDLK_RIGHT && zoom > 10)
                {
                    camera.x = camera.x + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                     }

                 }

                else if( event.key.keysym.sym == SDLK_LEFT && zoom > 10)
                {
                    camera.x = camera.x - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_DOWN && zoom > 10)
                {
                    camera.y = camera.y + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_UP && zoom > 10)
                {
                    camera.y = camera.y - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                        }

                     }

                 }

            }

        }
//        clip();

        //Show the tiles
        if(selected)
        {
            highlight[ 0 ]->show2();
        }

        if(paint && !atCapacity)
            draw(tiles);

        if(rubber)
            rub(tiles);

        if(copying)
            Sel(tiles);

        if(!canGrab || paste)
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                if(tiles[t]->isGrabbed)
                {
                    if(tiles[t]->isUsed())
                        tiles[t]->show();
                    else
                        monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                    tiles[t]->isGrabbed = false;
                }
            }
            paste = false;
        }

        creatorInterface.render(0 ,0);
        creatorInterface2.render(1000, 0);
        palette[20]->show4();

        gFont = TTF_OpenFont( "font2.ttf", 24 );
        pixels_remaining = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);
        std::stringstream ss1;
        ss1 << pixels_remaining;
        SDL_Color textColor2 = { 163, 163, 163 };
        pixelDisplay.loadFromRenderedText( ss1.str(), textColor2 );
        pixelDisplay.render(1054, 70);

        std::stringstream ss2;
        ss2 << zoom/10;
        pixelDisplay.loadFromRenderedText( ss2.str(), textColor2 );
        pixelDisplay.render(75, 455);

        std::stringstream ss3;
        ss3 << pointer_width + 1;
        pixelDisplay.loadFromRenderedText( ss3.str(), textColor2 );
        pixelDisplay.render(1074, 388);

        int temp = 0;
        for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
        {
            if(tiles[i]->isUsed() == 1)
            {
                temp++;
            }
        }
        sword_pixels_used = temp;

        if(check_capacity())
            atCapacity = false;
        else
            atCapacity = true;


        if(canPaint)
        {
            Sel5.render(1038, 127);
        }

        else if(canRubber)
        {
            Sel5.render(1038, 190);
        }

        else if(canFill)
        {
            Sel5.render(1038, 258);
        }

        else if(canGrab)
        {
            Sel5.render(37, 33);
        }

        else if(canPaste)
        {
            Sel5.render(35, 168);
        }

        else if(canSquare)
        {
            Sel5.render(35, 240);
        }

        if(buttonsClicked() == 1)
        {
            button_click1.render(35, 97, &clicked_button[0]);
        }

        else if(buttonsClicked() == 2)
        {
            button_click1.render(35, 168, &clicked_button[1]);
        }

        else if(buttonsClicked() == 3)
        {
            button_click1.render(35, 240, &clicked_button[2]);
        }

        else if(buttonsClicked() == 4)
        {
            button_click1.render(35, 312, &clicked_button[3]);
        }

        else if(buttonsClicked() == 5)
        {
            button_click1.render(28, 439, &clicked_button[4]);
        }

        else if(buttonsClicked() == 6)
        {
            button_click1.render(28, 471, &clicked_button[5]);
        }

        else if(buttonsClicked() == 11)
        {
            button_click1.render(1027, 372, &clicked_button[4]);
        }

        else if(buttonsClicked() == 12)
        {
            button_click1.render(1027, 404, &clicked_button[5]);
        }

        if(canChooseColour)
        {
            paletteDisplay.render(1000, 120);

            for(int i = 0; i < 20; i++)
            {
                palette[i]->show4();
            }

            if(buttonsClicked() == 18)
            {
                button_click1.render(1045, 398, &clicked_button[6]);
            }

            else if(buttonsClicked() == 19)
            {
                button_click1.render(1103, 398, &clicked_button[7]);
            }

            gFont = TTF_OpenFont( "font2.ttf", 18 );
            std::stringstream ss4;
            ss4 << currentRed;
            pixelDisplay.loadFromRenderedText( ss4.str(), textColor2 );
            pixelDisplay.render(1020, 370);

            std::stringstream ss5;
            ss5 << currentGreen;
            pixelDisplay.loadFromRenderedText( ss5.str(), textColor2 );
            pixelDisplay.render(1085, 370);

            std::stringstream ss6;
            ss6 << currentBlue;
            pixelDisplay.loadFromRenderedText( ss6.str(), textColor2 );
            pixelDisplay.render(1150, 370);

        }

        if(red_chosen)
        {
            Sel6.render(1015, 359);
        }

        if(green_chosen)
        {
            Sel6.render(1080, 359);
        }

        if(blue_chosen)
        {
            Sel6.render(1145, 359);
        }


        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    std::ofstream map2( "lazyB.map" );
    save_tiles( tiles, map2 );


    return 0;
}


int PlayerCreator:: Create4()
{
    bool quit = false;

    clip();
    setup_buttons();
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderClear( gRenderer );
    std::ifstream map( "lazyU.map" );

    //The tiles that will be used
    PlayerTile *tiles[ TOTAL_PLAYER_TILES ];

    PlayerTile *highlight[ 1 ];

    PlayerTile *palette[ 21 ];
    //The frame rate regulator
    Timer fps;

    //Set the tiles
    if( set_tiles( tiles, map ) == false )
    {
        return 1;
    }

 //   blackT.render(left_padding, 0, &zooming3[zoom/10]);


    for( int t = 0; t < TOTAL_PLAYER_TILES; t++ )
        {
            //SDL_SetRenderDrawColor( gRenderer, 68, 0xFF, 0xFF, 0xFF );
          //  SDL_RenderClear( gRenderer );
            if(tiles[ t ]->isUsed())
                tiles[ t ]->show();
            else
            {
               // black.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming[1]);
                monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
            }
        }



    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        SDL_PumpEvents();
        if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        {
            if(canSquare)
                square(tiles);
        }

        set_palette(palette);

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(canRubber)
                        rubber = true;
                    else if(canPaint)
                        paint = true;
                    else if(canGrab)
                        selectSquare(tiles, copyTiles);
                    else if(canPaste)
                        pasteSquare(tiles, copyTiles);
                    else if(canFill)
                        FillAcc(tiles);
                    else if(canSelect)
                        select_tile(tiles, highlight);

                    int temp = interface(tiles, copyTiles);
                    if( temp == 1)
                        return 0;
                    else if(temp == 2)
                    {
                        std::ofstream map2( "lazyU.map" );
                        save_tiles( tiles, map2 );
                        return 1;
                    }

                    if(canChooseColour)
                        select_colour(palette);
                }
            }

            if(event.type == SDL_MOUSEBUTTONUP )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    rubber = false;
                    paint = false;
                    if(canSquare)
                    {
                        square(tiles);
                    }
                    if(canGrab)
                    {
                        selectSquare(tiles, copyTiles);
                    }

                    interface2(tiles, copyTiles);
                    zoom_width_clicked = false;
                }
            }


            if( event.type == SDL_QUIT )
            {
                //Quit the program
                std::ofstream map2( "lazyU.map" );
                save_tiles( tiles, map2 );
                return 1;
            }

            if( event.type == SDL_KEYDOWN )
            {


            if( event.key.keysym.sym == SDLK_RIGHT && zoom > 10)
                {
                    camera.x = camera.x + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                     }

                 }

                else if( event.key.keysym.sym == SDLK_LEFT && zoom > 10)
                {
                    camera.x = camera.x - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_DOWN && zoom > 10)
                {
                    camera.y = camera.y + 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );

                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);
                        }

                    }

                 }


                else if( event.key.keysym.sym == SDLK_UP && zoom > 10)
                {
                    camera.y = camera.y - 50;
                    setup_buttons();
                    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
                    SDL_RenderClear( gRenderer );
                    for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
                    {
                        if(tiles[t]->isUsed())
                            tiles[t]->show();
                        else
                        {
                            monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                        }

                     }

                 }

            }

        }
//        clip();

        //Show the tiles
        if(selected)
        {
            highlight[ 0 ]->show2();
        }

        if(paint && !atCapacity)
            draw(tiles);

        if(rubber)
            rub(tiles);

        if(copying)
            Sel(tiles);

        if(!canGrab || paste)
        {
            for(int t = 0; t < TOTAL_PLAYER_TILES; t++)
            {
                if(tiles[t]->isGrabbed)
                {
                    if(tiles[t]->isUsed())
                        tiles[t]->show();
                    else
                        monitorT2.render(tiles[t]->get_box().x - camera.x, tiles[t]->get_box().y - camera.y, &zooming3[zoom/10]);

                    tiles[t]->isGrabbed = false;
                }
            }
            paste = false;
        }

        creatorInterface.render(0 ,0);
        creatorInterface2.render(1000, 0);
        palette[20]->show4();

        gFont = TTF_OpenFont( "font2.ttf", 24 );
        pixels_remaining = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);
        std::stringstream ss1;
        ss1 << pixels_remaining;
        SDL_Color textColor2 = { 163, 163, 163 };
        pixelDisplay.loadFromRenderedText( ss1.str(), textColor2 );
        pixelDisplay.render(1054, 70);

        std::stringstream ss2;
        ss2 << zoom/10;
        pixelDisplay.loadFromRenderedText( ss2.str(), textColor2 );
        pixelDisplay.render(75, 455);

        std::stringstream ss3;
        ss3 << pointer_width + 1;
        pixelDisplay.loadFromRenderedText( ss3.str(), textColor2 );
        pixelDisplay.render(1074, 388);

        int temp = 0;
        for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
        {
            if(tiles[i]->isUsed() == 1)
            {
                temp++;
            }
        }
        gun_pixels_used = temp;

        if(check_capacity())
            atCapacity = false;
        else
            atCapacity = true;


        if(canPaint)
        {
            Sel5.render(1038, 127);
        }

        else if(canRubber)
        {
            Sel5.render(1038, 190);
        }

        else if(canFill)
        {
            Sel5.render(1038, 258);
        }

        else if(canGrab)
        {
            Sel5.render(37, 33);
        }

        else if(canPaste)
        {
            Sel5.render(35, 168);
        }

        else if(canSquare)
        {
            Sel5.render(35, 240);
        }

        if(buttonsClicked() == 1)
        {
            button_click1.render(35, 97, &clicked_button[0]);
        }

        else if(buttonsClicked() == 2)
        {
            button_click1.render(35, 168, &clicked_button[1]);
        }

        else if(buttonsClicked() == 3)
        {
            button_click1.render(35, 240, &clicked_button[2]);
        }

        else if(buttonsClicked() == 4)
        {
            button_click1.render(35, 312, &clicked_button[3]);
        }

        else if(buttonsClicked() == 5)
        {
            button_click1.render(28, 439, &clicked_button[4]);
        }

        else if(buttonsClicked() == 6)
        {
            button_click1.render(28, 471, &clicked_button[5]);
        }

        else if(buttonsClicked() == 11)
        {
            button_click1.render(1027, 372, &clicked_button[4]);
        }

        else if(buttonsClicked() == 12)
        {
            button_click1.render(1027, 404, &clicked_button[5]);
        }

        if(canChooseColour)
        {
            paletteDisplay.render(1000, 120);

            for(int i = 0; i < 20; i++)
            {
                palette[i]->show4();
            }

            if(buttonsClicked() == 18)
            {
                button_click1.render(1045, 398, &clicked_button[6]);
            }

            else if(buttonsClicked() == 19)
            {
                button_click1.render(1103, 398, &clicked_button[7]);
            }

            gFont = TTF_OpenFont( "font2.ttf", 18 );
            std::stringstream ss4;
            ss4 << currentRed;
            pixelDisplay.loadFromRenderedText( ss4.str(), textColor2 );
            pixelDisplay.render(1020, 370);

            std::stringstream ss5;
            ss5 << currentGreen;
            pixelDisplay.loadFromRenderedText( ss5.str(), textColor2 );
            pixelDisplay.render(1085, 370);

            std::stringstream ss6;
            ss6 << currentBlue;
            pixelDisplay.loadFromRenderedText( ss6.str(), textColor2 );
            pixelDisplay.render(1150, 370);

        }

        if(red_chosen)
        {
            Sel6.render(1015, 359);
        }

        if(green_chosen)
        {
            Sel6.render(1080, 359);
        }

        if(blue_chosen)
        {
            Sel6.render(1145, 359);
        }


        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    std::ofstream map2( "lazyU.map" );
    save_tiles( tiles, map2 );


    return 0;
}
