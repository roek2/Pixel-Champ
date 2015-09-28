#include "SDL.h"
#include "SDL_image.h"
#include <fstream>
#include <stack>
#include "converterHeader.h"
#include "bitmap_image.hpp"
using namespace std;
int pixelcount = 0;
int pixelcountM = 0;
int pixelcountS = 0;
int pixelcountG = 0;
extern int trueWidth;
extern int trueHeight;
extern int properHeight;
extern bool LAZYDEBUG;
extern int test_failures;
extern int test_success;

Converter :: Converter()
{
   health = 80;
   size = 0;
   size2 = 0;
   size3 = 0;
   size4 = 0;
   size5 = 0;
   size6 = 0;
   size7 = 0;
   size8 = 0;
   size9 = 0;
   size10 = 0;
   begin = false;
}

int Converter :: widthMaker(int sizes)
{
    trueWidth = 0;
    for(int i = 0; i < size; i++)
    {
        if(pixel_array[i].box.x >= trueWidth)
        {
            trueWidth = pixel_array[i].box.x;
        }

        if(pixel_array[i].box.y <= trueHeight)
        {
            if(pixel_array[i].level == 6)
                trueHeight = pixel_array[i].box.y;
        }
    }
    trueHeight = 128 - trueHeight;

    properHeight = 128;
    for(int i = 0; i < size; i++)
    {
        if(pixel_array[i].level == 6)
        {
            if(pixel_array[i].box.y <= properHeight)
            {
                properHeight = pixel_array[i].box.y;
            }
        }
    }


    if(LAZYDEBUG)
    {
        if(trueWidth > 0 && trueWidth < 128)
        {
            printf("Width Generation: Success\n");
        }
        else
        {
            printf("Width Generation: Failed\n");
        }


        if(trueHeight > 0 && trueHeight < 128)
        {
            printf("Height Generation: Success\n");
        }
        else
        {
            printf("Height Generation: Failed\n");
        }
    }
}

void Converter :: HFlip(std::ifstream &map, std::ofstream &map2 )
{
    playerSkin temp;
    int j = 0;
    int newX = 0;
    for(int i = 0; i < 4096 * 4; i++)
    {
       map >> temp.red;
       map >> temp.green;
       map >> temp.x;
       map >> temp.y;
       map >> temp.blue;
       map >> temp.used;

        map2 << temp.red << " ";
        map2 << temp.green << " ";
        map2 << 1270 - temp.x << " ";
        map2 << temp.y << " ";
        map2 << temp.blue << " ";
        map2 << temp.used << " ";
    }

    map2.close();

}

void Converter :: PFlip(std::ifstream &map, std::ofstream &map2 )
{
    playerSkin temp;
    for(int i = 0; i < 4096 * 4; i++)
    {
       map >> temp.red;
       map >> temp.green;
       map >> temp.x;
       map >> temp.y;
       map >> temp.blue;
       map >> temp.used;

       map2 << temp.red << " ";
       map2 << temp.green << " ";
       map2 << temp.y << " ";
       map2 << temp.x << " ";
       map2 << temp.blue << " ";
       map2 << temp.used << " ";
    }

    map2.close();

}

void Converter :: VFlip(std::ifstream &map, std::ofstream &map2 )
{
    std::stack<playerSkin > reverser;
    playerSkin temp;
    int j = 0;
    int newX = 0;
    for(int i = 0; i < 4096 * 4; i++)
    {
       map >> temp.red;
       map >> temp.green;
       map >> temp.x;
       map >> temp.y;
       map >> temp.blue;
       map >> temp.used;
       reverser.push(temp);
    }

    while(!reverser.empty())
    {
       map2 << reverser.top().red << " ";
       map2 << reverser.top().green << " ";
       map2 << reverser.top().x  << " ";
       map2 << reverser.top().y << " ";
       map2 << reverser.top().blue << " ";
       map2 << reverser.top().used << " ";
       reverser.pop();
    }
    map2.close();

    ifstream map3 ( "lazyG.map");
    ofstream map4 ( "lazyH.map");

    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            map3 >> temp.red;
            map3 >> temp.green;
            map3 >> temp.x;
            map3 >> temp.y;
            map3 >> temp.blue;
            map3 >> temp.used;

            map4 << temp.red << " ";
            map4 << temp.green << " ";
            map4 << (j * 10) << " ";
            map4 << (i * 10) << " ";
            map4 << temp.blue << " ";
            map4 << temp.used << " ";
        }

    }
    map4.close();

    ifstream map5 ( "lazyH.map");
    ofstream map6 ( "lazyI.map");
    HFlip(map5, map6);


}

void Converter :: VFlipGun(std::ifstream &map, std::ofstream &map2 )
{
    std::stack<playerSkin > reverser;
    playerSkin temp;
    int j = 0;
    int newX = 0;
    for(int i = 0; i < 4096 * 4; i++)
    {
       map >> temp.red;
       map >> temp.green;
       map >> temp.x;
       map >> temp.y;
       map >> temp.blue;
       map >> temp.used;
       reverser.push(temp);
    }

    while(!reverser.empty())
    {
       map2 << reverser.top().red << " ";
       map2 << reverser.top().green << " ";
       map2 << reverser.top().x  << " ";
       map2 << reverser.top().y << " ";
       map2 << reverser.top().blue << " ";
       map2 << reverser.top().used << " ";
       reverser.pop();
    }
    map2.close();

    ifstream map3 ( "lazyW.map");
    ofstream map4 ( "lazyY.map");

    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            map3 >> temp.red;
            map3 >> temp.green;
            map3 >> temp.x;
            map3 >> temp.y;
            map3 >> temp.blue;
            map3 >> temp.used;

            map4 << temp.red << " ";
            map4 << temp.green << " ";
            map4 << (j * 10) << " ";
            map4 << (i * 10) << " ";
            map4 << temp.blue << " ";
            map4 << temp.used << " ";
        }

    }
    map4.close();

    ifstream map5 ( "lazyY.map");
    ofstream map6 ( "lazyZ.map");
    HFlip(map5, map6);


}




bitmap_image Converter :: makeBitmap(std::ifstream &map)
{
   playerSkin style;
   int p = 0;
   style.x = 0;
   style.y = 0;
   style.red = 0;
   style.green = 0;
   style.blue = 0;
   style.used = 0;
   bitmap_image image(128,128);
   image_drawer draw(image);
   draw.pen_color(0 ,255 ,255);
   for(int j = 0; j < 128; j++)
   {
           draw.pen_width(1);
           draw.vertical_line_segment(0, 128, j);
   }

   for(int i = 0; i <= 4096 * 4; i++)
   {
       map >> style.red;
       map >> style.green;
       map >> style.x;
       map >> style.y;
       map >> style.blue;
       map >> style.used;

       draw.pen_color(style.red ,style.green ,style.blue);
       if(!style.used)
       {
          draw.pen_color(0 ,255 ,255);
       }
       else
       {
            if((style.y/10) % 2 == 0)
            {
                pixels[p].x = style.x/10;
                pixels[p].y = style.y/10;
                p++;
            }
       }
       draw.pen_width(1);
       draw.vertical_line_segment(128, (style.y/10), (style.x/10));




   }
       pixelcount = p;
       pixelcountM = p;
       return image;

}

bitmap_image Converter :: makeWeaponBitmap(std::ifstream &map)
{
   playerSkin style;
   int p = 0;
   style.x = 0;
   style.y = 0;
   style.red = 0;
   style.green = 0;
   style.blue = 0;
   style.used = 0;
   bitmap_image image(128,128);
   image_drawer draw(image);
   draw.pen_color(0 ,255 ,255);
   for(int j = 0; j < 128; j++)
   {
           draw.pen_width(1);
           draw.vertical_line_segment(0, 128, j);
   }

   for(int i = 0; i <= 4096 * 4; i++)
   {
       map >> style.red;
       map >> style.green;
       map >> style.x;
       map >> style.y;
       map >> style.blue;
       map >> style.used;

       draw.pen_color(style.red ,style.green ,style.blue);
       if(!style.used)
       {
          draw.pen_color(0 ,255 ,255);
       }
       else
       {
           if((style.y/10) % 2 == 0)
           {
                pixels[p].x = style.x/10;
                pixels[p].y = style.y/10;
                p++;
           }

       }
       draw.pen_width(1);
       draw.vertical_line_segment(128, (style.y/10), (style.x/10));




   }
       pixelcount = p;
       pixelcountS = p;
       return image;

}


bitmap_image Converter :: makeGunBitmap(std::ifstream &map)
{
   playerSkin style;
   int p = 0;
   style.x = 0;
   style.y = 0;
   style.red = 0;
   style.green = 0;
   style.blue = 0;
   style.used = 0;
   bitmap_image image(128,128);
   image_drawer draw(image);
   draw.pen_color(0 ,255 ,255);
   for(int j = 0; j < 128; j++)
   {
           draw.pen_width(1);
           draw.vertical_line_segment(0, 128, j);
   }

   for(int i = 0; i <= 4096 * 4; i++)
   {
       map >> style.red;
       map >> style.green;
       map >> style.x;
       map >> style.y;
       map >> style.blue;
       map >> style.used;

       draw.pen_color(style.red ,style.green ,style.blue);
       if(!style.used)
       {
          draw.pen_color(0 ,255 ,255);
       }
       else
       {
            if((style.y/10) % 2 == 0)
            {
                pixels[p].x = style.x/10;
                pixels[p].y = style.y/10;
                p++;
            }
       }
       draw.pen_width(1);
       draw.vertical_line_segment(128, (style.y/10), (style.x/10));




   }
       pixelcount = p;
       pixelcountG = p;                                             //dont think of changing, tried and didnt work, needs to be global
       return image;

}



bitmap_image Converter :: makeBitmap2(std::ifstream &map)
{
   playerSkin style;
   style.x = 0;
   style.y = 0;
   style.red = 0;
   style.green = 0;
   style.blue = 0;
   style.used = 0;
   bitmap_image image2(128,128);
   image_drawer draw(image2);
   draw.pen_color(0 ,255 ,255);
   for(int j = 0; j < 128; j++)
   {
           draw.pen_width(1);
           draw.vertical_line_segment(0, 128, j);
   }

   for(int i = 0; i <= 4096 * 4; i++)
   {
       map >> style.red;
       map >> style.green;
       map >> style.x;
       map >> style.y;
       map >> style.blue;
       map >> style.used;

       draw.pen_color(style.red ,style.green ,style.blue);
       if(!style.used)
       {
          draw.pen_color(0 ,255 ,255);
       }
       else
       {

         //   pixels[pixelcount].x = style.x/10;
          //  pixels[pixelcount].y = style.y/10;
          //  pixelcount++;
       }
       draw.pen_width(1);
       draw.vertical_line_segment(128, (style.y/10), (style.x/10));




   }

       return image2;

}

void Converter :: test(std::ifstream &ff)
{

}

bool Converter :: construct()
{
    size = 0;
   size2 = 0;
   size3 = 0;
   size4 = 0;
   size5 = 0;
   size6 = 0;
   size7 = 0;
   size8 = 0;
   size9 = 0;
   size10 = 0;
   test_success = 0;
   test_failures = 0;
   begin = false;

    ifstream inputMap1( "lazy.map");
    ifstream inputMap2( "lazyA.map");
    ifstream inputMap3( "lazyB.map");
    ifstream inputMap4( "lazyB.map");
    ifstream inputMap6( "lazyU.map");
    ifstream inputMap7( "lazyU.map");

    ofstream outputMap1( "lazyC.map");
    ofstream outputMap2( "lazyD.map");
    ofstream outputMap3( "lazyE.map");
    ofstream outputMap4( "lazyG.map");
    ofstream outputMap6( "lazyV.map");
    ofstream outputMap7( "lazyW.map");

    HFlip(inputMap1, outputMap1);
    HFlip(inputMap2, outputMap2);
    PFlip(inputMap3, outputMap3);
    VFlip(inputMap4, outputMap4);
    PFlip(inputMap6, outputMap6);
    VFlipGun(inputMap7, outputMap7);


    ifstream inputMap5( "lazyE.map");
    ofstream outputMap5( "lazyF.map");
    HFlip(inputMap5, outputMap5);


    ifstream inputMap8( "lazyV.map");
    ofstream outputMap8( "lazyX.map");
    HFlip(inputMap8, outputMap8);


    ifstream CharStandMapR( "lazy.map");
    ifstream CharRunMapR( "lazyA.map");
    ifstream CharStandMapL( "lazyC.map");
    ifstream CharRunMapL( "lazyD.map");
    ifstream WeaponMapU( "lazyB.map");
    ifstream WeaponMapL( "lazyE.map");
    ifstream WeaponMapR( "lazyF.map");
    ifstream WeaponMapD( "lazyI.map");
    ifstream GunMapU( "lazyU.map");
    ifstream GunMapL( "lazyV.map");
    ifstream GunMapR( "lazyX.map");
    ifstream GunMapD( "lazyZ.map");

//------------------------------------------------------------------

    if(LAZYDEBUG)
    {
        if(CharStandMapR == NULL)
        {
            printf("X - failed to load CharStandMapR\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load CharStandMapR\n");
            test_success++;
        }

        if(CharRunMapR == NULL)
        {
            printf("X - failed to load CharRunMapR\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load CharRunMapR\n");
            test_success++;
        }

        if(CharStandMapL == NULL)
        {
            printf("X - failed to load CharStandMapL\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load CharStandMapL\n");
            test_success++;
        }

        if(CharRunMapL == NULL)
        {
            printf("X - failed to load CharRunMapL\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load CharRunMapL\n");
            test_success++;
        }

        //-----------------------------------------------


        if(WeaponMapU == NULL)
        {
            printf("X - failed to load WeaponMapU\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load WeaponMapU\n");
            test_success++;
        }

        if(WeaponMapD == NULL)
        {
            printf("X - failed to load WeaponMapD\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load WeaponMapD\n");
            test_success++;
        }

        if(WeaponMapL == NULL)
        {
            printf("X - failed to load WeaponMapL\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load WeaponMapL\n");
            test_success++;
        }

        if(WeaponMapR == NULL)
        {
            printf("X - failed to load WeaponMapR\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load WeaponMapR\n");
            test_success++;
        }

        //---------------------------------------------------

        if(GunMapU == NULL)
        {
            printf("X - failed to load GunMapU\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load GunMapU\n");
            test_success++;
        }

        if(GunMapD == NULL)
        {
            printf("X - failed to load GunMapD\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load GunMapD\n");
            test_success++;
        }

        if(GunMapL == NULL)
        {
            printf("X - failed to load GunMapL\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load GunMapL\n");
            test_success++;
        }

        if(GunMapR == NULL)
        {
            printf("X - failed to load GunMapR\n");
            test_failures++;
        }

        else
        {
            printf("O - Succeeded to load GunMapR\n\n");
            test_success++;
        }

    }

//---------------------------------------------------------------------



    construct_active_array();

    makeBitmap(CharStandMapR).save_image("first_test5.bmp");
    size = Check_for_pixels(pixel_array, size);
    widthMaker(size);

    makeBitmap2(CharRunMapR).save_image("first_test6.bmp");
    makeBitmap(CharStandMapL).save_image("first_test7.bmp");
    makeBitmap2(CharRunMapL).save_image("first_test8.bmp");

    size2 = Check_for_pixels(pixel_array2, size2);

    makeWeaponBitmap(WeaponMapL).save_image("first_test9.bmp");
    size3 = Check_for_pixels(pixel_array3, size3);
    makeWeaponBitmap(WeaponMapR).save_image("first_test10.bmp");
    size4 = Check_for_pixels(pixel_array4, size4);
    makeWeaponBitmap(WeaponMapD).save_image("first_test11.bmp");
    size5 = Check_for_pixels(pixel_array5, size5);
    makeWeaponBitmap(WeaponMapU).save_image("first_test12.bmp");
    size6 = Check_for_pixels(pixel_array6, size6);

    makeGunBitmap(GunMapL).save_image("first_test13.bmp");
    size7 = Check_for_pixels(pixel_array7, size7);
    makeGunBitmap(GunMapR).save_image("first_test14.bmp");
    size8 = Check_for_pixels(pixel_array8, size8);
    makeGunBitmap(GunMapD).save_image("first_test15.bmp");
    size9 = Check_for_pixels(pixel_array9, size9);
    makeGunBitmap(GunMapU).save_image("first_test16.bmp");
    size10 = Check_for_pixels(pixel_array10, size10);


    inputMap1.close();
    inputMap2.close();
    inputMap3.close();
    inputMap4.close();
    inputMap6.close();
    inputMap7.close();

    outputMap1.close();
    outputMap2.close();
    outputMap3.close();
    outputMap4.close();
    outputMap6.close();
    outputMap7.close();

    inputMap5.close();
    outputMap5.close();
    inputMap8.close();
    outputMap8.close();

    CharStandMapR.close();
    CharRunMapR.close();
    CharStandMapL.close();
    CharRunMapL.close();
    WeaponMapU.close();
    WeaponMapL.close();
    WeaponMapR.close();
    WeaponMapD.close();
    GunMapU.close();
    GunMapL.close();
    GunMapR.close();
    GunMapD.close();

    if(LAZYDEBUG)
    {
        printf("\nTest Success: %d\n", test_success);
        printf("\nTest Failures: %d\n", test_failures);
    }

    return true;
}


bool Converter :: construct_active_array()
{
    ColRect complete;
    complete.box.x = 0;
    complete.box.y = 0;
    complete.box.h = 128;
    complete.box.w = 128;

    rects[0] = complete;
    rects[0].level = 1;
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int i = 1;

    while (i <= 1364)
    {
        rects[i].box.x = (complete.box.x + (64 * w));                                 /////yo finish this shit!!!
        rects[i].box.y = (complete.box.y + (64 * x));
        rects[i].box.h = complete.box.h/2;
        rects[i].box.w = complete.box.w/2;
        rects[i].level = 2;
        i++;


        for(int j = 0; j < 4; j ++)
        {
            rects[i].box.x = ((complete.box.x + (64 * w)) + ( 32 * y ));
            rects[i].box.y = ((complete.box.y + (64 * x)) + ( 32 * z ));
            rects[i].box.h = complete.box.h/4;
            rects[i].box.w = complete.box.w/4;
            rects[i].level = 3;
            i++;

            for(int k = 0; k < 4; k ++)
            {
                rects[i].box.x = ((complete.box.x + (64 * w)) + ( 32 * y ) + ( 16 * a ));
                rects[i].box.y = ((complete.box.y + (64 * x)) + ( 32 * z ) + ( 16 * b ));
                rects[i].box.h = complete.box.h/8;
                rects[i].box.w = complete.box.w/8;
                rects[i].level = 4;
                i++;

                for(int m = 0; m < 4; m ++)
                {
                    rects[i].box.x = (((complete.box.x + (64 * w)) + ( 32 * y )) + ( 16 * a ) + ( 8 * c));
                    rects[i].box.y = (((complete.box.y + (64 * x)) + ( 32 * z )) + ( 16 * b ) + (8 * d));
                    rects[i].box.h = complete.box.h/16;
                    rects[i].box.w = complete.box.w/16;
                    rects[i].level = 5;
                    i++;

                    for(int n = 0; n < 4; n ++)
                    {
                        rects[i].box.x = (((complete.box.x + (64 * w)) + ( 32 * y )) + ( 16 * a ) + ( 8 * c) + ( 4 * e)) ;
                        rects[i].box.y = (((complete.box.y + (64 * x)) + ( 32 * z )) + ( 16 * b ) + (8 * d) + ( 4 * f)) ;
                        rects[i].box.h = complete.box.h/32;
                        rects[i].box.w = complete.box.w/32;
                        rects[i].level = 6;
                        i++;

                        if(e == 1 && f == 1)
                        {
                            f = 0;
                            e = 0;
                        }

                        else if(e == 1)
                        {
                            f++;
                            e = 0;
                        }
                        else if(e == 0)
                            e++;

                    }

                    if(c == 1 && d == 1)
                    {
                        d = 0;
                        c = 0;
                    }

                    else if(c == 1)
                    {
                        d++;
                        c = 0;
                    }
                    else if(c == 0)
                        c++;

                }


                if(a == 1 && b == 1)
                {
                    a = 0;
                    b = 0;
                }

                else if(a == 1)
                {
                    b++;
                    a = 0;
                }
                else if(a == 0)
                    a++;

            }


            if(y == 1 && z == 1)
            {
                z = 0;
                y = 0;
            }

            else if(y == 1)
            {
                z++;
                y = 0;
            }
            else if(y == 0)
                y++;

        }

        if(w == 1 && x == 1)
        {
            w = 0;
            x = 0;
        }

        else if(w == 1)
        {
            x++;
            w = 0;
        }
        else if(w == 0)
            w++;

    }

    if(LAZYDEBUG)
    {
        if(rects[i-1].box.w == 4 && rects[i].box.w == 0 && rects[i-1].level == 6 && rects[i].level == 0)
            printf("Created Rect breakdown: Success\n");
        else
            printf("Created Rect breakdown: Failure %d\n");
    }

    return true;

}

int Converter :: Check_for_pixels(ColRect pix[], int sizes)
{
    //int p = 0;                                  //move this out into header + re-name
    int until = 2;
    for(int j = 0; j < 1364; j++)
    {
        for(int i = 0; i < pixelcount; i++)
        {

            if((pixels[i].x >= rects[j].box.x && pixels[i].x < (rects[j].box.x + rects[j].box.w)) && (pixels[i].y >= rects[j].box.y && pixels[i].y < (rects[j].box.y + rects[j].box.h)))
            {

                pix[sizes] = rects[j];
                sizes++;
                i = i + (2 * pixelcount);
            }
        }
    }

    int j = 0;
    pix[0].jump = 1000;

    for(int k = 1; k < sizes; k++)
    {
        for(until = 2; until <= 6; until++)
        {
            if(pix[k].level == until)
            {
                j = k + 1;
                while(pix[j].level != until && j < sizes)
                    j++;
                pix[k].jump = j - k;
                if(j == (sizes - 1))
                    pix[j].jump = 1000;
            }
        }
    }

    if(LAZYDEBUG)
    {
        if(sizes == 0)
            printf("Constructing collision boxes: Failed\n");
        else
            printf("Constructing collision boxes: Success\n");
    }

    return sizes;

}
