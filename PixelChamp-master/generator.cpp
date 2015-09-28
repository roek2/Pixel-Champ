#include "SDL.h"
#include <fstream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "baseHeader.h"
#include "generatorHeader.h"
#include "timerHeader.h"
#include "LTextureHeader.h"
#include "playerTileHeader.h"
#include "playerCreatorHeader.h"
#include "playerstatsHeader.h"
#include "converterHeader.h"
#include "charSelect.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

ifstream readfile3;
ofstream newfile3;
extern SDL_Event event;
extern int FRAMES_PER_SECOND;
extern int TOTAL_PLAYER_TILES;
extern SDL_Renderer* gRenderer;
extern LTexture generator;
extern LTexture generator2;
extern LTexture generator3;
extern LTexture paused;
extern int total_pixels_used;
extern int man_pixels_used;
extern int sword_pixels_used;
extern int gun_pixels_used;
extern bool rPressed;
extern int pixelcount;
extern int pixelcountM;
extern int pixelcountS;
extern int pixelcountG;
extern int pixel_capacity;
extern TTF_Font *gFont;
LTexture char1;
LTexture char2;
LTexture wep1;
LTexture wep2;
LTexture sel;
LTexture sel2;
LTexture sel3;
LTexture sel4;
LTexture sel7;
LTexture bar_prompt;
LTexture pLeft;
extern int Level;
int xPosition = 1;
int yPosition = 1;
int pixels_left = 0;
PlayerCreator mumbo;
Converter conv;
int maxHealth;
int maxEnergy;
extern SDL_Rect life;
extern SDL_Rect stat;
extern SDL_Rect stat2;
extern SDL_Rect energy;
extern LTexture life_bar;
extern LTexture stat_bar;
extern LTexture stat2_bar;
extern LTexture energy_bar;
LTexture statistics;
LTexture selection;
int health_pixels = 0;
int stat_pixels = 0;
int stat2_pixels = 0;
int sword_pixels = 0;
int energy_pixels = 0;
int swordStr = 2;
int gunStr = 2;
CharSelect cs;
extern bool load_out1;
extern bool menu;
int screen2 = 1;
int saveNum = 0;
int generatorNum = 0;
int sessionTime = 0;


int totalHour = 0;
int totalMin = 0;
int totalSec = 0;
extern int StartingHour;
extern int StartingMin;
extern int StartingSec;
extern bool load_game;


extern int StartingDate;

#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string.h>
#include <ctime>

bool Generator:: loadImages()
{
    if(screen2 == 2)
        generator.render(0,0);
    else if(screen2 == 1)
        generator2.render(0,0);
    else if(screen2 == 3)
        generator3.render(0,0);

    if(screen2 == 1)
    {
      sel4.loadFromFile("select13.png");
    }

    if(screen2 == 2)
    {
        char1.loadFromFile("first_test5.bmp");
        char1.render(155, 138);

        char2.loadFromFile("first_test6.bmp");
        char2.render(363,138);

        wep1.loadFromFile("first_test12.bmp");
        wep1.render(575,138);

        wep2.loadFromFile("first_test16.bmp");
        wep2.render(791,138);

        sel.loadFromFile("charSelect.png");
        sel2.loadFromFile("select2.png");
        sel3.loadFromFile("select3.png");
        sel4.loadFromFile("select4.png");
        sel7.loadFromFile("select7.png");
    }
}

bool Generator:: loadImages2()
{
    paused.render(0,0);
    char1.loadFromFile("first_test5.bmp");
    char1.render(227, 160);

    char2.loadFromFile("first_test6.bmp");
    char2.render(435,160);

    wep1.loadFromFile("first_test12.bmp");
    wep1.render(647,160);

    wep2.loadFromFile("first_test16.bmp");
    wep2.render(862,160);

    sel.loadFromFile("charSelect.png");
    sel2.loadFromFile("select2.png");
    sel3.loadFromFile("select12.png");
    sel4.loadFromFile("select13.png");
    sel7.loadFromFile("select7.png");

}

void Generator:: count_pixels()
{
    man_pixels_used = 0;
    sword_pixels_used = 0;
    gun_pixels_used = 0;

    std::ifstream map( "lazy.map" );

    PlayerTile *tiles[ TOTAL_PLAYER_TILES ];

    mumbo.set_tiles( tiles, map );

    for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
    {
        if(tiles[i]->isUsed() == 1)
        {
          man_pixels_used++;
        }
    }

    std::ifstream map2( "lazyB.map" );

    PlayerTile *tiles2[ TOTAL_PLAYER_TILES ];

    mumbo.set_tiles( tiles2, map2 );

    for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
    {
        if(tiles2[i]->isUsed() == 1)
        {
          sword_pixels_used++;
        }
    }

    std::ifstream map3( "lazyU.map" );

    PlayerTile *tiles3[ TOTAL_PLAYER_TILES ];

    mumbo.set_tiles( tiles3, map3 );

    for(int i = 0; i < TOTAL_PLAYER_TILES; i++)
    {
        if(tiles3[i]->isUsed() == 1)
        {
          gun_pixels_used++;
        }
    }

    total_pixels_used = man_pixels_used + sword_pixels_used + gun_pixels_used;
}

void Generator:: show_sel()
{
     gFont = TTF_OpenFont( "font2.ttf", 14 );
    SDL_Color textColor3 = { 163, 163, 163 };
    bar_prompt.loadFromRenderedText( "Customise your character", textColor3 );

    if(yPosition == 2)
    {
        bar_prompt.render(140, 55);
    }

    if(xPosition == 1 && yPosition == 2)
        sel.render(150,132);
    else if(xPosition == 3 && yPosition == 2)
        sel.render(357,132);
    else if(xPosition == 5 && yPosition == 2)
        sel.render(569,132);
    else if(xPosition == 7 && yPosition == 2)
        sel.render(786,130);
    else if(xPosition == 1 && yPosition == 1)
        sel7.render(150, 80);
    else if(xPosition == 3 && yPosition == 1)
        sel7.render(357, 80);
    else if(xPosition == 5 && yPosition == 1)
        sel7.render(569, 80);
    else if(xPosition == 7 && yPosition == 1)
        sel7.render(786, 80);
    else if(xPosition == 2 && yPosition == 1)
        sel7.render(220, 80);
    else if(xPosition == 4 && yPosition == 1)
        sel7.render(427, 80);
    else if(xPosition == 6 && yPosition == 1)
        sel7.render(639, 80);
    else if(xPosition == 8 && yPosition == 1)
        sel7.render(856, 80);
    else if(xPosition == 9 && yPosition == 2)
        sel7.render(956, 170);


    else if(yPosition == 3)
    {
        sel3.render(149, 330);
        SDL_Color textColor3 = { 163, 10, 10 };
        bar_prompt.loadFromRenderedText( "Press D to add pixels or A to remove", textColor3 );
        bar_prompt.render(260, 300);
    }
    else if(yPosition == 4)
    {
        sel4.render(149, 409);
        textColor3 = { 10, 133, 10 };
        bar_prompt.loadFromRenderedText( "Press D to add pixels or A to remove", textColor3 );
        bar_prompt.render(260, 380);
    }
    else if(yPosition == 5)
    {
        sel4.render(149, 498);
        bar_prompt.loadFromRenderedText( "Press D to add pixels or A to remove", textColor3 );
        bar_prompt.render(260, 466);
    }
    else if(yPosition == 6)
    {
        sel4.render(149, 582);
        bar_prompt.loadFromRenderedText( "Press D to add pixels or A to remove", textColor3 );
        bar_prompt.render(260, 552);
    }
    else if(yPosition == 7)
        sel2.render(865, 561 );

    gFont = TTF_OpenFont( "font2.ttf", 24 );
    std::stringstream ss1;
    ss1 << pixels_left;
    SDL_Color textColor2 = { 163, 163, 163 };
    pLeft.loadFromRenderedText( ss1.str(), textColor2 );
    pLeft.render(950, 35);
}

void Generator:: show_stats()
{
    if(xPosition == 1 && yPosition == 1)
    {
        readfile3.open("saves/1/info.map");
        saveNum = 1;
    }

    if(xPosition == 2 && yPosition == 1)
    {
        readfile3.open("saves/2/info.map");
        saveNum = 2;
    }

    if(xPosition == 3 && yPosition == 1)
    {
        readfile3.open("saves/3/info.map");
        saveNum = 3;
    }

    int roomNum = 0;
    int date = 0;
    int month = 0;
    int year = 0;
    int hour = 0;
    int minute = 0;
    int seconds = 0;
    int DisplaytotalHour = 0;
    int DisplaytotalMin = 0;
    int DispalytotalSec = 0;
    int pixels = 0;


    readfile3 >> roomNum;
    readfile3 >> date;
    readfile3 >> month;
    readfile3 >> year;
    readfile3 >> hour;
    readfile3 >> minute;
    readfile3 >> seconds;
    readfile3 >> DisplaytotalHour;
    readfile3 >> DisplaytotalMin;
    readfile3 >> DispalytotalSec;
    readfile3 >> pixels;
    readfile3.close();


    gFont = TTF_OpenFont( "font2.ttf", 24 );
    std::stringstream ss1;
    SDL_Color textColor2 = { 163, 163, 163 };
    if(date < 10)
        ss1 << "0";
    ss1 << date << "/";
    statistics.loadFromRenderedText( ss1.str(), textColor2 );
    statistics.render(560, 276);

    std::stringstream ss2;
    if(month < 10)
        ss2 << "0";
    ss2 << month << "/";
    statistics.loadFromRenderedText( ss2.str(), textColor2 );
    statistics.render(610, 276);

    std::stringstream ss3;
    ss3 << year;
    statistics.loadFromRenderedText( ss3.str(), textColor2 );
    statistics.render(660, 276);

    std::stringstream ss4;
    if(hour < 10)
        ss4 << "0";
    ss4 << hour << ":";
    statistics.loadFromRenderedText( ss4.str(), textColor2 );
    statistics.render(550, 323);

    std::stringstream ss5;
    if(minute < 10)
        ss5 << "0";
    ss5 << minute << ":";
    statistics.loadFromRenderedText( ss5.str(), textColor2 );
    statistics.render(590, 323);

    std::stringstream ss6;
    if(seconds < 10)
        ss6 << "0";

    ss6 << seconds;
    statistics.loadFromRenderedText( ss6.str(), textColor2 );
    statistics.render(630, 323);

    std::stringstream ss7;
    ss7 << pixels;
    statistics.loadFromRenderedText( ss7.str(), textColor2 );
    statistics.render(625, 433);



    std::stringstream ss8;
    if(DisplaytotalHour < 10)
        ss8 << "0";
    ss8 << DisplaytotalHour << ":";
    statistics.loadFromRenderedText( ss8.str(), textColor2 );
    statistics.render(610, 377);

    std::stringstream ss9;
    if(DisplaytotalMin < 10)
        ss9 << "0";
    ss9 << DisplaytotalMin << ":";
    statistics.loadFromRenderedText( ss9.str(), textColor2 );
    statistics.render(650, 377);

    std::stringstream ss10;
    if(DispalytotalSec < 10)
        ss10 << "0";
    ss10 << DispalytotalSec;
    statistics.loadFromRenderedText( ss10.str(), textColor2 );
    statistics.render(690, 377);


}

void Generator:: show_sel2()
{
    gFont = TTF_OpenFont( "font2.ttf", 14 );
    SDL_Color textColor3 = { 163, 163, 163 };
    bar_prompt.loadFromRenderedText( "Customise your character", textColor3 );

    if(yPosition == 1)
    {
        bar_prompt.render(140, 105);
    }

    if(xPosition == 1 && yPosition == 1)
        sel.render(220,153);
    else if(xPosition == 2 && yPosition == 1)
        sel.render(428,153);
    else if(xPosition == 3 && yPosition == 1)
        sel.render(642,153);
    else if(xPosition == 4 && yPosition == 1)
        sel.render(857,151);

    else if(yPosition == 2)
        sel2.render(505, 362 );
    else if(yPosition == 3)
        sel4.render(477, 450 );
    else if(yPosition == 4)
        sel3.render(462, 536 );



    gFont = TTF_OpenFont( "font2.ttf", 24 );
    std::stringstream ss1;
    ss1 << pixels_left;
    SDL_Color textColor2 = { 163, 163, 163 };
    pLeft.loadFromRenderedText( ss1.str(), textColor2 );
    pLeft.render(950, 35);
}

void Generator:: show_sel4()
{


    if(xPosition == 1)
        sel4.render(476, 125 );

    else if(xPosition == 2)
        sel4.render(476, 229 );

    else if(xPosition == 3)
        sel4.render(475, 336 );

    else if(xPosition == 4)
        sel4.render(475, 440 );

    gFont = TTF_OpenFont( "font2.ttf", 24 );
    std::stringstream ss1;
    ss1 << pixels_left;
    SDL_Color textColor2 = { 163, 163, 163 };
    pLeft.loadFromRenderedText( ss1.str(), textColor2 );
    pLeft.render(950, 35);
}

void Generator:: show_sel5()
{

    selection.loadFromFile( "select9.png");

    if(yPosition == 2)
        selection.render(188, 413 );

    else if(xPosition == 1 && yPosition == 1)
        selection.render(184, 51 );

    else if(xPosition == 2 && yPosition == 1)
        selection.render(460, 51 );

    else if(xPosition == 3 && yPosition == 1)
        selection.render(742, 51 );

}

void Generator :: saveGame()
{
        char test [100];
        char test4 [100];
        char test5 [100];
        char test6 [100];
        char test7 [100];
        stringstream strs;
        strs << saveNum;
        string temp_str = strs.str();
        char* char_type = (char*) temp_str.c_str();

    //-------------------------------------------


        char *test2 = char_type;

        strcpy(test, "saves/");
        readfile3.open("lazy.map");
        strcat(test, test2);
        newfile3.open(strcat( test , "/stand.map"));

        char ch;
        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        strcpy(test4, "saves/");
        readfile3.open("lazyA.map");
        strcat(test4, test2);
        newfile3.open(strcat( test4 , "/run.map"));

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        strcpy(test6, "saves/");
        readfile3.open("lazyB.map");
        strcat(test6, test2);
        newfile3.open(strcat( test6 , "/melee.map"));

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        strcpy(test5, "saves/");
        readfile3.open("lazyU.map");
        strcat(test5, test2);
        newfile3.open(strcat( test5 , "/bullet.map"));

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();


        strcpy(test7, "saves/");
        strcat(test7, test2);
        newfile3.open(strcat( test7 , "/info.map"));

        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );
        int temp = 0;

        int currHour = now->tm_hour;
        int currMin = now->tm_min;
        int currSec = now->tm_sec;
        int currDate = now->tm_mday;


        if(currDate > StartingDate)
        {
            currHour += 24;
        }


        totalSec += (currSec - StartingSec);
        StartingSec = currSec;
        if(totalSec < 0)
        {
            totalSec = 60 + totalSec;
            currMin -= 1;
        }

        else if(totalSec >= 60)
        {
            totalSec = totalSec - 60;
            currMin += 1;
        }

        totalMin += (currMin - StartingMin);
        StartingMin = currMin;
        if(totalMin < 0)
        {
            totalMin = 60 + totalMin;
            currHour -= 1;
        }

        if(totalMin >= 60)
        {
            totalMin = totalMin - 60;
            currHour += 1;
        }


        totalHour += (currHour - StartingHour);
        StartingHour = currHour;
        if(Level == 222)
        {
            generatorNum = 1;
        }

        else if(Level == 528)
        {
            generatorNum = 2;
        }

        newfile3 << generatorNum << " "
        << now->tm_mday << " "
        << now->tm_mon + 1 << " "
        << now->tm_year + 1900 << " "
        << now->tm_hour << " "
        << now->tm_min << " "
        << now->tm_sec << " "
        << totalHour << " "
        << totalMin << " "
        << totalSec << " "
        << pixel_capacity << " ";



        newfile3.close();


}

void Generator :: saveChar1()
{

    if(!load_out1)
    {
        readfile3.open("lazy.map");
        newfile3.open("slot1.map");

        char ch;
        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyA.map");
        newfile3.open("slotA1.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyB.map");
        newfile3.open("slotB1.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyU.map");
        newfile3.open("slotU1.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }
        readfile3.close();
        newfile3.close();
    }

    else
    {
        readfile3.open("lazy.map");
        newfile3.open("slot2.map");

        char ch;
        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyA.map");
        newfile3.open("slotA2.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyB.map");
        newfile3.open("slotB2.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("lazyU.map");
        newfile3.open("slotU2.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }
        readfile3.close();
        newfile3.close();
    }
}


void Generator :: switchChar1()
{

    if(load_out1)
    {
        readfile3.open("slot1.map");
        newfile3.open("lazy.map");

        char ch;
        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotA1.map");
        newfile3.open("lazyA.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotB1.map");
        newfile3.open("lazyB.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotU1.map");
        newfile3.open("lazyU.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }
        readfile3.close();
        newfile3.close();
        load_out1 = false;
    }

    else
    {
        readfile3.open("slot2.map");
        newfile3.open("lazy.map");

        char ch;
        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotA2.map");
        newfile3.open("lazyA.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotB2.map");
        newfile3.open("lazyB.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }

        readfile3.close();
        newfile3.close();

        readfile3.open("slotU2.map");
        newfile3.open("lazyU.map");

        while(!readfile3.eof())
        {
            readfile3.get(ch);
            newfile3<<ch;
        }
        readfile3.close();
        newfile3.close();
        load_out1 = true;
    }
}




bool Generator:: select_path(PlayerStats &stats)
{

    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
            {
                if(yPosition == 1 && xPosition > 1 )
                    xPosition--;

                else if(yPosition == 2  && xPosition > 1)
                    xPosition -= 2;

                else if(yPosition == 7)
                {
                    xPosition = 1;
                    yPosition = 6;
                }
            }
            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT )
            {
                if(yPosition == 1 && xPosition < 8)
                    xPosition++;
                if(yPosition == 2 && xPosition < 9)
                    xPosition += 2;
                else if(yPosition > 2 && yPosition < 7)
                    yPosition = 7;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(yPosition < 6)
                    yPosition++;
                if(xPosition % 2 == 0)
                    xPosition--;
                if(xPosition == 9)
                    xPosition = 1;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(yPosition > 1 && xPosition < 9)
                    yPosition--;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                if(xPosition == 1 && yPosition == 2)
                {
                    mumbo.Create();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;

                }

                else if(xPosition == 3 && yPosition == 2)
                {
                    mumbo.Create2();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 5 && yPosition == 2)
                {
                    mumbo.Create3();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 7 && yPosition == 2)
                {
                    mumbo.Create4();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 1 && yPosition == 7)
                {
                    screen2 = 1;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 1 && yPosition == 1)
                {
                    cs.run(1, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    cs.run(2, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 5 && yPosition == 1)
                {
                    cs.run(3, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 7 && yPosition == 1)
                {
                    cs.run(4, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    cs.run(1, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    cs.run(2, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 6 && yPosition == 1)
                {
                    cs.run(3, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 8 && yPosition == 1)
                {
                    cs.run(4, true);
                    xPosition = 1;
                    yPosition = 1;
                }


                else if(xPosition == 9 && yPosition == 2)
                {
                    switchChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                conv.construct();
                loadImages();

            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_B)
            {
                if(yPosition == 3 && xPosition == 1 && stats.maxHealth < 640 && pixels_left >= 10)
                {
                    stats.maxHealth += 10;
                    health_pixels += 10;
                }

                else if(yPosition == 4 && xPosition == 1 && stats.maxEnergy < 400 && pixels_left >= 10)
                {
                    stats.maxEnergy += 10;
                    energy_pixels += 10;
                }

                else if(yPosition == 5 && xPosition == 1 && swordStr < 30 && pixels_left >= 30)
                {
                    swordStr++;
                    sword_pixels += 30;
                }

                else if(yPosition == 6 && xPosition == 1 && gunStr < 30 && pixels_left >= 30)
                {
                    gunStr++;
                    stat2_pixels += 30;
                }
            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_X)
            {
                if(yPosition == 3 && xPosition == 1 && stats.maxHealth > 120)
                {
                    stats.maxHealth -= 10;
                    health_pixels -= 10;
                }

                else if(yPosition == 4 && xPosition == 1 && stats.maxEnergy > 0)
                {
                    stats.maxEnergy -= 10;
                    energy_pixels -= 10;
                }

                else if(yPosition == 5 && xPosition == 1 && swordStr > 2)
                {
                    swordStr--;
                    sword_pixels -= 30;
                }

                else if(yPosition == 6 && xPosition == 1 && gunStr > 2)
                {
                    gunStr--;
                    stat2_pixels -= 30;
                }

            }


        }

        if( event.type == SDL_KEYDOWN )
        {

            if( event.key.keysym.sym == SDLK_LEFT )
            {
                if(yPosition == 1 && xPosition > 1 )
                    xPosition--;

                else if(yPosition == 2  && xPosition > 1)
                    xPosition -= 2;

                else if(yPosition == 7)
                {
                    xPosition = 1;
                    yPosition = 6;
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT )
            {
                if(yPosition == 1 && xPosition < 8)
                    xPosition++;
                if(yPosition == 2 && xPosition < 9)
                    xPosition += 2;
                else if(yPosition > 2 && yPosition < 7)
                    yPosition = 7;
            }

            else if(event.key.keysym.sym == SDLK_DOWN )
            {
                if(yPosition < 6)
                    yPosition++;
                if(xPosition % 2 == 0)
                    xPosition--;
                if(xPosition == 9)
                    xPosition = 1;
            }

            else if(event.key.keysym.sym == SDLK_UP )
            {
                if(yPosition > 1 && xPosition < 9)
                    yPosition--;
            }

            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(xPosition == 1 && yPosition == 2)
                {
                    mumbo.Create();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;

                }

                else if(xPosition == 3 && yPosition == 2)
                {
                    mumbo.Create2();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 5 && yPosition == 2)
                {
                    mumbo.Create3();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 7 && yPosition == 2)
                {
                    mumbo.Create4();
                    saveChar1();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 1 && yPosition == 7)
                {
                    screen2 = 1;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 1 && yPosition == 1)
                {
                    cs.run(1, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    cs.run(2, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 5 && yPosition == 1)
                {
                    cs.run(3, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 7 && yPosition == 1)
                {
                    cs.run(4, false);
                    saveChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    cs.run(1, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    cs.run(2, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 6 && yPosition == 1)
                {
                    cs.run(3, true);
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 8 && yPosition == 1)
                {
                    cs.run(4, true);
                    xPosition = 1;
                    yPosition = 1;
                }


                else if(xPosition == 9 && yPosition == 2)
                {
                    switchChar1();
                    count_pixels();
                    xPosition = 1;
                    yPosition = 1;
                }

                conv.construct();
                loadImages();

            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_B)
            {
                if(yPosition == 3 && xPosition == 1 && stats.maxHealth < 640 && pixels_left >= 10)
                {
                    stats.maxHealth += 10;
                    health_pixels += 10;
                }

                else if(yPosition == 4 && xPosition == 1 && stats.maxEnergy < 400 && pixels_left >= 10)
                {
                    stats.maxEnergy += 10;
                    energy_pixels += 10;
                }

                else if(yPosition == 5 && xPosition == 1 && swordStr < 30 && pixels_left >= 30)
                {
                    swordStr++;
                    sword_pixels += 30;
                }

                else if(yPosition == 6 && xPosition == 1 && gunStr < 30 && pixels_left >= 30)
                {
                    gunStr++;
                    stat2_pixels += 30;
                }
            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_X)
            {
                if(yPosition == 3 && xPosition == 1 && stats.maxHealth > 120)
                {
                    stats.maxHealth -= 10;
                    health_pixels -= 10;
                }

                else if(yPosition == 4 && xPosition == 1 && stats.maxEnergy > 0)
                {
                    stats.maxEnergy -= 10;
                    energy_pixels -= 10;
                }

                else if(yPosition == 5 && xPosition == 1 && swordStr > 2)
                {
                    swordStr--;
                    sword_pixels -= 30;
                }

                else if(yPosition == 6 && xPosition == 1 && gunStr > 2)
                {
                    gunStr--;
                    stat2_pixels -= 30;
                }

            }


        }

    }

    return 0;

}

bool Generator :: select_path3()
{
    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
            {

                if(yPosition == 1 && xPosition > 1)
                    xPosition--;
            }
            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT )
            {
                if(yPosition == 1 && xPosition < 4)
                    xPosition++;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(yPosition < 4)
                    yPosition++;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(yPosition > 1)
                    yPosition--;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                if(xPosition == 1 && yPosition == 1)
                {
                    mumbo.Create();
                    saveChar1();
                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    mumbo.Create2();
                    saveChar1();
                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    mumbo.Create3();
                    saveChar1();
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    mumbo.Create4();
                    saveChar1();
                }

                else if(yPosition == 2)
                {
                    return 1;
                }

                else if(yPosition == 3)
                {
                    load_game = true;
                    return 1;
                }

                else if(yPosition == 4)
                {
                    menu = true;
                    Level = 20;
                    return 1;
                }


                conv.construct();

            }
        }

        if( event.type == SDL_KEYDOWN )
        {

            if( event.key.keysym.sym == SDLK_LEFT )
            {

                if(yPosition == 1 && xPosition > 1)
                    xPosition--;
            }
            else if(event.key.keysym.sym == SDLK_RIGHT )
            {
                if(yPosition == 1 && xPosition < 4)
                    xPosition++;
            }

            else if(event.key.keysym.sym == SDLK_DOWN )
            {
                if(yPosition < 4)
                    yPosition++;
            }

            else if(event.key.keysym.sym == SDLK_UP )
            {
                if(yPosition > 1)
                    yPosition--;
            }

            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(xPosition == 1 && yPosition == 1)
                {
                    mumbo.Create();
                    saveChar1();
                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    mumbo.Create2();
                    saveChar1();
                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    mumbo.Create3();
                    saveChar1();
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    mumbo.Create4();
                    saveChar1();
                }

                else if(yPosition == 2)
                {
                    return 1;
                }

                else if(yPosition == 3)
                {
                    load_game = true;
                    return 1;
                }

                else if(yPosition == 4)
                {
                    menu = true;
                    Level = 20;
                    return 1;
                }


                conv.construct();

            }
        }

    }
}

bool Generator :: select_path4()
{
    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(xPosition < 4)
                    xPosition++;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(xPosition > 1)
                    xPosition--;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                if(xPosition == 1)
                {
                    screen2 = 2;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 2)
                {
                    screen2 = 3;
                    xPosition = 1;
                    yPosition = 2;
                }

                else if(xPosition == 3)
                {
                    return 1;
                }

                else if(xPosition == 4)
                {
                    menu = true;
                    Level = 20;
                    return 1;
                }


                conv.construct();

            }
        }


        if( event.type == SDL_KEYDOWN )
        {

            if(event.key.keysym.sym == SDLK_DOWN)
            {
                if(xPosition < 4)
                    xPosition++;
            }

            else if(event.key.keysym.sym == SDLK_UP)
            {
                if(xPosition > 1)
                    xPosition--;
            }

            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(xPosition == 1)
                {
                    screen2 = 2;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(xPosition == 2)
                {
                    screen2 = 3;
                    xPosition = 1;
                    yPosition = 2;
                }

                else if(xPosition == 3)
                {
                    return 1;
                }

                else if(xPosition == 4)
                {
                    menu = true;
                    Level = 20;
                    return 1;
                }


                conv.construct();

            }
        }


    }
}


bool Generator :: select_path5()
{
    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
            {

                if(xPosition > 1 && yPosition == 1)
                    xPosition--;
            }
            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT )
            {
                if(xPosition < 3 && yPosition == 1)
                    xPosition++;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(yPosition == 1)
                    yPosition++;

            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(yPosition == 2)
                    yPosition--;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                if(yPosition == 2)
                {
                    screen2 = 1;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(yPosition == 1)
                {
                    if(xPosition == 1)
                    {
                        saveNum = 1;
                        saveGame();
                    }

                    else if(xPosition == 2)
                    {
                        saveNum = 2;
                        saveGame();
                    }

                    else if(xPosition == 3)
                    {
                        saveNum = 3;
                        saveGame();
                    }

                }


                conv.construct();

            }
        }


        if( event.type == SDL_KEYDOWN )
        {

            if( event.key.keysym.sym == SDLK_LEFT )
            {

                if(xPosition > 1 && yPosition == 1)
                    xPosition--;
            }
            else if(event.key.keysym.sym == SDLK_RIGHT )
            {
                if(xPosition < 3 && yPosition == 1)
                    xPosition++;
            }

            else if(event.key.keysym.sym == SDLK_DOWN )
            {
                if(yPosition == 1)
                    yPosition++;

            }

            else if(event.key.keysym.sym == SDLK_UP )
            {
                if(yPosition == 2)
                    yPosition--;
            }

            else if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(yPosition == 2)
                {
                    screen2 = 1;
                    xPosition = 1;
                    yPosition = 1;
                }

                else if(yPosition == 1)
                {
                    if(xPosition == 1)
                    {
                        saveNum = 1;
                        saveGame();
                    }

                    else if(xPosition == 2)
                    {
                        saveNum = 2;
                        saveGame();
                    }

                    else if(xPosition == 3)
                    {
                        saveNum = 3;
                        saveGame();
                    }

                }


                conv.construct();

            }
        }


    }
}

bool Generator :: select_path2()
{
    while( SDL_PollEvent( &event ) )
    {


        if( event.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT )
            {
                if(yPosition == 1 && xPosition > 1 )
                    xPosition--;

                else if(yPosition == 2  && xPosition > 1)
                    xPosition -= 2;

                else if(yPosition == 7)
                {
                    xPosition = 1;
                    yPosition = 6;
                }
            }
            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT )
            {
                if(yPosition == 1 && xPosition < 8)
                    xPosition++;
                if(yPosition == 2 && xPosition < 7)
                    xPosition += 2;
                else if(yPosition > 2 && yPosition < 7)
                    yPosition = 7;
            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_DPAD_DOWN )
            {
                if(yPosition < 6)
                    yPosition++;
                if(xPosition % 2 == 0)
                    xPosition--;
            }

            else if(event.cbutton.button  == SDL_CONTROLLER_BUTTON_DPAD_UP )
            {
                if(yPosition > 1)
                    yPosition--;
            }

            else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
            {
                if(xPosition == 1 && yPosition == 2)
                {
                    mumbo.Create();
                }

                else if(xPosition == 3 && yPosition == 2)
                {
                    mumbo.Create2();
                }

                else if(xPosition == 5 && yPosition == 2)
                {
                    mumbo.Create3();
                }

                else if(xPosition == 7 && yPosition == 2)
                {
                    mumbo.Create4();
                }

                else if(xPosition == 1 && yPosition == 7)
                {
                    return 1;
                }

                else if(xPosition == 1 && yPosition == 1)
                {
                    cs.run(1, false);

                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    cs.run(2, false);

                }

                else if(xPosition == 5 && yPosition == 1)
                {
                    cs.run(3, false);

                }

                else if(xPosition == 7 && yPosition == 1)
                {
                    cs.run(4, false);

                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    cs.run(1, true);
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    cs.run(2, true);
                }

                else if(xPosition == 6 && yPosition == 1)
                {
                    cs.run(3, true);
                }

                else if(xPosition == 8 && yPosition == 1)
                {
                    cs.run(4, true);
                }

                conv.construct();

            }
        }



        if( event.type == SDL_KEYDOWN )
        {

            if( event.key.keysym.sym == SDLK_LEFT )
            {
                if(yPosition == 1 && xPosition > 1 )
                    xPosition--;

                else if(yPosition == 2  && xPosition > 1)
                    xPosition -= 2;

                else if(yPosition == 7)
                {
                    xPosition = 1;
                    yPosition = 6;
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                if(yPosition == 1 && xPosition < 8)
                    xPosition++;
                if(yPosition == 2 && xPosition < 7)
                    xPosition += 2;
                else if(yPosition > 2 && yPosition < 7)
                    yPosition = 7;
            }

            else if(event.key.keysym.sym == SDLK_DOWN )
            {
                if(yPosition < 6)
                    yPosition++;
                if(xPosition % 2 == 0)
                    xPosition--;
            }

            else if(event.key.keysym.sym == SDLK_UP )
            {
                if(yPosition > 1)
                    yPosition--;
            }

            else if(event.key.keysym.sym == SDLK_UP)
            {
                if(xPosition == 1 && yPosition == 2)
                {
                    mumbo.Create();
                }

                else if(xPosition == 3 && yPosition == 2)
                {
                    mumbo.Create2();
                }

                else if(xPosition == 5 && yPosition == 2)
                {
                    mumbo.Create3();
                }

                else if(xPosition == 7 && yPosition == 2)
                {
                    mumbo.Create4();
                }

                else if(xPosition == 1 && yPosition == 7)
                {
                    return 1;
                }

                else if(xPosition == 1 && yPosition == 1)
                {
                    cs.run(1, false);

                }

                else if(xPosition == 3 && yPosition == 1)
                {
                    cs.run(2, false);

                }

                else if(xPosition == 5 && yPosition == 1)
                {
                    cs.run(3, false);

                }

                else if(xPosition == 7 && yPosition == 1)
                {
                    cs.run(4, false);

                }

                else if(xPosition == 2 && yPosition == 1)
                {
                    cs.run(1, true);
                }

                else if(xPosition == 4 && yPosition == 1)
                {
                    cs.run(2, true);
                }

                else if(xPosition == 6 && yPosition == 1)
                {
                    cs.run(3, true);
                }

                else if(xPosition == 8 && yPosition == 1)
                {
                    cs.run(4, true);
                }

                conv.construct();

            }
        }


    }
}




bool Generator:: run(PlayerStats &stats)
{
    bool quit = false;

    loadImages();

    Timer fps;

    count_pixels();

    while( quit == false )
    {
        //Start the frame timer
        fps.start();
        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        loadImages();

        if(screen2 == 1)
        {
            if(select_path4() == 1)
            {

                quit = true;
                rPressed = false;

            }
        }

        if(screen2 == 2)
        {
            if(select_path(stats) == 1)
            {
                quit = true;
                rPressed = false;
            }
        }

        if(screen2 == 3)
        {
            if(select_path5() == 1)
            {
                quit = true;
                rPressed = false;
            }
            show_stats();
        }

        if(screen2 == 2)
            show_sel();
        else if(screen2 == 1)
            show_sel4();
        else if(screen2 == 3)
            show_sel5();

        stat_pixels = health_pixels + sword_pixels + energy_pixels + stat2_pixels;
        pixels_left = pixel_capacity - (man_pixels_used + sword_pixels_used + gun_pixels_used + stat_pixels);

        if(screen2 == 2)
        {
            life.w = stats.maxHealth;
            life_bar.render(152, 332, &life);

            stat.w = swordStr * 10;
            stat_bar.render(152, 500, &stat);

            energy.w = stats.maxEnergy;
            energy_bar.render(151, 411, &energy);

            stat2.w = gunStr * 10;
            stat2_bar.render(152, 584 , &stat2);
        }

        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    stats.health = stats.maxHealth;
    stats.energy = stats.maxEnergy;

    return 0;
}


bool Generator:: run2()
{
    bool quit = false;

    loadImages();

    Timer fps;
    screen2 = 2;

    while( quit == false )
    {
        //Start the frame timer
        fps.start();
        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        loadImages();
        if(select_path2() == true)
        {
            quit = true;
            rPressed = false;
        }
        show_sel();

        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    return 0;
}

bool Generator:: run3()
{
    bool quit = false;

    loadImages2();

    Timer fps;

    count_pixels();

    xPosition = 1;
    yPosition = 1;

    while( quit == false )
    {
        //Start the frame timer
        fps.start();
        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        loadImages2();
        if(select_path3() == true)
        {
            quit = true;
            rPressed = false;
        }
        show_sel2();

        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    return 0;
}

