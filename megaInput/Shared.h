#ifndef Shared_h
#define Shared_h


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
#define ID_MIN_PART 64
#define ID_MAX_PART 71

const uint8_t STEP_BUTTON[] = {32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7};

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

const uint8_t segmentRows[6] = {6, 3, 12, 13, 10, 15};

#endif
