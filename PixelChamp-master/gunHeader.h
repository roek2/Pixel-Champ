#ifndef GUNHEADER
#define GUNHEADER

class Dot;
class enemy;
class Tile;
class Setup;
class Converter;
class Particle;
struct ColRect;

class gun : public weapon
{

      public:

      gun(int length, int width);

      SDL_Rect get_position(Dot myDot, Setup foo);

      Particle *particles[20];

      void weaponControl(Dot myDot);

      void shoot(Dot myDot, enemy *monsters[], Tile *tiles[], Converter conv);

      int project;

      bool shot;

      bool reload;

      int reload_counter;

      int shot_dis;

      bool left;

      bool right;

      int speed;

      int charge;

      void show();

      void power_surge();

      bool perPixel(ColRect pixel_array6[], int size, SDL_Rect box2);

};

#endif
