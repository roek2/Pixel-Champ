#ifndef CONVERTERHEADER
#define CONVERTERHEADER
#include <fstream>
#include "bitmap_image.hpp"

struct playerSkin
{
      int red;
      int green;
      int blue;
      int x;
      int y;
      int used;

};

struct ColRect
{

      SDL_Rect box;
      int level;
      int jump;
};

class Converter
{
      public:
      Converter();
      int health;
      void HFlip(std::ifstream &ff, std::ofstream &ff2);
      void PFlip(std::ifstream &ff, std::ofstream &ff2);
      void VFlip(std::ifstream &ff, std::ofstream &ff2);
      void VFlipGun(std::ifstream &ff, std::ofstream &ff2);
      bitmap_image makeBitmap(std::ifstream &ff);
      bitmap_image makeWeaponBitmap(std::ifstream &ff);
      bitmap_image makeGunBitmap(std::ifstream &ff);
      bitmap_image makeBitmap2(std::ifstream &ff);
      playerSkin pixels[4096 * 2];
      ColRect rects[1364];
      ColRect pixel_array[1364];
      ColRect pixel_array2[1364];
      ColRect pixel_array3[1364];
      ColRect pixel_array4[1364];
      ColRect pixel_array5[1364];
      ColRect pixel_array6[1364];
      ColRect pixel_array7[1364];
      ColRect pixel_array8[1364];
      ColRect pixel_array9[1364];
      ColRect pixel_array10[1364];
      bool construct();
      bool construct_active_array();
      int size;
      int size2;
      int size3;
      int size4;
      int size5;
      int size6;
      int size7;
      int size8;
      int size9;
      int size10;

      int sizeB;
      int size2B;
      int size3B;
      int size4B;
      int size5B;
      int size6B;
      int size7B;
      int size8B;
      int size9B;
      int size10B;
      int widthMaker(int sizes);

      int Check_for_pixels(ColRect pix[], int size);
      bool begin;
      void test(std::ifstream &ff);
};



#endif
