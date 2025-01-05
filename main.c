#include "LIB/inc.c"
#include "MMC3/mmc3_code.h"
#include "MMC3/mmc3_code.c"
#include "MUSIC/famistudio_cc65.h"
#pragma bss-name(push, "ZEROPAGE")
long temp0=0;
long temp1=0;
unsigned char pad_state_1;
unsigned char pad_new_1;
#pragma bss-name(pop)
#pragma bss-name(push, "XRAM")
// extra RAM at $6000-$7fff
unsigned char wram_array[0x2000];

#pragma bss-name(pop)
#pragma rodata-name ("BANK0")
#pragma code-name ("BANK0")
void set_pal_intro(){
    pal_clear();
    pal_all(story_pal);
}
void play_story_cut(){
    famistudio_music_play(0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro1);
    ppu_wait_nmi();
    ppu_on_all();
    for(temp0=480;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(4);
    set_chr_mode_3(5);
    set_chr_mode_4(6);
    set_chr_mode_5(7);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro2);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=300;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(8);
    set_chr_mode_3(9);
    set_chr_mode_4(10);
    set_chr_mode_5(11);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro3);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=300;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro4);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=300;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro5);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=300;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(12);
    set_chr_mode_3(13);
    set_chr_mode_4(14);
    set_chr_mode_5(15);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro6);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=300;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(16);
    set_chr_mode_3(17);
    set_chr_mode_4(18);
    set_chr_mode_5(19);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro7);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=600;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(20);
    set_chr_mode_3(21);
    set_chr_mode_4(22);
    set_chr_mode_5(23);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro8);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=600;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(24);
    set_chr_mode_3(25);
    set_chr_mode_4(26);
    set_chr_mode_5(27);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro9);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=1800;temp0>0;--temp0)ppu_wait_nmi();
    pal_fade_to(4, 0);
}
void play_title(){
    set_chr_mode_2(28);
    set_chr_mode_3(29);
    set_chr_mode_4(30);
    set_chr_mode_5(31);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(title);
    ppu_wait_nmi();
    ppu_on_all();
    famistudio_sfx_play(0, FAMISTUDIO_SFX_CH0);
    pal_bright(4);
    while(TRUE){
        pad_state_1 = pad_poll(0);
        pad_new_1 = get_pad_new(0);
        if((pad_state_1 & PAD_LEFT)&&(pad_state_1 & PAD_UP)&&(pad_state_1 & PAD_B)&&(pad_new_1 & PAD_A))famistudio_sfx_play(1, FAMISTUDIO_SFX_CH0);
        if(pad_new_1 & PAD_START)break;
        ppu_wait_nmi();
    }
}
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")
void main(){
    //disable_irq(); // This disable irq is for some bug with famistudio engine
    //now this code had move into crt0.s
    ppu_off();
    banked_call(0, set_pal_intro);
    oam_size(1);
    ppu_on_all();
    banked_call(0, play_story_cut);
    famistudio_music_stop();
    //for(temp0=60;temp0>0;--temp0)ppu_wait_nmi();
    banked_call(0, play_title);

    while(TRUE){
        oam_clear();
        ppu_wait_nmi();
    }
}