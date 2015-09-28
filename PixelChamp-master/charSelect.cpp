#include "SDL.h"
#include <fstream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "baseHeader.h"
#include "generatorHeader.h"
#include "timerHeader.h"
#include "charSelect.h"
#include "converterHeader.h"
#include "LTextureHeader.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

ifstream readfile;
ofstream newfile;

SDL_Event event2;
LTexture Select1;
LTexture Select2;
LTexture Select3;
LTexture Select4;
LTexture Select5;
LTexture Select6;
LTexture Select7;
LTexture Select8;
LTexture Select9;
LTexture Select10;
LTexture Select11;
LTexture Select12;
extern LTexture Selector;
LTexture char_sel;
extern SDL_Renderer* gRenderer;
extern int FRAMES_PER_SECOND;
int xSelect_position = 1;
int ySelect_position = 1;
extern LTexture Sel5;
int page_number = 0;
extern Converter conv;
extern bool CHARDEBUG;
extern int test_failures;
extern int test_success;

bool CharSelect :: loadCharChoice(int type)
{
    test_success = 0;
    test_failures = 0;

    Selector.render(0,0);
    char test[100];

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select1.loadFromFile( strcat(test, "/images/char1.bmp"));
    Select1.render(216, 32);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select2.loadFromFile( strcat(test, "/images/char5.bmp"));
    Select2.render(216, 215);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select3.loadFromFile( strcat(test, "/images/char9.bmp"));
    Select3.render(216, 395);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select4.loadFromFile(strcat(test, "/images/char2.bmp"));
    Select4.render(424, 32);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select5.loadFromFile(strcat(test, "/images/char6.bmp"));
    Select5.render(424, 215);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select6.loadFromFile(strcat(test, "/images/char10.bmp"));
    Select6.render(424, 395);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select7.loadFromFile(strcat(test, "/images/char3.bmp"));
    Select7.render(638, 32);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select8.loadFromFile(strcat(test, "/images/char7.bmp"));
    Select8.render(638, 215);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select9.loadFromFile(strcat(test, "/images/char11.bmp"));
    Select9.render(638, 395);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select10.loadFromFile(strcat(test, "/images/char4.bmp"));
    Select10.render(853, 32);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select11.loadFromFile(strcat(test, "/images/char8.bmp"));
    Select11.render(853, 215);

    test = {{}};

    if(type == 1)
        strcpy(test, "stand");
    else if(type == 2)
        strcpy(test, "run");
    else if(type == 3)
        strcpy(test, "melee");
    else
        strcpy(test, "bullet");

    Select12.loadFromFile(strcat(test, "/images/char12.bmp"));
    Select12.render(853, 395);


    if(CHARDEBUG)
    {
        if(Select1.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select2.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select3.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select4.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select5.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select6.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select7.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select8.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select9.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select10.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select11.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }

        if(Select12.getWidth() == 0)
        {
            printf("Character load: Failed\n");
            test_failures++;
        }
        else
        {
            printf("Character load: Success\n");
            test_success++;
        }


    }

    if(CHARDEBUG)
    {
        printf("Char Test Successes:%d\n", test_success);
        printf("Char Test Failed:%d\n", test_failures);
        CHARDEBUG = false;
    }


}

bool CharSelect :: show_select()
{

    if(xSelect_position == 1 && ySelect_position == 1)
        char_sel.render(212,25);
    else if(xSelect_position == 2 && ySelect_position == 1)
        char_sel.render(419,25);
    else if(xSelect_position == 3 && ySelect_position == 1)
        char_sel.render(631,25);
    else if(xSelect_position == 4 && ySelect_position == 1)
        char_sel.render(848,25);
    else if(xSelect_position == 1 && ySelect_position == 2)
        char_sel.render(211,211);
    else if(xSelect_position == 2 && ySelect_position == 2)
        char_sel.render(418,211);
    else if(xSelect_position == 3 && ySelect_position == 2)
        char_sel.render(631,211);
    else if(xSelect_position == 4 && ySelect_position == 2)
        char_sel.render(847,211);
    else if(xSelect_position == 1 && ySelect_position == 3)
        char_sel.render(211,389);
    else if(xSelect_position == 2 && ySelect_position == 3)
        char_sel.render(418,389);
    else if(xSelect_position == 3 && ySelect_position == 3)
        char_sel.render(631,389);
    else if(xSelect_position == 4 && ySelect_position == 3)
        char_sel.render(847,389);
    else
        Sel5.render(147,577);

}

int CharSelect:: select_path(int type, bool save)
{

    while( SDL_PollEvent( &event2 ) )
    {
        if( event2.type == SDL_CONTROLLERBUTTONDOWN )
        {

            if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT && xSelect_position > 1)
            {
                xSelect_position--;
            }

            else if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && xSelect_position < 4)
            {
                xSelect_position++;
            }

            else if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP && ySelect_position > 1)
            {
                ySelect_position--;
            }

            else if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN && ySelect_position < 3)
            {
                ySelect_position++;
            }

            else if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP && ySelect_position == 4)
            {
                ySelect_position--;
            }

            else if( event2.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN && ySelect_position == 3)
            {
                ySelect_position++;
            }

            else if(event2.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                if(ySelect_position == 4)
                    return 1;
                else if(chooseInputFile(type, save) == 1)
                        return 2;
            }
        }
    }

    return 0;
}

bool CharSelect:: chooseInputFile(int type, bool save)
{
    char test[100];
    char test3[100];
    int number = xSelect_position + 4 * (ySelect_position - 1) + (12 * page_number);


    //-------------------------------------------
    stringstream strs;
    strs << number;
    string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();

    //-------------------------------------------


    char *test2 = char_type;
    if(type == 1)
    {
        strcpy(test, "stand");
        strcpy(test3, "stand");
    }
    else if(type == 2)
    {
        strcpy(test, "run");
        strcpy(test3, "run");
    }
    else if(type == 3)
    {
        strcpy(test, "melee");
        strcpy(test3, "melee");
    }
    else if(type == 4)
    {
        strcpy(test, "bullet");
        strcpy(test3, "bullet");
    }

    strcat(test, "/maps/char");
    strcat(test, test2);
    strcat(test, ".map");


    strcat(test3, "/images/char");
    strcat(test3, test2);
    strcat(test3, ".bmp");


    cout << test;

    if(save)
    {
        ifstream load1("lazy.map");
        ifstream load2("lazyA.map");
        ifstream load3("lazyB.map");
        ifstream load4("lazyU.map");
        if(type == 1)
            conv.makeBitmap2(load1).save_image(test3);
        else if(type == 2)
            conv.makeBitmap2(load2).save_image(test3);
        else if(type == 3)
            conv.makeBitmap2(load3).save_image(test3);
        else if(type == 4)
            conv.makeBitmap2(load4).save_image(test3);

        newfile.open(test);
        printf("\n");
        CHARDEBUG = true;
        if(CHARDEBUG)
        {
            if(newfile == NULL)
            {
                printf("failed to load character file\n");
            }
            else
            {
                printf("Succeeded to load character file\n");
            }
            CHARDEBUG = false;
        }
    }
    else
        readfile.open(test);
    copyCharacter(type, save);
    return 1;
}

bool CharSelect:: copyCharacter(int type, bool save)
{
    if(save)
    {
        if(type == 1)
            readfile.open("lazy.map");
        else if(type == 2)
            readfile.open("lazyA.map");
        else if(type == 3)
            readfile.open("lazyB.map");
        else
            readfile.open("lazyU.map");
    }

    else
    {
        if(type == 1)
            newfile.open("lazy.map");
        else if(type == 2)
            newfile.open("lazyA.map");
        else if(type == 3)
            newfile.open("lazyB.map");
        else
            newfile.open("lazyU.map");
    }

    char ch;
    while(!readfile.eof())
    {
        readfile.get(ch);
        newfile<<ch;
    }
    readfile.close();
    newfile.close();
    //getch();
    return 0;
}


int CharSelect:: run(int type, bool save)
{
    bool quit = false;

    Timer fps;
    char_sel.loadFromFile("charSelect.png");

    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        SDL_SetRenderDrawColor( gRenderer, 188, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        loadCharChoice(type);
        int endpoint = select_path(type, save);
        if(endpoint == 1)
            quit = true;
        else if(endpoint == 2)
            return 2;
        else
        show_select();

        SDL_RenderPresent( gRenderer );
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }
    return 0;
}
