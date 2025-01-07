#include "neslib.h"
const unsigned char frisk_0_data[]={

	  0, 16,0x07,0,
	  0,  0,0x01,0,
	  8,  0,0x03,0,
	 16,  0,0x05,0,
	  8, 16,0x09,0,
	 16, 16,0x0b,0,
	128

};

const unsigned char frisk_1_data[]={

	  0, 15,0x0d,0,
	  0,- 1,0x01,0,
	  8,- 1,0x03,0,
	 16,- 1,0x05,0,
	  8, 15,0x0f,0,
	 16, 15,0x0b,0,
	128

};

const unsigned char frisk_2_data[]={

	  0, 15,0x13,0,
	  0,- 1,0x01,0,
	  8,- 1,0x03,0,
	 16,- 1,0x05,0,
	  8, 15,0x15,0,
	 16, 15,0x0b,0,
	128

};

const unsigned char frisk_3_data[]={

	  0,  0,0x19,0,
	  8,  0,0x1b,0,
	 16,  0,0x1d,0,
	  0, 16,0x1f,0,
	  8, 16,0x21,0,
	128

};

const unsigned char frisk_4_data[]={

	  0,  1,0x19,0,
	  8,  1,0x1b,0,
	 16,  1,0x1d,0,
	  0, 17,0x23,0,
	  8, 17,0x25,0,
	128

};

const unsigned char frisk_5_data[]={

	 12,  0,0x19,0|OAM_FLIP_H,
	  4,  0,0x1b,0|OAM_FLIP_H,
	- 4,  0,0x1d,0|OAM_FLIP_H,
	 12, 16,0x1f,0|OAM_FLIP_H,
	  4, 16,0x21,0|OAM_FLIP_H,
	128

};

const unsigned char frisk_6_data[]={

	 12,  1,0x19,0|OAM_FLIP_H,
	  4,  1,0x1b,0|OAM_FLIP_H,
	- 4,  1,0x1d,0|OAM_FLIP_H,
	 12, 17,0x23,0|OAM_FLIP_H,
	  4, 17,0x25,0|OAM_FLIP_H,
	128

};

const unsigned char frisk_7_data[]={

	  0,  0,0x27,0,
	  8,  0,0x29,0,
	 16,  0,0x2b,0,
	  0, 16,0x2d,0,
	  8, 16,0x2f,0,
	 16, 16,0x31,0,
	128

};

const unsigned char frisk_8_data[]={

	  0,- 1,0x27,0,
	  8,- 1,0x29,0,
	 16,- 1,0x2b,0,
	  0, 15,0x33,0,
	  8, 15,0x35,0,
	 16, 15,0x37,0,
	128

};

const unsigned char frisk_9_data[]={

	  0,- 1,0x27,0,
	  8,- 1,0x29,0,
	 16,- 1,0x2b,0,
	  0, 15,0x39,0,
	  8, 15,0x3b,0,
	 16, 15,0x3d,0,
	128

};
const unsigned char *frisk_up[]={
    frisk_7_data,
    frisk_8_data,
    frisk_7_data,
    frisk_9_data
};
const unsigned char *frisk_left[]={
    frisk_3_data,
    frisk_4_data,
    frisk_3_data,
    frisk_4_data
};
const unsigned char *frisk_right[]={
    frisk_5_data,
    frisk_6_data,
    frisk_5_data,
    frisk_6_data
};
const unsigned char *frisk_down[]={
	frisk_0_data,
    frisk_1_data,
    frisk_0_data,
    frisk_2_data
};
const unsigned char **frisk_all[]={
    frisk_up,
    frisk_down,
    frisk_left,
    frisk_right
};
const unsigned char umbrella_0_data[]={

	  0,  0,0x3e,1,
	  8,  0,0x40,1,
	 16,  0,0x42,1,
	 24,  0,0x40,1|OAM_FLIP_H,
	 32,  0,0x3e,1|OAM_FLIP_H,
	 16, 16,0x44,1,
	128

};

