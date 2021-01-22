/*
ITEMHandler is the class that handles the creation and processing of ITEM packets.

Contributors:
    Seeky (main documentation)
References:
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/ITEM
*/

class ITEMHandler {
    static ITEMHandler * sInstance; // 809c20f8
    static ITEMHandler * getStaticInstance(); // 8065c0ec
    static void destroyStaticInstance(); // 8065c368

    ITEMHandler(); // 8065c3a8
    // destructor was inlined
    void update(); // 8065c5e8
    void broadcastStoredItemGet(uint32_t playerId); // 8065c6c0
    void broadcastStoredItemClear(uint32_t playerId); // 8065c74c
    uint32_t getPlayerStoredItem(uint32_t playerId); // 8065d21c
    uint32_t getPlayerMode(uint32_t playerId); // 8065d568
    void importNewPackets(); // 8065dd3c

    ITEMPacket sendPackets[2]; // 0x8 byte structs, 1 for each player in split screen
    ITEMPacket recvPackets[12]; // index player id
    // unknown 0x70-9f
    uint32_t times[12];
    // unknown 0xd0-183
};
