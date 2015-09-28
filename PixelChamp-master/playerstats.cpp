#include "SDL.h"
#include "SDL_image.h"
#include "playerstatsHeader.h"
#include <fstream>
extern int pixelcount;

PlayerStats :: PlayerStats()
{
   defence = 0;
   weight = 0;
   jump = 0;
   health = 200;
   maxHealth = 200;
   maxEnergy = 100;
   energy = 100;
}

void PlayerStats :: set_defence()
{
   defence = (int)pixelcount/250;
}

void PlayerStats :: set_weight()
{
   weight = (int)pixelcount/280;
}

int PlayerStats :: get_health()
{
    return health;
}

int PlayerStats :: get_energy()
{
    return energy;
}
