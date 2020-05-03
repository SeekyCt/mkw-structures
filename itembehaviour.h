/*
ItemBehaviour is a struct containing various information about how an item should behave
An array of these structs exists at 809c36a0 PAL, which is set up by the function 807bcae0 PAL
TheLordScruffy helped with some of the fields of this struct, as well as http://wiki.tockdom.com/wiki/Filesystem/rel/StaticR.rel#Item_behaviour_modifier
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
  uint32_t objectId;
  uint32_t numberOfItems;
  uint32_t unknown_0xc;
  uint8_t unknown_0x10;
  uint8_t padding2[3]; // Ignored when copying to array
  ItemUseType useType;
  void * useFunction; // Item is draggable if this is null
} ItemBehaviour;
// Total size 0x1c
