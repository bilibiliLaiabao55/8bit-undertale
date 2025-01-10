; Startup code for cc65 and Shiru's NES library
; based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>




; Edited to work with MMC3 code
.define SOUND_BANK 12
;segment BANK12






;REMOVED initlib
;this called the CONDES function

    .export _exit,__STARTUP__:absolute=1
	.import push0,popa,popax,_main,zerobss,copydata

; Linker generated symbols
	.import __STACK_START__   ,__STACKSIZE__ ;changed
	.import __ROM0_START__  ,__ROM0_SIZE__
	.import __STARTUP_LOAD__,__STARTUP_RUN__,__STARTUP_SIZE__
	.import	__CODE_LOAD__   ,__CODE_RUN__   ,__CODE_SIZE__
	.import	__RODATA_LOAD__ ,__RODATA_RUN__ ,__RODATA_SIZE__
	.import NES_MAPPER, NES_PRG_BANKS, NES_CHR_BANKS, NES_MIRRORING

    .include "zeropage.inc"




PPU_CTRL	=$2000
PPU_MASK	=$2001
PPU_STATUS	=$2002
PPU_OAM_ADDR=$2003
PPU_OAM_DATA=$2004
PPU_SCROLL	=$2005
PPU_ADDR	=$2006
PPU_DATA	=$2007
PPU_OAM_DMA	=$4014
PPU_FRAMECNT=$4017
DMC_FREQ	=$4010
CTRL_PORT1	=$4016
CTRL_PORT2	=$4017

OAM_BUF		=$0200
;PAL_BUF		=$01c0
VRAM_BUF	=$0700


.segment "BSS"
PAL_BUF: .res 32
;move this out of the hardware stack
;the mmc3 code is using more of the stack
;and might collide with $1c0-1df



.segment "ZEROPAGE"

NTSC_MODE: 			.res 1
FRAME_CNT1: 		.res 1
FRAME_CNT2: 		.res 1
VRAM_UPDATE: 		.res 1
NAME_UPD_ADR: 		.res 2
NAME_UPD_ENABLE: 	.res 1
PAL_UPDATE: 		.res 1
PAL_BG_PTR: 		.res 2
PAL_SPR_PTR: 		.res 2
SCROLL_X: 			.res 1
SCROLL_Y: 			.res 1
SCROLL_X1: 			.res 1
SCROLL_Y1: 			.res 1
PAD_STATE: 			.res 2		;one byte per controller
PAD_STATEP: 		.res 2
PAD_STATET: 		.res 2
PPU_CTRL_VAR: 		.res 1
PPU_CTRL_VAR1: 		.res 1
PPU_MASK_VAR: 		.res 1
RAND_SEED: 			.res 2

TEMP: 				.res 11
SPRID:				.res 1

PAD_BUF		=TEMP+1

PTR			=TEMP	;word
LEN			=TEMP+2	;word
NEXTSPR		=TEMP+4
SCRX		=TEMP+5
SCRY		=TEMP+6
SRC			=TEMP+7	;word
DST			=TEMP+9	;word

RLE_LOW		=TEMP
RLE_HIGH	=TEMP+1
RLE_TAG		=TEMP+2
RLE_BYTE	=TEMP+3

;nesdoug code requires
VRAM_INDEX:			.res 1
META_PTR:			.res 2
DATA_PTR:			.res 2





.segment "HEADER"

    .byte $4e,$45,$53,$1a
	.byte <NES_PRG_BANKS
	.byte <NES_CHR_BANKS
	.byte <NES_MIRRORING|(<NES_MAPPER<<4)
	.byte <NES_MAPPER&$f0
	.byte 1 ;8k of PRG RAM
	.res 7,0


; linker complains if I don't have at least one mention of each bank
.segment "ONCE"
.segment "BANK0"
.segment "BANK1"
.segment "BANK2"
.segment "BANK3"
.segment "BANK4"
.segment "BANK5"
.segment "BANK6"
.segment "BANK7"
.segment "BANK8"
.segment "BANK9"
.segment "BANK10"
.segment "BANK11"
.segment "BANK12"


.segment "STARTUP"
; this should be mapped to the last PRG bank

start:
_exit:

    sei
	cld
	ldx #$40
	stx CTRL_PORT2
    ldx #$ff
    txs
    inx
    stx PPU_MASK
    stx DMC_FREQ
    stx PPU_CTRL		;no NMI
	
	
	;x is zero

initPPU:
    bit PPU_STATUS
@1:
    bit PPU_STATUS
    bpl @1
@2:
    bit PPU_STATUS
    bpl @2

clearPalette:
	lda #$3f
	sta PPU_ADDR
	stx PPU_ADDR
	lda #$0f
	ldx #$20
@1:
	sta PPU_DATA
	dex
	bne @1
	
	
;	lda #$01				; DEBUGGING
;	sta PPU_DATA
;	lda #$11
;	sta PPU_DATA
;	lda #$21
;	sta PPU_DATA
;	lda #$30
;	sta PPU_DATA

clearVRAM:
	txa
	ldy #$20
	sty PPU_ADDR
	sta PPU_ADDR
	ldy #$10
@1:
	sta PPU_DATA
	inx
	bne @1
	dey
	bne @1

clearRAM:
    txa
@1:
    sta $000,x
    sta $100,x
    sta $200,x
    sta $300,x
    sta $400,x
    sta $500,x
    sta $600,x
    sta $700,x
    inx
    bne @1
	
; don't call any subroutines until the banks are in place	
	
	
	
; MMC3 reset

; set which bank at $8000
; also $c000 fixed to 14 of 15
	lda #0 ; PRG bank zero
	jsr _set_prg_8000
; set which bank at $a000
	lda #13 ; PRG bank 13 of 15
	jsr _set_prg_a000
	
; with CHR invert, set $0000-$03FF
	lda #0
	jsr _set_chr_mode_2
; with CHR invert, set $0400-$07FF
	lda #1
	jsr _set_chr_mode_3
; with CHR invert, set $0800-$0BFF
	lda #2
	jsr _set_chr_mode_4
; with CHR invert, set $0C00-$0FFF
	lda #3
	jsr _set_chr_mode_5
; with CHR invert, set $1000-$17FF
	lda #4
	jsr _set_chr_mode_0
; with CHR invert, set $1800-$1FFF
	lda #6
	jsr _set_chr_mode_1
;set mirroring to vertical, no good reason	
	lda #0
	jsr _set_mirroring
;allow reads and writes to WRAM	
	lda #$80 ;WRAM_ON 0x80
	jsr _set_wram_mode
	
	cli ;allow irq's to happen on the 6502 chip	
		;however, the mmc3 IRQ was disabled above
	
	



    jsr zerobss
	jsr	copydata

    lda #<(__STACK_START__+__STACKSIZE__) ;changed
    sta	sp
    lda	#>(__STACK_START__+__STACKSIZE__)
    sta	sp+1            ; Set argument stack ptr

;	jsr	initlib
; removed. this called the CONDES function





	








	lda #%10000000
	sta <PPU_CTRL_VAR
	sta PPU_CTRL		;enable NMI
	lda #%00000110
	sta <PPU_MASK_VAR

waitSync3:
	lda <FRAME_CNT1
@1:
	cmp <FRAME_CNT1
	beq @1

detectNTSC:
	ldx #52				;blargg's code
	ldy #24
@1:
	dex
	bne @1
	dey
	bne @1

	lda PPU_STATUS
	and #$80
	sta <NTSC_MODE

	jsr _ppu_off

	lda #0
	ldx #0
	jsr _set_vram_update

	lda #$fd
	sta <RAND_SEED
	sta <RAND_SEED+1

	lda #0
	sta PPU_SCROLL
	sta PPU_SCROLL
	
	
	
;BANK12
	
	lda #SOUND_BANK ;swap the music in place before using
					;SOUND_BANK is defined above
	jsr _set_prg_8000
	
	ldx #<music_data_undertale
	ldy #>music_data_undertale
	lda 1
	jsr famistudio_init

	ldx #<sounds
	ldy #>sounds
	jsr famistudio_sfx_init
	
	lda #$00 ;PRG bank #0 at $8000, back to basic
	jsr _set_prg_8000
	jsr _disable_irq ;disable mmc3 IRQ
	lda #4
	jsr _pal_bright
	jsr _pal_clear
	jsr _oam_clear
    ; oam_size(1); 
    lda #1
    jsr _oam_size
	jmp _main			;no parameters
	
	

	.include "MMC3/mmc3_code.asm"
	.include "LIB/neslib.s"
	.include "LIB/nesdoug.s"

;NMI handler

nmi:
    pha
    txa
    pha
    tya
    pha
    
    lda #0
    sta mmc3_index
    sta irq_done


    lda <PPU_MASK_VAR    ;if rendering is disabled, do not access the VRAM at all
    and #%00011000
    bne @renderingOn
    jmp @skipAll

@renderingOn:
    lda <VRAM_UPDATE ;is the frame complete?
    bne @doUpdate
    jmp @skipAll ;skipUpd ***

@doUpdate:
    lda #0
    sta <VRAM_UPDATE

    lda #>OAM_BUF        ;update OAM
    sta PPU_OAM_DMA

    lda <PAL_UPDATE        ;update palette if needed
    bne @updPal
    jmp @updVRAM

@updPal:

    ldx #0
    stx <PAL_UPDATE

    lda #$3f
    sta PPU_ADDR
    stx PPU_ADDR

    ldy PAL_BUF                ;background color, remember it in X
    lda (PAL_BG_PTR),y
    sta PPU_DATA
    tax
    
    .repeat 3,I
    ldy PAL_BUF+1+I
    lda (PAL_BG_PTR),y
    sta PPU_DATA
    .endrepeat

    .repeat 3,J        
    stx PPU_DATA            ;background color
    .repeat 3,I
    ldy PAL_BUF+5+(J*4)+I
    lda (PAL_BG_PTR),y
    sta PPU_DATA
    .endrepeat
    .endrepeat

    .repeat 4,J        
    stx PPU_DATA            ;background color
    .repeat 3,I
    ldy PAL_BUF+17+(J*4)+I
    lda (PAL_SPR_PTR),y
    sta PPU_DATA
    .endrepeat
    .endrepeat

@updVRAM:
    
    lda <NAME_UPD_ENABLE
    beq @skipUpd

    jsr _flush_vram_update2

@skipUpd:

    lda #0
    sta PPU_ADDR
    sta PPU_ADDR

    lda <SCROLL_X
    sta PPU_SCROLL
    lda <SCROLL_Y
    sta PPU_SCROLL

    lda <PPU_CTRL_VAR
    sta PPU_CTRL
        
    jsr irq_parser ; needs to happen inside v-blank... 
                   ; so goes before the music
            ; but, if screen is off this should be skipped

@skipAll:

    lda <PPU_MASK_VAR
    sta PPU_MASK

    inc <FRAME_CNT1
    inc <FRAME_CNT2
    lda <FRAME_CNT2
    cmp #6
    bne @skipNtsc
    lda #0
    sta <FRAME_CNT2

@skipNtsc:

;switch the music into the prg bank first
    lda #(6 | A12_INVERT)
    sta $8000
    lda #SOUND_BANK
    sta $8001 ;change bank at $8000-9fff
    jsr famistudio_update
;if famitone update went long, we could be interrupted
;by an IRQ below here...
    
;push to stack 
    lda mmc3_8000
    pha
;restore prg bank    
    lda #(6 | A12_INVERT)
    sta mmc3_8000 ; just in case IRQ interrupts this
    sta $8000
    lda BP_BANK_8000
    sta $8001 
;pull from stack  
    pla
    sta mmc3_8000 ;restore this mmc3 register
    sta $8000 ;in case we interrupted the main code

    pla
    tay
    pla
    tax
    pla
    rti
	

	
.segment "CODE"	
; When music files get very big, it's probably best to
; split the songs into multiple swapped banks
; the music code itself is in the regular CODE banks.
; It could be moved into BANK12 if music data is small.
	.include "MUSIC/famistudio_ca65.s"
.segment "BANK12"	
	.include "MUSIC/music.s"
	.include "MUSIC/sounds.s"
	
	
;.segment "SAMPLES"
;	.incbin "MUSIC/BassDrum.dmc"



.segment "VECTORS"

    .word nmi	;$fffa vblank nmi
    .word start	;$fffc reset
   	.word irq	;$fffe irq / brk


.segment "CHARS"
	.incbin "CHR/intro.chr"
	.res 48
	.res 256
	.incbin "CHR/title.chr"
	.res 720
	.incbin "CHR/spr.chr"
; the CHARS segment is much bigger, and I could have 
; incbin-ed many more chr files
	
