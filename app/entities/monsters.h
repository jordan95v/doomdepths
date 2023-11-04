#ifndef DEF_HEADER_MONSTERS
#define DEF_HEADER_MONSTERS

#include "../utils/headers.h"


typedef struct
{
    char *name;
    int current_health;
    int max_health;
    int min_attack;
    int max_attack;
    int defense;
} Monster;

typedef struct
{
    Monster **monsters;
    int count;
} Monsters;


extern Monster *create_monster(char *name, int health, int min_attack, int max_attack, int defense);
extern Monsters *create_random_monster(int count);
extern void destroy_monsters(Monsters *monsters);
extern void print_monsters_list(Monsters *monsters);
extern void remove_monster(Monsters *monsters, Monster *monster);

#endif