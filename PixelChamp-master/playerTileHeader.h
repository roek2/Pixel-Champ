#ifndef PLAYERTILEHEADER
#define PLAYERTILEHEADER

class LTexture;

class PlayerTile : public base
{
   private:
    //The attributes of the tile
   // SDL_Rect box

    int le;

    int he;

    int used;

        int colRed;

    int colGreen;

    int colBlue;

    public:
    //Initializes the variables
    PlayerTile( int x, int y, int red, int green, int length, int height, int blue, int used);

   // LTexture *gModulatedTexture;

    //Shows the tile
    SDL_Rect box;
    void show();
    void show2();
    void show3();
    void show4();



    //Get the tile type

    bool chosen;

    bool is_chosen();

    int get_red();

    int get_green();

    int get_length();

    int get_height();

    int get_x();

    int get_y();

    int get_blue();

    int isUsed();

    int isGrabbed;


    //Get the collision box
    SDL_Rect &get_box();
};

#endif
