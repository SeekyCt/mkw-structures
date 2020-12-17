/*
Raceinfo is a class that stores various information about the race and players, as well as handling some RNG
A pointer to an instance of this class is stored at 0x809bd730 PAL
Thanks to _tZ and Kevin for help with this, and Leseratte for the race finish time fields
*/

class Random { // I'll move this at some point
  virtual ~Random; // 80555538 PAL
  Random(); // 80555464 PAL
  int next(); // 80555578 PAL
  int nextLimited(int limit); // 805555cc PAL
  
  // vtable 808b42e0 PAL
  // 0x4-17 is unknown
}; // Total size 0x18

class GmDataAbstract {
  // vtable
  Raceinfo * raceinfo;
}; // Total size 0x8

class GmDataOnlineVsPlayer {
  GmDataOnlineVsPlayer(); // 80532488 PAL
  
  Timer raceFinishTime;
  // unknown 0xc-13
}; // Total size 0x14

class GmDataOnlineVs : public GmDataAbstract { // vtable override 808b3928 PAL
  // unknown virtual function 1
  virtual updateLocalPlayers(); // 8053fb98 PAL
  // unknown virtual function 3
  virtual handlePositionTracking(); // 8053f4a0 PAL
  // unknown virtual functions 5-9
  // constructor was inlined
  
  GmDataOnlineVsPlayer players[12];
  RACEHEADER2 sendRH2; // 0x28 bytes
  // unknown 0x120-173
}; // Total size 0x174

class Timer {
  virtual ~Timer(); // 8051c334 PAL
  Timer(); // 8051c374 PAL
  
  // vtable 808b2d44 PAL
  uint16_t minutes;
  uint8_t seconds;
  // padding 0x7
  uint16_t milliseconds;
  // unknown 0xa-b
}; // Total size 0xc

class TimerManager {
  virtual ~TimerManager(); // 805376e0 PAL
  virtual reset(); // 80535864 PAL
  virtual update(); // 80535904 PAL
  // constructor was inlined
  
  // vtable 808b34b0 PAL
  Timer timers[3];
  Random random;
  // unknown 0x40-4f
}; // Total size 0x50

class RaceinfoRandom : public Random {
  RaceinfoRandom(int param_2);
}; // Total size 0x18

class RaceinfoPlayer {
  virtual ~RaceinfoPlayer(); // 80532f48 PAL
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
  // unknown 0x21-23
  uint8_t currentLap;
  uint8_t maxLap;
  uint8_t currentKCP;
  uint8_t maxKCP;
  // unknown 0x29-37
  uint32_t stateFlags; // bit flags:
    /*
      64 is coming last animation?
      32 is finishing the race?
      16 is a dc?
      4 is driving wrong way
      2 is end of race camera
      1 is in race?
    */
  Timer * lapFinishTimes; // array of 12 for... some reason
  Timer * raceFinishTime;
  // 0x44-47 unknown
  ControllerHolder * controllerHolder; // see inputdata.h
  // 0x4c-53 unknown
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
  void * gamemodeData; // different class for each gamemode
  TimerManager * timerManager;
  uint8_t * playerIdInEachPosition; // pointer to an array of player ids, 0 is the id in 1st, 1 is 2nd...
  // unknown 0x1c-1f
  uint32_t timer;
  // unknown 0x24-2d
  bool canCountdownStart; // instantly true offline, needs syncing online
  bool cutSceneMode; // true for modes 11 & 12
  // unknown 0x30-3b
  KMGHolder * kmg;
  // unknown 0x40-4b
}; // Total size 0x4c
