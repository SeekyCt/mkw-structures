/*
EVENTHandler is the class that handles the creation and processing of EVENT packets.

Contributors:
    Seeky (main documentation)
References:
    http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/EVENT
*/

typedef enum : uint8_t {
    STATE_FREE, // no data present
    STATE_FULL, // some data present
    STATE_EXPIRED // expired data present
} EVENTEntryState;

typedef struct {
    uint8_t entryHeaders[24]; // see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/EVENT#Event_Types
    uint8_t entryData[0xe0]; // variable-length data for each entry placed back-to-back
} EVENTPacket; // total size 0xf8

typedef struct { // 'Unpacked' version of one entry in the EVENT packet
    uint32_t timestamp;
    uint8_t data[21];
    EVENTEntryState state;
    uint8_t objectNumber; // see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items
    uint8_t action; // see http://wiki.tockdom.com/wiki/MKWii_Network_Protocol/EVENT#Event_Types
    uint8_t dataLength;
    // unknown 0x1d-1f
} EVENTEntry; // total size 0x20

class EVENTHandler {
    static EVENTHandler * sInstance; // 809c20f0
    static EVENTHandler * getStaticInstance(); // 8065b4e8
    static void destroyStaticInstance(); // 8065b600

    EVENTHandler(); // 8065b640
    ~EVENTHandler(); // 8065ba8c
    void update(); // 8065b730
    void addEntry(uint32_t objectId, uint32_t action, void * data, uint32_t dataLength); // 8065b780
    bool doesFreeEntryExist(); // 8065b8d4
    void reset(); // 8065b998, clears all entries
    void freeExpiredSendEntries(); // 8065bacc
    void exportSendEntries(); // 8065bb94, puts send entries into packet buffer in MiscPacketHandler
    void importRecvEntries(); // 8065bce4, parses incoming packets from RKNetController
    void processRecvEntries(); // 8065be40

    bool isPrepared;
    // unknown 0x1-3
    EVENTEntry sendEntries[24];
    EVENTEntry recvEntries[12][24]; // index player id
    uint32_t recvEntryPresences[12][24]; // 0 if empty, 1 if not
    uint32_t freeDataSpaceInSendBuffer; // entryData remaining in the outgoing packet buffer
}; // total size 0x2b88
