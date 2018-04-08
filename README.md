## MC-303 Moding ##
*** Work in progress ***
Unsatisfied with this GrooveBox's workflow, making a new instrument by taking over its frontend.

### Requires printf ###
https://playground.arduino.cc/Main/Printf

Since we only have 6 seven segment digits to write to, we reduce the buffer size: `#define PRINTF_BUF 16 // define the tmp buffer size (change if desired)`


### Knob Grid ###


|#|AccentRate|Timing|Time/Rate|LFO|Cutoff|Resonance|Envelope|
|---|     ---|   ---|      ---|---|   ---|      ---|     ---|
|0|PART_DECAY|PART_ATTACK|PART_FINE_TUNE|PART_COARSE_TUNE|PART_CUTOFF|PART_RESONANCE|PART_RELEASE|
|1|   |PART_VIBRATO_RATE|PART_VIBRATO_DEPTH|PART_VIBRATO_DELAY|PART_MODULATION|PART_PAN|PART_VOLUME|
|2|   |CHORUS_TYPE|CHORUS_RATE|CHORUS_FEEDBACK|   |   |PART_CHORUS_DEPTH|
|3|   |REVERB_TYPE|REVERB_TIME|REVERB_FEEDBACK|   |   |PART_REVERB_DEPTH|
|4|PART_DRUM_PITCH|PART_DRUM_TVA|PART_DRUM_PAN|PART_DRUM_REVERB|PART_DRUM_CHORUS|PART_DRUM_PAN|PART_VOLUME|
|5|   |   |   |   |   |   |
