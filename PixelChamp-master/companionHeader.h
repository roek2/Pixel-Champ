#ifndef COMPANIONHEADER
#define COMPANIONHEADER

class Tile;
class mTile;
class turret;
class Dot;
class weapon;
class Converter;
extern int cutscene;

class companion : public Dot
{

    public:
    companion();
    int get_xVel();
    bool moving;
    void animate(Dot myDot);
    void live( Dot myDot, Tile *tiles[]);
    int jump_counter;
};

#endif
