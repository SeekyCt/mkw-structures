/*
RKNetController is the class that handles the game specific network code (ex. RACE Packets) and controls DWC
A pointer to an instance of this class is stored at 0x809c20d8 PAL
See also http://wiki.tockdom.com/wiki/MKWii_Network_Protocol
*/

typedef struct {
  StatusData statusData; // 8 bytes, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/Server/gpcm.gs.nintendowifi.net#locstring
  // unknown 0x8-b
} RKNetFriend; // Total size 0xc, different to DWC's friend struct

class PacketHolder {
public:
  PacketHolder(uint32_t bufferSize); // 8065a24c PAL
  ~PacketHolder(); // 8065a2ac PAL
  void clear(); // 8065a30c PAL
  void append(void * src, uint32_t len); // 8065a38c PAL

  void * packet; // data buffer pointer
  uint32_t bufferSize; // maximum data size
  uint32_t packetSize; // current data size
} PacketHolder; // Total size 0xc

class SplitRACEPointers {
public:
  SplitRACEPointers(uint32_t bufferSize); // 8065a3dc PAL
  ~SplitRACEPointers(); // 8065a474 PAL
  
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
  // unknown 0x54-57
} RKNetControllerSub; // Total size 0x58

class RKNetController {
public:
  virtual ~RKNetController(); // 8065741c PAL
  RKNetController(void * r4); // 80657004 PAL
  void clearSplitSendPacketHolders(); // 80656f40 PAL
  void combineSplitSendPackets(); // 80657ab0 PAL
  void connectToAnybodyAsync(); // 80659170 PAL
  void connectToGameServerFromGroupId(); // 80659680 PAL
  void connectToWFC(); // 80658b9c PAL
  int getFriendSearchType(int friendNumber); // 80659fa4 PAL
  int getLocalPlayerId(int localPlayerNum); // 80659d58 PAL
  uint32_t getSplitSendPacketsTotalSize(uint32_t aid); // 806580c4 PAL
  void handleError(); // 806581cc PAL
  void resetSubs(); // 80658d3c PAL
  bool isConnectedToAnyone(); // 80656f00 PAL
  void mainLoop(int r4, int r5, int r6); // 80657504 PAL
  void processPlayerDisconnect(uint32_t aid); // 80658990 PAL
  void processRACEPacket(uint32_t aid, void * packet, uint32_t size); // 80659a84 PAL
  void resetAidsBelongingToPlayerIds(); // 80659d20 PAL
  void scheduleShutdown(); // 806561a8 PAL
  bool sendAidNextRACEPacket(uint32_t aid); // 80657fe4 PAL
  void sendPacketsAndUpdateUSER(); // 80657a70 PAL
  void setupGameServer(); // 806595b8 PAL
  void startMatching(); // 80659044 PAL
  void startMainLoop(); // 80655c10 PAL
  void trySendNextRACEPacket(); // 80657e30 PAL
  void updateAidsBelongingToPlayerIds(); // 80659bc0 PAL
  void updateStatusDatas(); // 8065a0b4 PAL
  void updateSubsAndVr(); // 80658de0 PAL
  
  // vtable 808c097c PAL
  // unknown 0x4-1f
  EGG::ExpHeap * expHeap;
  EGG::TaskThread * taskThread;
  // unknown 0x28-0x37
  RKNetControllerSub subs[2];
  // unknown 0xe8-ef
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
  bool friendStatusesHaveUpdates; // true if unprocessed updates have been received
  uint8_t unknown_0x2757
  char profanityCheckResult; // 1 if name is bad
  // unknown 0x2759-275b
  int badWordsNum; // number of bad strings in the profanity check
  // unknown 0x2760-2763
  int vr;
  int br;
  int lastSendBufferUsed[12]; // last full send buffer used for each aid, 0 or 1
  int lastRecvBufferUsed[12][8]; // last recv buffer used for each packet per aid, 1 or0
  int currentSub; // index of the current sub to use, 0 or 1
  uint8_t aidsBelongingToPlayerIds[12]; // index is player id, value is aid
  uint32_t disconnectedAids; // 1 if disconnected, index 1 << aid
  uint32_t disconnectedPlayerIds; // index 1 << playerId
  // unknown 0x2934-29c7
};

void RKNet::userRecvCallback(uint32_t aid, void * packet, uint32_t size); // 806585f4 PAL

void * RKNet::DWCAlloc(int r3, uint32_t size, int alignment); // 80658500 PAL
void RKNet::DWCFree(int r3, void * buffer); // 8065858c PAL
void RKNet::SOAlloc(int r3, void * buffer); // 80658418 PAL
void RKNet::SOFree(int r3, void * buffer); // 80658498 PAL
