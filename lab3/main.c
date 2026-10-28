#include <stdio.h>

#include "macro.h"
#include "monster.h"
#include "army.h"

#define NB_MONSTERS 10

int main() {
  struct monster* monsters[NB_MONSTERS];
  struct army* army = create_army();
  char name[NAME_SIZE];

  for (int i = 0; i < NB_MONSTERS; i++) {
    snprintf(name, NAME_SIZE, "Pikachu-%d", i);
    monsters[i] = create_monster(name, 100);
    add_monster_to_army(army, monsters[i]);
  }

  display_army(army);

  delete_army(army);
  for (int i = 0; i < NB_MONSTERS; i++)
    delete_monster(monsters[i]);

  return 0;
}
