#ifndef CHARGERHEADER
#define CHARGERHEADER

class Tile;
class Dot;
class weapon;
class sword;
class gun;
class Setup;
class Converter;

class charger : public enemy
{
    public:

    bool direction;
    int counter2;

    bool left_charge;
    bool right_charge;
    int startingX;
    int startingY;
    int charge;
    int animate_counter;
    int animate_counter2;
    bool moving;
    bool angry;
    bool launched;
    bool airStunned;
    int stunAnimCount;
    void knockBack(Dot myDot);
    void airStun();

    int mozey_counter;

    charger(int x, int y, int health, int w, int h);

    void move(Tile *tiles[], Dot myDot);

    void run(Dot myDot, Tile *tiles[]);

    void lives(Dot myDot, Tile *tiles[], sword square, gun *bullets [], Converter conv);

    bool survey(Dot myDot, Tile *tiles[]);

    void collide_left();

    void collide_right();

    void collide_down();

    void mozey();

    void animation(Setup test);

    void launcher();

    void show();

    void die();

    void outWithABang();

};

#endif
