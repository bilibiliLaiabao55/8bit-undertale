#pragma rodata-name ("BANK0")
#pragma code-name ("BANK0")
#include "nametables/intro1.h"
#include "nametables/intro2.h"
#include "nametables/intro3.h"
#include "nametables/intro4.h"
#include "nametables/intro5.h"
#include "nametables/intro6.h"
#include "nametables/intro7.h"
#include "nametables/intro8.h"
#include "nametables/intro9.h"
#include "nametables/title.h"

const char story_pal[32] = {
    0x0F, 0x06, 0x17, 0x27, 
    0x0F, 0x30, 0x30, 0x30, 
    0x0F, 0x16, 0x00, 0x30, 
    0x0F, 0x30, 0x30, 0x30, 
    
    0x0F, 0x06, 0x17, 0x27, 
    0x0F, 0x30, 0x30, 0x30, 
    0x0F, 0x16, 0x00, 0x30, 
    0x0F, 0x30, 0x30, 0x30
};
#pragma rodata-name ("BANK1")
#pragma code-name ("BANK1")
#include "spr/frisk.h"
const unsigned char frisk_pal[]={
    0x0F, 0x06, 0x27, 0x2C
};
#pragma rodata-name ("CODE")
#pragma code-name ("CODE")