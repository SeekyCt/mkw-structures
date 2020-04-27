class PlayerHolderSub { 
public: 
  ~PlayerHolderSub() // 8021a144 PAL
  PlayerHolderSub() // 8021a0f0 PAL
  
  void * unknown_0x4;
  void * unknown_0x8;
  void * unknown_0xC;
};

class ItemSlotData : public PlayerHolderSub { // 808d27b4 vtable
public:
  virtual ~ItemSlotData(); // 807ba650 PAL

  ItemSlotTableHolder playerChances;
  ItemSlotTableHolder cpuChances;
  ItemSlotTableHolder specialChances;
  undefined * rowRecord;
  undefined * perColumnRowRecords;
  // unknown 0x30-33
  unsigned int[4] unknown_0x34; // can't remember why I thought this was an array, might be wrong
  unsigned int playerCount; // copied from the global variable by constructor
};

typedef struct {
  unsigned int columns;
  short * data;
} ItemSlotTableHolder;
