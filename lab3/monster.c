#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monster.h"

struct monster* create_monster(char* name, int health) {
  struct monster* m = malloc(sizeof(struct monster));
  snprintf(m->name, NAME_SIZE, "%s", name);
  m->health = health;
  return m;
}

void display_monster(struct monster* m) {
  printf("%s (%d hp)\n", m->name, m->health);
}

void delete_monster(struct monster* m) {
  free(m);
}
