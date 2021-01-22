/*
MiscPacketHandler the creation and processing of various packets.

Contributors:
    Seeky (main documentation)
References:
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/RACEHEADER_2
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/RACEDATA
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/EVENT
*/

class MiscPacketHandler {
    static MiscPacketHandler * sInstance; // 809c1f50
    static MiscPacketHandler * getStaticInstance(); // 80653208
    static void destroyStaticInstance(); // 80653284

    MiscPacketHandler(); // 80653df4
    // destructor was inlined
    void update(); // 80653728
    RACEDATAPacket * getPlayerRACEDATA(uint32_t playerId); // 80653abc
    void setSendRH2(RACEHEADER2Packet * data); // 80653c08
    RACEHEADER2Packet * getPlayerRH2(uint32_t playerId); // 80653cb8 
    void clearSendRH2s(); // 80653d78, clears all RACEHEADER2 packets in the RKNetController split send buffer
    void handlePlayerDisconnect(); // 80653ddc
    void updateAsSpectator(); // 80653f24
    void updateAsRacer(); // 80654150
    uint32_t getAidRH1Timer(uint32_t aid); // 806544a8
    uint32_t getMaxRaceTimerInRoom(); // 806545dc
    void addEVENTEntry(uint32_t objectId, uint32_t action, void * data, uint32_t dataLength); // 8065474c, forwarder to EVENTHandler::sInstance->addEVENTEntry
    bool isPlayerConnected(uint32_t playerId); // 80654820
    bool isPlayerLocal(uint32_t playerId); // 806548a8
    uint32_t playerIdToLocalPlayerIndex(uint32_t playerId); // 80654918, -1 for not local, 0 for split-screen player 1, 1 for player 2
    void processLagFrames(); // 80654b00
    void createSendRH1AndExportRACEDATAAndUSER(); // 80654d08, fills RACEHEADER1, RACEDATA and USEr packets in split send buffer
    void createSendRH1(); // 80655164, fills all RACEHEADER1 packets in split send buffer
    void processRecvPackets(); // 806554a0

    // unknown 0x0
    bool someoneIsLagging; // unsure
    // unknown 0x2-3
    uint32_t aidsWithSelectId; // bit flags, index 1 << aid
    uint32_t aidsWithNewROOMOrSelect; // same index
    // unknown 0xc-f
    uint16_t localLagFrames;
    uint16_t countdownTime; // from 3000
    // unknown 0x14-93
    EVENTPacket sendEVENTBuffer; // 0xf8 struct, see eventhandler.h
    // unknown 0x18c-18f
    uint64_t lastFriendUpdateTime;
    uint32_t playerRH1Timers[12]; // index player id
}; // Total size 0x1c8
