/*
RKNetController is the class that handles the game specific network code (ex. RACE Packets) and controls DWC

Contributors:
  Seeky (main documentation)
References:
  http://wiki.tockdom.com/wiki/MKWii_Network_Protocol
*/

typedef struct {
  StatusData statusData; // 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
  // unknown 0x8-b
} RKNetFriend; // Total size 0xc, different to DWC's friend struct

class PacketHolder {
  PacketHolder(uint32_t bufferSize); // 8065a24c
  ~PacketHolder(); // 8065a2ac
  void clear(); // 8065a30c
  void append(void * src, uint32_t len); // 8065a38c

  void * packet; // data buffer pointer
  uint32_t bufferSize; // maximum data size
  uint32_t packetSize; // current data size
} PacketHolder; // Total size 0xc

class SplitRACEPointers {
  SplitRACEPointers(uint32_t bufferSize); // 8065a3dc
  ~SplitRACEPointers(); // 8065a474
  
  PacketHolder * header;
  PacketHolder * raceHeader1;
  PacketHolder * raceHeader2;
  PacketHolder * roomSelect;
  PacketHolder * racedata;
  PacketHolder * user;
  PacketHolder * item;
  PacketHolder * event;
}; // Total size 0x20

typedef struct {
  uint8_t playersAtConsole
  // unknown 0x1-3
} ConnectionUserData; // Total size 0x4

typedef struct {
  uint64_t unknown_0x0; // a time for something
  uint32_t connectionCount; // number of consoles connected, including your own
  uint32_t playerCount; // number of players in the room, including yourself
  uint32_t connectedAids; // bit flags, 1 for connected, indexed 1 << aid
  uint32_t directConnectedAids; // bit flags, same as above
  uint32_t groupId; // group id for the room you're in
  uint32_t friendToJoin; // index in your friend roster of who you're joining
  uint8_t localPlayerCount; // number of players at your console
  uint8_t myAid; // aid of your console
  uint8_t hostAid; // aid of the host console
  ConnectionUserData connectionUserDatas[12]; // index is aid
  bool matchingSuspended;
  // unknown 0x54-57
} RKNetControllerSub; // Total size 0x58

typedef enum : int32_t {
  STATE_SHUTDOWN,
  STATE_LOGIN_START,
  STATE_LOGIN_AUTHORISED,
  STATE_LOGIN_FRIENDS_SYNCED,
  STATE_MATCHING,
  STATE_FAILED,
  STATE_ERROR
} RKNetConnectionState;

typedef enum : int32_t {
  SEARCH_VS_WW,
  SEARCH_VS_REGIONAL,
  SEARCH_BT_WW,
  SEARCH_BT_REGIONAL
} RKNetSearchType;

class RKNetController {
  static RKNetController * sInstance; // 809c20d8
  static RKNetController * getStaticInstance(); // 80655b24
  static void destroyStaticInstance(); // 80655bac

  virtual ~RKNetController(); // 8065741c
  RKNetController(void * r4); // 80657004
  void clearSplitSendPacketHolders(); // 80656f40
  void combineSplitSendPackets(); // 80657ab0
  void connectToAnybodyAsync(); // 80659170
  void connectToGameServerFromGroupId(); // 80659680
  void connectToWFC(); // 80658b9c
  int32_t getFriendSearchType(int32_t friendNumber); // 80659fa4
  int32_t getLocalPlayerId(int32_t localPlayerNum); // 80659d58
  uint32_t getSplitSendPacketsTotalSize(uint32_t aid); // 806580c4
  void handleError(); // 806581cc
  void resetSubs(); // 80658d3c
  bool isConnectedToAnyone(); // 80656f00
  void mainLoop(int32_t r4, int32_t r5, int32_t r6); // 80657504
  void processPlayerDisconnect(uint32_t aid); // 80658990
  void processRACEPacket(uint32_t aid, void * packet, uint32_t size); // 80659a84
  void resetAidsBelongingToPlayerIds(); // 80659d20
  void scheduleShutdown(); // 806561a8
  bool sendAidNextRACEPacket(uint32_t aid); // 80657fe4
  void sendPacketsAndUpdateUSER(); // 80657a70
  void setupGameServer(); // 806595b8
  void startMatching(); // 80659044
  void startMainLoop(); // 80655c10
  void trySendNextRACEPacket(); // 80657e30
  void updateAidsBelongingToPlayerIds(); // 80659bc0
  void updateStatusDatas(); // 8065a0b4
  void updateSubsAndVr(); // 80658de0
  
  // vtable 808c097c
  // unknown 0x4-1f
  EGG::ExpHeap * expHeap;
  EGG::TaskThread * taskThread;
  RKNetConnectionState connectionState;
  // unknown 0x2c-0x37
  RKNetControllerSub subs[2];
  RKNetSearchType searchType;
  // unknown 0xec-ef
  SplitRACEPointers * splitSendRACEPackets[2][12]; // split pointers for the outgoing packets, double buffered, indexed by aid
  SplitRACEPointers * splitRecvRACEPackets[2][12]; // split pointers for the incoming packets, double buffered, indexed by aid
  PacketHolder * fullSendPackets[12]; // combined outgoing packets, indexed by aid
  uint64_t lastRACESendTimes[12]; // time when last sent to that aid
  uint64_t lastRACERecvTimes[12]; // time when last received from that aid
  uint64_t RACESendTimesTaken[12]; // last send time minus the time of the send before it
  unit64_t RACERecvTiemsTaken[12]; // last receive time minus the time of the receive before it
  uint8_t lastRACESendAid; // aid a packet was last sent to
  uint8_t fullRecvPackets[12][0x2e0]; // 1 per aid
  // unknown 0x25e1-25e3
  StatusData ownStatusData; // 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
  RKNetFriend friends[30];
  bool friendsListIsChanged; // true if unprocessed changes have happeend
  bool shutdownScheduled; // will cause shutdown of wifi connection on next run of the main loop if true
  bool friendStatusUpdateScheduled; // if true, the main loop will update all friend statuses on the next iteration
  uint8_t unknown_0x2757;
  char profanityCheckResult; // 1 if name is bad
  // unknown 0x2759-275b
  int32_t badWordsNum; // number of bad strings in the profanity check
  // unknown 0x2760-2763
  int32_t vr;
  int32_t br;
  int32_t lastSendBufferUsed[12]; // last full send buffer used for each aid, 0 or 1
  int32_t lastRecvBufferUsed[12][8]; // last recv buffer used for each packet per aid, 1 or0
  int32_t currentSub; // index of the current sub to use, 0 or 1
  uint8_t aidsBelongingToPlayerIds[12]; // index is player id, value is aid
  uint32_t disconnectedAids; // 1 if disconnected, index 1 << aid
  uint32_t disconnectedPlayerIds; // index 1 << playerId
  // unknown 0x2934-29c7
};

void RKNet::userRecvCallback(uint32_t aid, void * packet, uint32_t size); // 806585f4

void * RKNet::DWCAlloc(int32_t r3, uint32_t size, int32_t alignment); // 80658500
void RKNet::DWCFree(int32_t r3, void * buffer); // 8065858c
void * RKNet::SOAlloc(int32_t r3, uint32_t size); // 80658418
void RKNet::SOFree(int32_t r3, void * buffer); // 80658498
