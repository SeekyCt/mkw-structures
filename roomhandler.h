/*
ROOMHandler is the class that handles the creation and processing of ROOM packets.
A pointer to an instance of this class is at 0x809c20e0 PAL
See also http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/ROOM
*/

typedef enum : int {
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
  ~ROOMHandler(); // 8065b008 PAL
  void clearAidSendPacket(uint32_t aid); // 8065b2ec PAL
  void exportAndImportPackets(); // 8065ad18 PAL
  ROOMPacket getRecvPacket(uint32_t aid); // 8065af64 PAL
  void importPackets(); // 8065b194 PAL
  void init(); // 8065b260 PAL
  void setAllSendPackets(ROOMPacket packet); // 8065ae70 PAL
  void setSendPacket(uint32_t aid, ROOMPacket packet); // 8065af74 PAL
  void tryExportROOMAndUSERPackets(); // 8065b048 PAL

  // unknown 0x0-3
  ROOMRole role;
  ROOMPacket sendPackets[12];
  ROOMPacket recvPackets[12];
  uint8_t lastSendAid;
  // unknown 0x69-6f
  uint64_t lastSendTime;
  // unknown 0x78-7f
};
