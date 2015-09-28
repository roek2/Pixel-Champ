#ifndef WEAPONHEADER
#define WEAPONHEADER

class Dot;

class weapon : public base
{
      protected:
      int le;
      int wi;

      public:

      SDL_Rect box;

      weapon(int length, int width);

      int get_width();

      virtual void weaponControl();

      virtual void show();

      void melee();

      virtual SDL_Rect get_position(Dot myDot);

      bool attack;

      bool hit;

      bool canAttack;

      bool look_up;

      bool look_down;
};

#endif
