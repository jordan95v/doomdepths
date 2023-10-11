#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "monsters.h"
#include "player.h"
#include "attack.h"
#include "headers.h"

/**
 * Attacks a monster with a random amount of damage based on the player's attack power.
 * The damage is then reduced by the monster's defense and subtracted from the monster's current health.
 * The player's attack count is also decremented by 1.
 *
 * @param monster A pointer to the monster being attacked.
 * @param player A pointer to the player attacking the monster.
 */
void attack_monster(Monster *monster, Player *player)
{
    int damage = rand() % (player->attack_power + 1) + 50;
    int total_damage = damage - monster->defense;
    if (total_damage < 0)
        total_damage = 0;
    monster->current_health -= total_damage;
    player->attack_left--;
    printf("You dealt %d damage to %s !", total_damage, monster->name);
}

/**
 * Manages the player's attack on monsters.
 *
 * @param monsters The Monsters struct containing the array of monsters.
 * @param player The Player struct containing the player's information.
 */
void manage_player_attack(Monsters *monsters, Player *player)
{
    // Reads user input to select a monster to attack.
    char user_input;
    while (true)
    {
        if (read(STDIN_FILENO, &user_input, 1) == 1)
        {
            GOTO_LOG;
            if (user_input == '0' + monsters->count + 1)
                return;
            else if (user_input < '1' || user_input > '0' + monsters->count)
                continue;
            else
            {
                // Checks if the player has any attack left.
                if (player->attack_left == 0)
                {
                    printf("You have no attack left !");
                    return;
                }
                // Attacks the selected monster.
                int choice = atoi(&user_input);
                Monster *monster = monsters->monsters[choice - 1];
                attack_monster(monster, player);
                if (monster->current_health <= 0)
                    remove_monster(monsters, monster);
                break;
            }
        }
    }
}

void attack_player(Player *player, Monster *monster)
{
    int damage = rand() % (monster->max_attack + 1) + monster->min_attack;
    int total_damage = damage;
    // if (total_damage < 0)
    //     total_damage = 0;
    player->current_health -= total_damage;
    SAVE_CURSOR;
    GOTO_LOG;
    printf("%s dealt %d damage to you ! Press a key to continue", monster->name, total_damage);
    print_player_stats(player);
    RESTORE_CURSOR;
    fflush(stdout);

    char user_input;
    if (read(STDIN_FILENO, &user_input, 1) == 1)
        return;
}