#include "../main.h"
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