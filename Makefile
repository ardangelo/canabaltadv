MUSIC := no

PATH := $(DEVKITARM)/bin:$(PATH)
include $(DEVKITARM)/gba_rules

INCLUDE	:= -Iinclude
LIBS		:= -ltonc -lkrawall
LIBPATHS	:= -Llib

SPECS	:= -specs=gba_mb.specs
ARCH	:= -mthumb-interwork -mthumb

ASFLAGS		:= -mthumb-interwork
CFLAGS	:= $(ARCH) $(INCLUDE) -O2 -Wall -fno-strict-aliasing
LDFLAGS		:= $(ARCH) $(SPECS) $(LIBPATHS) $(LIBS) -Wl,-Map,$(PROJ).map

ROMNAME := canabalt

all: $(ROMNAME).gba

# compile the gfx resources
buildings.o : tiles/buildings.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/buildings.c -o buildings.o
midground.o : tiles/midground.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/midground.c -o midground.o
background.o : tiles/background.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/background.c -o background.o
sprites.o : tiles/sprites.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/sprites.c -o sprites.o

# assemble the sound resources
ifeq ($(MUSIC),yes)
instruments.o: modules/instruments.s
	arm-none-eabi-as -o $@ $<
samples.o: modules/samples.s
	arm-none-eabi-as -o $@ $<
sanic.o: modules/sanic.s
	arm-none-eabi-as -o $@ $<
endif

# compile the object files
main.o : main.c main.h
	arm-none-eabi-gcc $(CFLAGS) -c main.c -o main.o

# link objects into an elf
ifeq ($(MUSIC),yes)
$(ROMNAME).elf : main.o buildings.o midground.o background.o sprites.o instruments.o samples.o sanic.o
	arm-none-eabi-gcc main.o buildings.o midground.o background.o sprites.o instruments.o samples.o sanic.o $(LDFLAGS) -o $(ROMNAME).elf
else
$(ROMNAME).elf : main.o buildings.o midground.o background.o sprites.o
	arm-none-eabi-gcc main.o buildings.o midground.o background.o sprites.o $(LDFLAGS) -o $(ROMNAME).elf
endif

# objcopy and fix the rom
$(ROMNAME).gba : $(ROMNAME).elf
	arm-none-eabi-objcopy -v -O binary $(ROMNAME).elf $(ROMNAME).gba
	gbafix $(ROMNAME).gba -t$(ROMNAME)

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o
	@rm -fv main.s .map
