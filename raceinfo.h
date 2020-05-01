/*
Raceinfo is a class that stores various information about the race and players, as well as handling some RNG
A pointer to an instance of this class is stored at 0x809bd730 PAL
Thanks to _tZ and Kevin for help with this
*/

class Random { // I'll move this at some point
  virtual ~Random; // 80555538 PAL
  int next(int limit); // 805555cc PAL
  
  // vtable 808b42e0 PAL
  // 0x4-17 is unknown
}; // Total size 0x18

class RaceinfoRandom : public Random {
  RaceinfoRandom(int param_2);
}; // Total size 0x18

class RaceinfoPlayer {
  ~RaceinfoPlayer(); // 80532f48 PAL
  RaceinfoPlayer(uint8_t id, uint32_t param_3); // 80533ed8 PAL
  
  // vtable 808b34a4 PAL
  // unknown 0x4-7
  uint8_t id;
  uint8_t unknown_0x9; // might be padding
  uint16_t checkpoint;
  float raceCompletion; // fraction of way through a lap (ex. 1.0 is the start of lap 1, 2.5 is half way through lap 2)
  float raceCompletionMax;
  float unknown_0x14;
  float nextCheckpointLapCompletion;
  float nextCheckpointLapCompletionMax;
  uint8_t position;
  // unknown 0x21-24
  uint8_t currentLap;
  uint8_t maxLap;
  uint8_t currentLap;
  uint8_t currentKCP;
  uint8_t maxKCP;
  // unknown 0x29-37
  uint32_t stateFlags;
    /*
      64 is coming last animation?
      32 is finishing the race?
      16 is a dc?
      4 is driving wrong way
      2 is end of race camera
      1 is in race?
    */
   void * unknown_0x3c;
   // 0x40-53 unknown
}; // Total size 0x54

class Raceinfo {
  virtual ~Raceinfo(); // 80532e3c PAL
  Raceinfo(); // 805327a0 PAL
  RaceinfoRandom * getRandom(); // 807bd718 PAL
  void * setupGamemodeData(Gamemode mode); // 80532188 PAL

  //vtable 808b3350 PAL
  RaceinfoRandom random1;
  RaceinfoRandom random2;
  RaceinfoPlayer ** players; // pointer to an array of pointers, length is player count
  void * gamemodeData; // different struct for each gamemode
  void * unknown_0x14;
  uint8_t * playerIdInEachPosition; // pointer to an array of player ids, 0 is the id in 1st, 1 is 2nd...
  uint32_t unknown_0x1c;
  uint32_t timer;
  uint8_t unknown_0x24;
  uint8_t unknown_0x25;
  uint8_t unknown_0x26; // possibly padding
  uint8_t unknown_0x27; // possibly padding
  uint32_t unknown_0x28;
  uint8_t unknown_0x2C;
  uint8_t unknown_0x2D;
  bool offlineRace;
  bool cutSceneMode; // true for modes 11 & 12
  // unknown 0x30-3b
  KMGHolder * kmg;
  // unknown 0x40-43
  float unknown_0x44;
  uint8_t unknown_0x45;
  // unknown 0x49-4b
}; // Total size 0x4c
