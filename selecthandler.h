/*
SELECTHandler is the class that handles the creation and processing of SELECT packets.

Contributors:
  Seeky (main documentation)
References:
  http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/SELECT
*/

typedef enum : int32_t {
  SELECT_PUBLIC_VS = 1,
  SELECT_PUBLIC_BATTLE = 2,
  SELECT_FRIEND_VS = 3,
  SELECT_FRIEND_BATTLE = 4
} SELECTRoomType;

typedef struct {
  uint16_t prevFinishPos;
  uint16_t score;
  uint8_t character;
  uint8_t vehicle;
  uint8_t trackVote;
  uint8_t starRank;
} SELECTPlayer; // Total size 0x8

typedef struct {
  uint64_t timeSender;
  uint64_t timeReceiver;
  SELECTPlayer players[2];
  uint32_t selectId;
  uint32_t battleFlags; // MSB is 1 for balloon, 0 for coin, the rest is 1 << (2 * aid) for teams - 1 if red, 0 if blue
  uint8_t aidsBelongingToPlayerIds[12]; // index is player id, value is aid
  uint8_t winningTrack;
  uint8_t phase;
  uint8_t winningVoter;
  uint8_t engineClass; // different enum to racedata
} SELECTPacket; // Total size 0x38

class SELECTHandler {
  static SELECTHandler * sInstance; // 809c2100
  static SELECTHandler * getStaticInstance(); // 8065fe8c
  static void destroyStaticInstance(); // 8065ff60

  SELECTHandler(SELECTRoomType roomType); // 8066076c
  ~SELECTHandler(); // 806607f4
  void allocatePlayerIdsToAids(); // 80662034
  void decideBattleTypeAndTeams(); // 80661934
  void decideEngineClass(); // 80661a5c
  void decideTrack(); // 80661ce8
  void generateSELECTId(); // 80661a14
  uint8_t * getAidsBelongingToPlayerIds(); // 806604cc
  BattleType getBattleType(); // 806604a8, see racedata.h for return type
  int32_t getEngineClass(); // 8066048c, not return type isn't same enum as racedata's
  int32_t getSELECTId(); // 80660470
  int32_t getPlayerCharacter(uint32_t aid, int32_t playerAtConsole); // 806604d4, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters
  SELECTPlayer * getPlayerSection(uint32_t aid, int32_t playerAtConsole); // 806605c4
  int32_t getPlayerStarRank(uint32_t aid, int32_t playerAtConsole); // 8066060c
  int32_t getPlayerTeam(uint32_t aid, int32_t playerAtConsole); // 80660654
  int32_t getPlayerVehicle(uint32_t aid, int32_t playerAtConsole); // 80660524, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles
  int32_t getPlayerVote(uint32_t aid, int32_t playerAtConsole); // 80660574, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
  int32_t getWinningTrack(); // 80660450, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
  int32_t getWinningVoter(); // 80660434
  void importNewRecvPackets(); // 80661078
  void initialiseBuffers(); // 8065ffa4
  void initialiseRecvBuffers(); // 80660a00
  void initialiseRecvBuffer(); // 80660a00
  void initialsePacketSELECTPlayers(SELECTPlayer * players); // 80660bd0
  void initialiseSendBuffer(); // 806608b4
  void prepareSendPacket(uint32_t aid, uint64_t sendTime); // 80661288
  void prepareSendUSERAndSELECTPackets(); // 80660f1c
  void processNewRecvVotes(); // 806614b0
  void setSendPacketPlayerDetails(int32_t character, int32_t vehicle, int32_t trackVote, int32_t playerAtConsole, int32_t starRank); // 80660750

  SELECTRoomType roomType;
  // unknown 0x4-7
  SELECTPacket sendPacket; // outgoing packet
  SELECTPacket recvPackets[12]; // incoming packets
  uint8_t lastSendAid; // aid a SELECT packet was last sent to
  // unknown 0x2e1-2e7
  uint64_t lastSendTime;
  uint64_t lastRecvTimes[12];
  uint64_t delaysFromPredictedRecvTimes[12]; // unsure
  int32_t onTimeRecvCounts[12]; // unsure
  uint32_t aidsWithNewSELECT; // bit flag, 1 for aids unprocessed SELECT packets are received from, index 1 << aid
  uint32_t aidsWithNewRH1; // same but for RACEHEADER1
  uint32_t aidsWithAccurateRaceSettings; // bit flag, 1 for aids agreed with about the settings of the room, index 1 << aid
  uint32_t aidsWithAccurateAidPidMap; // same but for the aid player id map
  uint32_t aidsThatHaveVoted; // same but for the aids that have picked a track
  // unknown 0x3f4-7
} // Total size 0x3f8
