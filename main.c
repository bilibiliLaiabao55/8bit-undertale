#include "LIB/inc.c"
#include "MMC3/mmc3_code.h"
#include "MMC3/mmc3_code.c"
#include "MUSIC/famistudio_cc65.h"
// should be in the regular 0x300 ram now
#pragma bss-name(push, "ZEROPAGE")
long temp0=0;
#pragma bss-name(pop)
#pragma bss-name(push, "XRAM")
// extra RAM at $6000-$7fff
unsigned char wram_array[0x2000];

#pragma bss-name(pop)
#pragma rodata-name ("BANK0")
#pragma code-name ("BANK0")
void play_story_cut(){
    ppu_off();
    pal_clear();
    set_prg_8000(0);
    pal_all(story_pal);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro1);
    ppu_wait_nmi();
    ppu_on_all();

    {
        //one_vram_buffer();
        delay(120);
    }
    delay(120);
    pal_fade_to(4, 0);

    ppu_off();
    bank_bg(1);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro2);
    ppu_wait_nmi();
    ppu_on_all();

    pal_fade_to(0, 4);
}
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")
void main(){
    //disable_irq(); // This disable irq is for some bug with famistudio engine
    //now this code had move into crt0.s
    ppu_off();
    oam_size(1);
    ppu_on_all();
    famistudio_music_play(0);
    banked_call(0, play_story_cut);

    while(TRUE){
        oam_clear();
        ppu_wait_nmi();
    }
}