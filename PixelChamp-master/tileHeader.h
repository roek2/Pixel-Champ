#ifndef TILEHEADER
#define TILEHEADER

class Tile : public base
{
    private:
    //The tile type
    int type;

    public:

    SDL_Rect box;
    //Initializes the variables
    Tile( int x, int y, int height, int width, int tileType, int artType );

    //Shows the tile
    void show();

    //Get the tile type
    int get_type();

    int art;

    int get_art();

    bool active;

    //Get the collision box
    SDL_Rect get_box();
};

#endif
