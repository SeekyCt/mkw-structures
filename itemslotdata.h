/*
ItemSlotData is the class that handles data from ItemSlot.bin / ItemSlotTable.slt

Contributors:
  Seeky (main documentation)
  Star (checkSpawnTimer)
References:
  http://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ItemSlot.bin
*/

typedef struct {
  uint32_t columns;
  short * data;
} ItemSlotTableHolder; // Total size 0x8

class ItemSlotData {
  static ItemSlotData * sInstance(); // 809c3670
  static ItemSlotData * getStaticInstance(); // 807ba77c
  static void destroyStaticInstance(); // 807ba814

  virtual ~ItemSlotData(); // 807ba650
  int32_t decideItem(int32_t itemboxSetting, int32_t position, int32_t r6, int32_t r7, void * r8); // 807bb42c
  uint8_t * processTableAndIter(uint8_t * itemTable, ItemSlotTableHolder * tableHolder, bool updateItemsInWheek, bool isSpecialTable); // 807ba9d8, takes a pointer to a raw table in an item slot file, processes the values and writes them to the data field of the table holder, then returns the pointer to the start of the next table
  void scaleTableForPlayerCount(ItemSlotTableHolder * tableHolder); // 807bad20
  void resetLightningTimer(); // 807bb9bc
  void resetBlueShellTimer(); // 807bb9c8, goes unused
  void resetBlooperTimer(); // 807bb9d4
  void resetPowTimer(); // 807bb9e0
  void updateTimers(); // 807bb9ec, also responsible for setting them to their initial values on the first frame
  bool checkSpawnTimer(int32_t objectId, int32_t r5); // 807bb380
  // Always constructed inline
  
  // vtable 808d27b4
  // unknown 0x4-f
  ItemSlotTableHolder playerChances;
  ItemSlotTableHolder cpuChances;
  ItemSlotTableHolder specialChances;
  int32_t * itemsInWheel; // first int32_t is number of items, followed by the item ids (visual only, doesn't stop you pulling other items)
  int32_t * specialBoxItemsInWheel; // a series of lists in same structure as itemsInWheel, one for each column of the special table
  // unknown 0x30-33
  uint32_t itemSpawnTimers[4]; // timers in frames for when an item can next be pulled. 0 = lightning, 1 = blue shell, 2 = blooper, 3 = pow
  uint32_t playerCount; // copied from the global variable by constructor, used to check when the player count changes online
}; // Total size 0x48
