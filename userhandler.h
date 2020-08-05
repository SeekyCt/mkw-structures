/*
USERHandler is the class that handles the creation and processing of USER packets.
A pointer to an instance of this class is stored at 0x809c2108 PAL
See also http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/USER
*/

class USERHandler {
  void update(); // 806629c0 PAL
  void prepare(); // 8066284c PAL, wipes all stored data and regenerate outgoing USER packet  
  void createSendPacket(); // 8066300c PAL
  void importRecvPackets(); // 80662ebc PAL

  bool isPrepared; // if false, will call prepare
  // unknown 0x1-7
  USERPacket sendPacket; // outgoing packet, 0xc0 struct, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/USER
  USERPacket recvPackets[12]; // incoming packets, index is aid
  // unknown 0x9c8-9ef
} // Total size 0x9f0
