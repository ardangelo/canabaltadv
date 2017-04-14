PATH := $(DEVKITARM)/bin:$(PATH)
include $(DEVKITARM)/gba_rules

INCLUDE	:= -Iinclude
LIBS		:= -ltonc
LIBPATHS	:= -Llib

SPECS	:= -specs=gba_mb.specs
ARCH	:= -mthumb-interwork -mthumb

ASFLAGS		:= -mthumb-interwork
CFLAGS	:= $(ARCH) $(INCLUDE) -O2 -Wall -fno-strict-aliasing
LDFLAGS		:= $(ARCH) $(SPECS) $(LIBPATHS) $(LIBS) -Wl,-Map,$(PROJ).map

ROMNAME := canabalt

all: $(ROMNAME).gba

# compile the gfx resources
bg.o : tiles/bg.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/bg.c -o bg.o
sprites.o : tiles/sprites.c
	arm-none-eabi-gcc $(CFLAGS) -c tiles/sprites.c -o sprites.o

# compile the object files
main.o : main.c
	arm-none-eabi-gcc $(CFLAGS) -c main.c -o main.o

# link objects into an elf
$(ROMNAME).elf : main.o bg.o sprites.o
	arm-none-eabi-gcc main.o bg.o sprites.o $(LDFLAGS) -o $(ROMNAME).elf

# objcopy and fix the rom
$(ROMNAME).gba : $(ROMNAME).elf
	arm-none-eabi-objcopy -v -O binary $(ROMNAME).elf $(ROMNAME).gba
	gbafix $(ROMNAME).gba -t$(ROMNAME)

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.o
	@rm -fv main.s .map
