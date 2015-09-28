#ifndef JUMPERHEADER
#define JUMPERHEADER

class Tile;
class Dot;
class weapon;
class sword;
class gun;
class Converter;

class jumper : public enemy
{
    public:
    jumper(int x, int y, int health, int w, int h);

    bool jumping;

    bool isJumping();

    bool direction;

    void move(Tile *tiles[], Dot myDot);

    void run(Dot myDot, Tile *tiles[]);

    void collide();

    void collide_down();

    void lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv);

    bool survey(Dot myDot, Tile *tiles[]);

    void knockBack(Dot myDot);

    void animation(Setup st);

    void show();

    void outWithABang();

    void die();

    bool died;

    bool dead;

};

#endif
