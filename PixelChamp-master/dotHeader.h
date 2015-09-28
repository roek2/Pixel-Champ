#ifndef DOTHEADER
#define DOTHEADER

class Tile;
class mTile;
class turret;
class enemy;
class jumper;
class charger;
class PlayerStats;
class Converter;
class Particle;



class Dot : public base
{
    private:
    //The velocity of the dot


    //determines if the player is jumping


    //tells you if the player is on the ground


    //if the player dies, this is where they will respawn
    int respawnX, respawnY;

    public:

        bool onGround;
        bool jump;

        int xVel, yVel;
    //Initializes the variables
    Dot();
        SDL_Rect box;

    PlayerStats *stats;

    //Takes key presses and adjusts the dot's velocity
    void handle_input();

    //Moves the dot
    void move( Tile *tiles[],Converter conv );
    void move2( Tile *tiles[]);

    bool touches_wallA( SDL_Rect box, Tile *tiles[]);

    //checks if the player is touching the ground
    bool touches_groundA(SDL_Rect box, Tile *tiles[]);

    bool touches_ground2A(SDL_Rect box, Tile *tiles[]);

    //check if the player is touching a roof
    bool touches_roofA(SDL_Rect box, Tile *tiles[]);

    //Shows the dot on the screen
    void show();

    //makes the player jump
    void makeJump();

    bool init;

    Particle *particles[20];
    Particle *particles2[20];

    void init_particle();

    //checks if the player has collidided with walls, mtiles or turrets
    bool touches_wall( SDL_Rect box, Tile *tiles[], Converter conv);

    //checks if the player is touching the ground
    bool touches_ground(SDL_Rect box, Tile *tiles[], Converter conv);

    bool touches_ground2(SDL_Rect box, Tile *tiles[], Converter conv);

    //check if the player is touching a roof
    bool touches_roof(SDL_Rect box, Tile *tiles[], Converter conv);

    //checks if a player is touching a tile that kills you
    bool touches_death( SDL_Rect box, Tile *tiles[], Converter conv);

    //checks if you are touching the end of level tile
    bool touches_win(Tile *tiles[] );

    //determines if a player has beaten a level
    bool wins( Tile *tiles[] );

    //determines if a player has died
    bool dies( Tile *tiles[], Converter conv);

    //checks if the player has aquired the time travel device
    bool getTime(SDL_Rect box, Tile *tiles[], bool timeGadget);

    bool is_onGround();

    //Sets the camera over the dot
    void set_camera();

    //sets the resapwn for the character based on the level
    void set_respawn();

    //stops the player when pausing
    void togglePause();

    void dashable();

    void load();

    bool per_pixel(SDL_Rect box, SDL_Rect mon, Converter conv);

    bool knockback(enemy monster, Converter conv);

    int getXpos();

    void part_effect(SDL_Rect box);

    void bounce();

    void double_jump();

    int getYpos();

    void cutscene();

    void dash();

    int dashX;
    int dashY;

    bool airCombo();

    bool second_jump;

    int combo_counter;

    bool turnLeft(Tile *tiles[], Converter conv);
    bool turnRight(Tile *tiles[], Converter conv);
    bool turnL;
    bool turnR;
    bool bigJump;
    bool canJump;

    bool can_dash;
    bool turning;
    //bool dontFall;


};

#endif
