#include "LIB/neslib.h"
#include "LIB/nesdoug.h" 
#include "MMC3/mmc3_code.h"
#include "MMC3/mmc3_code.c"
#include "MUSIC/famistudio_cc65.h"
// should be in the regular 0x300 ram now

unsigned char irq_array[32];
unsigned char double_buffer[32];

#pragma bss-name(push, "XRAM")
// extra RAM at $6000-$7fff
unsigned char wram_array[0x2000];

#pragma bss-name(pop)
void main(){
    //set_prg_8000(12);
    famistudio_music_play(0);
    ppu_off();
    oam_size(1);
    ppu_on_all();
    while(TRUE){
        ppu_wait_nmi();
    }
}