/*
InputData is the class that handles all controller inputs
A pointer to an instance of this class is stored at 0x809bd70c PAL
*/

class InputState {
  // vtable 808b2f2c PAL
  uint16_t unknown_0x4; // stores button presses in some form
  uint16_t unknown_0x6; // stores button presses in some form
  float stickX; // -1.0 to 1.0
  float stickY; // -1.0 to 1.0
  uint8_t quantisedStickX; // 0-14
  uint8_t quantisedStickY; // 0-14
  uint8_t motionControlFlick; // 1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
  uint8_t motionControlFlick2; // not sure what the difference is from the other one
  // unknown 0x14-17
};

class ControllerHolder {
  virtual ~ControllerHolder(); // 805222b4 PAL
  virtual unknown1(); // 80521198 PAL
  virtual unknown2(); // 80521110 PAL
  virtual unknown3();// 805226f4 PAL
  virtual unknown4();// 8051ce84 PAL
  virtual unknown5();// 8051ce8c PAL
  virtual unknown6();// 80520ebc PAL
  ControllerHolder(); // 80520f64 PAL - inlined in RealControllerHolder()

  // vtable 808b2dd8 PAL
  // unknown 0x4-27;
  InputState inputStates[2]; // 0 is current frame, 1 is previous
  // unknown 0x58-d7
}; // Total size 0xd8

class RealControllerHolder : public ControllerHolder {
  virtual ~RealControllerHolder(); // 805222f4 PAL
  virtual unknown1(); // 80521768 PAL
  virtual unknown2(); // 80522708 PAL
  virtual unknown4(); // 80522700 PAL
  virtual unknown5(); // 805226f8 PAL
  virtual unknown6(); // 80520ebc PAL
  RealControllerHolder(); // PAL 805220bc
  
  // vtable 808b2d90 PAL
  void * unknown_0xd8; // 0x2774 struct
  // unknown 0xdc-e7  
  void * unknown_0xe8; // 0x1c class with constructor 80524ac4 PAL
}; // Total size 0xec

class VirtualControllerHolder : public ControllerHolder {
  virtual ~VirtualControllerHolder(); // 8052279c PAL
  virtual unknown3(); // 805219ac PAL
  
  // vtable 808b2db4 PAL
  // unknown 0xd8-17f
} // Total size 0x180

class InputData {
public: 
  virtual ~InputData(); // 805231dc PAL
  InputData(); // 805232f0 PAL

  // vtable 808b2fc8 PAL
  RealControllerHolder realControllerHolders[4]; // Stores inputs from a real controller at the same console
  VirtualControllerHolder virtualControllerHolders[12]; // Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
  // unknown 0x15b4-415b
}; // Total size 0x415c
