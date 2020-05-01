/*
InputData is the class that handles all controller inputs
A pointer to an instance of this class is stored at 0x809bd70c PAL
*/

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
  // I've not documented this yet but if you use a RAM viewer and play around with a controller you can find what you want pretty easily
} // Total size 0xd8

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
