/*
SELECTHandler is the class that handles the creation and processing of SELECT packets.
A pointer to an instance of this class is stored at 0x809c2100 PAL
See also http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/SELECT
*/

typedef enum : int {
  SELECT_PUBLIC_VS = 1,
  SELECT_PUBLIC_BATTLE = 2,
  SELECT_FRIEND_VS = 3,
  SELECT_FRIEND_BATTLe = 4
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
  SELECTHandler(SELECTRoomType roomType); // 8066076c PAL
  ~SELECTHandler(); // 806607f4 PAL
  void allocatePlayerIdsToAids(); // 80662034 PAL
  void decideBattleTypeAndTeams(); // 80661934 PAL
  void decideEngineClass(); // 80661a5c PAL
  void decideTrack(); // 80661ce8 PAL
  void generateMySELECTId(); // 80661a14 PAL
  uint8_t * getAidsBelongingToPlayerIds(); // 806604cc PAL
  BattleType getBattleType(); // 806604a8 PAL, see racedata.h for return type
  int getEngineClass(); // 8066048c PAL, not return type isn't same enum as racedata's
  int getMySELECTId(); // 80660470 PAL
  int getPlayerCharacter(uint32_t aid, int playerAtConsole); // 806604d4 PAL, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters
  SELECTPlayer * getPlayerSection(uint32_t aid, int playerAtConsole); // 806605c4 PAL
  int getPlayerStarRank(uint32_t aid, int playerAtConsole); // 8066060c PAL
  int getPlayerTeam(uint32_t aid, int playerAtConsole); // 80660654 PAL
  int getPlayerVehicle(uint32_t aid, int playerAtConsole); // 80660524 PAL, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles
  int getPlayerVote(uint32_t aid, int playerAtConsole); // 80660574 PAL, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
  int getWinningTrack(); // 80660450 PAL, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
  int getWinningVoter(); // 80660434 PAL
  void importNewRecvPackets(); // 80661078 PAL
  void initialiseBuffers(); // 8065ffa4 PAL
  void initialiseRecvBuffers(); // 80660a00 PAL
  void initialiseRecvBuffer(); // 80660a00 PAL
  void initialsePacketSELECTPlayers(SELECTPlayer * players); // 80660bd0 PAL
  void initialiseSendBuffer(); // 806608b4 PAL
  void prepareSendPacket(uint32_t aid, uint64_t sendTime); // 80661288 PAL
  void prepareSendUSERAndSELECTPackets(); // 80660f1c PAL
  void processNewRecvVotes(); // 806614b0 PAL
  void setSendPacketPlayerDetails(int character, int vehicle, int trackVote, int playerAtConsole, int starRank); // 80660750 PAL

  SELECTRoomType roomType;
  // unknown 0x4-7
  SELECTPacket sendPacket; // outgoing packet
  SELECTPacket recvPackets[12]; // incoming packets
  uint8_t lastSendAid; // aid a SELECT packet was last sent to
  // unknown 0x2e1-2e7
  uint64_t lastSendTime;
  uint64_t lastRecvTimes[12];
  // unknown 0x350-3e7
  uint32_t aidsWithAccurateRaceSettings; // bit flag, 1 for aids agreed with about the settings of the room, index 1 << aid
  uint32_t aidsWithAccurateAidPidMap; // same but for the aid player id map
  uint32_t aidsThatHaveVoted; // same but for the aids that have picked a track
  // unknown 0x3f4-7
} // Total size 0x3f8
