# MPLAB IDE generated this makefile for use with GNU make.
# Project: Labirynth -  C18 - PIC18F Starter Kit.mcp
# Date: Wed Feb 22 16:58:58 2023

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

Labirynth\ -\ \ C18\ -\ PIC18F\ Starter\ Kit.cof : main.o graph.o physics.o levels.o soft_start.o BMA150.o mtouch.o oled.o
	$(LD) /l"c:\mcc18\lib" "rm18f46j50_g.lkr" "main.o" "graph.o" "physics.o" "levels.o" "soft_start.o" "BMA150.o" "mtouch.o" "oled.o" /u_CRUNTIME /m"Labirynth -  C18 - PIC18F Starter Kit.map" /w /o"Labirynth -  C18 - PIC18F Starter Kit.cof"

main.o : main.c stdio.h stdlib.h string.h oled.h mtouch.h BMA150.h physics.h graph.h main.c GenericTypeDefs.h Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h HardwareProfile.h HardwareProfile\ -\ PIC18F\ Starter\ Kit.h soft_start.h levels.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "main.c" -fo="main.o"

graph.o : graph.c physics.h graph.h stdio.h stdlib.h string.h oled.h graph.c Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h GenericTypeDefs.h levels.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "graph.c" -fo="graph.o"

physics.o : physics.c physics.h graph.h BMA150.h math.h stdio.h stdlib.h string.h oled.h physics.c GenericTypeDefs.h levels.h Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "physics.c" -fo="physics.o"

levels.o : levels.c physics.h graph.h levels.c levels.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "levels.c" -fo="levels.o"

soft_start.o : soft_start.c stdio.h stdlib.h string.h soft_start.c GenericTypeDefs.h Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "soft_start.c" -fo="soft_start.o"

BMA150.o : BMA150.c stdio.h stdlib.h string.h BMA150.h BMA150.c Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h GenericTypeDefs.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "BMA150.c" -fo="BMA150.o"

mtouch.o : mtouch.c stdio.h stdlib.h string.h mtouch.h mtouch.c Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "mtouch.c" -fo="mtouch.o"

oled.o : oled.c stdio.h stdlib.h string.h oled.h oled.c GenericTypeDefs.h Compiler.h p18cxxx.h p18f46j50.h stdarg.h stddef.h
	$(CC) -p=18F46J50 /i"." -I"..\..\..\..\..\Microchip\Include" "oled.c" -fo="oled.o"

clean : 
	$(RM) "main.o" "graph.o" "physics.o" "levels.o" "soft_start.o" "BMA150.o" "mtouch.o" "oled.o" "Labirynth -  C18 - PIC18F Starter Kit.cof" "Labirynth -  C18 - PIC18F Starter Kit.hex" "Labirynth -  C18 - PIC18F Starter Kit.map"

