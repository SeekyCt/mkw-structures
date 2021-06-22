/*
PlayerHolder contains most player-specific data during a race

Contributors:
  stebler (main documentation)
  SwareJonge (extra methods and attributes)
  1superchip (extra timer attributes, correcting some signing of types)
  CLF78 (helped with jump pads)
References:
  http://wiki.tockdom.com/wiki/BSP_(File_Format)
  http://wiki.tockdom.com/wiki/KartParam.bin
  http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
*/

typedef struct {
  float x, y, z;
} Vec3; // total size 0xc

typedef struct {
  float x, y, z, w;
} Quat; // total size 0x10

typedef float Mat34[3][4];

class PlayerBoost {
public:
  virtual ~PlayerBoost(); // 8057811c
  PlayerBoost(); // 80588d28
  void reset(); // 80588d74
  bool activate(uint32_t type, int16_t frames); // 80588db0
  void cancelAll(); // 80588e18
  bool update(bool *unk0); // 80588e24

  // vtable 808b5fd8
  int16_t frames[6];
  uint16_t types; // bit flags:
    /*
      0 mt, ssmt, start boost
      1 unused (intended for star)
      2 mushroom, boost panel
      3 unused (intended for bullet)
      4 trick, zipper
      5 unused (intended for mega and tc)
    */
  // unknown 0x11 - 0x12
  float multiplier;
  float acceleration;
  // unknown float 0x1c
  float speedLimit;
}; // total size 0x24

typedef struct {
  float minSpeed;
  float maxSpeed;
  float velY;
} JumpPadProperties; // total size 0xc

typedef enum : int32_t {
  STUNT_TRICK_BASIC = 0,
  BIKE_FLIP_TRICK_X_NOSE = 1,
  BIKE_FLIP_TRICK_X_TAIL = 2,
  FLIP_TRICK_Y_LEFT = 3,
  FLIP_TRICK_Y_RIGHT = 4,
  KART_FLIP_TRICK_Z = 5,
  BIKE_SIDE_STUNT_TRICK = 6,
} TrickType;

typedef enum : int32_t {
  STUNT = 0,
  SINGLE_FLIP = 1,
  DOUBLE_FLIP = 2,
} TrickCategory;

typedef struct {
  float initialAngleDiff;
  float minAngleDiff;
  float minAngleDiffMul;
  float angleDiffMulDec;
} TrickProperties; // total size 0x10

class PlayerTrick {
public:
  virtual ~PlayerTrick(); // 80575aa8
  virtual void start(Vec3 *left); // 80575ee8
  virtual void startInner(TrickCategory category); // 8057616c
  // unknown virtual functions 1 - 2
  virtual void updateRot(); // 805764fc

  PlayerTrick(); // 80575a44
  void updateNext(); // 80575b38
  void tryStart(Vec3 *left); // 80575d7c
  void update(); // 805763e4
  void end(); // 805766b8

  PlayerPointers *pointers;
  // unknown 0x4 - 0xb
  // vtable 808b58b0
  TrickType type;
  TrickCategory category;
  byte nextDirection;
  // unknown 0x19
  int16_t nextTimer;
  float rotDir;
  TrickProperties *properties;
  float angle;
  float angleDiff;
  float angleDiffMul;
  float angleDiffMulDec;
  float maxAngle;
  int16_t cooldown;
  bool boostRampEnabled;
  // unknown 0x3b
  Quat rot;
  PlayerSub10 *playerSub10;
}; // total size 0x50

class PlayerTrickBike : PlayerTrick {
public:
  virtual ~PlayerTrickBike(); // 80576afc
  virtual void start(Vec3 *left); // 80576758
  virtual void startInner(TrickCategory category); // 8057689c
  virtual void updateRot(); // 80576994

  // vtable 808b5890
}; // total size 0x50

class PlayerZipper {
public:
  virtual ~PlayerZipper(); // 80574170
  PlayerZipper(); // 80574114
  void update(); // 80574340
  void end(int unk0); // 805758e4

  PlayerPointers *pointers;
  // unknown 0x4 - 0xb
  // vtable 808b5798
}; // total size 0x90

class PlayerSub10 {
public:
  virtual ~PlayerSub10(); // 80587b78
  // unknown virtual function 1
  virtual setTurnParams(); // 8057829c
  // unknown virtual function 3
  virtual activateStar(); // 80580268
  virtual activateMega(); // 80580b14
  virtual applyInk(int unk); // 80581a58
  // unknown virtual functions 7-11
  virtual void cancelWheelie(); // 8057dc40
  virtual bool checkWheelie(); // 80589744
  virtual updateTurn(); // 8057a8b4
  virtual updateVehicleSpeed(); // 8057ab68
  virtual updateUpsWhileAirborne(); // 8057d888
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
  updateHopPhysics(); // 80579968
  updateDir(); // 8057a140
  updateAcceleration(); // 8057b9bc
  updateOffroad(); // 8057c3d4
  updateRotation(); // 8057c69c
  updateStandstillBoostRot(); // 8057d1d4
  updateUps(); // 8057d398
  updateManualDrift(); // 8057dc44
  updateAutoDrift(); // 8057e0dc
  updateHopAndSlipdrift(); // 8057e804
  activateMushroom(); // 8057f3d8
  endTrick(); // 8057f7a8
  activateZipperBoost(); // 8057f96c
  tryStartJumpPad(); // 8057fd18
  applyLightning(); // 80580438
  applyLightningEffect(int frames, int unk0, int unk1); // 80580778
  activateTc(); // 80581a28
  deactivateTc(); // 80581a40
  updateInk(); // 80581b1c
  applyStartBoost(int frames); // 8058212c
  tryEndJumpPad(); // 80582530
  updateBoost(); // 80582694, always inlined
  releaseMt(int unk0, int unk1); // 80582f9c
  updateStickyRoad(); // 80583b88
  setInitialPhysicsValues(Vec3 *position, Vec3 *angles); // 80584044
  doRespawn(); // 80584334
  enterCannon(); // 8058498c
  updateCannon(); // 80584d58
  activateBullet(int unk); // 805858ac
  updateDiving(); // 805869dc
  updateSlipstream(); // 80586fa8
  updateSpecialFloor(); // 80587590, always inlined

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
  Vec3 smoothedUp;
  Vec3 up;
  Vec3 landingDir;
  Vec3 dir;
  Vec3 lastDir;
  Vec3 vel1Dir;
  // unknown Vec3 0x80
  Vec3 dirDiff;
  bool hasLandingDir;
  // unknown 0x99 - 0x9b, likely padding
  float outsideDriftAngle;
  float landingAngle;
  Vec3 outsideDriftLastDir;
  float speedRatioCapped; // to 1
  float speedRatio;
  float kclSpeedFactor;
  float kclRotFactor;
  float kclWheelSpeedFactor;
  float kclWheelRotFactor;
  int16_t flooorCollisionCount;
  // unknown 0xca - 0xcb
  int hopStickX;
  int hopFrame;
  Vec3 hopUp;
  Vec3 hopDir;
  int slipstreamCharge;
  // unknown float 0xf0
  float divingRot;
  float boostRot;
  int16_t driftState; // 1: charging mt, 2: mt charged, 3: smt charged
  int16_t mtCharge;
  int16_t smtCharge;
  int16_t mtBoost;
  float outsideDriftBonus;
  PlayerBoost boost;
  int16_t zipperBoost;
  int16_t zipperBoostMax;
  // unknown 0x130 - 0x147
  int16_t offroadInvincibilityFrames;
  // unk uint16_t 0x14a
  uint16_t ssmtCharge;
  // unknown 0x14e - 0x157
  float effectiveTurn;
  float conservedTurn;
  // float playerSize perhaps?
  Vec3 scale;
  // unknown float 0x170
  float someScale;
  float shockSpeedMultiplier;
  float megaScale;
  // unknown 0x180 - 0x187
  int16_t mushroomBoost2; // 0x188, another mushroom boost timer
  int16_t starTimer; // 0x18A, timer for Star
  int16_t shockTimer; // 0x18C, used when shocked by KC Zappers, TC, or Shock
  int16_t blooperCharacterInk; // 0x18E, timer for ink on player
  uint8_t field_0x190; // set to 1 when the blooper state is applied
  // unknown 0x191
  int16_t crushTimer; // 0x192, timer for being crushed by Thwomp & Mega
  int16_t MegaTimer; // 0x194, timer for Mega mushroom
  // unknown 0x196 - 0x1af
  float jumpPadMinSpeed;
  float jumpPadMaxSpeed;
  // unknown floats 0x1b8, 0x1bc
  JumpPadProperties jumpPadProperties;
  int16_t rampBoost;
  // unknown 0x1c6 - 0x227
  float hopVelY;
  float hopPosY;
  float hopGravity;
  // unknown 0x234 - 0x248
  uint32_t drivingDirection; // 0: forwards, 1: braking, 2: waiting on the backwards counter, 3: backwards
  uint16_t backwardsAllowCounter;
  // unknown 0x24e - 0x24f
  uint32_t specialFloor; // bit flags:
    /*
      0 boost panel
      1 boost ramp
      2 jump pad
    */
  // unknown 0x254 - 0x257
  PlayerTrick *trick;
  PlayerZipper *zipper;
  // unknown 0x260 - 0x287
  float rawTurn;
  // unknown float 0x28c
  int16_t ghostVanishTimer;
  // unknown 0x292 - 0x293
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
  virtual setTurnParams(); // 80587c54
  virtual void cancelWheelie(); // 80588b30
  virtual bool checkWheelie(); // 80588fe0
  virtual updateVehicleRotationVector(float turn); // 80587d68
  virtual getWheelieSoftSpeedLimitBonus(); // 80588324
  virtual updateWheelie(); // 80587d64
  virtual updateMtCharge(); // 80588888
  virtual startWheelie(); // 80588350
  virtual cancelWheelie(); // 805883c4
  // unknown virtual function 26
  PlayerSub10Bike(); // 80587b30

  // vtable 808b5ee8
  float leanRot;
  float leanRotCap;
  float leanRotInc;
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

class PlayerSub14 {
  PlayerSub14(); // 805672cc
}; // Total size 0x100

class PlayerSub18 {
public:
  virtual void processVehicleBodyCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, KclFlags *kclFlags); // 8056e764
  virtual void processWheelCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, KclFlags *kclFlags); // 8056e8d4
  virtual ~PlayerSub18(); // 80573ff0

  PlayerSub18(); // 8056e56c
  void processMovingRoad(CollisionData *collisionData, KclFlags *kclFlags); // 8056e930
  processFloor(CollisionData *collisionData, Hitbox *hitbox, void *unk, KclFlags *kclFlags, bool allowBoostPanels); // 8056ea04
  checkPlayerCollision(PlayerPointers **otherPlayer); // 8056f7f0
  checkItemCollision(); // 8057257c
  updateCollisions(); // 80572c20
  int handleNoopCollision(); // 80573170
  int handleBananaCollision(); // 80573178
  int handleShellCollision(); // 80573190
  int handleBlueShellCollision(); // 805731b0
  int handleBombCollision(); // 805731c8
  int handleMushroomCollision(); // 805731e0
  int handleStarCollision(); // 80573224
  int handleFibCollision(); // 8057325c
  activeOob(int unk0, int unk1, int unk2, int unk3); // 80573b00
  updateRespawn(); // 80573ed4
  updateCollisionsInner(float unk0, float unk1, uint32_t playerIdx, PlayerPhysics *playerPhysics, collisionGroup *collisionGroup, Quat *rotation, Vec3 *scale, bool enableHwg, Vec3 *unk2); // 805b6724

  // vtable 808b56a8
  PlayerPointers *playerPointers;
  // unknown 0x8 - 0x2b
  uint32_t surfaceProperties; // bit flags:
    /*
       0: wall
       1: solid oob
       4: boost ramp
       6: offroad
       8: boost panel or ramp
      11: trickable
    */
  // unknown 0x30 - 0x47
  int16_t preRespawnTimer;
  int16_t solidOobTimer;
  // unknown 0x4c - 0x73
}; // Total size 0x74

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
       2 drift input
       3 drift (manual)
       4 oob, before being respawned
       5 wall 3 collision
       6 wall collision
       7 first frame of hop
       8 first frame of acceleration
       9 first frame of groundtime
      10 floor collision with the vehicle body
      11 floor collision with any wheel
      12 floor collision with all wheels
      13 stick left
      15 airtime > 20
      16 sticky road
      18 ground
      19 hop
      20 boost
      24 stick right
      26 mushroom boost
      27 charging a slipstream
      28 drift (auto)
      29 wheelie
      30 jump pad enabled
      31 ramp boost
    */
  uint32_t bitfield1; // bit flags:
    /*
       0 hit by an item or an object
       1 first frame of respawn
       3 first frame of cannon
       4 in cannon
       5 first frame of trick
       6 in a trick
       7 offroad invincibility
      10 over a zipper
      13 zipper boost
      15 zipper trick
      20 mt boost
      22 in a trick
      30 on a trickable surface
      31 in a star
    */
  uint32_t bitfield2; // bit flags:
    /*
       0 charging a slipstream
       1 in a slipstream
       4 wheelie rotation
       7 shocked
      15 in a mega
      16 crushed
      18 stopped
      19 vanished
      27 in a bullet
      28 ink applied
      29 has a tc
    */
  uint32_t bitfield3; // bit flags:
    /*
       5 hwg (horizontal wall glitch)
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
  Vec3 floorNor;
  // unknown Vec3 0x34
  // unknown 0x40 - 0x6b
  int32_t hwgTimer;
  // unknown 0x70 - 0x73
  uint32_t boostRampType;
  uint32_t jumpPadType;
  // unknown 0x7c - 0x7f
  uint32_t cnptId;
  // unknown 0x84 - 0x87
  float stickX;
  float stickY;
  // unknown 0x90 - 0x9b
  float startBoostCharge;
  int32_t startBoostIdx; // -1 when burning out
  // unknown 0xa4 - 0xa5
  int16_t trickableTimer;
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
  applyWheelSuspension(Vec3 *unk0, Vec3 *normalAcceleration, Vec3 *unk1, bool unk2); // 805b6150

  // vtable 808b7314
  Mat34 inertiaTensor;
  Mat34 invInertiaTensor;
  float rotationSpeed;
  Vec3 position;
  Vec3 vel0; // speed caused by gravity and normal force
  // unknown Vec3 0x80, 0x8c, 0x98
  Vec3 rotVec0; // contains drift, diving and wheel rotation
  Vec3 vel2;
  Vec3 rotVec1;
  Vec3 vel3;
  Vec3 vel; // sum of vel0, vel1, vel2 and vel3
  float speedNorm;
  Vec3 rotVec2;
  Quat mainRot;
  Quat fullRot; // also includes specialRot
  Vec3 normalAcceleration;
  Vec3 normalRotVec;
  Quat specialRot; // e.g. trick
  // unknown Quat 0x138
  float gravity; // 1.3f most of the time
  Vec3 vel1; // speed caused by the vehicle engine
  // unknown 0x158 - 0x177
  float stabilizationFactor;
  Vec3 speed1Adj;
  // unknown 0x180 - 0x1b3
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

  uint32_t types; // bit flags:
    /*
      0 floor
      1 wall
      2 invisible wall
      3 trickable
      6 wall 3
    */
  Vec3 nor;
  Vec3 floorNor;
  // unknown Vec3 0x1c, 0x28
  Vec3 vel;
  Vec3 relPos;
  Vec3 movement;
  // unknown Vec3 0x58
  float speedFactor;
  float rotFactor;
  uint32_t closestFloorFlags;
  uint32_t closestFloorSettings;
  // unknown 0x74 - 0x7b
  uint32_t intensity
  // unknown 0x80 - 0x83
}; // Total size 0x84

class Hitbox {
public:
  Hitbox(); // 805b7f48
  reset(); // 808b7f84
  update(float scale0, float scale1, Vec3 *scale, Quat *rotation, Vec3 *centerPosition); // 805b7fbc

  void *bspHitbox; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  float radius;
  // unknown int32_t 0x8
  Vec3 position;
  Vec3 lastPosition;
  // unknown Vec3 0x24
}; // Total size 0x30

class HitboxGroup {
public:
  HitboxGroup(); // 805b82bc
  HitboxGroup(BspHitbox *hitboxes); // 805b84c0
  HitboxGroup(float radius, Vec3 *position); // 805b875c
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
  Vec3 position;
  // unknown Quat 0x24, 0x34, 0x44, 0x54, 0x64, 0x74
  // unknown 0x84 - 0x9b
  // unknown Mat34 0x9c
  // unknown Vec3 0xcc, 0xd8, 0xe4
  Vec3 speed;
  // unknown float 0xfc
}; // Total size 0x100

class 3DObject {
public:
  3DObject(PlayerParams *playerParams, uint32_t unknown); // 80592848

  // unknown 0x0 - 0xb
  // vtable 808b6450
  // unknown Vec3 0x10
  // unknown Mat34 0x1c
  // unknown Mat34 0x4c
  // unknown 0x7c - 0x8b
}; // Total size 0x8c

class PlayerGraphics : 3DObject { // tentative name
public:
  getWheelMatrixBike(Mat34 *wheelMatrix, uint32_t wheelIdx); // 8056dd54

  // unknown 0x8c - 0x8f
  PlayerPhysicsHolder *playerPhysicsHolder;
  // unknown float angle 0x94
  // unknown vec3 0x98
  // unknown 0xa4 - 0xa7
  // unknown Mat34 0xa8 and 0xd8, generated from kartDriverDispParam
  // unknown 0x108 - 0x167
  // unknown Mat34 0x168 and 0x198, also generated from KartDriverDispParam
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

class GpStats {
public:
  bool startBoostSuccessful;
  // unknown 0x1 - 0x3, maybe padding
  uint32_t mtCount;
  uint32_t offroadFrames;
  // unknown uint32_t 0xc
  uint32_t objectCollisionCount;
  uint32_t oobCount;
  // unknown uint16_t 0x18
  // unknown 0x1a - 0x1b, maybe padding
}; // Total size 0x1c

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
  GpStats *gpStats;
  // unknown 0x38 - 0x3b
}; // Total size 0x3c

class WheelPhysics {
public:
  WheelPhysics(uint32_t wheelIdx, uint32_t bspWheelIdx); // 8059940c
  initHitboxGroup(); // 80599470
  realign(Vec3 *bottomDirection, Vec3 *unknown); // 80599ad0

  PlayerPointers *playerPointers;
  // unknown pointers 0x4, 0x8
  // vtable 808b66a4
  uint32_t wheelIdx;
  uint32_t bspWheelIdx;
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  HitboxGroup *hitboxGroup;
  Vec3 position;
  // unknown Vec3 0x2c
  Vec3 lastSpeed;
  float posY;
  // unknown Vec3 0x48, 0x54, 0x60, 0x6c
  Vec3 topmostPosition;
}; // Total size 0x84

class WheelPhysicsHolder {
public:
  WheelPhysicsHolder(uint32_t wheelIdx, bool xMirroredKart, uint32_t bspWheelIdx); // 80599ed4
  update(float unknown, Vec3 *gravity, Mat34 *wheelMat); // 8059a278
  applySuspensions(Vec3 *forwardDirection, Vec3 *unknown); // 8059a574

  PlayerPointers *playerPointers;
  // unknown 0x4 - 0xb
  // vtable 808b66b0
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  WheelPhysics *wheelPhysics;
  uint32_t xMirroredKart;
  uint32_t bspWheelIdx;
  uint32_t wheelIdx;
  Vec3 topmostPosition;
  float slackY;
  // unknown 0x34 - 0x3b
  Vec3 bottomDirection;
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
  Vec3 *getPlayerPosition(); // 8059020c
  Stats *getPlayerStats(); // 80590874
  PlayerSub *getPlayerSub(); // 805908d8
  PlayerSub *getPlayerSub(); // 80590764
  PlayerSub10 *getPlayerSub10(); // 8059077c
  PlayerSub14 *getPlayerSub14(); // 80590d20
  PlayerSub18 *getPlayerSub18(); // 8059084c
  Vec3 *getScale(); // 805914bc
  Vec3 *getSpeed(); // 80590d08
  Vec3 *getSpeedRatioCapped(); // 80590dc0
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
  setPlayerPosition(Vec3 *position); // 80590238
  setPlayerRotation(Quat *rotation); // 80590288

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
