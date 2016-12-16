//Made by M.Widomski mateuszwidomski@gmail.com
//
//MIDI messages based on MIDI specifications
//functions' names are more or less same as MIDI command's names 
//
//channel - MIDI channel 0:15 (9 (10th channel) is for percussion only)
//cable - virtual MIDI cable see Universal Serial Bus Device Class Definition for MIDI Devices [4] for further details.
//
//All other functions are written based on main MIDI commands
//Not all Control Change (CC) commands are included, though they can be called using controlChg function 
// You can find detiled description of CC in MIDI Control Change Messages Table [3]
//
//based on:
//[1] https://www.midi.org/specifications/item/table-1-summary-of-midi-message
//[2] https://www.midi.org/specifications/item/table-2-expanded-messages-list-status-bytes
//[3] https://www.midi.org/specifications/item/table-3-control-change-messages-data-bytes-2
//[4] http://www.usb.org/developers/docs/devclass_docs/midi10.pdf



//%%%%%%%%%%%%%%%%%%%%%%%% Main MIDI commands %%%%%%%%%%%%%%%%%%%%%%%%

void noteOff(int note, int vel, int channel = 0, int cable = 0) {
  // note,vel - 7bit values 0:127 / 0x0:0x7F
  MIDIEvent e = {(0x10 * cable + 0x8), 0x80 + channel, note, vel};
  MIDIUSB.write(e);
}
void noteOn(int note, int vel, int channel = 0, int cable = 0) {
  MIDIEvent e = {(0x10 * cable + 0x9), 0x90 + channel, note, vel};
  MIDIUSB.write(e);
}
void aftertouch(int note, int vel, int channel = 0, int cable = 0) {
  MIDIEvent e = {(0x10 * cable + 0xA), 0xA0 + channel, note, vel};
  MIDIUSB.write(e);
}
void ctrlChg(int ctrl, int val, int channel = 0, int cable = 0) {
  MIDIEvent e = {(0x10 * cable + 0xB), 0xB0 + channel, ctrl, val};
  MIDIUSB.write(e);
}
void progChg(int prog, int channel = 0, int cable = 0) {
  MIDIEvent e = {(0x10 * cable + 0xC), 0xC0 + channel, prog, 0};
  MIDIUSB.write(e);
}
void aftertouchMono(int vel, int channel = 0, int cable = 0) {
  MIDIEvent e = {(0x10 * cable + 0xD), 0xD0 + channel, vel, 0};
  MIDIUSB.write(e);
}
void pitchChg(int val, int channel = 0, int cable = 0) {
  //val 14bit precise 0x2000 = 8192 central / 0x3FFF = 16383 max
  MIDIEvent e = {(0x10 * cable + 0xE), 0xE0 + channel, val - (val >> 7) << 7  , val >> 7 };
  MIDIUSB.write(e);
}


//%%%%%%%%%%%%%%%%%%%%%%%% analog in pitch controller %%%%%%%%%%%%%%%%%%%%%%%%
//standard usage:

//                AIpitchCtrl(A1); -set pitch to A1 value (on channel 0)
//                AIpitchCtrl(An,ch); -set pitch to An value on ch'th channel
void AIpitchCtrl(int analog, int channel = 0, int cable = 0) {
  analog = map(analogRead(analog), 0, 1023, 0, 16383);
  pitchChg(analog, channel, cable);
}


//%%%%%%%%%%%%%%%%%%%%%%%% bank change only LSB is uded by GM 2 %%%%%%%%%%%%%%%%%%%%%%%%
//standard usage:
//                bankChg(); -reset to zero (on channel 0)
//                bankChg(n); -set n'th bank (on channel 0)
//                bankChg(n,ch); -set n'th bank on ch'th channel
//should be followed by progChg

void bankChg(int LSB = 0, int MSB = 0, int channel = 0, int cable = 0) {
  ctrlChg(0, MSB, channel, cable);
  ctrlChg(32, LSB, channel, cable);
}

//%%%%%%%%%%%%%%%%%%%%%%%% 14bit CC %%%%%%%%%%%%%%%%%%%%%%%% 14bit CC
//val is 14bit precise 0x2000 = 8192 central / 0x3FFF = 16383 max
//standard usage:
//                eg. modWheel(n); -set modulation to n (on channel 0)
//                eg. portamentoTime(n,ch); -set portamento time on ch'th channel to n


void modWheel(int val, int channel = 0, int cable = 0) {
  ctrlChg(1, val >> 7 , channel, cable);
  ctrlChg(33, val - (val >> 7) << 7, channel, cable);

}
void breathCtrl(int val, int channel = 0, int cable = 0) {
  ctrlChg(2, val >> 7 , channel, cable);
  ctrlChg(34, val - (val >> 7) << 7, channel, cable);
}
void Ctrl3(int val, int channel = 0, int cable = 0) {
  ctrlChg(3, val >> 7 , channel, cable);
  ctrlChg(35, val - (val >> 7) << 7, channel, cable);
}
void footCtrl(int val, int channel = 0, int cable = 0) {
  ctrlChg(4, val >> 7 , channel, cable);
  ctrlChg(36, val - (val >> 7) << 7, channel, cable);
}
void portamentoTime(int val, int channel = 0, int cable = 0) {
  ctrlChg(5, val >> 7 , channel, cable);
  ctrlChg(37, val - (val >> 7) << 7, channel, cable);
}
void dataEntry(int val, int channel = 0, int cable = 0) {
  ctrlChg(6, val >> 7 , channel, cable);
  ctrlChg(38, val - (val >> 7) << 7, channel, cable);
}
void channelVolume(int val, int channel = 0, int cable = 0) {
  ctrlChg(7, val >> 7 , channel, cable);
  ctrlChg(39, val - (val >> 7) << 7, channel, cable);
}
void balance(int val, int channel = 0, int cable = 0) {
  ctrlChg(8, val >> 7 , channel, cable);
  ctrlChg(40, val - (val >> 7) << 7, channel, cable);
}
void Ctrl9(int val, int channel = 0, int cable = 0) {
  ctrlChg(9, val >> 7 , channel, cable);
  ctrlChg(41, val - (val >> 7) << 7, channel, cable);
}
void pan(int val, int channel = 0, int cable = 0) {
  ctrlChg(10, val >> 7 , channel, cable);
  ctrlChg(42, val - (val >> 7) << 7, channel, cable);
}
void expressionCtrl(int val, int channel = 0, int cable = 0) {
  ctrlChg(11, val >> 7 , channel, cable);
  ctrlChg(43, val - (val >> 7) << 7, channel, cable);
}
void effectCtrl1(int val, int channel = 0, int cable = 0) {
  ctrlChg(12, val >> 7 , channel, cable);
  ctrlChg(44, val - (val >> 7) << 7, channel, cable);
}
void effectCtrl2(int val, int channel = 0, int cable = 0) {
  ctrlChg(13, val >> 7 , channel, cable);
  ctrlChg(45, val - (val >> 7) << 7, channel, cable);
}
void Ctrl14(int val, int channel = 0, int cable = 0) {
  ctrlChg(14, val >> 7 , channel, cable);
  ctrlChg(46, val - (val >> 7) << 7, channel, cable);
}
void Ctrl15(int val, int channel = 0, int cable = 0) {
  ctrlChg(15, val >> 7 , channel, cable);
  ctrlChg(47, val - (val >> 7) << 7, channel, cable);
}

//General Purpose Controller
void GPC1(int val, int channel = 0, int cable = 0) {
  ctrlChg(16, val >> 7 , channel, cable);
  ctrlChg(48, val - (val >> 7) << 7, channel, cable);
}
void GPC2(int val, int channel = 0, int cable = 0) {
  ctrlChg(17, val >> 7 , channel, cable);
  ctrlChg(49, val - (val >> 7) << 7, channel, cable);
}
void GPC3(int val, int channel = 0, int cable = 0) {
  ctrlChg(18, val >> 7 , channel, cable);
  ctrlChg(50, val - (val >> 7) << 7, channel, cable);
}
void GPC4(int val, int channel = 0, int cable = 0) {
  ctrlChg(19, val >> 7 , channel, cable);
  ctrlChg(51, val - (val >> 7) << 7, channel, cable);
}
//%%%%%%%%%%%%%%%%%%%%%%%% 7bit CC %%%%%%%%%%%%%%%%%%%%%%%% 7bit CC
//val is 7bit precise 0x40 = 64 central / 0x7F = 127 max
//standard usage: same as 14 bit CC

//default: Variation 
void soundCtrl1(int val, int channel = 0, int cable = 0) {
  ctrlChg(70, val , channel, cable);
}

//default: Timbre/Harmonic Intens.
void soundCtrl2(int val, int channel = 0, int cable = 0) {
  ctrlChg(71, val , channel, cable);
}

//default: Release Time
void soundCtrl3(int val, int channel = 0, int cable = 0) {
  ctrlChg(72, val , channel, cable);
}

//default: Attack Time
void soundCtrl4(int val, int channel = 0, int cable = 0) {
  ctrlChg(73, val , channel, cable);
}

//default: Brightness
void soundCtrl5(int val, int channel = 0, int cable = 0) {
  ctrlChg(74, val , channel, cable);
}

//default: Decay Time
void soundCtrl6(int val, int channel = 0, int cable = 0) {
  ctrlChg(75, val , channel, cable);
}

//default: Vibrato Rate 
void soundCtrl7(int val, int channel = 0, int cable = 0) {
  ctrlChg(76, val , channel, cable);
}

//default: Vibrato Depth 
void soundCtrl8(int val, int channel = 0, int cable = 0) {
  ctrlChg(77, val , channel, cable);
}

//default: Vibrato Delay 
void soundCtrl9(int val, int channel = 0, int cable = 0) {
  ctrlChg(78, val , channel, cable);
}

//default: undefined 
void soundCtrl10(int val, int channel = 0, int cable = 0) {
  ctrlChg(79, val , channel, cable);
}

void GPC5(int val, int channel = 0, int cable = 0) {
  ctrlChg(80, val , channel, cable);
}
void GPC6(int val, int channel = 0, int cable = 0) {
  ctrlChg(81, val , channel, cable);
}
void GPC7(int val, int channel = 0, int cable = 0) {
  ctrlChg(82, val , channel, cable);
}
void GPC8(int val, int channel = 0, int cable = 0) {
  ctrlChg(83, val , channel, cable);
}

void portamentoCtrl(int val, int channel = 0, int cable = 0) {
  ctrlChg(84, val , channel, cable);
}

//default: reverb send level 
void effect1(int val, int channel = 0, int cable = 0) {
  ctrlChg(91, val , channel, cable);
}

//default: Tremolo Depth
void effect2(int val, int channel = 0, int cable = 0) {
  ctrlChg(92, val , channel, cable);
}

//default: Chorus Depth
void effect3(int val, int channel = 0, int cable = 0) {
  ctrlChg(93, val , channel, cable);
}

//default: Celeste [Detune] Depth
void effect4(int val, int channel = 0, int cable = 0) {
  ctrlChg(94, val , channel, cable);
}

//default: Phaser Depth
void effect5(int val, int channel = 0, int cable = 0) {
  ctrlChg(95, val , channel, cable);
}

//high res velocity prefix LSB
void HRvel(int val, int channel = 0, int cable = 0) {
  ctrlChg(88, val , channel, cable);
}

//%%%%%%%%%%%%%%%%%%%%%%%% ON/OFF CC %%%%%%%%%%%%%%%%%%%%%%%% ON/OFF CC
//val is boolean
//standard usage:
//                eg. dumperPedal(1); -turn dumper pedal on (on channel 0)
//                eg. legato(0,ch); -set legato of on ch'th channel

void dumperPedal(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(64, 127 , channel, cable);
  else ctrlChg(64, 0 , channel, cable);
}
void portamento(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(65, 127 , channel, cable);
  else ctrlChg(65, 0 , channel, cable);
}
void sostenuto(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(66, 127 , channel, cable);
  else ctrlChg(66, 0 , channel, cable);
}
void softPedal(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(67, 127 , channel, cable);
  else ctrlChg(67, 0 , channel, cable);
}
void legato(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(68, 127 , channel, cable);
  else ctrlChg(68, 0 , channel, cable);
}
void hold2(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(69, 127 , channel, cable);
  else ctrlChg(69, 0 , channel, cable);
}

void omniMode(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(125, 0 , channel, cable);
  else ctrlChg(124, 0 , channel, cable);
}
void localCtrl(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(122, 127 , channel, cable);
  else ctrlChg(122, 0 , channel, cable);
}
void mono(bool val, int channel = 0, int cable = 0) {
  if (val) ctrlChg(126, 0 , channel, cable);
  else ctrlChg(127, 0 , channel, cable);
}


//%%%%%%%%%%%%%%%%%%%%%%%% panic!!! - all notes off %%%%%%%%%%%%%%%%%%%%%%%% panic!!!
void panic(int channel = 0, int cable = 0) {
  ctrlChg(123, 0 , channel, cable);
}
//%%%%%%%%%%%%%%%%%%%%%%%% reset all controllers %%%%%%%%%%%%%%%%%%%%%%%% reset
void resetAll(int channel = 0, int cable = 0) {
  ctrlChg(121, 0 , channel, cable);
}

