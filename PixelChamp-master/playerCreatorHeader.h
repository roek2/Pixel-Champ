#ifndef PLAYERCREATORHEADER
#define PLAYERCREATORHEADER
#include <fstream>
class PlayerTile;

class PlayerCreator : public base
{
      public:
      PlayerCreator();
      void select_tile( PlayerTile *tiles[], PlayerTile *highlight[]);
      bool put_tile( PlayerTile *tiles[], int red, int green, int length, int height, int blue, int inner_height);
      bool set_tiles( PlayerTile *tiles[],  std::ifstream &ff);
      void save_tiles( PlayerTile *tiles[], std::ofstream &ff );
      int Create();
      int Create2();
      int Create3();
      int Create4();
      bool zoomInAndOut(PlayerTile *tiles[]);
      void clip();
      void draw(PlayerTile *tiles[]);
      void rub(PlayerTile *tiles[]);
      void FillAcc(PlayerTile *tiles[]);
      void Fill(PlayerTile *tiles[], int i);
      void square(PlayerTile *tiles[]);
      void deleteSquare(PlayerTile *tiles[]);
      void selectSquare(PlayerTile *tiles[], PlayerTile *copyTiles[]);
      void pasteSquare(PlayerTile *tiles[], PlayerTile *copyTiles[]);
      void Sel(PlayerTile *tiles[]);
      void setup_buttons();
      bool check_capacity();
      int interface(PlayerTile *tiles[], PlayerTile *copyTiles[]);
      void interface2(PlayerTile *tiles[], PlayerTile *copyTiles[]);
      void copySelect(PlayerTile *tiles[], PlayerTile *copyTiles[]);
      int buttonsClicked();
      void set_palette(PlayerTile *palette[]);
      void select_colour(PlayerTile *palette[]);
};

#endif
