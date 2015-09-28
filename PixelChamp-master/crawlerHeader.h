#ifndef CRAWLERHEADER
#define CRAWLERHEADER

class Tile;
class Dot;
class weapon;
class sword;
class gun;
class Converter;

class crawler : public enemy
{
    public:
    crawler(int x, int y, int health, int w, int h);

    bool direction;

    void move(Tile *tiles[], Dot myDot);

    void run(Dot myDot, Tile *tiles[]);

    void collide();

    void collide_down();

    void lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv);

    bool survey(Dot myDot, Tile *tiles[]);

    void knockBack(Dot myDot);

    void animation(Setup sp);

    void show();

    void die();

    void outWithABang();
};

#endif
