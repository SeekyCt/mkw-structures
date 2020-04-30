/*
ItemSlotData is the class that handles data from ItemSlot.bin / ItemSlotTable.slt
A pointer to an instance of this class is stored at 0x809c3670 PAL
See also http://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ItemSlot.bin
*/

class PlayerHolderSub { // This'll get moved once I figure out what it is properly or write up PlayerHolder info
public: 
  virtual ~PlayerHolderSub(); // 8021a144 PAL
  PlayerHolderSub(); // 8021a0f0 PAL
  
  // vtable 802a2b48 PAL
  void * unknown_0x4;
  void * unknown_0x8;
  void * unknown_0xC;
};

typedef struct {
  unsigned int columns;
  short * data;
} ItemSlotTableHolder;

class ItemSlotData : public PlayerHolderSub {
public:
  virtual ~ItemSlotData(); // 807ba650 PAL
  int decideItem(int itemboxSetting, int position, int r6, int r7, void * r8); // 807bb42c PAL
  byte * processTableAndIter(byte * itemTable, ItemSlotTableHolder tableHolder, int r6, int r7); // 807ba9d8 PAL, takes a pointer to a raw table in an item slot file, processes the values and writes them to the data field of the table holder, then returns the pointer to the start of the next table
  // Always constructed inline
  
  // vtable 808d27b4 PAL
  ItemSlotTableHolder playerChances;
  ItemSlotTableHolder cpuChances;
  ItemSlotTableHolder specialChances;

  // Not too sure about these fields yet, I'll give better names & stuff once I research them more
  undefined * rowRecord; 
  undefined * perColumnRowRecords;
  
  // unknown 0x30-33
  unsigned int[4] unknown_0x34; // can't remember why I thought this was an array, might be wrong
  unsigned int playerCount; // copied from the global variable by constructor, used to check when the player count changes online
};
