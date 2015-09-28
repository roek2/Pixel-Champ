#include "SDL.h"
#include <fstream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "baseHeader.h"
#include "MenuHeader.h"
#include "timerHeader.h"
#include "LTextureHeader.h"
#include "playerTileHeader.h"
#include "playerCreatorHeader.h"
#include "playerstatsHeader.h"
#include "converterHeader.h"
#include "charSelect.h"
#include "generatorHeader.h"
#include "converterHeader.h"
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

ifstream readfile2;
ofstream newfile2;
extern TTF_Font *gFont;
extern SDL_Renderer* gRenderer;
extern SDL_Event event;
int menuNum = 1;
extern Converter conv;
int menu_position = 1;
extern LTexture mainMenu;
extern LTexture menuSelect;
extern LTexture fadeIn;
extern int FRAMES_PER_SECOND;
extern CharSelect cs;
int menu_image = 1;
int menu_icon = 1;
int fadeInAlpha = 250;
extern PlayerStats stats;
bool fadeOut = false;
extern int StartTime;
extern int StartingHour;
extern int StartingMin;
extern int StartingSec;
LTexture stats2;
extern int totalHour;
extern int totalMin;
extern int totalSec;
extern int StartingDate;
int room = 0;
extern bool intro;
extern bool kidnapped;
extern int pixel_capacity;
extern int Level;


extern int fall;
extern int fall2;
extern LTexture falling;
extern LTexture freeFall;
extern LTexture backgroundT;
extern LTexture darken1;
extern LTexture credit3;

bool Menu:: loadImages()
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
        credit3.render(456,70);

        if(menuNum == 2)
        {
            if(menu_image != 2)
            {
                mainMenu.loadFromFile("credit4.png");
                menu_image = menuNum;
            }

            mainMenu.render(456,70);
        }

        if(menuNum == 3)
        {
            if(menu_image != 3)
            {
                mainMenu.loadFromFile("credit5.png");
                menu_image = menuNum;
            }

            mainMenu.render(356,70);
        }


}

void Menu:: show_sel()
{
    if(menuNum == 1)
    {
     //   if(menu_icon != 1)
        {
            menuSelect.loadFromFile("icon2.png");
            menu_icon = menuNum;
        }

        if(menu_position == 1)
        {
            menuSelect.render(490, 185);
        }

        else if(menu_position == 2)
        {
            menuSelect.render(463, 260);
        }

        else if(menu_position == 3)
        {
            menuSelect.render(447, 333);
        }

        else if(menu_position == 4)
        {
            menuSelect.render(490, 405);
        }

    }

    if(menuNum == 2)
    {

        if(menu_position == 1)
        {
            menuSelect.render(505, 193);
        }

        else if(menu_position == 2)
        {
            menuSelect.render(505, 288);
        }

        else if(menu_position == 3)
        {
            menuSelect.render(510, 380);
        }

    }

    if(menuNum == 3)
    {
        std::ifstream save1( "saves/1/info.map");
        std::ifstream save2( "saves/2/info.map");
        std::ifstream save3( "saves/3/info.map");

        if(menu_position == 1)
        {
            menuSelect.render(505, 185);
            show_stats(save1);
        }

        else if(menu_position == 2)
        {
            menuSelect.render(505, 245);
            show_stats(save2);
        }

        else if(menu_position == 3)
        {
            menuSelect.render(510, 310);
            show_stats(save3);
        }

        else if(menu_position == 4)
        {
            menuSelect.render(510, 373);
        }


    }

}

//std::ifstream map( "map/Lazy221.map");

void Menu:: show_stats(std::ifstream &save)
{

    int hour;
    int minute;
    int seconds;
    int date;
    int month;
    int year;
    int playHour;
    int playMin;
    int playSec;
    int savePixels;

    save >> room;
    save >> date;
    save >> month;
    save >> year;
    save >> hour;
    save >> minute;
    save >> seconds;
    save >> playHour;
    save >> playMin;
    save >> playSec;
    save >> savePixels;

    totalHour = playHour;
    totalMin = playMin;
    totalSec = playSec;
    pixel_capacity = savePixels;

    gFont = TTF_OpenFont( "font2.ttf", 18 );
    std::stringstream ss1;
    SDL_Color textColor2 = { 163, 163, 163 };
    if(date < 10)
        ss1 << "0";
    ss1 << date << "/";
    stats2.loadFromRenderedText( ss1.str(), textColor2 );
    stats2.render(460, 458);

    std::stringstream ss2;
    if(month < 10)
        ss2 << "0";
    ss2 << month << "/";
    stats2.loadFromRenderedText( ss2.str(), textColor2 );
    stats2.render(490, 458);

    std::stringstream ss3;
    ss3 << year;
    stats2.loadFromRenderedText( ss3.str(), textColor2 );
    stats2.render(525, 458);

    std::stringstream ss4;
    if(hour < 10)
        ss4 << "0";
    ss4 << hour << ":";
    stats2.loadFromRenderedText( ss4.str(), textColor2 );
    stats2.render(460, 492);

    std::stringstream ss5;
    if(minute < 10)
        ss5 << "0";
    ss5 << minute << ":";
    stats2.loadFromRenderedText( ss5.str(), textColor2 );
    stats2.render(485, 492);

    std::stringstream ss6;
    if(seconds < 10)
        ss6 << "0";
    ss6 << seconds;
    stats2.loadFromRenderedText( ss6.str(), textColor2 );
    stats2.render(515, 492);

    std::stringstream ss7;
    ss7 << savePixels;
    stats2.loadFromRenderedText( ss7.str(), textColor2 );
    stats2.render(530, 561);

    std::stringstream ss8;
    if(playHour < 10)
        ss8 << "0";
    ss8 << playHour << ":";
    stats2.loadFromRenderedText( ss8.str(), textColor2 );
    stats2.render(510, 525);

    std::stringstream ss9;
    if(playMin < 10)
        ss9 << "0";
    ss9 << playMin << ":";
    stats2.loadFromRenderedText( ss9.str(), textColor2 );
    stats2.render(545, 525);

    std::stringstream ss10;
    if(playSec < 10)
        ss10 << "0";
    ss10 << playSec;
    stats2.loadFromRenderedText( ss10.str(), textColor2 );
    stats2.render(580, 525);



}


void Menu:: load_game()
{

    intro = false;
    kidnapped = true;


    if(room == 1)
    {
        Level = 222;
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        StartingHour = now->tm_hour;
        StartingMin = now->tm_min;
        StartingSec = now->tm_sec;
        StartingDate = now->tm_mday;
    }

    else if(room == 2)
    {
        Level = 528;
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        StartingHour = now->tm_hour;
        StartingMin = now->tm_min;
        StartingSec = now->tm_sec;
        StartingDate = now->tm_mday;
    }

    else if(room == 3)
    {

    }

    else if(room == 4)
    {

    }
}

int Menu:: select_path()
{

    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(menuNum == 1)
                {
                    if(menu_position > 1)
                        menu_position--;
                }

                if(menuNum == 2)
                {
                    if(menu_position > 1)
                        menu_position--;
                }



                else if(menuNum == 3)
                {
                    if(menu_position > 1)
                        menu_position--;
                }
            }

            else if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(menuNum == 1)
                {
                    if(menu_position < 4)
                        menu_position++;
                }


                if(menuNum == 2)
                {
                    if(menu_position < 3)
                        menu_position++;
                }


                else if(menuNum == 3)
                {
                    if(menu_position < 4)
                        menu_position++;
                }
            }




            else if( event.cbutton.button == SDL_CONTROLLER_BUTTON_A )
            {

                if(menuNum == 1)
                {
                    if(menu_position == 1)
                    {

/*
                        time_t t = time(0);   // get time now
                        struct tm * now = localtime( & t );
                        StartingHour = now->tm_hour;
                        StartingMin = now->tm_min;
                        StartingSec = now->tm_sec;
                        StartingDate = now->tm_mday;

                        totalHour = 0;
                        totalMin = 0;
                        totalSec = 0;

                      //  cout << StartingTime;
                        return 1;

*/
                    }

                    else if(menu_position == 2)
                    {
                        return 2;
                    }

                    else if(menu_position == 3)
                    {
                        return 3;
                    }

                    else if(menu_position == 4)
                    {
                        return 4;
                    }
                }

                if(menuNum == 2)
                {
                    if(menu_position == 1)
                    {
                        return 6;
                    }

                    else if(menu_position == 2)
                    {
                        return 7;
                    }

                    else if(menu_position == 3)
                    {
                        return 5;
                    }

                }

                if(menuNum == 3)
                {
                    if(menu_position == 1)
                    {
                        return 10;
                    }

                    else if(menu_position == 2)
                    {
                        return 10;
                    }

                    else if(menu_position == 3)
                    {
                        return 10;
                    }

                    else if(menu_position == 4)
                    {
                        return 9;
                    }
                }


            }
        }


        if( event.type == SDL_KEYDOWN )
        {

            if( event.key.keysym.sym == SDLK_UP )
            {
                if(menuNum == 1)
                {
                    if(menu_position > 1)
                        menu_position--;
                }

                if(menuNum == 2)
                {
                    if(menu_position > 1)
                        menu_position--;
                }



                else if(menuNum == 3)
                {
                    if(menu_position > 1)
                        menu_position--;
                }
            }

            else if( event.key.keysym.sym == SDLK_DOWN )
            {
                if(menuNum == 1)
                {
                    if(menu_position < 4)
                        menu_position++;
                }


                if(menuNum == 2)
                {
                    if(menu_position < 3)
                        menu_position++;
                }


                else if(menuNum == 3)
                {
                    if(menu_position < 4)
                        menu_position++;
                }
            }


            else if( event.key.keysym.sym == SDLK_RETURN )
            {

                if(menuNum == 1)
                {
                    if(menu_position == 1)
                    {
 /*                       time_t t = time(0);   // get time now
                        struct tm * now = localtime( & t );
                        StartingHour = now->tm_hour;
                        StartingMin = now->tm_min;
                        StartingSec = now->tm_sec;
                        StartingDate = now->tm_mday;

                        totalHour = 0;
                        totalMin = 0;
                        totalSec = 0;

                      //  cout << StartingTime;
                        return 1;

*/
                    }

                    else if(menu_position == 2)
                    {
                        return 2;
                    }

                    else if(menu_position == 3)
                    {
                        return 3;
                    }

                    else if(menu_position == 4)
                    {
                        return 4;
                    }
                }

                if(menuNum == 2)
                {
                    if(menu_position == 1)
                    {
                        return 6;
                    }

                    else if(menu_position == 2)
                    {
                        return 7;
                    }

                    else if(menu_position == 3)
                    {
                        return 5;
                    }

                }

                if(menuNum == 3)
                {
                    if(menu_position == 1)
                    {
                        return 10;
                    }

                    else if(menu_position == 2)
                    {
                        return 10;
                    }

                    else if(menu_position == 3)
                    {
                        return 10;
                    }

                    else if(menu_position == 4)
                    {
                        return 9;
                    }
                }


            }
        }

    }
    return 0;

}

void Menu :: clearChar()
{
    readfile2.open("blank.map");
    newfile2.open("lazy.map");

    char ch;
    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("blank.map");
    newfile2.open("lazyA.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("blank.map");
    newfile2.open("lazyB.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("blank.map");
    newfile2.open("lazyU.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }
    readfile2.close();
    newfile2.close();
}


void Menu :: introChar()
{
    readfile2.open("intro.map");
    newfile2.open("lazy.map");

    char ch;
    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("introA.map");
    newfile2.open("lazyA.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("blank.map");
    newfile2.open("lazyB.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }

    readfile2.close();
    newfile2.close();

    readfile2.open("blank.map");
    newfile2.open("lazyU.map");

    while(!readfile2.eof())
    {
        readfile2.get(ch);
        newfile2<<ch;
    }
    readfile2.close();
    newfile2.close();
}



bool Menu:: run(Generator gen)
{
    bool quit = false;

    Timer fps;
    menuSelect.loadFromFile("icon2.png");


    while( quit == false )
    {
        //Start the frame timer
        fps.start();
        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        loadImages();


        if(fadeOut)
        {
            fadeInAlpha += 5;
        }

        int path = select_path();

        if(path == 1)
        {
            introChar();
            fadeOut = true;
        }

        else if(path == 2)
        {
            menuNum = 3;
            menu_position = 1;
        }


        else if(path == 3)
        {
            menuNum = 2;
            menu_position = 1;
        }

        else if(path == 4)
        {
            quit = true;
            return 1;
        }
        else if(path == 5)
        {
            menuNum = 1;
            menu_position = 1;
        }

        else if(path == 7)
        {
            int end_point = 1;
            end_point = cs.run(1, false);
            if(end_point == 2)
            {
                conv.construct();
                gen.run2();
            }
        }

        else if(path == 6)
        {
            clearChar();
            conv.construct();
            gen.run2();
        }

        else if(path == 9)
        {
            menuNum = 1;
        }

        else if(path == 10)
        {
            load_game();
            fadeOut = true;
        }


        if(fadeInAlpha == 255)
        {
            quit = true;
            fadeOut = false;
        }
/*
        else if(path == 2)
        {
            cs.run(1, false);
        } */
        show_sel();

        fadeIn.setAlpha(fadeInAlpha);
        fadeIn.render(0,0);
        if(fadeInAlpha > 0 && !fadeOut)
            fadeInAlpha -= 5;

        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    return 0;
}
