#ifndef ENEMYHEADER
#define ENEMYHEADER

class Tile;
class Dot;
class weapon;
class sword;
class gun;
class Setup;
class Particle;
class Converter;
class LTexture;

struct ColRect;

class enemy : public base
{

    public:
    int jump_counter;
    point test;
    enemy(int x, int y, int health, int w, int h);
    enemy();

    Particle *particles[100];
    Particle *particles2[100];
    int he;
    int spawnX;
    int spawnY;

    SDL_Rect box;
    int xVel;
    int yVel;
    bool hurt;
    int hurt_counter;
    bool alive;
    int getSpawnX();
    int getSpawnY();
    int animate_counter;
    int stunCounter;
    int ouch_counter;
    void ouched();
    int get_health();
    int damage_counter;
    int damage_counter2;
    int pain;
    int pain1;
    bool showing_damage1;
    bool showing_damage2;
    int defence;

    bool detect;

    int detect_counter;

    virtual void show();

    virtual void move(Tile *tiles[], Dot myDot);

    void jump();

    bool onGround;

    bool launchable;

    bool touches_wall(Tile *tiles[]);

    bool touches_ground(Tile *tiles[]);

    virtual void animation(Setup test);

    bool touches_ground2(Tile *tiles[]);

    bool touches_left(Tile *tiles[]);

    bool touches_right(Tile *tiles[]);

    virtual void run(Dot myDot, Tile *tiles[]);

    void hit(sword square, Dot myDot, gun *bullets[], Converter conv);

    virtual void knockBack(Dot myDot);

    virtual void airStun();

    void tempvinsibility();

    virtual bool survey(Dot myDot, Tile *tiles[]);

    bool point2wall(Tile *tiles[]);

    virtual void lives(Dot myDot, Tile *tiles[], sword square, gun *bullets[], Converter conv);

    bool test2(ColRect pixel_array6[], int size, SDL_Rect square);

    virtual void collide();

    virtual void die();

    void collatural_damage();

    virtual void outWithABang();

    bool perPixelCollision(sword square, Converter conv);

    bool perPixelCollisionGun(gun square, Converter conv);

    int getXpos();

    int getYpos();

    int box_num;

    int spriteNumber;

    void loadEnemyTiles();

    bool perPC;
    bool perPCG;
    bool dead;

    int type;
 //   LTexture *enemySpriteClip;


};

#endif
