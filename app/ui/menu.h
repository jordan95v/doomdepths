#ifndef MENU_H
#define MENU_H

int handle_start_menu(sqlite3 *db);
int handle_death_menu();
int handle_delete_save_menu(sqlite3 *db);
void log(char *message, int line);
void clear(int line);

#endif // MENU_H