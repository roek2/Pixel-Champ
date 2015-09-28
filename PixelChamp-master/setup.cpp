#include "SDL.h"
#include <fstream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "baseHeader.h"
#include "setupHeader.h"
#include "dotHeader.h"
#include "LTextureHeader.h"
using namespace std;

LTexture dotT;
LTexture bitT;
LTexture weaponsT;
LTexture weapons2T;
LTexture monitorT;
LTexture monitorT2;
LTexture black;
LTexture blackT;
LTexture blackBackground;
LTexture blank;
LTexture enemysT;
LTexture pixelT;
LTexture tileSheetT;
LTexture tileSheet2T;
LTexture tileSheet3T;
LTexture enemySheetClip;
LTexture enemySheetClipBig;
LTexture screenT;
LTexture backgroundT;
LTexture background2T;
LTexture playerbgT;
LTexture compT;
LTexture partT;
LTexture enemySheetClipOuch;
LTexture generator;
LTexture generator2;
LTexture generator3;
LTexture paused;
LTexture creatorInterface;
LTexture creatorInterface2;
LTexture button1;
LTexture textOfSorts;
LTexture textOfSorts2;
LTexture prompt1;
LTexture prompt2;
LTexture Sel5;
LTexture Sel6;
LTexture button_click1;
LTexture pixelDisplay;
LTexture paletteDisplay;
LTexture life_bar;
LTexture stat_bar;
LTexture stat2_bar;
LTexture energy_bar;
LTexture life_bar_con;
LTexture heart;
LTexture power;
LTexture Selector;
LTexture mainMenu;
LTexture menuSelect;
LTexture fadeIn;
LTexture dark;
LTexture baddy;
LTexture baddy2;
LTexture pink;
LTexture speech_bubble;
LTexture speech2;
LTexture falling;
LTexture freeFall;
LTexture darken1;
LTexture credit1;
LTexture credit2;
LTexture credit3;
LTexture pixelBox;
Mix_Music *gMusic = NULL;
Mix_Chunk *walk = NULL;
Mix_Chunk *jumpSound = NULL;
Mix_Chunk *swordSound = NULL;
Mix_Chunk *gunSound = NULL;
Mix_Chunk *dashSound = NULL;
Mix_Chunk *enemyDeathSound = NULL;

extern TTF_Font *gFont;
extern SDL_Rect cutOut;
extern bool direction;
extern int animate_counter;

extern Mix_Chunk *win;
extern Mix_Chunk *lose;
extern Mix_Chunk *notime;
extern Mix_Chunk *alert;
extern Mix_Music *music;

extern int TOTAL_TILES;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;
int animate_counter2 = 0;
extern bool moving_left;
extern bool moving_right;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern bool MEDIADEBUG;
extern bool MUSICDEBUG;
extern bool FONTDEBUG;
extern bool IMAGEDEBUG;
extern int test_success;
extern int test_failures;

SDL_Rect enemyClips[25];
SDL_Rect enemyClipsBig[25];
SDL_Rect particleClips[6];          //changed from 4
extern SDL_Rect life;
extern SDL_Rect stat;
extern SDL_Rect energy;
extern SDL_Rect stat2;
extern SDL_Rect life_con;
extern SDL_Rect life_bar_con_end;
SDL_GameController* gGameController = NULL;


bool Setup:: init()
{

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Enable VSync
		if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		{
			printf( "Warning: VSync not enabled!" );
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				}

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }

                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					return false;
				}

				 gGameController = SDL_GameControllerOpen( 0 ); if( gGameController == NULL ) { printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() ); }
			}

		}
	}
    return true;
}





SDL_Surface* Setup:: load_image( std::string filename )
{

    SDL_Surface* optimizedImage = NULL;
}

void Setup:: clip_tiles()
{
        //Clip the sprite sheet and assign the different sprites to the tiles
    enemyClips[ 1 ].x = 0;
    enemyClips[ 1 ].y = 0;
    enemyClips[ 1 ].w = 110;
    enemyClips[ 1 ].h = 110;

    enemyClips[ 2 ].x = 120;
    enemyClips[ 2 ].y = 0;                     //green
    enemyClips[ 2 ].w = 110;
    enemyClips[ 2 ].h = 110;

    enemyClips[ 3 ].x = 240;                         //blue
    enemyClips[ 3 ].y = 0;
    enemyClips[ 3 ].w = 110;
    enemyClips[ 3 ].h = 110;

    enemyClips[ 4 ].x = 360;
    enemyClips[ 4 ].y = 0;
    enemyClips[ 4 ].w = 110;
    enemyClips[ 4 ].h = 110;

    enemyClips[ 5 ].x = 480;
    enemyClips[ 5 ].y = 0;
    enemyClips[ 5 ].w = 110;
    enemyClips[ 5 ].h = 110;

    enemyClips[ 6 ].x = 0;
    enemyClips[ 6 ].y = 120;
    enemyClips[ 6 ].w = 110;
    enemyClips[ 6 ].h = 110;

    enemyClips[ 7 ].x = 120;
    enemyClips[ 7 ].y = 120;
    enemyClips[ 7 ].w = 110;
    enemyClips[ 7 ].h = 110;

    enemyClips[ 8 ].x = 240;
    enemyClips[ 8 ].y = 120;
    enemyClips[ 8 ].w = 110;
    enemyClips[ 8 ].h = 110;

    enemyClips[ 9 ].x = 360;
    enemyClips[ 9 ].y = 120;
    enemyClips[ 9 ].w = 110;
    enemyClips[ 9 ].h = 110;

    enemyClips[ 10 ].x = 0;
    enemyClips[ 10 ].y = 240;
    enemyClips[ 10 ].w = 110;
    enemyClips[ 10 ].h = 110;

    enemyClips[ 11 ].x = 120;
    enemyClips[ 11 ].y = 240;
    enemyClips[ 11 ].w = 110;
    enemyClips[ 11 ].h = 110;

    enemyClips[ 12 ].x = 240;
    enemyClips[ 12 ].y = 240;
    enemyClips[ 12 ].w = 110;
    enemyClips[ 12 ].h = 110;

    enemyClips[ 13 ].x = 360;
    enemyClips[ 13 ].y = 240;
    enemyClips[ 13 ].w = 110;
    enemyClips[ 13 ].h = 110;

    enemyClips[ 14 ].x = 480;
    enemyClips[ 14 ].y = 240;
    enemyClips[ 14 ].w = 110;
    enemyClips[ 14 ].h = 110;

    enemyClips[ 15 ].x = 0;
    enemyClips[ 15 ].y = 360;
    enemyClips[ 15 ].w = 119;
    enemyClips[ 15 ].h = 110;

    enemyClips[ 16 ].x = 120;
    enemyClips[ 16 ].y = 360;
    enemyClips[ 16 ].w = 119;
    enemyClips[ 16 ].h = 110;

    enemyClips[ 17 ].x = 240;
    enemyClips[ 17 ].y = 360;
    enemyClips[ 17 ].w = 119;
    enemyClips[ 17 ].h = 110;

    enemyClips[ 18 ].x = 360;
    enemyClips[ 18 ].y = 360;
    enemyClips[ 18 ].w = 119;
    enemyClips[ 18 ].h = 110;

    enemyClips[ 19 ].x = 480;
    enemyClips[ 19 ].y = 360;
    enemyClips[ 19 ].w = 119;
    enemyClips[ 19 ].h = 110;

    enemyClips[ 20 ].x = 0;
    enemyClips[ 20 ].y = 480;
    enemyClips[ 20 ].w = 110;
    enemyClips[ 20 ].h = 110;

    enemyClips[ 21 ].x = 120;
    enemyClips[ 21 ].y = 480;
    enemyClips[ 21 ].w = 110;
    enemyClips[ 21 ].h = 110;

    enemyClips[ 22 ].x = 240;
    enemyClips[ 22 ].y = 480;
    enemyClips[ 22 ].w = 110;
    enemyClips[ 22 ].h = 110;

    enemyClips[ 23 ].x = 360;
    enemyClips[ 23 ].y = 480;
    enemyClips[ 23 ].w = 110;
    enemyClips[ 23 ].h = 110;

    enemyClips[ 24 ].x = 480;
    enemyClips[ 24 ].y = 480;
    enemyClips[ 24 ].w = 110;
    enemyClips[ 24 ].h = 110;

    enemyClipsBig[ 1 ].x = 0;
    enemyClipsBig[ 1 ].y = 0;
    enemyClipsBig[ 1 ].w = 242;
    enemyClipsBig[ 1 ].h = 229;

    enemyClipsBig[ 2 ].x = 242;
    enemyClipsBig[ 2 ].y = 0;                     //green
    enemyClipsBig[ 2 ].w = 242;
    enemyClipsBig[ 2 ].h = 229;

    enemyClipsBig[ 3 ].x = 0;                         //blue
    enemyClipsBig[ 3 ].y = 229;
    enemyClipsBig[ 3 ].w = 242;
    enemyClipsBig[ 3 ].h = 229;

    enemyClipsBig[ 4 ].x = 242;
    enemyClipsBig[ 4 ].y = 229;
    enemyClipsBig[ 4 ].w = 242;
    enemyClipsBig[ 4 ].h = 229;

    enemyClipsBig[ 5 ].x = 484;
    enemyClipsBig[ 5 ].y = 0;
    enemyClipsBig[ 5 ].w = 180;
    enemyClipsBig[ 5 ].h = 229;

    enemyClipsBig[ 6 ].x = 666;
    enemyClipsBig[ 6 ].y = 0;
    enemyClipsBig[ 6 ].w = 322;
    enemyClipsBig[ 6 ].h = 300;

    enemyClipsBig[ 7 ].x = 1306;
    enemyClipsBig[ 7 ].y = 0;
    enemyClipsBig[ 7 ].w = 320;
    enemyClipsBig[ 7 ].h = 300;

    enemyClipsBig[ 8 ].x = 1626;
    enemyClipsBig[ 8 ].y = 0;
    enemyClipsBig[ 8 ].w = 320;
    enemyClipsBig[ 8 ].h = 300;

    enemyClipsBig[ 9 ].x = 986;
    enemyClipsBig[ 9 ].y = 0;
    enemyClipsBig[ 9 ].w = 322;
    enemyClipsBig[ 9 ].h = 300;

    particleClips[ 0 ].x = 0;
    particleClips[ 0 ].y = 0;
    particleClips[ 0 ].w = 4;
    particleClips[ 0 ].h = 4;

    particleClips[ 1 ].x = 4;
    particleClips[ 1 ].y = 0;
    particleClips[ 1 ].w = 4;
    particleClips[ 1 ].h = 4;

    particleClips[ 2 ].x = 8;
    particleClips[ 2 ].y = 0;
    particleClips[ 2 ].w = 4;
    particleClips[ 2 ].h = 4;

    particleClips[ 3 ].x = 12;
    particleClips[ 3 ].y = 0;
    particleClips[ 3 ].w = 4;
    particleClips[ 3 ].h = 4;

    particleClips[ 4 ].x = 16;
    particleClips[ 4 ].y = 0;
    particleClips[ 4 ].w = 4;
    particleClips[ 4 ].h = 4;

    particleClips[ 5 ].x = 20;
    particleClips[ 5 ].y = 0;
    particleClips[ 5 ].w = 4;
    particleClips[ 5 ].h = 4;

    particleClips[ 6 ].x = 24;
    particleClips[ 6 ].y = 0;
    particleClips[ 6 ].w = 4;
    particleClips[ 6 ].h = 4;

    cutOut.x = 0;
    cutOut.y = 0;
    cutOut.w = 400;
    cutOut.h = 100;

    life.x = 0;
    life.y = 0;
    life.h = 14;

    stat.x = 0;
    stat.y = 0;
    stat.h = 14;

    stat2.x = 0;
    stat2.y = 0;
    stat2.h = 14;

    energy.x = 0;
    energy.y = 0;
    energy.h = 14;

    life_con.x = 0;
    life_con.y = 0;
    life_con.h = 19;

    life_bar_con_end.x = 645;
    life_bar_con_end.y = 0;
    life_bar_con_end.h = 19;
    life_bar_con_end.w = 5;

}



bool Setup:: load_files()
{
    dotT.loadFromFile( "first_test7.bmp" );
    monitorT.loadFromFile( "monitor2.png");
    monitorT.setBlendMode( SDL_BLENDMODE_BLEND );
    monitorT.setAlpha(100);
    monitorT2.loadFromFile( "mon2.png" );

    blank.loadFromFile( "blank.png");
    black.loadFromFile( "black.png" );
    compT.loadFromFile( "tile_select2.png");
    compT.setBlendMode( SDL_BLENDMODE_BLEND );
    compT.setAlpha(255);
    Sel5.loadFromFile( "select5.png");
    Sel6.loadFromFile( "select6.png");
    button_click1.loadFromFile( "button_click1.png");
    mainMenu.loadFromFile( "Main_Menu.png");
    speech_bubble.loadFromFile( "speech.png");
    speech2.loadFromFile( "speech2.png");

    blackT.loadFromFile( "black2.png");
    blackBackground.loadFromFile( "black2.png");

    backgroundT.loadFromFile( "newbg.png");
    tileSheetT.loadFromFile( "newTile.png");
    enemySheetClip.loadFromFile( "EnemyClips4.png" );
    enemySheetClipBig.loadFromFile( "EnemyClips2.png" );
    enemySheetClipOuch.loadFromFile("EnemyClipsOuch.png");
    enemySheetClipOuch.setBlendMode( SDL_BLENDMODE_BLEND );
    enemySheetClipOuch.setAlpha(100);

    partT.loadFromFile("bits.bmp");
    paletteDisplay.loadFromFile("newPalette.png");

    fadeIn.loadFromFile( "black2.png");
    fadeIn.setBlendMode( SDL_BLENDMODE_BLEND );

    generator.loadFromFile( "customise7.png");
    generator2.loadFromFile( "gen2.png");
    generator3.loadFromFile( "gen3.png");
    paused.loadFromFile( "pause.png");
    creatorInterface.loadFromFile( "customise10.png");
    creatorInterface2.loadFromFile( "customise11.png");
    button1.loadFromFile( "button1.png");
    life_bar.loadFromFile( "life_bar.png");
    stat_bar.loadFromFile( "stat_bar.png");
    stat2_bar.loadFromFile( "stat_bar2.png");
    energy_bar.loadFromFile( "energy_bar.png");
    life_bar_con.loadFromFile( "life_bar_con.png");
    heart.loadFromFile( "heart.png");
    power.loadFromFile( "power.png");
    Selector.loadFromFile( "Selector.png");
    dark.loadFromFile("black2.png");
    dark.setBlendMode( SDL_BLENDMODE_BLEND );
    dark.setAlpha(90);
    pixelBox.loadFromFile("pixelBox.png");

    baddy.loadFromFile( "baddy.png");
    baddy2.loadFromFile( "baddy2.png");
    pink.loadFromFile( "pink.png");
    falling.loadFromFile("PrtCave3.png");
    freeFall.loadFromFile("falling.bmp");
    darken1.loadFromFile("darken1.png");
    darken1.setBlendMode( SDL_BLENDMODE_BLEND );
    darken1.setAlpha(60);
    credit1.loadFromFile("credit1.png");
    credit2.loadFromFile("credit2.png");
    credit3.loadFromFile("credit3.png");

   // gMusic = Mix_LoadMUS( "music.wav" );
   // Mix_PlayMusic( gMusic, -1 );
   // Mix_VolumeMusic(10);

    walk = Mix_LoadWAV( "step.wav" );
    Mix_VolumeChunk(walk, 8);


    jumpSound = Mix_LoadWAV( "doubleJump.wav" );
    Mix_VolumeChunk(jumpSound, 10);

    swordSound = Mix_LoadWAV( "sword.wav" );
    Mix_VolumeChunk(swordSound, 5);

    gunSound = Mix_LoadWAV( "gun.wav" );
    Mix_VolumeChunk(gunSound, 8);

    dashSound = Mix_LoadWAV( "dash3.wav" );
    Mix_VolumeChunk(dashSound, 12);

    enemyDeathSound = Mix_LoadWAV( "dash.wav" );
    Mix_VolumeChunk(enemyDeathSound, 8);


    gFont = TTF_OpenFont( "font2.ttf", 24 );

		//Render text
    SDL_Color textColor = { 200, 0, 0 };
    if( !textOfSorts.loadFromRenderedText( "Pixel Pack", textColor ) )
    {
        printf( "Failed to render text texture!\n" );
        return false;
    }

    SDL_Color textColor2 = { 100, 0, 0 };
    if( !textOfSorts2.loadFromRenderedText( "Pixel Pack", textColor2 ) )
    {
        printf( "Failed to render text texture!\n" );
        return false;
    }

    SDL_Color textColor4 = { 0, 162, 232 };
    if( !prompt1.loadFromRenderedText( "R", textColor4 ) )
    {
        printf( "Failed to render text texture!\n" );
        return false;
    }



    SDL_Color textColor3 = { 0, 0, 200 };
    if( !prompt2.loadFromRenderedText( "R", textColor3 ) )
    {
        printf( "Failed to render text texture!\n" );
        return false;
    }


	if(MEDIADEBUG)
    {
        printf( "\n------------Media Tests-----------\n \n" );

        if(MUSICDEBUG)
        {

            printf( "Music Tests:\n \n" );
            if( gMusic == NULL )
            {
                 printf( "X - Failed to load Game music! \n");
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load Game music! \n" );
                 test_success++;
            }

            if( walk == NULL )
            {
                 printf( "X - Failed to load walk sound effect! \n");
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load walk sound effect! \n" );
                 test_success++;
            }

            if( enemyDeathSound == NULL )
            {
                 printf( "X - Failed to load enemy death sound effect! \n" );
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load enemy death sound effect! \n" );
                 test_success++;
            }

            if( dashSound == NULL )
            {
                 printf( "X - Failed to load dash sound effect! \n" );
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load dash sound effect! \n" );
                 test_success++;
            }

            if( gunSound == NULL )
            {
                 printf( "X - Failed to load gun sound effect! \n" );
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load gun sound effect! \n" );
                 test_success++;
            }

            if( swordSound == NULL )
            {
                 printf( "X - Failed to load sword sound effect! \n" );
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load sword sound effect! \n" );
                 test_success++;
            }

            if( jumpSound == NULL )
            {
                 printf( "X - Failed to load double jump sound effect! \n");
                 test_failures++;
            }

            else
            {
                 printf( "O - Succeeded to load double jump sound effect! \n" );
                 test_success++;
            }

        }

        if(FONTDEBUG)
        {

            printf( "\nFont Tests:\n \n" );
            if( gFont == NULL )
            {
                printf( "X - Failed to load game font! \n");
                test_failures++;
            }

            else
            {
                printf( "O - Succeeded to load game font! \n");
                test_success++;
            }
        }

        if(IMAGEDEBUG)
        {
           printf( "\nImage Tests:\n\n");
           if( dotT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'first_test7'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'first_test7'! \n");
               test_success++;
           }

           if( monitorT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'monitorT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'monitorT'! \n");
               test_success++;
           }

           if( monitorT2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'monitorT2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'monitorT2'! \n");
               test_success++;
           }

           if( black.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'black'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'black'! \n");
               test_success++;
           }

           if( compT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'compT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'compT'! \n");
               test_success++;
           }

           if( Sel5.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'Sel5'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'Sel5'! \n");
               test_success++;
           }

           if( Sel6.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'Sel6'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'Sel6'! \n");
               test_success++;
           }


           if( button_click1.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'button_click1'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'button_click1'! \n");
               test_success++;
           }

           if( mainMenu.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'mainMenu'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'mainMenu'! \n");
               test_success++;
           }

           if( speech_bubble.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'speech_bubble'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'speech_bubble'! \n");
               test_success++;
           }

           if( speech2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'speech2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'speech2'! \n");
               test_success++;
           }

           if( blackT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'blackT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'blackT'! \n");
               test_success++;
           }

           if( blackBackground.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'blackBackground'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'blackBackground'! \n");
               test_success++;
           }

           if( backgroundT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'backgroundT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'backgroundT'! \n");
               test_success++;
           }

           if( tileSheetT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'tileSheetT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'tileSheetT'! \n");
               test_success++;
           }

           if( enemySheetClip.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'enemySheetClip'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'enemySheetClip'! \n");
               test_success++;
           }

           if( enemySheetClipBig.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'enemySheetClipBig'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'enemySheetClipBig'! \n");
               test_success++;
           }

           if( enemySheetClipOuch.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'enemySheetClipOuch'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'enemySheetClipOuch'! \n");
               test_success++;
           }

           if( partT.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'partT'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'partT'! \n");
               test_success++;
           }

           if( paletteDisplay.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'paletteDisplay'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'paletteDisplay'! \n");
               test_success++;
           }

           if( fadeIn.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'fadeIn'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'fadeIn'! \n");
               test_success++;
           }

           if( generator.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'generator'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'generator'! \n");
               test_success++;
           }

           if( generator2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'generator2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'generator2'! \n");
               test_success++;
           }

           if( generator3.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'generator3'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'generator3'! \n");
               test_success++;
           }

           if( paused.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'paused'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'paused'! \n");
               test_success++;
           }

           if( creatorInterface.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'creatorInterface'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'creatorInterface'! \n");
               test_success++;
           }

           if( creatorInterface2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'creatorInterface2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'creatorInterface2'! \n");
               test_success++;
           }

           if( button1.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'button1'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'button1'! \n");
               test_success++;
           }

           if( life_bar.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'life_bar'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'life_bar'! \n");
               test_success++;
           }

           if( stat_bar.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'stat_bar'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'stat_bar'! \n");
               test_success++;
           }

           if( stat2_bar.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'stat2_bar'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'stat2_bar'! \n");
               test_success++;
           }

           if( energy_bar.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'energy_bar'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'energy_bar'! \n");
               test_success++;
           }

           if( life_bar_con.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'life_bar_con'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'life_bar_con'! \n");
               test_success++;
           }

           if( heart.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'heart'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'heart'! \n");
               test_success++;
           }

           if( power.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'power'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'power'! \n");
               test_success++;
           }

           if( Selector.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'Selector'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'Selector'! \n");
               test_success++;
           }

           if( dark.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'dark'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'dark'! \n");
               test_success++;
           }

           if( pixelBox.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'pixelBox'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'pixelBox'! \n");
               test_success++;
           }

           if( baddy.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'baddy'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'baddy'! \n");
               test_success++;
           }

           if( baddy2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'baddy2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'baddy2'! \n");
               test_success++;
           }

           if( pink.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'pink'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'pink'! \n");
               test_success++;
           }

           if( falling.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'falling'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'falling'! \n");
               test_success++;
           }

           if( freeFall.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'freeFall'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'freeFall'! \n");
               test_success++;
           }

           if( darken1.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'darken1'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'darken1'! \n");
               test_success++;
           }

           if( credit1.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'credit1'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'credit1'! \n");
               test_success++;
           }

           if( credit2.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'credit2'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'credit2'! \n");
               test_success++;
           }

           if( credit3.getHeight() == NULL )
           {
               printf( "X - Failed to load LTexture 'credit3'! \n");
               test_failures++;
           }

           else
           {
               printf( "O - Succeeded to load LTexture 'credit3'! \n");
               test_success++;
           }

        }

    printf( "\n" );
    printf( "Media report:\n" );
    printf( "Test Success: ");
    printf("%d\n", test_success);

    printf( "Test Failures: ");
    printf("%d\n", test_failures);

    }

    return true;
}

bool Setup:: animate(Dot myDot)
{

     if(moving_left || moving_right)
                   animate_counter++;

     if(direction == true)
     {
           dotT.loadFromFile( "first_test7.bmp" );
          // comp = load_image( "Untitled_c2.png" );

           if(animate_counter > 4 && myDot.is_onGround())
           {
                 dotT.loadFromFile( "first_test8.bmp" );

            //     comp = load_image( "Untitled_c4.png" );
                 if(animate_counter2 == 2)
                 {
                    Mix_PlayChannel( -1, walk, 0 );
                    animate_counter = 0;
                    animate_counter2 = 0;
                 }
                 animate_counter2++;
                 //return false;
           }

           if(!myDot.is_onGround())
           {
               dotT.loadFromFile( "first_test8.bmp" );
           }
     }

     else
     {      dotT.loadFromFile( "first_test5.bmp" );
         // dot = load_image( "first_test5.bmp" );
     //     dot = load_image( "first_test5.bmp" );
    //      comp = load_image( "Untitled_c.png" );
          if(animate_counter > 4 && myDot.is_onGround())
          {
                 dotT.loadFromFile( "first_test6.bmp" );

           //      comp = load_image( "Untitled_c3.png" );
                 if(animate_counter2 == 2)
                 {
                     Mix_PlayChannel( -1, walk, 0 );
                    animate_counter = 0;
                    animate_counter2 = 0;
                 }
                 animate_counter2++;
                 //return false;
          }

           if(!myDot.is_onGround())
           {
               dotT.loadFromFile( "first_test6.bmp" );
           }
     }

     return true;
}

