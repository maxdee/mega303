#ifndef MCConstants_h
#define MCConstants_h

#define SCALE_BUTTON 113
#define FUNC_BUTTON 114
#define SHIFT_BUTTON 115

#define PART_SELECT_BUTTON 56
#define PART_MUTE_BUTTON 58
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

#define ENCODER_BUTTON 128
#define TAP_BUTTON 129

const int PART_BUTTON[] = {64, 65, 66, 67, 68, 69, 70, 71};

const int STEP_BUTTON[] = {32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7};
const int STEP_LOOKUP[40] = {9, 10, 11, 12, 13, 14, 15, 16,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0,
							 1, 2, 3, 4, 5, 6, 7, 8
						 	};
const int STEP_LED[] = {32, 33, 34, 35, 36, 37, 38, 39, 0, 1, 2, 3, 4, 5, 6, 7};

#define SONG_LED 40
#define PATTERN_LED 41
#define TRANSPOSE_LED 42
#define TRANSPOSE_LED 42
#define OCTAVE_DOWN_LED 43
#define OCTAVE_UP_LED 44
#define PTNSET_LED 45
#define RPSSET_LED 45
#define RECSTEP_LED 47

#define PART_SELECT_LED 56
#define PART_MUTE_LED 58
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

#endif
