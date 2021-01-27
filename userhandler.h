/*
USERHandler is the class that handles the creation and processing of USER packets.

Contributors:
    Seeky (main documentation)
References:
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/USER
*/

class USERHandler {
    static USERHandler * sInstance; // 809c2108
    static USERHandler * getStaticInstance(); // 80662778
    static void destroyStaticInstance(); // 806627f8

    // constructor and destructor were inlined
    void prepare(); // 8066284c, wipes all stored packets and regenerates outgoing packet  
    void reset(); // 80662944, clears all flags, send packet and received packets, sets prepared to false
    void update(); // 806629c0
    void exportSendPacket(uint32_t aid); // 80662abc, copies the outgoing packet for the specified aid into RKNetController's split send buffers
    void handlePlayerDisconnect(uint32_t aid); // 80662b00, clears flags about them and split sending & receiving buffers in RKNetController  
    void readSaveVr(); // 80662d80, reads versus rating from save data into send packet
    void readSaveBr(); // 80662dc4, reads battle rating from save data into send packet
    void importRecvPackets(); // 80662ebc
    void createSendPacket(); // 8066300c

    bool isPrepared; // if false, will call prepare
    // unknown 0x1-7
    USERPacket sendPacket; // outgoing packet, 0xc0 struct, see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/USER
    USERPacket recvPackets[12]; // incoming packets, index is aid
    // 0x9c8-9db mii related
    // unknown 0x9dc-9df
    // 0x9e0-9eb some bit flags about aids
    // unknown 0x9ec-9ef
} // Total size 0x9f0
