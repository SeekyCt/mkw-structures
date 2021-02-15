/*
Raceinfo is a class that stores various information about the race and players, as well as handling some RNG

Contributors:
  Seeky (main documentation)
  _tZ (RaceinfoPlayer attributes)
  Kevin (various attributes)
  Leseratte (race finish time attributes)
  stebler (intro timer attribute)
  Melg (battle score attribute)
*/

class GmDataAbstract {
  // vtable
  Raceinfo * raceinfo;
}; // Total size 0x8

class GmDataOnlineVsPlayer {
  GmDataOnlineVsPlayer(); // 80532488
  
  Timer raceFinishTime;
  // unknown 0xc-13
}; // Total size 0x14

class GmDataOnlineVs : GmDataAbstract { // vtable override 808b3928
  // unknown virtual function 1
  virtual updateLocalPlayers(); // 8053fb98
  // unknown virtual function 3
  virtual handlePositionTracking(); // 8053f4a0
  // unknown virtual functions 5-9
  // constructor was inlined
  
  GmDataOnlineVsPlayer players[12];
  RACEHEADER2 sendRH2; // 0x28 bytes
  // unknown 0x120-173
}; // Total size 0x174

class Timer {
  virtual ~Timer(); // 8051c334
  Timer(); // 8051c374
  
  // vtable 808b2d44
  uint16_t minutes;
  uint8_t seconds;
  // padding 0x7
  uint16_t milliseconds;
  // unknown 0xa-b
}; // Total size 0xc

class TimerManager {
  virtual ~TimerManager(); // 805376e0
  virtual reset(); // 80535864
  virtual update(); // 80535904
  // constructor was inlined
  
  // vtable 808b34b0
  Timer timers[3];
  Random random;
  // unknown 0x40-4f
}; // Total size 0x50

class RaceinfoRandom : Random {
  RaceinfoRandom(int32_t r4); // 80555514
}; // Total size 0x18

class RaceinfoPlayer {
  virtual ~RaceinfoPlayer(); // 80532f48
  RaceinfoPlayer(uint8_t id, uint32_t param_3); // 80533ed8
  
  // vtable 808b34a4
  // unknown 0x4-7
  uint8_t id;
  uint8_t unknown_0x9; // might be padding
  uint16_t checkpoint;
  float raceCompletion; // fraction of way through a lap (ex. 1.0 is the start of lap 1, 2.5 is half way through lap 2)
  float raceCompletionMax;
  float firstKcpLapCompletion;
  float nextCheckpointLapCompletion;
  float nextCheckpointLapCompletionMax;
  uint8_t position;
  uint8_t respawn;
  uint16_t battleScore;
  uint16_t currentLap;
  uint8_t maxLap;
  uint8_t currentKCP;
  uint8_t maxKCP;
  // unknown 0x29-2b
  uint32_t frameCounter;
  uint32_t framesInFirst;
  // unknow 0x34-37
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
  static Raceinfo * sInstance; // 809bd730
  static Raceinfo * getStaticInstance(); // 80532084
  static void destroyStaticInstance(); // 805320d4

  virtual ~Raceinfo(); // 80532e3c
  Raceinfo(); // 805327a0
  RaceinfoRandom * getRandom(); // 807bd718
  void * setupGamemodeData(Gamemode mode); // 80532188
  bool isStage(uint32_t stage);

  // vtable 808b3350
  RaceinfoRandom * random1;
  RaceinfoRandom * random2;
  RaceinfoPlayer ** players; // pointer to an array of pointers, length is player count
  void * gamemodeData; // different class for each gamemode
  TimerManager * timerManager;
  uint8_t * playerIdInEachPosition; // pointer to an array of player ids, 0 is the id in 1st, 1 is 2nd...
  // unknown 0x1c-1d
  int16_t introTimer;
  uint32_t timer;
  // unknown 0x24-27
  uint32_t stage; // 0: intro camera, 1: countdown, 2: race
  // unknown 0x2c-2d
  bool canCountdownStart; // instantly true offline, needs syncing online
  bool cutSceneMode; // true for modes 11 & 12
  // unknown 0x30-3b
  KMGHolder * kmg;
  // unknown 0x40-4b
}; // Total size 0x4c
