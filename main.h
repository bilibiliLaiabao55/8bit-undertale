#pragma bss-name(push, "ZEROPAGE")
long temp0=0;
long temp1=0;
unsigned char pad_state_1;
unsigned char pad_new_1;
unsigned char frisk_x;
unsigned char frisk_y;
unsigned char frisk_face;
unsigned char frisk_frame_delay;
unsigned char frisk_frame;
#pragma bss-name(pop)
#pragma bss-name(push, "XRAM")
// extra RAM at $6000-$7fff
unsigned char wram_array[0x2000];

#pragma bss-name(pop)