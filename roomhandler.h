/*
ROOMHandler is the class that handles the creation and processing of ROOM packets.

Contributors:
  Seeky (main documentation)
References:
  http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/ROOM
*/

typedef enum : int32_t {
  ROOM_HOST,
  ROOM_GUEST
} ROOMRole;

typedef enum : uint8_t {
  ROOM_START = 1,
  ROOM_REGISTER_FRIEND = 2,
  ROOM_JOIN_MESSAGE = 3,
  ROOM_CHAT_MESSAGE = 4
} ROOMMessageType;
 
typedef struct {
  ROOMMessageType messageType;
  uint16_t param1;
  uint8_t param2;
} ROOMPacket; // Total size 0x4 (often kept in a register rather than pointed to)

class ROOMHandler {
  static ROOMHandler * sInstance; // 8065aa88
  static ROOMHandler * getStaticInstance(); // 809c20e0
  static void destroyStaticInstance(); // 8065ab4c

  ~ROOMHandler(); // 8065b008
  void clearAidSendPacket(uint32_t aid); // 8065b2ec
  void exportAndImportPackets(); // 8065ad18
  ROOMPacket getRecvPacket(uint32_t aid); // 8065af64
  void importPackets(); // 8065b194
  void init(); // 8065b260
  void setAllSendPackets(ROOMPacket packet); // 8065ae70
  void setSendPacket(uint32_t aid, ROOMPacket packet); // 8065af74
  void tryExportROOMAndUSERPackets(); // 8065b048

  // unknown 0x0-3
  ROOMRole role;
  ROOMPacket sendPackets[12];
  ROOMPacket recvPackets[12];
  uint8_t lastSendAid;
  // unknown 0x69-6f
  uint64_t lastSendTime;
  // unknown 0x78-7f
}; // Total size 0x80
