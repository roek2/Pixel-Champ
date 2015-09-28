#ifndef PLAYERSTATSHEADER
#define PLAYERSTATSHEADER

class PlayerStats
{
      public:
      PlayerStats();
      int defence;
      int weight;
      int jump;
      int health;
      int maxHealth;
      int maxEnergy;
      int get_health();
      void set_defence();
      void set_weight();
      void set_jump();
      int energy;
      int get_energy();
};

#endif
