#include "SDL.h"
#ifndef CHARSELECT
#define CHARSELECT
class CharSelect
{
    public:
        bool loadCharChoice(int type);
        bool show_select();
        int select_path(int type, bool save);
        int run(int type, bool save);
        bool copyCharacter(int type, bool save);
        bool chooseInputFile(int type, bool save);
};

#endif
