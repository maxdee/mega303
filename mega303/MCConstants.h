#ifndef MCConstants_h
#define MCConstants_h


///////////////////////////////////////////////////////////////////////////////
// Notes
///////////////////////////////////////////////////////////////////////////////
/**
 * MCInput produces events with a ID and a value
 * MCMode takes these ID and produces and parameter change for parts.
 * ID 127 to 142 step buttons
 * ID 143 to 149 pots
 *
 */

#define STEP_COUNT 16
#define SLOT_COUNT 8
#define PART_COUNT 8


// something like this?
// typedef struct {
// 	int steps[16]; // notes 1-127
// 	int changed; // changes if any step modified
// } sixteenStep;

// const uint8_t PROGRAM_BANKS[] = {20, 15, 20, 20, 9, 8, 20, 13, 13, 12, 11, 12, 17, 16, 13, 10, 20, 11, 19, 12, 11, 14};

///////////////////////////////////////////////////////////////////////////////
// Parameters
///////////////////////////////////////////////////////////////////////////////

#define PART_NOTE_OFF 			0
#define PART_NOTE_ON 			1
#define PART_CONTROL_CHANGE		2
#define PART_PROGRAM_CHANGE 	3
#define PART_PATCH 				4
#define PART_KIT 				5
#define PART_COARSE_TUNE 		6
#define PART_FINE_TUNE 			7
#define PART_CUTOFF 			8
#define PART_RESONANCE 			9
#define PART_PORTAMENTO_TIME 	10
#define PART_VIBRATO_RATE		11
#define PART_VIBRATO_DEPTH		12
#define PART_VIBRATO_DELAY		13
#define PART_ATTACK				14
#define PART_DECAY				15
#define PART_RELEASE			16
#define PART_DRUM_PITCH			17
#define PART_DRUM_TVA			18
#define PART_DRUM_PAN			19
#define PART_DRUM_REVERB		20
#define PART_DRUM_CHORUS		21
#define PART_PAN				22
#define PART_VOLUME				23
#define PART_MODULATION			24
#define PART_EXPRESSION			25
#define PART_SUSTAIN			26

#define PART_ADD_NOTE 			27
#define PART_CLEAR_STEP			28
#define PART_CLEAR_ALL 			29

///////////////////////////////////////////////////////////////////////////////
// input ID
///////////////////////////////////////////////////////////////////////////////

#define SCALE_BUTTON 113
#define FUNC_BUTTON 114
#define SHIFT_BUTTON 115

#define SELECT_PART_BUTTON 56
#define MUTE_PART_BUTTON 58
#define RHYTHM_MUTE_BUTTON 57

#define ARPEGGIO_BUTTON 60
#define QUANTIZE_BUTTON 59
#define EFFECT_BUTTON 74
#define PORTA_BUTTON 75
#define MODRATE_BUTTON 76
#define ENVELOPE_BUTTON 77

#define PTNSET_BUTTON 8
#define RPSSET_BUTTON 9
#define PLAYMODE_BUTTON 10
#define OCTAVE_DOWN_BUTTON 11
#define OCTAVE_UP_BUTTON 12
#define TRANSPOSE_BUTTON 13

#define SELECT_LEFT_BUTTON 78
#define SELECT_RIGHT_BUTTON 79
#define FWD_BUTTON 17
#define BWD_BUTTON 16

#define REC_BUTTON 18
#define STOP_BUTTON 19
#define PLAY_BUTTON 20
#define ENTER_BUTTON 21
#define EXIT_BUTTON 22

#define ENCODER_BUTTON 150
#define TAP_BUTTON 151

const uint8_t PART_BUTTON[] = {64, 65, 66, 67, 68, 69, 70, 71};

const uint8_t STEP_BUTTON[] = {32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7};
const uint8_t STEP_LOOKUP[40] = {9, 10, 11, 12, 13, 14, 15, 16,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 1, 2, 3, 4, 5, 6, 7, 8
						 	};
// const int STEPS_OFFSET
const uint8_t POTENTIOMETER[] = {149, 148, 147, 146, 145, 144, 143};
#define POT_0 143
#define POT_1 144
#define POT_2 145
#define POT_3 146
#define POT_4 147
#define POT_5 148
#define POT_6 149

const uint8_t STEP_LED[] = {32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7};

#define SONG_LED 40
#define PATTERN_LED 41
#define TRANSPOSE_LED 42
#define TRANSPOSE_LED 42
#define OCTAVE_DOWN_LED 43
#define OCTAVE_UP_LED 44
#define PTNSET_LED 45
#define RPSSET_LED 45
#define RECSTEP_LED 47

#define SELECT_PART_LED 56
#define MUTE_PART_LED 58
#define RHYTHM_MUTE_LED 57

#define ARPEGGIO_LED 60
#define GRID_LED 61
#define GROOVE_LED 62
#define SHUFFLE_LED 63

#define REALTIME_LED 72
#define EFFECT_LED 74
#define PORTA_LED 75
#define RATEMOD_LED 76
#define ENVELOPE_LED 77

#define TEMPO_LED 88
#define SETPTN_LED 89
#define PTNSONG_LED 90
#define SETRPS_LED 91
#define TONE_LED 92

#define PLAY_LED 93
#define REC_LED 94

#define FUNC_LED 112

#define SCALE_4_LED 116
#define SCALE_3_LED 117
#define SCALE_2_LED 118
#define SCALE_1_LED 119
///////////////////////////////////////////////////////////////////////////////
// input ID
///////////////////////////////////////////////////////////////////////////////
#define PATCH_COUNT 316
const uint8_t PROGRAM_BANKS[PATCH_COUNT][2] = {
  {64, 1 },          // "Synth 1" patches
  {65, 1 },
  {67, 1 },
  {66, 1 },
  {64, 2 },
  {65, 2 },
  {66, 2 },
  {67, 2 },
  {68, 2 },
  {69, 2 },
  {70, 2 },
  {71, 2 },
  {72, 2 },
  {73, 2 },
  {64, 3 },
  {65, 3 },
  {66, 3 },
  {64, 4 },
  {65, 4 },
  {64, 5 },
  {65, 5 },          // "Synth 2" patches
  {66, 5 },
  {67, 5 },
  {68, 5 },
  {69, 5 },
  {70, 5 },
  {64, 6 },
  {65, 6 },
  {66, 6 },
  {67, 6 },
  {64, 7 },
  {65, 7 },
  {66, 7 },
  {64, 8 },
  {65, 8 },
  {64, 9 },          // "Synth Bass 1" patches
  {65, 9 },
  {66, 9 },
  {67, 9 },
  {68, 9 },
  {69, 9 },
  {70, 9 },
  {64, 10 },
  {65, 10 },
  {66, 10 },
  {67, 10 },
  {68, 10 },
  {69, 10 },
  {64, 11 },
  {64, 12 },
  {65, 12 },
  {66, 12 },
  {67, 12 },
  {68, 12 },
  {69, 12 },
  {70, 12 },          // "Synth Bass 2" patches
  {64, 13},
  {65, 13 },
  {66, 13 },
  {67, 13 },
  {68, 13 },
  {69, 13 },
  {70, 13 },
  {71, 13 },
  {64, 14 },
  {65, 14 },
  {66, 14 },
  {67, 14 },
  {68, 14 },
  {69, 14 },
  {70, 14 },
  {71, 14 },
  {64, 15 },
  {65, 15 },
  {64, 16 },
  {64, 17 },          // "Bass" patches
  {65, 17 },
  {64, 18 },
  {65, 18 },
  {65, 19 },
  {64, 19 },
  {66, 19 },
  {64, 20 },
  {64, 21 },
  {64, 22 },          // "Synth Stack" patches
  {66, 22 },
  {64, 23 },
  {65, 23 },
  {65, 22 },
  {67, 22 },
  {66, 23 },
  {67, 23 },
  {64, 24 },          // "Pad 1" patches
  {65, 24 },
  {66, 24 },
  {67, 24 },
  {68, 24 },
  {69, 24 },
  {70, 24 },
  {64, 25 },
  {65, 25 },
  {66, 25 },
  {67, 25 },
  {68, 25 },
  {69, 25 },
  {64, 26 },
  {65, 26 },
  {66, 26 },
  {67, 26 },
  {68, 26 },
  {69, 26 },
  {64, 27 },
  {65, 27 },          // "Pad 2" patches
  {66, 27 },
  {67, 27 },
  {68, 27 },
  {69, 27 },
  {70, 27 },
  {71, 27 },
  {72, 27 },
  {73, 27 },
  {64, 28 },
  {65, 28 },
  {66, 28 },
  {67, 28 },
  {64, 29 },          // "Strings" patches
  {65, 29 },
  {64, 30 },
  {65, 30 },
  {66, 30 },
  {67, 30 },
  {68, 30 },
  {64, 31 },
  {65, 31 },
  {66, 31 },
  {64, 32 },
  {65, 32 },
  {64, 33 },
  {64, 34 },          // "Voice" patches
  {67, 35 },
  {70, 35 },
  {72, 35 },
  {64, 35 },
  {65, 35 },
  {66, 35 },
  {68, 35 },
  {69, 35 },
  {71, 35 },
  {73, 35 },
  {74, 35 },
  {64, 41 },          // "Piano" patches
  {65, 41 },
  {64, 42 },
  {65, 42 },
  {66, 42 },
  {67, 42 },
  {64, 43 },
  {65, 43 },
  {64, 44 },
  {65, 44 },
  {66, 44 },
  {64, 45 },          // "Organ" patches
  {65, 45 },
  {64, 46 },
  {65, 46 },
  {64, 47 },
  {64, 48 },
  {65, 48 },
  {64, 49 },
  {64, 50 },
  {64, 51 },
  {64, 52 },
  {65, 52 },
  {64, 36 },          // "SFX 1" patches
  {65, 36 },
  {66, 36 },
  {67, 36 },
  {68, 36 },
  {69, 36 },
  {70, 36 },
  {71, 36 },
  {64, 37 },
  {65, 37 },
  {66, 37 },
  {67, 37 },
  {68, 37 },
  {69, 37 },
  {70, 37 },
  {71, 37 },
  {72, 37 },
  {64, 79 },          // "SFX 2" patches
  {65, 79 },
  {66, 79 },
  {64, 80 },
  {65, 80 },
  {64, 81 },
  {65, 81 },
  {66, 81 },
  {64, 82 },
  {65, 82 },
  {66, 82 },
  {67, 82 },
  {68, 82 },
  {69, 82 },
  {64, 83 },
  {65, 83 },
  {64, 84 },          // "SFX 3" patches
  {65, 84 },
  {66, 84 },
  {64, 85 },
  {65, 85 },
  {66, 85 },
  {67, 85 },
  {68, 85 },
  {64, 86 },
  {65, 86 },
  {66, 86 },
  {67, 86 },
  {68, 86 },
  {64, 38 },          // "Noise" patches
  {65, 38 },
  {66, 38 },
  {67, 38 },
  {64, 39 },
  {65, 39 },
  {66, 39 },
  {67, 39 },
  {64, 40 },
  {65, 40 },
  {64, 53 },          // "Chromatic percussion" patches
  {66, 53 },
  {65, 53 },
  {67, 53 },
  {64, 54 },
  {65, 54 },
  {64, 55 },
  {66, 55 },
  {67, 55 },
  {65, 55 },
  {64, 56 },
  {65, 56 },
  {64, 57 },
  {65, 57 },
  {67, 57 },
  {66, 57 },
  {68, 57 },
  {71, 57 },
  {69, 57 },
  {70, 57 },
  {64, 58 },          // "Guitar" patches
  {65, 58 },
  {64, 59 },
  {66, 60 },
  {65, 59 },
  {66, 59 },
  {67, 59 },
  {64, 60 },
  {65, 60 },
  {67, 60 },
  {68, 60 },
  {64, 62 },          // "Wind 1" patches
  {65, 62 },
  {66, 62 },
  {64, 63 },
  {65, 63 },
  {66, 63 },
  {64, 64 },
  {65, 64 },
  {64, 66 },
  {65, 66 },
  {66, 66 },
  {67, 66 },
  {68, 66 },
  {70, 66 },
  {72, 66 },
  {64, 65 },
  {71, 66 },
  {69, 66 },
  {73, 66 },
  {64, 67 },          // "Wind 2" patches
  {65, 67 },
  {66, 67 },
  {64, 68 },
  {65, 68 },
  {66, 68 },
  {64, 69 },
  {64, 70 },
  {65, 70 },
  {66, 70 },
  {67, 70 },
  {64, 71 },
  {64, 72 },          // "Ethnic" patches
  {65, 72 },
  {64, 73 },
  {64, 74},
  {64, 76 },
  {65, 76 },
  {66, 76 },
  {67, 76 },
  {68, 76 },
  {69, 76 },
  {70, 76 },
  {64, 77 },          // "Hit" patches
  {65, 77 },
  {66, 77 },
  {67, 77 },
  {68, 77 },
  {69, 77 },
  {70, 77 },
  {71, 77 },
  {72, 77 },
  {73, 77 },
  {64, 78 },
  {65, 78 },
  {66, 78 },
  {67, 78 }
 };


#endif
