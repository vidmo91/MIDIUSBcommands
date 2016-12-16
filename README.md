# MIDIUSBcommands

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

Shorten list of functions:
CC commands' numbers for specyfic functions are inside header file 

//%%%%%%%%%%%%%%%%%%%%%%%% Main MIDI commands %%%%%%%%%%%%%%%%%%%%%%%%

void noteOff(int note, int vel, int channel = 0, int cable = 0) 
void noteOn(int note, int vel, int channel = 0, int cable = 0) 
void aftertouch(int note, int vel, int channel = 0, int cable = 0) 
void ctrlChg(int ctrl, int val, int channel = 0, int cable = 0) 
void progChg(int prog, int channel = 0, int cable = 0) 
void aftertouchMono(int vel, int channel = 0, int cable = 0) 
void pitchChg(int val, int channel = 0, int cable = 0) 

//%%%%%%%%%%%%%%%%%%%%%%%% bank change only LSB is uded by GM 2 %%%%%%%%%%%%%%%%%%%%%%%%
//standard usage:
//                bankChg(); -reset to zero (on channel 0)
//                bankChg(n); -set n'th bank (on channel 0)
//                bankChg(n,ch); -set n'th bank on ch'th channel
//should be followed by progChg

void bankChg(int LSB = 0, int MSB = 0, int channel = 0, int cable = 0) {

//%%%%%%%%%%%%%%%%%%%%%%%% 14bit CC %%%%%%%%%%%%%%%%%%%%%%%% 14bit CC
//val is 14bit precise 0x2000 = 8192 central / 0x3FFF = 16383 max//standard usage:
//                eg. modWheel(n); -set modulation to n (on channel 0)
//                eg. portamentoTime(n,ch); -set portamento time on ch'th channel to n


void modWheel(int val, int channel = 0, int cable = 0) 
void breathCtrl(int val, int channel = 0, int cable = 0) 
void Ctrl3(int val, int channel = 0, int cable = 0) 
void footCtrl(int val, int channel = 0, int cable = 0) 
void portamentoTime(int val, int channel = 0, int cable = 0) 
void dataEntry(int val, int channel = 0, int cable = 0) 
void channelVolume(int val, int channel = 0, int cable = 0) 
void balance(int val, int channel = 0, int cable = 0) 
void Ctrl9(int val, int channel = 0, int cable = 0) 
void pan(int val, int channel = 0, int cable = 0) 
void expressionCtrl(int val, int channel = 0, int cable = 0) 
void effectCtrl1(int val, int channel = 0, int cable = 0) 
void effectCtrl2(int val, int channel = 0, int cable = 0) 
void Ctrl14(int val, int channel = 0, int cable = 0) 
void Ctrl15(int val, int channel = 0, int cable = 0) 
//General Purpose Controller
void GPC1(int val, int channel = 0, int cable = 0) 
void GPC2(int val, int channel = 0, int cable = 0) 
void GPC3(int val, int channel = 0, int cable = 0) 
void GPC4(int val, int channel = 0, int cable = 0) 
//%%%%%%%%%%%%%%%%%%%%%%%% 7bit CC %%%%%%%%%%%%%%%%%%%%%%%% 7bit CC
//val is 7bit precise 0x40 = 64 central / 0x7F = 127 max
//standard usage: same as 14 bit CC

//default: Variation 
void soundCtrl1(int val, int channel = 0, int cable = 0) 
//default: Timbre/Harmonic Intens.
void soundCtrl2(int val, int channel = 0, int cable = 0) 
//default: Release Time
void soundCtrl3(int val, int channel = 0, int cable = 0) 
//default: Attack Time
void soundCtrl4(int val, int channel = 0, int cable = 0) 
//default: Brightness
void soundCtrl5(int val, int channel = 0, int cable = 0) 
//default: Decay Time
void soundCtrl6(int val, int channel = 0, int cable = 0)
//default: Vibrato Rate 
void soundCtrl7(int val, int channel = 0, int cable = 0) 
//default: Vibrato Depth 
void soundCtrl8(int val, int channel = 0, int cable = 0) 
//default: Vibrato Delay 
void soundCtrl9(int val, int channel = 0, int cable = 0) 
//default: undefined 
void soundCtrl10(int val, int channel = 0, int cable = 0)

void GPC5(int val, int channel = 0, int cable = 0) 
void GPC6(int val, int channel = 0, int cable = 0) 
void GPC7(int val, int channel = 0, int cable = 0) 
void GPC8(int val, int channel = 0, int cable = 0) 

void portamentoCtrl(int val, int channel = 0, int cable = 0) 

//default: reverb send level 
void effect1(int val, int channel = 0, int cable = 0)
//default: Tremolo Depth
void effect2(int val, int channel = 0, int cable = 0)
//default: Chorus Depth
void effect3(int val, int channel = 0, int cable = 0) 
//default: Celeste [Detune] Depth
void effect4(int val, int channel = 0, int cable = 0)
//default: Phaser Depth
void effect5(int val, int channel = 0, int cable = 0)
//high res velocity prefix LSB
void HRvel(int val, int channel = 0, int cable = 0)

//%%%%%%%%%%%%%%%%%%%%%%%% ON/OFF CC %%%%%%%%%%%%%%%%%%%%%%%% ON/OFF CC
//val is boolean
//standard usage:
//                eg. dumperPedal(1); -turn dumper pedal on (on channel 0)
//                eg. legato(0,ch); -set legato of on ch'th channel

void dumperPedal(bool val, int channel = 0, int cable = 0) 
void portamento(bool val, int channel = 0, int cable = 0) 
void sostenuto(bool val, int channel = 0, int cable = 0) 
void softPedal(bool val, int channel = 0, int cable = 0) 
void legato(bool val, int channel = 0, int cable = 0) 
void hold2(bool val, int channel = 0, int cable = 0) 
void omniMode(bool val, int channel = 0, int cable = 0) 
void localCtrl(bool val, int channel = 0, int cable = 0)
void mono(bool val, int channel = 0, int cable = 0) 

//%%%%%%%%%%%%%%%%%%%%%%%% panic!!! - all notes off %%%%%%%%%%%%%%%%%%%%%%%% panic!!!
void panic(int channel = 0, int cable = 0) 
//%%%%%%%%%%%%%%%%%%%%%%%% reset all controllers %%%%%%%%%%%%%%%%%%%%%%%% reset
void resetAll(int channel = 0, int cable = 0) 


