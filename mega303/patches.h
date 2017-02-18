// Patch info from https://github.com/james7780/EG101

// Pathc categories
char *patchCategories[22] = {
  "Synth 1",
  "Synth 2",
  "Syn Bs 1",
  "Syn Bs 2",
  "Bass",
  "Syn Stack",
  "Pad 1",
  "Pad 2",
  "Strings",
  "Voice",
  "Piano",
  "Organ",
  "SFX 1",
  "SFX 2",
  "SFX 3",
  "Noise",
  "Chr. Perc",
  "Guitar",
  "Wind 1",
  "Wind 2",
  "Ethnic",
  "Hit" };

// The info for patches
typedef struct {
  char name[14];
  byte bank;
  byte pc;
} PATCHINFO;

// JH 2015-05-03 - Updated for Arduino 1.6.0
//PROGMEM PATCHINFO patchInfo[440] = {
const PATCHINFO PROGMEM patchInfo[440] = {
  { "Lead TB1", 64, 1 },          // "Synth 1" patches
  { "Lead TB2", 65, 1 },
  { "Lead TB3", 67, 1 },
  { "Wow TB", 66, 1 },
  { "MG Saw", 64, 2 },
  { "Voc Saw", 65, 2 },
  { "Cheese Saw", 66, 2 },
  { "Saw Lead", 67, 2 },
  { "Calc Saw", 68, 2 },
  { "OB2 Saw 1", 69, 2 },
  { "Juno6 Saw", 70, 2 },
  { "JP8 Pls", 71, 2 },
  { "MG Pls", 72, 2 },
  { "Flicker", 73, 2 },
  { "Tri Lead 1", 64, 3 },
  { "Tri Lead 2", 65, 3 },
  { "PR5 Squ", 66, 3 },
  { "JU2 SubOsc", 64, 4 },
  { "Frog Wave", 65, 4 },
  { "Seq.Synth", 64, 5 },

  { "Polysynth", 65, 5 },          // "Synth 2" patches
  { "JP8 Pls.2", 66, 5 },
  { "JP8 Squ", 67, 5 },
  { "260 Pls.90", 68, 5 },
  { "Reso Pls", 69, 5 },
  { "Reso Stack", 70, 5 },
  { "Soft Lead", 64, 6 },
  { "8DV Saw 1", 65, 6 },
  { "PR5 Saw 1", 66, 6 },
  { "D50 Saw", 67, 6 },
  { "MG Sweep", 64, 7 },
  { "Sweep Lead", 65, 7 },
  { "Vocoderman", 66, 7 },
  { "4th Lead 1", 64, 8 },
  { "4th Lead 2", 65, 8 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Normal TB", 64, 9 },          // "Synth Bass 1" patches
  { "Dist TB 1", 65, 9 },
  { "Dist TB 2", 66, 9 },
  { "Acid TB 1", 67, 9 },
  { "Acid TB 2", 68, 9 },
  { "Acid TB 3", 69, 9 },
  { "Acid TB 4", 70, 9 },
  { "101 Bass 1", 64, 10 },
  { "101 Bass 2", 65, 10 },
  { "101 Bass 3", 66, 10 },
  { "House Bass", 67, 10 },
  { "Sine Bass", 68, 10 },
  { "Dub Bass", 69, 10 },
  { "Pizz Bass", 64, 11 },
  { "MG Bass 1", 64, 12 },
  { "MG Bass 2", 65, 12 },
  { "MG Bass 3", 66, 12 },
  { "MG Bass 4", 67, 12 },
  { "FM Bass", 68, 12 },
  { "Cheese Bass", 69, 12 },

  { "Syn SB Bass", 70, 12 },          // "Synth Bass 2" patches
  { "Blip Bass", 64, 13},
  { "KGP Bass", 65, 13 },
  { "TBMG Bass 1", 66, 13 },
  { "MG Bass 5", 67, 13 },
  { "JPMG Bass", 68, 13 },
  { "Click Bass", 69, 13 },
  { "KMP Bass", 70, 13 },
  { "Osc.Bass", 71, 13 },
  { "Reso Bass", 64, 14 },
  { "Wow MG Bass", 65, 14 },
  { "Wow 101 Bass", 66, 14 },
  { "SweepWowBass", 67, 14 },
  { "MG 5th Bass", 68, 14 },
  { "Doom Bass", 69, 14 },
  { "Rubber Bass 1", 70, 14 },
  { "Rubber Bass 2", 71, 14 },
  { "Acid Bass", 64, 15 },
  { "Bubble Bass", 65, 15 },
  { "Organ Bass", 64, 16 },

  { "Ac Bass 1", 64, 17 },          // "Bass" patches
  { "Ac Bass 2", 65, 17 },
  { "Fingrd Bs 1", 64, 18 },
  { "Fingrd Bs 2", 65, 18 },
  { "Dust Pick Bs", 65, 19 },
  { "Picked Bs 1", 64, 19 },
  { "Picked Bs 2", 66, 19 },
  { "Fretless Bs", 64, 20 },
  { "Slap Bass", 64, 21 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Syn Stack 1", 64, 22 },          // "Synth Stack" patches
  { "Syn Stack 2", 66, 22 },
  { "Syn SB 1", 64, 23 },
  { "Syn SB 2", 65, 23 },
  { "Oct Stack", 65, 22 },
  { "Saw Stack", 67, 22 },
  { "Brass Perc", 66, 23 },
  { "Dirty SB", 67, 23 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Atmosphere", 64, 24 },          // "Pad 1" patches
  { "FeedBackWv", 65, 24 },
  { "X-MOD", 66, 24 },
  { "Pacifica", 67, 24 },
  { "7th Atom", 68, 24 },
  { "Outer Space", 69, 24 },
  { "Rev Atom", 70, 24 },
  { "2.2 Pad", 64, 25 },
  { "Jungle Pad", 65, 25 },
  { "Psycho Pad", 66, 25 },
  { "Pipe Pad", 67, 25 },
  { "Ambient Pad", 68, 25 },
  { "Flanger Pad", 69, 25 },
  { "Bell Pad", 64, 26 },
  { "7th Bell Pad", 65, 26 },
  { "Fantasia", 66, 26 },
  { "Crystal", 67, 26 },
  { "Exo Bell Pad", 68, 26 },
  { "Echo Bell", 69, 26 },
  { "Warm Pad", 64, 27 },

  { "Soundtrack", 65, 27 },          // "Pad 2" patches
  { "Oct Pad", 66, 27 },
  { "OB Str Pad", 67, 27 },
  { "X-MOD Pad", 68, 27 },
  { "Sweep Pad 1", 69, 27 },
  { "Sweep Pad 2", 70, 27 },
  { "OB Soft Pad", 71, 27 },
  { "Goblin", 72, 27 },
  { "Echo Drops", 73, 27 },
  { "Random Pad", 64, 28 },
  { "LFO Sweep", 65, 28 },
  { "Horror Pad", 66, 28 },
  { "Pls Key Pad", 67, 28 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Real Str 1", 64, 29 },          // "Strings" patches
  { "Real Str 2", 65, 29 },
  { "Auh Str", 64, 30 },
  { "Hi Str", 65, 30 },
  { "Syn Str 1", 66, 30 },
  { "Syn Str 2", 67, 30 },
  { "Syn Str 3", 68, 30 },
  { "Noise Str", 64, 31 },
  { "RND Str", 65, 31 },
  { "LFO Str", 66, 31 },
  { "Slow Str", 64, 32 },
  { "Slow Syn Str", 65, 32 },
  { "Pizz Str", 64, 33 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Choir Auhs", 64, 34 },          // "Voice" patches
  { "Auh", 67, 35 },
  { "Auh Auh", 70, 35 },
  { "Auhbient", 72, 35 },
  { "Space voice", 64, 35 },
  { "Sweepvox", 65, 35 },
  { "Synthvox 1", 66, 35 },
  { "Synthvox 2", 68, 35 },
  { "Leadvox", 69, 35 },
  { "Sky Vox", 71, 35 },
  { "Vibravox", 73, 35 },
  { "Noisevox", 74, 35 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Ac Piano", 64, 41 },          // "Piano" patches
  { "Bright Piano", 65, 41 },
  { "E. Piano 1", 64, 42 },
  { "E. Piano 2", 65, 42 },
  { "E. Piano 3", 66, 42 },
  { "E. Piano 4", 67, 42 },
  { "Org.E.Piano", 64, 43 },
  { "Noise Piano", 65, 43 },
  { "Clavichord", 64, 44 },
  { "Analog Clav", 65, 44 },
  { "Digi Clav", 66, 44 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Organ 1", 64, 45 },          // "Organ" patches
  { "Lp-Hp Organ", 65, 45 },
  { "Organ 2", 64, 46 },
  { "Perc Organ", 65, 46 },
  { "Slow organ", 64, 47 },
  { "SmkyOrgChrd", 64, 48 },
  { "Organ Chord", 65, 48 },
  { "60's Organ", 64, 49 },
  { "Dist Organ", 64, 50 },
  { "Church Organ", 64, 51 },
  { "Organ Loop", 64, 52 },
  { "LF-Organ", 65, 52 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "UFO SFX", 64, 36 },          // "SFX 1" patches
  { "Saw in Saw", 65, 36 },
  { "Feed Bell", 66, 36 },
  { "Abduction", 67, 36 },
  { "Loop Sweep", 68, 36 },
  { "UP FX", 69, 36 },
  { "Rodocorder", 70, 36 },
  { "Noise Grow", 71, 36 },
  { "LFO Techno", 64, 37 },
  { "Calculating", 65, 37 },
  { "Emergency!", 66, 37 },
  { "FX Beats", 67, 37 },
  { "Analog FX", 68, 37 },
  { "Transformer", 69, 37 },
  { "Dusty Scratch", 70, 37 },
  { "Space Worms", 71, 37 },
  { "Winky FX", 72, 37 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Scratch Rew", 64, 79 },          // "SFX 2" patches
  { "Scratch Push", 65, 79 },
  { "Scratch Pull", 66, 79 },
  { "Tape Rewind", 64, 80 },
  { "Vinyl Stop", 65, 80 },
  { "Starship", 64, 81 },
  { "Burst Noise", 65, 81 },
  { "Laser-gun", 66, 81 },
  { "Seashore", 64, 82 },
  { "Rain", 65, 82 },
  { "Thunder", 66, 82 },
  { "Wind", 67, 82 },
  { "Stream", 68, 82 },
  { "Bubble", 69, 82 },
  { "Bird", 64, 83 },
  { "Low Bird", 65, 83 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Telephone", 64, 84 },          // "SFX 3" patches
  { "Gun Shot", 65, 84 },
  { "Machine-gun", 66, 84 },
  { "Car Pass", 64, 85 },
  { "Car Crash", 65, 85 },
  { "Siren", 66, 85 },
  { "Jet Plane", 67, 85 },
  { "Helicopter", 68, 85 },
  { "Laughing", 64, 86 },
  { "Screaming", 65, 86 },
  { "Punch", 66, 86 },
  { "Heart Beat", 67, 86 },
  { "Applause", 68, 86 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "PR5 Noise 1", 64, 38 },          // "Noise" patches
  { "PR5 Noise 2", 65, 38 },
  { "Pink Noise", 66, 38 },
  { "White Noise", 67, 38 },
  { "Bomb Wind", 64, 39 },
  { "Syn Wind", 65, 39 },
  { "Vinyl Noise", 66, 39 },
  { "Noise Snare", 67, 39 },
  { "Explosion", 64, 40 },
  { "Pink Bomb", 65, 40 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Glockenspiel", 64, 53 },          // "Chromatic percussion" patches
  { "Beat glocken", 66, 53 },
  { "Vibraphone", 65, 53 },
  { "Marimba", 67, 53 },
  { "Timpani", 64, 54 },
  { "Steel Drum", 65, 54 },
  { "Sqr Perc", 64, 55 },
  { "MG Perc", 66, 55 },
  { "Perc Glass", 67, 55 },
  { "Juno Bell", 65, 55 },
  { "Tubular Bell", 64, 56 },
  { "Vib Bell", 65, 56 },
  { "7th Bells", 64, 57 },
  { "Ring Bell", 65, 57 },
  { "Ring Mod", 67, 57 },
  { "Digi Bell 1", 66, 57 },
  { "Digi Bell 2", 68, 57 },
  { "Digi Bell 3", 71, 57 },
  { "Dirty Bell 1", 69, 57 },
  { "Dirty Bell 2", 70, 57 },

  { "Steel Str Gtr", 64, 58 },          // "Guitar" patches
  { "12 Str Gtr", 65, 58 },
  { "Jazz Gtr", 64, 59 },
  { "Jazz Stl Gtr", 66, 60 },
  { "Clean Gtr", 65, 59 },
  { "Dist Gtr", 66, 59 },
  { "Gt. Harmonics", 67, 59 },
  { "Acid Gtr 1", 64, 60 },
  { "Acid Gtr 2", 65, 60 },
  { "Sitar Gtr", 67, 60 },
  { "Wah Gtr", 68, 60 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Brass 1", 64, 62 },          // "Wind 1" patches
  { "Brite Brs 1", 65, 62 },
  { "Brite Brs 2", 66, 62 },
  { "Brass+Str", 64, 63 },
  { "SB Brs Sect", 65, 63 },
  { "ST Brs Sect", 66, 63 },
  { "OB Brass", 64, 64 },
  { "Hybrid Brs", 65, 64 },
  { "Syn Brs 1", 64, 66 },
  { "Syn Brs 2", 65, 66 },
  { "Br.Syn.Brs.1", 66, 66 },
  { "Br.Syn.Brs.2", 67, 66 },
  { "Warm Brs 1", 68, 66 },
  { "Warm Brs 2", 70, 66 },
  { "Warm Brs 3", 72, 66 },
  { "4th Brass", 64, 65 },
  { "Str Brs", 71, 66 },
  { "Stack Brs 1", 69, 66 },
  { "Stack Brs 2", 73, 66 },
  { "---", 0, 0 },

  { "Trumpet", 64, 67 },          // "Wind 2" patches
  { "Mute Trumpet", 65, 67 },
  { "Sax+Trumpet", 66, 67 },
  { "Alto Sax", 64, 68 },
  { "Baritone Sax", 65, 68 },
  { "Bright Sax", 66, 68 },
  { "Flute", 64, 69 },
  { "Pan Flute", 64, 70 },
  { "Afro Flute", 65, 70 },
  { "Pipe Lead 1", 66, 70 },
  { "Pipe Lead 2", 67, 70 },
  { "Shakuhachi", 64, 71 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },

  { "Sitar 1", 64, 72 },          // "Ethnic" patches
  { "Sitar 2", 65, 72 },
  { "Kalimba", 64, 73 },
  { "Bagpipe", 64, 74},
  { "MG Blip 1", 64, 76 },
  { "Rev Blip", 65, 76 },
  { "MG Blip 2", 66, 76 },
  { "Syn Perc", 67, 76 },
  { "Powa", 68, 76 },
  { "Douby", 69, 76 },
  { "P-Mod Perc", 70, 76 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },


  { "Bam Hit", 64, 77 },          // "Hit" patches
  { "Bit Hit", 65, 77 },
  { "Orch Hit", 66, 77 },
  { "BF Hit", 67, 77 },
  { "Organ Hit", 68, 77 },
  { "Bim Hit", 69, 77 },
  { "Dist Hit", 70, 77 },
  { "Brass Fall", 71, 77 },
  { "Str Hit", 72, 77 },
  { "Space Frog", 73, 77 },
  { "Hoo!", 64, 78 },
  { "Ha!", 65, 78 },
  { "Afro Feet", 66, 78 },
  { "Breath 3", 67, 78 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 },
  { "---", 0, 0 }

 };
