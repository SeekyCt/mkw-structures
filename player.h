/*
PlayerHolder contains most player-specific data during a race

Contributors:
  stebler (main documentation)
  SwareJonge (extra methods and attributes)
  1superchip (extra timer attributes, correcting some signing of types)
References:
  http://wiki.tockdom.com/wiki/BSP_(File_Format)
  http://wiki.tockdom.com/wiki/KartParam.bin
  http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
*/

typedef struct {
  float x, y, z;
} VEC3; // total size 0xc

typedef struct {
  float x, y, z, w;
} VEC4; // total size 0x10

typedef float MAT34[3][4];

class PlayerSub10 {
public:
  virtual ~PlayerSub10(); // 80587b78
  // unknown virtual function 1
  virtual setTurnParams(); // 8057829c
  // unknown virtual functions 3-12
  virtual bool checkWheelie(); // 80589744
  virtual updateTurn(); // 8057a8b4
  virtual updateVehicleSpeed(); // 8057ab68
  // unknown virtual function 16
  virtual updateVehicleRotationVector(float turn); // 8057cf0c
  virtual float getWheelieSoftSpeedLimitBonus(); // 8057c3c8
  virtual updateWheelie(); // 8058758c
  // unknown virtual function 19
  virtual bool canHop(); // 8057da18
  virtual hop(); // 8057da5c
  virtual updateMtCharge(); // 8057ee50
  // unknown virtual function 23
  PlayerSub10(); // 80577fc4
  init(bool unk0, bool unk1); // 805784d4
  update(); // 805788dc
  updateDir(); // 8057a140
  updateAcceleration(); // 8057b9bc
  updateRotation(); // 8057c69c
  updateStandstillBoostRot(); // 8057d1d4
  updateTop(); // 8057d398
  updateManualDrift(); // 8057dc44
  updateAutoDrift(); // 8057e0dc
  applyStartBoost(int frames); // 8058212c
  setInitialPhysicsValues(VEC3 *position, VEC3 *angles); // 80584044
  updateDiving(); // 805869dc

  PlayerPointers *playerPointers;
  // unknown pointers 0x4, 0x8
  // vtable 808b5f60
  float speedMultiplier; // 50cc: 0.8, 100cc: 0.9, 150cc: 1.0
  float baseSpeed;
  float softSpeedLimit;
  // unknown float 0x1c, maybe another speed limit
  float vehicleSpeed;
  float lastSpeed;
  // unknown float 0x28, maybe last speed
  float hardSpeedLimit;
  float acceleration;
  float speedDragMultiplier;
  // unknown VEC3 0x38
  VEC3 top;
  // unknown VEC3 0x50
  VEC3 dir;
  VEC3 lastDir;
  VEC3 vehicleSpeedDir;
  // unknown VEC3 0x80
  VEC3 dirDiff;
  // unknown uint8_t 0x98
  // unknown 0x99 - 0x9b, likely padding
  // unknown floats 0x9c, 0xa0
  // unknown VEC3 0xa4
  float speedRatioCapped; // to 1
  float speedRatio;
  // unknown float 0xb8
  float rotationFactor;
  // unknown floats 0xc0, 0xc4
  // unknown 0xc8 - 0xdf
  VEC3 hopDir;
  // unknown 0xec - 0xf3
  float divingRotation;
  // unknown float 0xf8
  int16_t driftState; // 1: charging mt, 2: mt charged
  int16_t mtCharge;
  int16_t mtCharge2; // second one used by karts
  int16_t mtBoost;
  // unknown 0x104 - 0x10b
  int16_t allMTBoost; // also includes the boost from a SSMT and the start boost
  // unknown uint16_t 0x10e
  int16_t mushroomBoost;
  // unknown uint16_t 0x112
  int16_t trickBoost;
  // unknown uint16_t 0x116
  uint16_t boostType; 
  // unknown 0x11a - 0x11b
  float boostMultiplier; // this gets multiplied with nextspeed which will be the next speed
  float boostAcceleration;
  // unknown 0x124 - 0x147
  uint16_t zipperBoost; // boost that's mostly used on ramps
  // unk uint16_t 0x14a
  uint16_t ssmtCharge;
  // unknown 0x14e - 0x157
  float realTurn;
  float weightedTurn;
  // float playerSize perhaps?
  VEC3 scale;
  // unknown floats 0x170, 0x174, 0x178
  // unknown 0x17c - 0x187
  int16_t mushroomBoost2; // 0x188, another mushroom boost timer
  int16_t starTimer; // 0x18A, timer for Star
  int16_t shockTimer; // 0x18C, used when shocked by KC Zappers, TC, or Shock
  int16_t blooperCharacterInk; // 0x18E, timer for ink on player
  uint8_t field_0x190; // set to 1 when the blooper state is applied
  // unknown 0x191
  int16_t crushTimer; // 0x192, timer for being crushed by Thwomp & Mega
  int16_t MegaTimer; // 0x194, timer for Mega mushroom
  // unknown 0x196 - 0x1C3
  uint16_t zipperBoost2;
  // unknown 0x1C6 - 0x248
  uint32_t drivingDirection; // 0: forwards, 1: braking, 2: waiting on the backwards counter, 3: backwards
  uint16_t backwardsAllowCounter;
  // unknown 0x24e - 0x287
  float rawTurn;
  // unknown 0x28c - 0x293
}; // Total size 0x294

class PlayerSub10Remote : PlayerSub10 {
  // vtable 808b5d90
}; // Total size 0x294

class PlayerSub10RealLocal : PlayerSub10 {
  // vtable 808b5e78
}; // Total size 0x294

class PlayerSub10Bike : PlayerSub10 {
public:
  virtual ~PlayerSub10Bike(); // 80589704
  virtual bool checkWheelie(); // 80588fe0
  virtual updateVehicleRotationVector(float turn); // 80587d68
  virtual getWheelieSoftSpeedLimitBonus(); // 80588324
  virtual updateWheelie(); // 80587d64
  virtual updateMtCharge(); // 80588888
  virtual startWheelie(); // 80588350
  virtual cancelWheelie(); // 805883c4
  // unknown virtual function 26
  PlayerSub10Bike(); // 808b5ee8

  // vtable 808b5ee8
  float turnRotZ;
  // unknown float 0x298
  float turnRotZInc;
  float wheelieRot;
  float maxWheelieRot;
  uint32_t wheelieTimer;
  uint8_t field_0x2AC; // could be a wheelie flag (0 = not in wheelie, 1 = in wheelie), set to 1 when starting wheelie and 0 when ending wheelie?
  // unknown 0x2ad - 0x2B3
  uint16_t wheelietimer2; // from what i know the same as wheelieTimer, but stored as a ushort
  uint16_t wheelieCooldown;
  // unknown 0x2b8 - 0x2bf
  void *turnParams;
}; // Total size 0x2c4

class PlayerSub10BikeRemote : PlayerSub10Bike {
  // vtable 808b5d18
}; // Total size 0x2c4

class PlayerSub10BikeRealLocal : PlayerSub10Bike {
  // vtable 808b5e00
}; // Total size 0x2c4

class PlayerSub1c {
public:
  PlayerSub1c(PlayerParams *playerParams); // 805943b4
  updateFromInput(); // 8059487c
  computeStartBoost(); // 805959d4
  applyStartBoost(int startBoostIdx); // 80595af8
  updateCollisions(); // 80594bd4

  // vtable 808b6534
  uint32_t bitfield0; // bit flags:
    /*
       0 accelerate
       1 brake
       2 hop
       3 drift (manual)
       7 first frame of hop
       8 first frame of acceleration
      11 floor collision with any wheel
      12 floor collision with all wheels
      13 stick left
      18 ground
      19 hop
      20 boost
      24 stick right
      28 drift (auto)
      29 wheelie
    */
  uint32_t bitfield1; // bit flags:
    /*
      20 mt boost
    */
  uint32_t bitfield2; // bit flags:
    /*
      27 in a bullet
    */
  uint32_t bitfield3; // bit flags:
    /*
       8 start boost charge
    */
  uint32_t bitfield4; // bit flags:
    /*
       0 cpu-controlled
       1 real local
       2 local
       3 remote
       4 automatic drift
       6 ghost
    */
  // unknown pointer 0x18, contains a pointer to PlayerPointers
  uint32_t airtime;
  // unknown 0x20 - 0x27
  VEC3 top;
  // unknown VEC3 0x34
  // unknown 0x40 - 0x87
  float stickX;
  float stickY;
  // unknown 0x90 - 0x9b
  float startBoostCharge;
  int startBoostIdx; // -1 when burning out
  // unknown 0xa4 - 0xbf
}; // Total size 0xc0

class PlayerSub {
public:
  PlayerSub(PlayerParams *playerParams); // 80595d48

  PlayerPointers *playerPointers;
  // unknown pointers 0x4, 0x8
  // vtable 808b659c
  PlayerSub10 *playerSub10;
  PlayerSub14 *playerSub14;
  PlayerSub18 *playerSub18; // contains vehicle body collision data
  PlayerSub1c *playerSub1c; // contains input-related state
  // unknown 0x20 - 0x98
}; // Total size 0x9c

class PlayerPhysics {
private:
  PlayerPhysics(); // 805b4b54

public:
  virtual ~PlayerPhysics(); // 8059f678
  virtual stabilize(); // 805b5b68
  // unknown virtual function 2
  PlayerPhysics(); // 805b4af8
  initInertia0(); // 805b4dc4
  initInertia1(); // 805b4e84
  reset(); // 805b4d24
  update(float one, float maxSpeed, bool unknown); // 805b5170
  applyWheelSuspension(VEC3 *unk0, VEC3 *normalAcceleration, VEC3 *unk1, bool unk2); // 805b6150

  // vtable 808b7314
  MAT34 inertiaTensor;
  MAT34 invInertiaTensor;
  float rotationSpeed;
  VEC3 position;
  VEC3 gravitySpeed; // speed caused by gravity and normal force
  // unknown VEC3 0x80, 0x8c, 0x98
  VEC3 rotVec0; // contains drift, diving and wheel rotation
  VEC3 speed2;
  VEC3 rotVec1;
  VEC3 speed3;
  VEC3 speed; // sum of gravitySpeed, engineSpeed, speed2 and speed3
  float speedNorm;
  VEC3 rotVec2;
  VEC4 rotation0; // as a quaternion
  VEC4 rotation1; // this is probably the next or the previous rotation
  // unknown VEC3 0x110
  VEC3 wheelRotVec;
  // unknown VEC4 0x128, 0x138
  float gravity; // 1.3f most of the time
  VEC3 engineSpeed; // speed caused by the vehicle engine
  // unknown 0x158 - 0x1b3
}; // Total size 0x1b4

class PlayerPhysicsBike : PlayerPhysics {
public:
  virtual ~PlayerPhysicsBike(); // 805b66e4
  virtual stabilize(); // 805b6448

  // vtable 808b7300
}; // Total size 0x1b4

class CollisionData {
public:
  CollisionData(); // 805b821c

  // unknown 0x0 - 0x3
  VEC3 normal;
  VEC3 floorNormal;
  // unknown VEC3 0x1c, 0x28, 0x34
  VEC3 position;
  // unknown VEC3 0x4c, 0x58
  // unknown 0x64 - 0x83
}; // Total size 0x84

class Hitbox {
public:
  Hitbox(); // 805b7f48
  reset(); // 808b7f84
  update(float scale0, float scale1, VEC3 *scale, VEC4 *rotation, VEC3 *centerPosition); // 805b7fbc

  void *bspHitbox; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  float radius;
  // unknown int 0x8
  VEC3 position;
  VEC3 lastPosition;
  // unknown VEC3 0x24
}; // Total size 0x30

class HitboxGroup {
public:
  HitboxGroup(); // 805b82bc
  HitboxGroup(BspHitbox *hitboxes); // 805b84c0
  HitboxGroup(float radius, VEC3 *position); // 805b875c
  updateBoundingRadius(); // 805b883c
  reset(); // 805b8330

  uint16_t hitboxCount;
  // padding 0x2 - 0x3
  float boundingRadius;
  CollisionData collisionData;
  Hitbox *hitboxes;
  // unknown uint32_t 0x90
  // unknown float 0x94
  // unknown float 0x98
}; // Total size 0x9c

class PlayerPhysicsHolder {
public:
  PlayerPhysicsHolder(bool isBike, StatsAndBsp *statsAndBsp, void *arg_r5, uint32_t wheelCount); // 805a04a0
  init(bool isBike); // 8059f5bc
  resetQuaternions(); // 805a0410

  // vtable 808b69e8
  PlayerPhysics *playerPhysics;
  HitboxGroup *hitboxGroup;
  // unknown 0xc - 0x17
  VEC3 position;
  // unknown VEC4 0x24, 0x34, 0x44, 0x54, 0x64, 0x74
  // unknown 0x84 - 0x9b
  // unknown MAT34 0x9c
  // unknown VEC3 0xcc, 0xd8, 0xe4
  VEC3 speed;
  // unknown float 0xfc
}; // Total size 0x100

class 3DObject {
public:
  3DObject(PlayerParams *playerParams, uint32_t unknown); // 80592848

  // unknown 0x0 - 0xb
  // vtable 808b6450
  // unknown VEC3 0x10
  // unknown MAT34 0x1c
  // unknown MAT34 0x4c
  // unknown 0x7c - 0x8b
}; // Total size 0x8c

class PlayerGraphics : 3DObject { // tentative name
public:
  getWheelMatrixBike(MAT34 *wheelMatrix, uint32_t wheelIdx); // 8056dd54

  // unknown 0x8c - 0x8f
  PlayerPhysicsHolder *playerPhysicsHolder;
  // unknown float angle 0x94
  // unknown vec3 0x98
  // unknown 0xa4 - 0xa7
  // unknown MAT34 0xa8 and 0xd8, generated from kartDriverDispParam
  // unknown 0x108 - 0x167
  // unknown MAT34 0x168 and 0x198, also generated from KartDriverDispParam
  // unknown 0x1c8 - 0x22f
  float wheelForwardRotationSpeed; // from KartPartsDispParam/BikePartsDispParam
  float wheelBackwardRotationSpeed; // same
  // unknown 0x238 - 0x35f
}; // Total size 0x360

class StatsAndBsp {
public:
  Stats *stats; // http://wiki.tockdom.com/wiki/KartParam.bin
  Bsp *bsp; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
}; // Total size 0x8

class PlayerParams {
public:
  PlayerParams(uint32_t playerIdx, VehicleId vehicle, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp,
               void *unknown, KartDriverDispParams *kartDriverDispParams, KartPartsDispParams *kartPartsDispParams,
               BikePartsDispParams *bikePartsDispParams, DriverDispParams *driverDispParams); // 80592fc0

  uint32_t isBike;
  VehicleId vehicle;
  CharacterId character;
  uint16_t wheelCount0;
  uint16_t wheelCount1;
  uint8_t playerIdx;
  // padding 0x11 - 0x13
  StatsAndBsp *statsAndBsp;
  // unknown pointer 0x18
  KartDriverDispParams *kartDriverDispParams;
  KartPartsDispParams *kartPartsDispParams; // http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  BikePartsDispParams *bikePartsDispParams; // http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
  DriverDispParams *driverDispParams;
  float wheelCountRecip;
  float wheelCountPlusOneRecip; // 1.0f / (wheelCount + 1.0f)
  // unknown 0x34 - 0x3b
}; // Total size 0x3c

class WheelPhysics {
public:
  WheelPhysics(uint32_t wheelIdx, uint32_t bspWheelIdx); // 8059940c
  initHitboxGroup(); // 80599470
  realign(VEC3 *bottomDirection, VEC3 *unknown); // 80599ad0

  PlayerPointers *playerPointers;
  // unknown pointers 0x4, 0x8
  // vtable 808b66a4
  uint32_t wheelIdx;
  uint32_t bspWheelIdx;
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  HitboxGroup *hitboxGroup;
  VEC3 position;
  // unknown VEC3 0x2c
  VEC3 lastSpeed;
  float posY;
  // unknown VEC3 0x48, 0x54, 0x60, 0x6c
  VEC3 topmostPosition;
}; // Total size 0x84

class WheelPhysicsHolder {
public:
  WheelPhysicsHolder(uint32_t wheelIdx, bool xMirroredKart, uint32_t bspWheelIdx); // 80599ed4
  update(float unknown, VEC3 *gravity, MAT34 *wheelMat); // 8059a278
  applySuspensions(VEC3 *forwardDirection, VEC3 *unknown); // 8059a574

  PlayerPointers *playerPointers;
  // unknown 0x4 - 0xb
  // vtable 808b66b0
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  WheelPhysics *wheelPhysics;
  uint32_t xMirroredKart;
  uint32_t bspWheelIdx;
  uint32_t wheelIdx;
  VEC3 topmostPosition;
  float slackY;
  // unknown 0x34 - 0x3b
  VEC3 bottomDirection;
}; // Total size 0x48

class Wheel0 : 3DObject {
public:
  Wheel0(PlayerParams *playerParams); // 80598b08
  init(); // 80598bd4

  // vtable 808b6640
  // unknown 0x8c - 0x8f
  WheelPhysicsHolder *wheelPhysicsHolder;
}; // Total size 0x94

class Wheel1 : 3DObject {
public:
  Wheel1(PlayerParams *playerParams, bool xMirroredKart, uint32_t bspWheelIdx); // 8059aa44

  // vtable 808b67e0
  // unknown 0x8c - 0x8f
  uint32_t xMirroredKart;
  uint32_t bspWheelIdx;
  WheelPhysics *wheelPhysics;
  // unknown float 0x9c
}; // Total size 0xa0

class Wheel1Front : Wheel1 {
public:
  // vtable 808b6798
  // unknown 0xa0 - 0xcf
}; // Total size 0xd0

class PlayerPointers {
public:
  // all these methods use a double reference to PlayerPointers
  BikePartsDispParams *getBikePartsDispParams(); // 8059091c
  Bsp *getBsp(); // 80590888
  ControllerHolder *getControllerHolder();
  BspWheel *getBspWheel(uint32_t bspWheelIdx); // 805908b4
  KartDriverDispParams *getKartDriverDispParams(); // 805908e4
  PlayerGraphics *getPlayerGraphics(); // 8059069c
  uint8_t getPlayerIdx(); // 80590a5c
  PlayerPhysics *getPlayerPhysics(); // 805903cc
  PlayerPhysicsHolder *getPlayerPhysicsHolder(); // 805903ac
  HitboxGroup *getPlayerPhysicsHolderHitboxGroup(); // 805907d8
  VEC3 *getPlayerPosition(); // 8059020c
  Stats *getPlayerStats(); // 80590874
  PlayerSub *getPlayerSub(); // 805908d8
  PlayerSub *getPlayerSub(); // 80590764
  PlayerSub10 *getPlayerSub10(); // 8059077c
  PlayerSub14 *getPlayerSub14(); // 80590d20
  PlayerSub18 *getPlayerSub18(); // 8059084c
  VEC3 *getScale(); // 805914bc
  VEC3 *getSpeed(); // 80590d08
  VEC3 *getSpeedRatioCapped(); // 80590dc0
  VehicleType getVehicleType(); // 80590a10
  Wheel0 *getWheel0(uint32_t wheelIdx); // 805906b4
  Wheel1 *getWheel1(uint32_t wheelIdx); // 805906dc
  uint16_t getWheelCount0(); // 805902dc
  uint16_t getWheelCount1(); // 805902ec
  WheelPhysics *getWheelPhysics(uint32_t wheelIdx); // 80590734
  CollisionData *getWheelPhysicsCollisionData(uint32_t wheelIdx); // 80590834
  WheelPhysicsHolder *getWheelPhysicsHolder(uint32_t wheelIdx); // 80590704
  bool isBike(); // 80590a6c
  bool isCpu(); // 80590664
  setPlayerPosition(VEC3 *position); // 80590238
  setPlayerRotation(VEC4 *rotation); // 80590288

  PlayerParams *params;
  PlayerSub1c *playerSub1c;
  PlayerGraphics *playerGraphics;
  Wheel0 **wheels0;
  Wheel1 **wheels1;
  // unknown pointer 0x14
  PlayerSub *playerSub;
  // unknown pointers 0x1c, 0x20, 0x24
  PlayerSub10 *playerSub10;
  PlayerSub14 *playerSub14;
  PlayerSub18 *playerSub18;
  // unknown pointers 0x34 - 0x60
}; // Total size 0x64

class Player {
private:
  Player(uint32_t idx, VehicleId vehicle, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp, void *unknown,
         KartDriverDispParams *kartDriverDispParams, KartPartsDispParams *kartPartsDispParams, BikePartsDispParams
         *bikePartsDispParams, DriverDispParams *driverDispParams); // 8058ddbc

public:
  Player(uint32_t idx, VehicleId vehicle, CharacterId character, bool isBike); // 8058f5b4
  update(); // 8058eeb4
  update2(); // 8058eebc
  initWheels(); // 8058ea0c

  PlayerPointers *playerPointers; // a pointer to the inline instance at 0x1c
  // unknown pointer 0x4
  // unknown pointer 0x8
  // vtable 0x808b63ec
  PlayerSub *playerSub;
  PlayerParams *params;
  // unknown pointer 0x18
  PlayerPointers pointers;
}; // Total size 0x80

class PlayerBike : Player {
public:
  initWheels(); // 8058f2e8

  // vtable 0x808b63d0
}; // Total size 0x80

class PlayerHolderSub {
  // vtable 802a2b48
  // unknown 0x4-f
}; // Total size 0x10

class PlayerHolder : public PlayerHolderSub { // vtable override 808b6408
public:
  static PlayerHolder * sInstance; // 809c18f8
  static PlayerHolder * getStaticInstance(); // 8058faa8
  static void destroyStaticInstance(); // 8058faf8

  PlayerHolder(); // 8058fb2c
  Player *PlayerHolderGetPlayer(uint32_t idx); // 80590100
  void update(); // 8058ffe8

  PlayerHolderSub secondPHS;
  Player **players;
  uint8_t playerCount;
  // padding 0x25 - 0x27
  uint32_t someBitfield; // some bits are sets depending on the played track
  uint8_t *array0; // contains 1 element per player, set to the player index divided by 4
  uint8_t *array1; // contains 1 element per player, set to the player index modulo 4
  // unknown 0x34 - 0x37
}; // Total size 0x38
