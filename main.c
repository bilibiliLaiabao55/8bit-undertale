#include "LIB/inc.h"
#include "MMC3/mmc3_code.h"
#include "MMC3/mmc3_code.c"
#include "MUSIC/famistudio_cc65.h"
//bank 0 for intro
//bank 1 for save data
//bank 2 for objects like frisk and toriel
//bank 3 for level update
//bank 4 for battle
//bank 5 for cutscencs
//bank 6 for cutscencs, too
//bank 7 for shop
//bank 8 for level music
//bank 9 for cutscencs music
//bank 10 for battle music
//bank 11 for chara music
//bank 12 for sfx
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
unsigned char saved;

#pragma bss-name(pop)
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")
void pal_one(const unsigned char *pal_data, unsigned char pal_index){
    pal_col(pal_index*4,   pal_data[0]);
    pal_col(pal_index*4+1, pal_data[1]);
    pal_col(pal_index*4+2, pal_data[2]);
    pal_col(pal_index*4+3, pal_data[3]);
}
void get_pad_all(){
    pad_state_1 = pad_poll(0);
    pad_new_1 = get_pad_new(0);
}
#pragma rodata-name ("BANK0")
#pragma code-name ("BANK0")
void set_pal_intro(){
    pal_clear();
    pal_all(story_pal);
}
void play_intro(){
    set_chr_mode_2(0);
    set_chr_mode_3(1);
    set_chr_mode_4(2);
    set_chr_mode_5(3);
    famistudio_music_play(0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro1);
    ppu_wait_nmi();
    ppu_on_all();
    delay(255);
    delay(225);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_3(4);
    set_chr_mode_4(5);
    set_chr_mode_5(6);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro2);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    delay(255);
    delay(45);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_3(7);
    set_chr_mode_4(8);
    set_chr_mode_5(9);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro3);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    delay(255);
    delay(45);
    pal_fade_to(4, 0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro4);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    delay(255);
    delay(45);
    pal_fade_to(4, 0);
    ppu_off();
    vram_adr(NAMETABLE_A);
    vram_unrle(intro5);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    delay(255);
    delay(45);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_3(10);
    set_chr_mode_4(11);
    set_chr_mode_5(12);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro6);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    delay(255);
    delay(45);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(13);
    set_chr_mode_3(14);
    set_chr_mode_4(15);
    set_chr_mode_5(16);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro7);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=2;temp0>0;--temp0)delay(255);
    delay(90);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(17);
    set_chr_mode_3(18);
    set_chr_mode_4(19);
    set_chr_mode_5(20);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro8);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=2;temp0>0;--temp0)delay(255);
    delay(90);
    pal_fade_to(4, 0);
    ppu_off();
    set_chr_mode_2(20);
    set_chr_mode_3(21);
    set_chr_mode_4(22);
    set_chr_mode_5(23);
    vram_adr(NAMETABLE_A);
    vram_unrle(intro9);
    ppu_wait_nmi();
    ppu_on_all();
    pal_fade_to(0, 4);
    for(temp0=7;temp0>0;--temp0)delay(255);
    delay(15);
    pal_fade_to(4, 0);
}
void play_title(){
    temp1 = 1;
    while(temp1 == 1){
        set_pal_intro();
        play_intro();
        famistudio_music_stop();
        delay(60);
        set_chr_mode_2(24);
        set_chr_mode_3(25);
        ppu_off();
        vram_adr(NAMETABLE_A);
        vram_unrle(title);
        ppu_wait_nmi();
        ppu_on_all();
        famistudio_sfx_play(0, FAMISTUDIO_SFX_CH0);
        pal_bright(4);
        temp0 = 1800;
        while(temp1 == 1){
            pad_state_1 = pad_poll(0);
            pad_new_1 = get_pad_new(0);
            if((pad_state_1 & PAD_LEFT)&&(pad_state_1 & PAD_UP)&&(pad_state_1 & PAD_B)&&(pad_new_1 & PAD_A)){
                famistudio_sfx_play(1, FAMISTUDIO_SFX_CH0);
                temp1 = 1800;
            }
            if(pad_new_1 & PAD_START){
                temp1 = 0;
            }
            if(temp0 == 0)break;
            --temp0;
            ppu_wait_nmi();
        }
    }
}
#pragma rodata-name ("BANK1")
#pragma code-name ("BANK1")
void set_frisk(){
    set_chr_mode_0(26);
    pal_one(frisk_pal, 4);
    frisk_face = FRISK_FACE_DOWN;
}
void update_frisk(){
    oam_meta_spr(frisk_x, frisk_y, frisk_all[frisk_face][frisk_frame]);
    if(pad_state_1 & PAD_UP){
        frisk_y-=2;
        frisk_face=FRISK_FACE_UP;
    }
    if(pad_state_1 & PAD_DOWN){
        frisk_y+=2;
        frisk_face=FRISK_FACE_DOWN;
    }
    if(pad_state_1 & PAD_LEFT){
        frisk_x-=2;
        frisk_face=FRISK_FACE_LEFT;
    }
    if(pad_state_1 & PAD_RIGHT){
        frisk_x+=2;
        frisk_face=FRISK_FACE_RIGHT;
    }
    if((pad_state_1 & PAD_UP)||(pad_state_1 & PAD_DOWN)||(pad_state_1 & PAD_LEFT)||(pad_state_1 & PAD_RIGHT)){
        if(frisk_frame_delay==0){
            ++frisk_frame;
            frisk_frame_delay=8;
            if(frisk_frame==4)frisk_frame=0;
        }else --frisk_frame_delay;
    }else{
        frisk_frame = 0;
        frisk_frame_delay = 0;
    }
}
#pragma rodata-name ("BANK2")
#pragma code-name ("BANK2")
void set_bk_tileset(){
    set_chr_mode_2(0);
    set_chr_mode_3(1);
}
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")
void main(){
    //disable_irq(); // This disable irq is for some bug with famistudio engine
    //now this code had move into crt0.s
    set_wram_mode(WRAM_ON);
    ppu_off();
    ppu_on_all();
    set_vram_buffer();

    banked_call(0, play_title);
    banked_call(1, set_frisk);

    famistudio_music_play(3);
    banked_call(2, set_bk_tileset);
    while(TRUE){
        oam_clear();
        get_pad_all();
        banked_call(1, update_frisk);
        ppu_wait_nmi();
        ppu_wait_nmi();
    }
}