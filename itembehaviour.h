/*
ItemBehaviour is a struct containing various information about how an item should behave

Contributors:
  Seeky (main documentation)
  TheLordScruffy (object id field)
References:
  http://wiki.tockdom.com/wiki/Filesystem/rel/StaticR.rel#Item_behaviour_modifier
*/

typedef enum : int {
  ITEMUSE_USE,
  ITEMUSE_FIRE,
  ITEMUSE_TAIL,
  ITEMUSE_CIRCLE
} ItemUseType;

typedef struct {
  uint8_t unknkown_0x0;
  uint8_t unknkown_0x1;
  uint8_t padding[2]; // Ignored when copying to array
  uint32_t objectId; // see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items
  uint32_t numberOfItems;
  uint32_t unknown_0xc;
  uint8_t unknown_0x10;
  uint8_t padding2[3]; // Ignored when copying to array
  ItemUseType useType;
  void * useFunction; // Item is draggable if this is null
} ItemBehaviour; // Total size 0x1c

ItemBehaviour itemBehaviourTable[19]; // 807bcae0, index item id, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items

void setupItemBehaviourTable(); // 807bcae0, copies individual structs from rodata into table
