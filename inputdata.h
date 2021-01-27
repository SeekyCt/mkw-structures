/*
InputData is the class that handles all controller inputs

Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

class InputState {
  // vtable 808b2f2c
  uint16_t buttonActions; // bit flags:
    /* 
      0x1 = accelerate
      0x2 = brake + reverse (used for SSMT)
      0x4 = use item
      0x8 = hop + drift
      0x20 = rear-view camera
    */
  uint16_t buttonRaw; // bit flags, vary slightly by controller
    /*
    gcn:
      0x1 - d-pad left
      0x2 - d-pad right
      0x4 - d-pad down
      0x8 - d-pad up
      0x10 - Bumper (C / Z)
      0x20 - Right Trigger
      0x40 - Left Trigger
      0x100 - A
      0x200 - B
      0x400 - X
      0x800 - Y
      0x1000 - Start
    */
  float stickX; // -1.0 to 1.0
  float stickY; // -1.0 to 1.0
  uint8_t quantisedStickX; // 0-14
  uint8_t quantisedStickY; // 0-14
  uint8_t motionControlFlick; // 1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
  uint8_t motionControlFlick2; // not sure what the difference is from the other one
  uint8_t unknown_0x14;
  // unknown 0x15-17 - seem to be padding
}; // Total size 0x18

class ControllerHolder {
  virtual ~ControllerHolder(); // 805222b4
  virtual unknown1(); // 80521198
  virtual unknown2(); // 80521110
  virtual unknown3();// 805226f4
  virtual unknown4();// 8051ce84
  virtual unknown5();// 8051ce8c
  virtual unknown6();// 80520ebc
  ControllerHolder(); // 80520f64 - inlined in RealControllerHolder()

  // vtable 808b2dd8
  // unknown 0x4-27;
  InputState inputStates[2]; // 0 is current frame, 1 is previous
  // unknown 0x58-d7
}; // Total size 0xd8

class RealControllerHolder : ControllerHolder {
  virtual ~RealControllerHolder(); // 805222f4
  virtual unknown1(); // 80521768
  virtual unknown2(); // 80522708
  virtual unknown4(); // 80522700
  virtual unknown5(); // 805226f8
  virtual unknown6(); // 80520ebc
  RealControllerHolder(); // 805220bc
  
  // vtable 808b2d90
  void * rkgInputBuffer; // 0x2774 byte buffer for storing a controller input section of an RKG file
  // unknown 0xdc-e7  
  void * unknown_0xe8; // 0x1c class with constructor 80524ac4
}; // Total size 0xec

class VirtualControllerHolder : ControllerHolder {
  virtual ~VirtualControllerHolder(); // 8052279c
  virtual unknown3(); // 805219ac
  
  // vtable 808b2db4
  // unknown 0xd8-17f
} // Total size 0x180

class InputData {
  static InputData * sInstance; // 809bd70c
  static InputData * getStaticInstance(); // 8052313c
  static void destroyStaticInstance(); // 8052318c

  virtual ~InputData(); // 805231dc
  InputData(); // 805232f0

  // vtable 808b2fc8
  RealControllerHolder realControllerHolders[4]; // Stores inputs from a real controller at the same console
  VirtualControllerHolder virtualControllerHolders[12]; // Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
  // unknown 0x15b4-415b
}; // Total size 0x415c
