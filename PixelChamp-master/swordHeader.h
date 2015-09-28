#ifndef SWORDHEADER
#define SWORDHEADER

class Dot;
class setup;

class sword : public weapon
{

      public:

      sword(int length, int width);

      SDL_Rect get_position(Dot myDot, Setup foo);

      bool launchable;

      void weaponControl();

      void show();

      int attack_damage;

};

#endif
