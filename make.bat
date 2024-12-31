@echo off

set name="UNDERTALE"

cc65 -Oirs main.c --add-source
ca65 crt0.s
ca65 main.s

ld65 -C MMC3_128_128.cfg -o %name%.nes crt0.o main.o nes.lib -Ln labels.txt

del *.o

move /Y labels.txt BUILD\ 
move /Y main.s BUILD\ 
move /Y %name%.nes BUILD\ 

BUILD\%name%.nes
