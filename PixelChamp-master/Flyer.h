#ifndef FLYER_H
#define FLYER_H

class Tile;
class Dot;
class weapon;
class sword;
class gun;
class Setup;
class Converter;

class Flyer : public enemy
{

    public:
    Flyer(int x, int y, int health, int w, int h);

    bool home;

    void move(Tile *tiles[], Dot myDot);

    void run(Dot myDot, Tile *tiles[]);

    bool direction;

    void collide();

    void collide_down();

    void lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv);

    bool survey(Dot myDot, Tile *tiles[]);

    void knockBack(Dot myDot);

    void goHome();

    void animation(Setup sp);

    void show();

    void die();

    void outWithABang();


};

#endif
