#ifndef CHARGERHEADER
#define CHARGERHEADER
  
class Tile;
class Dot;
class weapon;
  
class charger : public enemy
{
    public:
    charger(int x, int y, int health);
           
    void run(Dot myDot, Tile *tiles[]);

};
  
#endif
